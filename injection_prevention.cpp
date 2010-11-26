/*
 *  Copyright (C) 2010 Padraig O'Sullivan
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include "config.h"
#include <drizzled/gettext.h>
#include <drizzled/plugin/query_rewrite.h>
#include <drizzled/message/transaction.pb.h>
#include <drizzled/plugin.h>

#include <boost/program_options.hpp>
#include <drizzled/module/option_map.h>
#include <vector>
#include <string>

#include "injection_prevention.hpp"
#include "common/sql_tokenizer.hpp"
#include "common/injection_exception.hpp"

namespace po= boost::program_options;
using namespace std;
using namespace drizzled;

static char *sysvar_injection_prevention_key = NULL;


InjectionPreventor::InjectionPreventor(string name_arg,
                                       const char* in_key)
  :
    plugin::QueryRewriter(name_arg),
    _randomization_key(in_key)
{
  pthread_mutex_init(&sysvar_key_lock, NULL);
}


InjectionPreventor::~InjectionPreventor()
{
  pthread_mutex_destroy(&sysvar_key_lock);

}


void InjectionPreventor::rewrite(const string& schema, string& to_rewrite)
{
  (void) schema;
  sql_tokenizer tokenizer(_randomization_key);
  try
  {
    tokenizer.derandomize_query(to_rewrite);
  }
  catch (injection_exception&)
  {
    to_rewrite.clear();
    to_rewrite.assign("select 1");
  }
}


void InjectionPreventor::randomize_query(char* query)
{
  sql_tokenizer tokenizer(_randomization_key);
  string output_query(query);
  tokenizer.randomize_query(output_query);
  free(query);
  query = (char*) malloc(output_query.length());
  memcpy(query, output_query.c_str(), output_query.length());
}


void InjectionPreventor::set_randomization_key(const string& new_key)
{
  pthread_mutex_lock(&sysvar_key_lock);
  _randomization_key.assign(new_key);
}


void InjectionPreventor::update_randomization_key_sysvar(const char** var_ptr)
{
  *var_ptr = _randomization_key.c_str();
  pthread_mutex_unlock(&sysvar_key_lock);
}


inline const string& InjectionPreventor::get_randomization_key() const
{
  return _randomization_key;
}


InjectionPreventor *injection_preventor = NULL; 

static int init(module::Context& context)
{
  const module::option_map& vm = context.getOptions();
  
  if (vm.count("key"))
  {
    sysvar_injection_prevention_key = const_cast<char *>(vm["key"].as<string>().c_str());
  }

  else
  {
    sysvar_injection_prevention_key = const_cast<char *>("");
  }

  injection_preventor = new InjectionPreventor("injection_preventor", sysvar_injection_prevention_key);
  if (injection_preventor == NULL)
  {
    return 1;
  }
  context.add(injection_preventor);
  return 0;
}


static int check_randomization_key(Session*, 
                                   drizzle_sys_var*,
                                   void* save,
                                   drizzle_value* value)
{
  char buff[STRING_BUFFER_USUAL_SIZE];
  int len = sizeof(buff);
  const char *input = value->val_str(value, buff, &len);

  if (input && injection_preventor)
  {
    injection_preventor->set_randomization_key(input);
    *(bool *) save = (bool) true;
    return 0;
  }
  *(bool *) save = (bool) false;
  return 1;
}


static void set_randomization_key(Session*,
                                  drizzle_sys_var*,
                                  void* var_ptr,
                                  const void* save)
{
  if (injection_preventor)
  {
    if (*(bool *)save != false)
    {
      /* update the value of the system variable */
      injection_preventor->update_randomization_key_sysvar((const char **) var_ptr);
    }
  }
}

static void init_options(drizzled::module::option_context& context)
{
  context("key",
          po::value<string>(),
          N_("Randomization key to use"));
}

static DRIZZLE_SYSVAR_STR(key,
                          sysvar_injection_prevention_key,
                          PLUGIN_VAR_OPCMDARG,
                          N_("Randomization key to use"),
                          check_randomization_key,
                          set_randomization_key,
                          "");

static drizzle_sys_var* injection_prevention_system_variables[]= {
  DRIZZLE_SYSVAR(key),
  NULL
};

DRIZZLE_PLUGIN(init, injection_prevention_system_variables, init_options);
