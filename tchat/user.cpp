// user.cpp -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 */

#include "user.h"

#ifdef _WIN32
#include "ptl\ptype.h"
#include "ptl\pcolor.h"
#else
#include "ptl/ptype.h"
#include "ptl/pcolor.h"
#endif

#include <iostream>
#include <string>

namespace chat
{
  auto
  User::set_user(
    const std::string& __name, 
    const std::string& __login, 
    const std::string& __password, 
    ptl::__u32         __id) -> void
  {
    _M_name     = __name;
    _M_login    = __login;
    _M_password = __password;
    _M_id       = __id;
  }

  auto
  User::out_user_name() -> void
  {
    ptl::pcolor __c;
    std::cout
      << __c.esc_tb( ptl::WHITE )
      << _M_name
      << __c.esc_c();
  }

  auto
  User::record_message(
    const std::string& __whom, 
    const std::string& __what) -> void
  {
    __msg[_M_msg_quantity]._S_name = __whom;
    __msg[_M_msg_quantity]._S_msg  = __what;

    ++_M_msg_quantity;
  }

  auto
  User::out_message() -> void
{
    ptl::pcolor __c;

    for (ptl::__u16 __index{0}; __index < _M_msg_quantity; ++__index)
      {
        std::cout
          << __c.esc_tb( ptl::CYAN )
          << __msg[__index]._S_name
          << __c.esc_c()
          << ": "
          << __msg[__index]._S_msg
          << std::endl;
      }
  }

} // namespace chat