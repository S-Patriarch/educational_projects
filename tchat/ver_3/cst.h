/*++

    Copyright (c) S-Patriarch, 2023

    Определение констант и глобальных переменных.

--*/

#ifndef __CHAT_CST_H__
#define __CHAT_CST_H__

#ifdef _WIN32
#pragma once
#endif

//////////////////////////////////////////////////////////////////////
namespace chat
{
    enum Parametr
    {
        HELP = 1,   // вывод информации об управляющих параметрах
        EDIT = 2,   // редактирование данных пользователя чата
        QUIT = 3,   // завершение работы чата
        OK   = 1000 // нормальный обмен сообщениями
    };

} // namespace chat

#endif // __CHAT_CST_H__