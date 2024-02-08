/*++

    (c) S-Patriarch, 2023
    (PTL) Patriarch library : pcolor.h

    Работа с цветовой esc-последовательностью в
    терминале (консоле).

Методы:

    esc_c  - сбрасывает цветовую esc-последовательность
    esc_tr - устанавливает обычный цвет текста
    esc_tb - устанавливает жирный цвет текста
    esc_br - устанавливает обычный цвет фона
    esc_bb - устанавливает жирный цвет фона

    getbkgcolor - получение цвета фона терминала

--*/

#ifndef __PTL_PCOLOR_H__
#define __PTL_PCOLOR_H__

#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

////////////////////////////////////////////////////////////////////////////////
namespace ptl
{
//------------------------------------------------------------------------------
enum Color {
    BLACK = 0, RED   = 1, GREEN   = 2, YELLOW = 3, BLUE = 4, MAGENTA = 5, 
    CYAN  = 6, WHITE = 7, CURRENT = 1000
};
//------------------------------------------------------------------------------
class pColor 
{
    unsigned short int _m_sizeArray {8};

    std::string* _m_textColorRegular; 
    std::string* _m_textColorBold;    
    std::string* _m_backgroundColorRegular;
    std::string* _m_backgroundColorBold;
    std::string  _m_colorClear;

public:
    pColor()
    { 
        _m_colorClear = "\033[0m";

        _m_textColorRegular = new std::string[_m_sizeArray] { 
            "\033[30m", "\033[31m", "\033[32m", "\033[33m", 
            "\033[34m", "\033[35m", "\033[36m", "\033[37m"
        };

        _m_textColorBold = new std::string[_m_sizeArray] { 
            "\033[30;1m", "\033[31;1m", "\033[32;1m", "\033[33;1m", 
            "\033[34;1m", "\033[35;1m", "\033[36;1m", "\033[37;1m"
        };

        _m_backgroundColorRegular = new std::string[_m_sizeArray] { 
            "\033[40m", "\033[41m", "\033[42m", "\033[43m", 
            "\033[44m", "\033[45m", "\033[46m", "\033[47m"
        };

        _m_backgroundColorBold = new std::string[_m_sizeArray] { 
            "\033[40;1m", "\033[41;1m", "\033[42;1m", "\033[43;1m", 
            "\033[44;1m", "\033[45;1m", "\033[46;1m", "\033[47;1m"
        };
    }

    virtual
    ~pColor() noexcept
    { 
        delete[] _m_textColorRegular;
        delete[] _m_textColorBold; 
        delete[] _m_backgroundColorRegular;
        delete[] _m_backgroundColorBold;
    }

    //--------------------------------------------------------------------------
    // Возвращает строку сброса цветовой esc-последовательности.
    //
    std::string esc_c() 
    { return _m_colorClear; }

    //--------------------------------------------------------------------------
    // Устанавливает цвет текста.
    // Возвращает строку цветовой esc-последовательности обычной
    // насыщенности по заданному _index от 0 до 7 включительно.
    //
    std::string esc_tr(Color index_)
    { return _m_textColorRegular[index_]; }

    //--------------------------------------------------------------------------
    // Устанавливает цвет текста.
    // Возвращает строку цветовой esc-последовательности жирной
    // насыщенности по заданному _index от 0 до 7 включительно.
    //
    std::string esc_tb(Color index_)
    { return _m_textColorBold[index_]; }

    //--------------------------------------------------------------------------
    // Устанавливает цвет фона.
    // Возвращает строку цветовой esc-последовательности обычной
    // насыщенности по заданному _index от 0 до 7 включительно.
    //
    std::string esc_br(Color index_ )
    { return _m_backgroundColorRegular[index_]; }

    //--------------------------------------------------------------------------
    // Устанавливает цвет фона.
    // Возвращает строку цветовой esc-последовательности жирной
    // насыщенности по заданному _index от 0 до 7 включительно.
    //
    std::string esc_bb(Color index_)
    { return _m_backgroundColorBold[index_]; }

    //--------------------------------------------------------------------------
    // Получение цвета фона терминала (Linux), консоли (Windows).
    // Возвращает индекс цвета перечисления Color.
    //
    Color getbkgcolor()
    {
        Color backgroundColor;

        #ifdef __linux__

            backgroundColor = Color::BLACK;

        #elif _WIN32

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            // Получаем информацию о текущих атрибутах экранного буфера
            GetConsoleScreenBufferInfo(hConsole, &csbi);
            // Извлекаем цвет фона
            WORD backgroundColor = csbi.wAttributes & 0xF0;
            backgroundColor = static_cast<Color>(backgroundColor);

        #endif

            if (backgroundColor != Color::BLACK   && 
                backgroundColor != Color::RED     && 
                backgroundColor != Color::GREEN   && 
                backgroundColor != Color::YELLOW  && 
                backgroundColor != Color::BLUE    && 
                backgroundColor != Color::MAGENTA && 
                backgroundColor != Color::CYAN    && 
                backgroundColor != Color::WHITE) {
                backgroundColor = Color::BLACK;
            }

        return backgroundColor;
    }
}; // class pColor

} // namespace ptl 

#endif // __PTL_PCOLOR_H__
