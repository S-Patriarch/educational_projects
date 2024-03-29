/*++

    Copyright (c) S-Patriarch, 2023

    Определение структор данных.

--*/

#ifndef __CHAT_SCT_H__
#define __CHAT_SCT_H__

#include <string>

//////////////////////////////////////////////////////////////////////
namespace chat
{
struct User {
    std::string s_userID {};     // id пользователя
    std::string s_userName {};   // имя пользователя
    std::string s_userFamaly {}; // фамилия пользователя
};

} // namespace chat

#endif // __CHAT_SCT_H__
