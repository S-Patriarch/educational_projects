// -*- C++ -*-
//
// Copyright (c) S-Patriarch, 2023
// Работа с исключениями - exception.
//
// (PTL) Patriarch library : pexcept.h

#pragma once
#if !defined( __PTL_PEXCEPT_H__ )
#define __PTL_PEXCEPT_H__

#include <exception>

// Пример использования данного класса исключений.
// В коде программы бросается исключение следующим образом.
// @code
//   throw ptl::pException( "E: Message to exception." );
// @endcode
// 
// Ловится данное исключение следующим образом.
// @code
//   try
//     {
//     throw ...
//     }
//   catch( std::exception& ex )
//     {
//     std::cout 
//       << "Поймано исключение: " 
//       << ex.what() 
//       << std::endl;
//     }
// @endcode

namespace ptl
  {
//////////////////////////////////////////////////////////////////////
  class pException final 
    : public std::exception
    {
    public:
      pException( const char* __message )
        : std::exception(), 
          _M_message( __message ) 
        { }

      ~pException() noexcept
        { }
//--------------------------------------------------------------------
// Перегрузка метода what() стандартного класса exception.
//
      virtual const char*
      what() const noexcept override
        { return _M_message; }

    private:
      const char*  _M_message{ }; // Сообщение для исключения
    };

  } // namespace ptl

#endif // __PTL_PEXCEPT_H__