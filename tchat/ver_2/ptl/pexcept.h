/*++

    Copyright (c) S-Patriarch, 2023
    (PTL) Patriarch library : pexcept.h

    Работа с исключениями.
    Класс наследуется от библиотечного класса - exception.

Использование:

    Пример использования данного класса исключений.
    В коде программы бросается исключение следующим образом.

    throw ptl::pException("E: Message to exception.");
 
    Ловится данное исключение следующим образом.

    try {
        throw ...
    }
    catch (std::exception& ex) {
        std::cout << "Поймано исключение: " 
                  << ex.what() 
                  << std::endl;
    }

--*/

#ifndef __PTL_PEXCEPT_H__
#define __PTL_PEXCEPT_H__

#ifdef _WIN32
#pragma once
#endif

#include <exception>

namespace ptl
{
    class pException final 
    : public std::exception
    {
    public:
        pException(
            const char*  __message
            )
        : std::exception()
        , _M_message(__message) 
        { }

        ~pException() noexcept 
        { }

//--------------------------------------------------------------------
// Перегрузка метода what() стандартного класса exception.
//
        virtual 
        const char* 
        what() const noexcept override 
        { return _M_message; }

    private:
        const char*  _M_message{ }; // сообщение для исключения
    };
}

#endif