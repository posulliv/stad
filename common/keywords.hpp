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
#include <boost/unordered_map.hpp>

class keywords
{

public:

  static keywords& singleton()
  {
    static keywords keyword_holder;
    return keyword_holder;
  }

  /** return true iff the given string is a keyword */
  bool is_keyword(const std::string& word);

private:

  keywords();

  boost::unordered_map<std::string, std::string> _keywords;

};
