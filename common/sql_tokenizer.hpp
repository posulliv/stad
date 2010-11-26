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

class sql_tokenizer
{

public:

  sql_tokenizer();
  sql_tokenizer(const std::string& in_key);

  /**
   * Tokenize the query and look for the randomization key.
   * If the query is not valid i.e. we find a keyword which
   * does not contain the correct randomization key, then we
   * throw an exception.
   * If all is ok, the query to be parsed without the randomization
   * key is placed in the output_query parameter.
   */
  void derandomize_query(std::string& output_query);

  /**
   * Tokenize the query and for any keyword we find append
   * the randomization key to that keyword.
   */
  void randomize_query(std::string& output_query);

  /** @return the current randomization key */
  const std::string& get_randomization_key() const;

  /** set the randomization key to use */
  void set_randomization_key(const std::string& new_key);

private:

  /** return true if the given token starts with a keyword */
  bool starts_with_keyword(std::string& token);

  std::string _separator1;
  std::string _separator2;
  std::string _separator3;
  std::string _randomization_key;
  boost::unordered_map<std::string, std::string> _keywords;

};
