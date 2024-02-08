/*++

    Copyright (c) S-Patriarch, 2023
    (PTL) Patriarch library : pbar.h

    Индикаторы выполнения и работа с ними.

Методы:

    set_min - установка минимальной процентной итерации
    set_max - установка максимальной процентной итерации
    set_style - установка стиля индикатора
    set_message - установка сообщения индикатора
    set_brackets - установка границ индикатора
    set_color - установка цвета индикатора
    get_min - получение минимальной процентной итерации
    get_max - получение максимальной процентной итерации
    update - обновление отрисовки индикатора выполнения

Использование:

    ptl::pBar  pb;
    ptl::hcrs();
    for (ptl::__u32 i{ pb.get_min() }; i <= pb.get_max(); i++) {
        pb.update(i);
        // выполнение операций...
    }
    ptl::scrs();

--*/

#ifndef __PTL_PBAR_H__
#define __PTL_PBAR_H__

#include <iostream>
#include <string>

#ifndef __PTL_PCOLOR_H__
#include "pcolor.h"
#endif

typedef unsigned short int __u16;
typedef unsigned int       __u32;

//////////////////////////////////////////////////////////////////////
namespace ptl
{
    class pBar 
    {
    public:
        pBar()
        {
            _M_minIterations = 0;
            _M_maxIterations = 100;
            _M_barWidth      = 30;
            _M_barColor      = Color::CURRENT;
            _M_bar           = "=";
            _M_style         = "complete";
            _M_percent       = "%";
            _M_message       = "";
            _M_bracketLeft   = "[";
            _M_bracketRigth  = "]";
        }

        ~pBar() noexcept 
        { }

//--------------------------------------------------------------------
// Установка минимальной процентной итерации.
//
        void 
        set_min(
            __u32 _min
            ) 
        { _M_minIterations = _min; }

//--------------------------------------------------------------------
// Установка максимальной процентной итерации.
//
        void 
        set_max(
            __u32 _max
            ) 
        { _M_maxIterations = _max; }

//--------------------------------------------------------------------
// Установка стиля индикатора.
//
        void 
        set_style(
            std::string _style, 
            std::string _percent
            )
        {
            _M_style   = _style;
            _M_percent = _percent;
        }

//--------------------------------------------------------------------
// Установка стиля индикатора.
//
        void 
        set_style(
            std::string _style, 
            std::string _percent,
            std::string _bar
            )
        {
            _M_style   = _style;
            _M_percent = _percent;
            _M_bar     = _bar;
        }

//--------------------------------------------------------------------
// Установка сообщения индикатора.
//
        void 
        set_message(
            std::string _message
            )
        { _M_message = _message; }

//--------------------------------------------------------------------
// Установка границ индикатора.
//
        void 
        set_brackets(
            std::string _bracketLeft,
            std::string _bracketRigth
            )
        {
            _M_bracketLeft  = _bracketLeft;
            _M_bracketRigth = _bracketRigth;
        }

//--------------------------------------------------------------------
// Установка цвета индикатора.
//
        void 
        set_color(
            Color _color
            ) 
        { _M_barColor = _color; }

//--------------------------------------------------------------------
// Получение минимальной процентной итерации.
//
        __u32 
        get_min() 
        { return _M_minIterations; }

//--------------------------------------------------------------------
// Получение максимальной процентной итерации.
//
        __u32 
        get_max() 
        { return _M_maxIterations; }

//--------------------------------------------------------------------
// Обновление отрисовки индикатора выполнения.
//
        void 
        update(
            __u32 _index
            )
        {
            // вычисление процента выполнения
            float  
            _progress = 
                static_cast<float>(_index) / _M_maxIterations;

            __u16  
            _completedWidth =
                static_cast<__u16>(_progress * _M_barWidth);

            pColor c;

            // вывод индикатора выполнения
            std::cout << _M_bracketLeft;

            for (__u16 i = 0; i <= _M_barWidth; i++) {
                if (i <= _completedWidth) {
                    if (_M_barColor == Color::CURRENT) {
                        std::cout << _M_bar;
                    }
                    else {
                        std::cout << c.esc_tb(_M_barColor)
                                  << _M_bar
                                  << c.esc_c();
                    }
                }
                else {
                    std::cout << " ";
                }
            }

            std::cout << _M_bracketRigth
                      << " "
                      << __u16(_progress * 100.0)
                      << _M_percent
                      << " "
                      << _M_message
                      << "\r";

            std::cout.flush();
        }

    private:
        __u32       _M_minIterations;
        __u32       _M_maxIterations;
        __u16       _M_barWidth;

        Color       _M_barColor;

        std::string _M_bar;
        std::string _M_style;
        std::string _M_percent;
        std::string _M_message;
        std::string _M_bracketLeft;
        std::string _M_bracketRigth;
    };

} // namespace ptl

#endif // __PTL_PBAR_H__