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
    const ptl::__s32 PORT { 53333 }; 
    const ptl::__s32 MAXPACKETSIZE { 4096 }; 

    ptl::__s32 _socketFileDescriptor;
    ptl::__s32 _connection;
    ptl::__s32 _connectionStatus;
    ptl::__s32 _bindStatus;

    socklen_t _length;

    char _msg[MAXPACKETSIZE];

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

} // namespace chat

#endif // __CHAT_CST_H__