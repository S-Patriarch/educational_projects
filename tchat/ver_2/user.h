/*++

    Copyright (c) S-Patriarch, 2023

    Заголовочный файл с описанием класса реализующего 
    работу с пользователем чата.

--*/

#ifndef __CHAT_USER_H__
#define __CHAT_USER_H__

#ifdef _WIN32
#pragma once
#endif

#include "cst.h"
#include <string>

namespace chat
{
    class User {
    public:
        User() = default;
        ~User() = default;

        void 
        set_user(
            const std::string&, 
            const std::string&, 
            const std::string&, 
            ptl::__u32
            );

        void 
        set_user_password(
            const std::string& _password_new
            )
        { 
            _M_password = _password_new; 
        }

        std::string 
        get_user_name() { return _M_name; }
        
        std::string 
        get_user_login() { return _M_login; }
        
        std::string 
        get_user_password() { return _M_password; }
        
        ptl::__u32 
        get_user_id() { return _M_id; }

        void 
        set_msg_quantity(
            ptl::__u16 _quantity
            ) 
        { 
            _M_msg_quantity = _quantity; 
        }

        ptl::__u16 
        get_msg_quantity() { return _M_msg_quantity; }
        
        void 
        clear_msg_quantity() { _M_msg_quantity = 0; }

        void 
        out_user_name();

        void 
        record_message(
            const std::string&, 
            const std::string&
            );
        
        void 
        out_message();

    private:
        std::string  _M_name{};     // Имя пользователя
        std::string  _M_login{};    // Логин пользователяo
        std::string  _M_password{}; // Пароль пользователя
        ptl::__u32   _M_id{};       // ID пользователя

        // Количество сообщений для пользователя
        ptl::__u16   _M_msg_quantity{}; 

        struct Messages {
            std::string  _S_name{}; // Имя отправителя сообщения
            std::string  _S_msg{};  // Текст сообщения
        };

        Messages     _msg[_Quantity_Messages];
    };

} 

#endif
