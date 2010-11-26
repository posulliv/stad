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

#include <string>
#include <iostream>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <boost/unordered_map.hpp>

#include "sql_tokenizer.hpp"
#include "keywords.hpp"
#include "injection_exception.hpp"

using namespace std;
using namespace boost;


sql_tokenizer::sql_tokenizer()
  :
    _separator1(""),
    _separator2(" "),
    _separator3(""),
    _randomization_key("")
{
}


sql_tokenizer::sql_tokenizer(const string& in_key)
  :
    _separator1(""),
    _separator2(" "),
    _separator3(""),
    _randomization_key(in_key)
{
}


void sql_tokenizer::derandomize_query(string& output_query)
{
  escaped_list_separator<char> els(_separator1, _separator2, _separator3);
  tokenizer<escaped_list_separator<char> > tok(output_query, els);
  string new_query;
  for (tokenizer<escaped_list_separator<char> >::iterator iter = tok.begin();
       iter != tok.end();
       ++iter)
  {
    string token(*iter);
    size_t pos = token.rfind(_randomization_key);
    if (pos != string::npos)
    {
      if (starts_with_keyword(token))
      {
        token.erase(pos);
      }
    }
    else
    {
      if (starts_with_keyword(token))
      {
        /* if its a keyword, throw an exception */
        throw injection_exception("SQL INJECTION!!!");
      }
    }
    new_query.append(token);
    new_query.append(" ");
  }
  output_query.assign(new_query);
}


void sql_tokenizer::randomize_query(string& output_query)
{
  escaped_list_separator<char> els(_separator1, _separator2, _separator3);
  tokenizer<escaped_list_separator<char> > tok(output_query, els);
  string new_query;
  for (tokenizer<escaped_list_separator<char> >::iterator iter = tok.begin();
       iter != tok.end();
       ++iter)
  {
    string token(*iter);
    if (starts_with_keyword(token))
    {
      token.append(_randomization_key);
    }
    new_query.append(token);
    new_query.append(" ");
  }
  output_query.assign(new_query);
}


const std::string& sql_tokenizer::get_randomization_key() const
{
  return _randomization_key;
}


void sql_tokenizer::set_randomization_key(const string& new_key)
{
  _randomization_key.assign(new_key);
}


bool sql_tokenizer::starts_with_keyword(string& token)
{
  /* convert token to lower case */
  std::transform(token.begin(),
                token.end(),
                token.begin(),
                ::tolower);

  /* lets be optimistic :) */
  keywords& keyword_holder = keywords::singleton();
  if (keyword_holder.is_keyword(token))
  {
    return true;
  }

  string token_parts;
  string latest_match;
  bool detected_keyword = false;
  for (string::iterator it = token.begin(); it != token.end(); ++it)
  {
    token_parts.push_back(*it);
    if (keyword_holder.is_keyword(token_parts))
    {
      detected_keyword = true;
      latest_match.assign(token_parts);
    }
  }
  
  return (detected_keyword ? true : false);
}
