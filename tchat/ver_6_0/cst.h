/*++

    Copyright (c) S-Patriarch, 2023

    Определение констант и глобальных переменных.

--*/

#ifndef __CHAT_CST_H__
#define __CHAT_CST_H__

#include <cstdint>
#include <string>

//////////////////////////////////////////////////////////////////////
namespace chat
{

const std::int32_t MAXPACKETSIZE {4096};
char               msg_[MAXPACKETSIZE];

const std::string  GIVE_ME_MESSAGES_FROM_THE_DATABASE {"1"};

} // namespace chat

#endif // __CHAT_CST_H__
