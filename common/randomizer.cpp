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

#include <boost/program_options.hpp>

#include "sql_tokenizer.hpp"


using namespace std;
namespace po=boost::program_options;

int main(int argc, char* argv[])
{
  string randomization_key;
  string query;
  po::variables_map vm;
  po::options_description my_options("Options specific to the drizzle client");
  my_options.add_options()
  ("key,k", po::value<string>(&randomization_key)->default_value(""),
  "Randomization key.")
  ("query,q", po::value<string>(&query)->default_value(""),
  "Input query.")
  ;
  po::store(po::parse_command_line(argc, argv, my_options), vm);
  po::notify(vm);
  sql_tokenizer tokenizer(randomization_key);
  tokenizer.randomize_query(query);
  cout << "randomized query is: " << endl << query << endl;
  return 0;
}
