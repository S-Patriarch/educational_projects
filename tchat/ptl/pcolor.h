// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы с цветовой схемой терминала.
 */

/**
 *  (PTL) Patriarch library : pcolor.h
 */

#pragma once
#if !defined( __PTL_PCOLOR_H__ )
#define __PTL_PCOLOR_H__

#include <string>

/*
 * Класс описывает работу с цветовой esc-последовательностью в 
 * терминале (консоле).
 * 
 * Методы:
 *   - esc_c()  - сбрасывает цветовую esc-последовательность
 *   - esc_tr() - устанавливает обычный цвет текста
 *   - esc_tb() - устанавливает жирный цвет текста
 *   - esc_br() - устанавливает обычный цвет фона
 *   - esc_bb() - устанавливает жирный цвет фона
 */

namespace ptl
  {
//////////////////////////////////////////////////////////////////////
  enum color
    {
    BLACK   = 0, RED     = 1, GREEN = 2, YELLOW = 3,
    BLUE    = 4, MAGENTA = 5, CYAN  = 6, WHITE  = 7,
    CURRENT = 1000
    };
//////////////////////////////////////////////////////////////////////
  class pcolor
    {
    protected:
      unsigned short int  _M_size_array{ 8 };

      std::string*        _M_text_color_regular; 
      std::string*        _M_text_color_bold;    
      std::string*        _M_background_color_regular;
      std::string*        _M_background_color_bold;
      std::string         _M_color_clear;

    public:
      pcolor()
        { 
        _M_color_clear = "\033[0m";

        _M_text_color_regular = new std::string[ _M_size_array ]
          { 
          "\033[30m", "\033[31m", "\033[32m", "\033[33m", 
          "\033[34m", "\033[35m", "\033[36m", "\033[37m"
          };

        _M_text_color_bold = new std::string[ _M_size_array ]
          { 
          "\033[30;1m", "\033[31;1m", "\033[32;1m", "\033[33;1m", 
          "\033[34;1m", "\033[35;1m", "\033[36;1m", "\033[37;1m"
          };

        _M_background_color_regular = new std::string[ _M_size_array ]
          { 
          "\033[40m", "\033[41m", "\033[42m", "\033[43m", 
          "\033[44m", "\033[45m", "\033[46m", "\033[47m"
          };

        _M_background_color_bold = new std::string[ _M_size_array ]
          { 
          "\033[40;1m", "\033[41;1m", "\033[42;1m", "\033[43;1m", 
          "\033[44;1m", "\033[45;1m", "\033[46;1m", "\033[47;1m"
          };
        }

      virtual
      ~pcolor() noexcept
        { 
        delete[] _M_text_color_regular;
        delete[] _M_text_color_bold; 
        delete[] _M_background_color_regular;
        delete[] _M_background_color_bold;
        }
//--------------------------------------------------------------------
// Возвращает строку сброса цветовой esc-последовательности.
//
      auto
      esc_c() -> std::string
        { return _M_color_clear; }
//--------------------------------------------------------------------
// Устанавливает цвет текста.
// Возвращает строку цветовой esc-последовательности обычной
// насыщенности по заданному __index от 0 до 7 включительно.
//
      auto
      esc_tr( color __index ) -> std::string
        { return _M_text_color_regular[ __index ]; }
//--------------------------------------------------------------------
// Устанавливает цвет текста.
// Возвращает строку цветовой esc-последовательности жирной
// насыщенности по заданному __index от 0 до 7 включительно.
//
      auto
      esc_tb( color __index ) -> std::string
        { return _M_text_color_bold[ __index ]; }
//--------------------------------------------------------------------
// Устанавливает цвет фона.
// Возвращает строку цветовой esc-последовательности обычной
// насыщенности по заданному __index от 0 до 7 включительно.
//
      auto
      esc_br( color __index ) -> std::string
        { return _M_background_color_regular[ __index ]; }
//--------------------------------------------------------------------
// Устанавливает цвет фона.
// Возвращает строку цветовой esc-последовательности жирной
// насыщенности по заданному __index от 0 до 7 включительно.
//
      auto
      esc_bb( color __index ) -> std::string
        { return _M_background_color_bold[ __index ]; }

    }; // class pcolor
  } // namespace ptl

#endif // __PTL_PCOLOR_H__