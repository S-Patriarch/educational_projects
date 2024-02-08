/*++

    Copyright (c) S-Patriarch, 2023

    Определение структор данных.

--*/

#ifndef __CHAT_STRUCT_H__
#define __CHAT_STRUCT_H__

#ifdef _WIN32
#pragma once
#endif

#ifdef __linux__
#include "ptl/ptype.h"
#elif _WIN32
#include "ptl\ptype.h"
#endif

//////////////////////////////////////////////////////////////////////
namespace chat
{
    struct User 
    {
        std::string _M_userLogin;        // логин пользователя
        ptl::__u32  _M_userId;           // uid пользователя
        std::string _M_userHashPassword; // хэш пароля пользователя
        std::string _M_userName;         // имя пользователя

        User() { _M_userId = 0; }
    };

    struct Message
    {
        std::string _M_msgToWhom;   // кому сообщение
        std::string _M_msgFromWhom; // от кого сообщение
        std::string _M_msgText;     // текст сообщения
    };

} // namespace chat

#endif // __CHAT_STRUCT_H__