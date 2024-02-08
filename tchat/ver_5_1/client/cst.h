/*++

    Copyright (c) S-Patriarch, 2023

    Определение констант и глобальных переменных.

--*/

#ifndef __CHAT_CST_H__
#define __CHAT_CST_H__

#ifdef _WIN32
#pragma once
#endif

#ifdef __linux__
#include "../ptl/ptype.h"
#elif _WIN32
#include "..\ptl\ptype.h"
#endif

//////////////////////////////////////////////////////////////////////
namespace chat
{
    const ptl::__s32 MAXPACKETSIZE { 4096 }; 
    char             _msg[MAXPACKETSIZE];

} // namespace chat

#endif // __CHAT_CST_H__