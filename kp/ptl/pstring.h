// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы со строками 
 */

/**
 *  (PTL) Patriarch library : pstring.h
 */

#pragma once
#if !defined(_PTL_PSTRING_H)
#define _PTL_PSTRING_H

#if !defined(_PTL_PTYPE_H)
#include "ptype.h"
#endif

#include <iostream>
#include <utility>

/*
 * Класс строка.
 *
 * Конструкторы:
 *   - конструктор создания
 *   - конструктор создания пустой строки
 *   - конструктор копирования
 *   - конструктор присваения копирования
 *   - конструктор перемещения
 *   - конструктор присвоения перемещения
 * Методы:
 *   - at() - возвращает указатель на строку
 *   - size() - возвращает размер строки без учета '\0'
 *   - s_len() - возвращает размер строки без учета '\0'
 *   - s_cpy() - копирует строку
 *   - s_cat() - объединяет две строки
 *   - swap() - обмен значениями двух объектов
 *   - del_all_char() - удаление всех символов в строке, кроме цифровых
 *   - is_kperiodic() - проверяет, является ли строка кратной числу
 */

namespace ptl
{
//////////////////////////////////////////////////////////////////////
  class pstring 
  {
  private:
    __u16  _M_size;   // Размер строки с учетом '\0'
    char*  _M_string; // Указатель на строку

  public:
    pstring(char const* __s)
    {
      _M_size   = s_len(__s) + 1;
      _M_string = new char[_M_size];

      s_cpy(_M_string, __s);
    }

    pstring()
    {
      _M_size = 1;
      _M_string = new char[_M_size];
      _M_string[0] = '\0';
    }

    pstring(const pstring& __other)
    {
      _M_string = new char[__other._M_size];
      _M_size   = __other._M_size;

      s_cpy(_M_string, __other._M_string);
    }

    pstring& 
    operator=(const pstring& __other)
    {
      _M_string = new char[__other._M_size];
      _M_size   = __other._M_size;

      s_cpy(_M_string, __other._M_string);
    }

    /** Конструктор копирования перемещения.
     */
    pstring(pstring&& __other) noexcept
    {
      _M_string = __other._M_string;
      _M_size   = __other._M_size;

      __other._M_string = nullptr;
      __other._M_size   = 0;
    }

    /** Конструктор присваивания перемещения.
     */
    pstring& 
    operator=(pstring&& __other) noexcept
    {
      _M_string = __other._M_string;
      _M_size   = __other._M_size;

      __other._M_string = nullptr;
      __other._M_size   = 0;

      return *this;
    }

    ~pstring() noexcept
    { delete[] _M_string; }
//--------------------------------------------------------------------
    /*
     * Метод, возвращает указатель на строку.
     */
    auto
    at() -> char*
    { return _M_string; }
//--------------------------------------------------------------------
    /*
     * Метод, возвращающий размер строки без учета '\0'.
     */
    auto
    size() -> __u16
      { return ( _M_size - 1 ); }
//--------------------------------------------------------------------
    /*
     * Метод, возвращающий размер строки без
     * использования библиотечной функции strlen() и
     * без учета '\0'.
     */
    auto
    s_len(char const* __s) -> __u16
    {
      __u16 __i;
      for (__i = 0; __s[__i] != '\0'; ++__i);
      return __i; 
    }
//--------------------------------------------------------------------
    /*
     * Метод, копирует строку __s2 в __s1 без
     * использования библиотечной функции strcpy().
     */
    auto
    s_cpy( char* __s1, char const* __s2 ) -> char*
      {
      __u16  __s_len{ s_len( __s2 ) };
      __u16  __i;

      for (__i = 0; __i < __s_len; ++__i )
        {
        __s1[__i] = __s2[__i];
        }

      __s1[__i] = '\0';
      return __s1;
    }
//--------------------------------------------------------------------
    /*
     * Метод, объединяет две строки без
     * использования библиотечной функции strcat().
     */
    auto
    s_cat(char* __s1, char const* __s2) -> char*
    {
      __u16 __i{ };

      /** Вычисляется длина __s1 и помещяется в __i.
       */
      for (__i = 0; __s1[__i] != '\0'; ++__i);

      for (__u16 __j{0}; __s2[__j] != '\0'; ++__j, ++__i)
        {
          __s1[__i] = __s2[__j];
        }

      __s1[__i] = '\0';
      return __s1;
    }
//--------------------------------------------------------------------
    /*
     * Обмен значениями двух объектов.
     */
    auto
    swap(pstring& __a, pstring& __b) -> void
    {
      pstring __temp{ std::move(__a) };
      __a = std::move(__b);
      __b = std::move(__temp);
    }
//--------------------------------------------------------------------
    /*
     * Удаление всех символов в строке, кроме цифровых.
     */
    auto
    del_all_char() -> char*
    {
      for (__u16 __i{0}; _M_string[__i] != '\0'; ++__i)
        {
          while (!(_M_string[__i] >= '0' && _M_string[__i] <= '9')
                && _M_string[__i] != '\0')
            {
              for (__u16 __j{__i};  _M_string[__j] != '\0'; ++__j)
                {
                  _M_string[__j] = _M_string[__j+1];
                }
            }
        }

      return _M_string;
    }
//--------------------------------------------------------------------
  auto
  is_kperiodic( char* __s, __u16 __k ) -> bool
    {
    // Проверяем, что длина строки кратна числу __k.
    if( size() % __k != 0 )
      {
      return false;
      }

    // Проверяем, что каждай __k-й символравен первому символу в строке.
    for( __u16 __i{ __k }; __i < size(); __i += __k )
      {
      if( __s[ __i ] != __s[ 0 ] )
        {
        return false;
        }
      }

    // Если все символы пошли проверку, то строка является кратной 
    // числу __k.
    return true;
    }
//--------------------------------------------------------------------
//    friend ostream& 
//    operator<<(ostream& __os, const pstring& __s);
  };
//--------------------------------------------------------------------
/*
  ostream& 
  operator<<(ostream& __os, const pstring& __s)
  {
    __os << __s._M_string;
    return __os;
  }
*/
} // namespace ptl

#endif // _PTL_PSTRING_H