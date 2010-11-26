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

#include <exception>
#include <string>

class injection_exception : public std::exception
{
public:

  injection_exception()
    :
      _error_code(0),
      _message()
  {}

  injection_exception(const std::string& msg, int in_error = 0)
    :
      _error_code(in_error),
      _message(msg)
  {}

  virtual ~injection_exception() throw() {}

  virtual const char* what() const throw()
  {
    return _message.c_str();
  }

  int error_code() const
  {
    return _error_code;
  }

  const std::string& message() const
  {
    return _message;
  }

private:

  const int _error_code;
  const std::string _message;

};
