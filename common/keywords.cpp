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

#include "keywords.hpp"

using namespace std;
using namespace boost;


keywords::keywords()
  :
    _keywords()
{
  _keywords.insert(make_pair("add", "add"));
  _keywords.insert(make_pair("all", "all"));
  _keywords.insert(make_pair("alter", "alter"));
  _keywords.insert(make_pair("analyze", "analyze"));
  _keywords.insert(make_pair("and", "and"));
  _keywords.insert(make_pair("any", "any"));
  _keywords.insert(make_pair("as", "as"));
  _keywords.insert(make_pair("asc", "asc"));
  _keywords.insert(make_pair("before", "before"));
  _keywords.insert(make_pair("between", "between"));
  _keywords.insert(make_pair("by", "by"));
  _keywords.insert(make_pair("count", "count"));
  _keywords.insert(make_pair("distinct", "distinct"));
  _keywords.insert(make_pair("drop", "drop"));
  _keywords.insert(make_pair("from", "from"));
  _keywords.insert(make_pair("having", "having"));
  _keywords.insert(make_pair("or", "or"));
  _keywords.insert(make_pair("select", "select"));
  _keywords.insert(make_pair("union", "union"));
  _keywords.insert(make_pair("where", "where"));
}


bool keywords::is_keyword(const string& word)
{
  boost::unordered_map<string, string>::iterator iter = _keywords.find(word);
  if (iter != _keywords.end())
  {
    return true;
  }
  return false;
}

