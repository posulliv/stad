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

#ifndef PLUGIN_STAD_INJECTION_PREVENTION_HPP
#define PLUGIN_STAD_INJECTION_PREVENTION_HPP

#include <string>

#include <drizzled/plugin/query_rewrite.h>


class InjectionPreventor : public drizzled::plugin::QueryRewriter
{

public:

  InjectionPreventor(std::string name_arg, const char* in_key);
  ~InjectionPreventor();

  virtual void rewrite(const std::string& schema, std::string& to_rewrite);

  void randomize_query(char* query);

  void set_randomization_key(const std::string& new_key);

  const std::string& get_randomization_key() const;

  void update_randomization_key_sysvar(const char** var_ptr);

private:

  std::string _randomization_key;
  pthread_mutex_t sysvar_key_lock;

};

#endif /* PLUGIN_STAD_INJECTION_PREVENTION_HPP */
