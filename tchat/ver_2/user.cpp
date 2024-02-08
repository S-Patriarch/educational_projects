/*++

    Copyright (c) S-Patriarch, 2023

--*/

#include "user.h"

#ifdef __linux__
#include "ptl/ptype.h"
#include "ptl/pcolor.h"
#elif _WIN32
#include "ptl\ptype.h"
#include "ptl\pcolor.h"
#endif

#include <iostream>
#include <string>

namespace chat
{
//--------------------------------------------------------------------
// Устанавливает параметры пользователя.
//
    void 
    User::set_user(
        const std::string& _name, 
        const std::string& _login, 
        const std::string& _password, 
        ptl::__u32         _id
        )
    {
        _M_name     = _name;
        _M_login    = _login;
        _M_password = _password;
        _M_id       = _id;
    }

//--------------------------------------------------------------------
// Выводит в терминал (консоль) имя пользователя.
//
    void 
    User::out_user_name()
    {
        ptl::pColor  c;

        std::cout << c.esc_tb(ptl::WHITE)
                  << _M_name
                  << c.esc_c();
    }

//--------------------------------------------------------------------
// Записывает посланное __whom сообщение __what.
//
    void 
    User::record_message(
        const std::string& _whom, 
        const std::string& _what
        )
    {
        _msg[_M_msg_quantity]._S_name = _whom;
        _msg[_M_msg_quantity]._S_msg  = _what;

        ++_M_msg_quantity;
    }

//--------------------------------------------------------------------
// Вывод входящих сообщений.
//
    void 
    User::out_message()
    {
        ptl::pColor  c;

        for (ptl::__u16 i{ 0 }; i < _M_msg_quantity; ++i) {
            std::cout << c.esc_tb(ptl::CYAN)
                      << _msg[i]._S_name
                      << c.esc_c()
                      << ": "
                      << _msg[i]._S_msg
                      << std::endl;
        }
    }
}
