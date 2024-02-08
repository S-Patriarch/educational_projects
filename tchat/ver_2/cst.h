/*++

    Copyright (c) S-Patriarch, 2023

--*/

#ifndef __CHAT_CST_H__
#define __CHAT_CST_H__

#ifdef _WIN32
#pragma once
#endif

#ifdef __linux__
#include "ptl/ptype.h"
#elif _WIN32
#include "ptl\ptype.h"
#endif

namespace chat
{
    constexpr ptl::__u16
    _Quantity_Messages{ 1000 }; // Количество сообщений для каждого пользователя

    constexpr ptl::__u16
    _Help{ 10 };                // Вывод информации об управляющих параметрах

    constexpr ptl::__u16
    _Change{ 20 };              // Смена пользователя чата

    constexpr ptl::__u16
    _Quit{ 30 };                // Завершение работы чата

    constexpr ptl::__u16
    _Edit{ 40 };                // Редактирование данных пользователя чата

    constexpr ptl::__u16
    _Ok{ 1000 };                // Нормальный обмен сообщениями
} 

#endif
