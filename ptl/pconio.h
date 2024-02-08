/*++

    Copyright (c) S-Patriarch, 2023
    (PTL) Patriarch library : pconio.h

    Работа с терминалом (консолью).

Функции:

    setlocale_WIN32_rus - локализация консоли ОС Windows для вывода
    setconsole_WIN32_rus - локализация консоли ОС Windows для ввода/вывода
    clrscr - очистка терминала
    clreol - удаляет все символы после курсора до конца строки
    gotoxy - постановка курсора в координаты _x и _y терминала
    where_x - возвращает установленную координату text._S_cur_x
    where_y - возвращает установленную координату text._S_cur_y
    hcrs - скрыть курсор
    scrs - показать курсор
    _getch - получение символа без ожидания нажатия enter (linux)
    get_hidden_input - скрытый ввод в терминале ОС Linux

--*/

#ifndef __PTL_PCONIO_H__
#define __PTL_PCONIO_H__

#include <iostream>

#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#elif _WIN32
#include <clocale>
#include <windows.h>
#endif

typedef unsigned short int __u16;
typedef signed int         __s32;

//////////////////////////////////////////////////////////////////////
namespace ptl
{
    struct textinfo {
        __u16 _S_cur_x { 0 };
        __u16 _S_cur_y { 0 };
    } text;

//--------------------------------------------------------------------
// Локализация консоли ОС Windows для вывода
// текста на русском языке.
// 
    void 
    setlocale_WIN32_rus()
    {
        #ifdef _WIN32
            setlocale(LC_ALL, "Russian");
        #endif
    }

//--------------------------------------------------------------------
// Локализация консоли ОС Windows для ввода/вывода
// текста на русском языке.
// 
    void 
    setconsole_WIN32_rus()
    {
        #ifdef _WIN32
            SetConsoleCP(1251);
            SetConsoleOutputCP(1251);
        #endif
    }

//--------------------------------------------------------------------
// Очистка терминала и постановка курсора в 
// верхний левый угол.
//
    void 
    clrscr() 
    { std::cout << "\033[2J\033[1;1H"; }

//--------------------------------------------------------------------
// Удаляет все символы, находящиеся после курсора и до конца
// строки, но не удаляет символы, расположенные перед
// текущей позицией курсора.
//
    void 
    clreol() 
    { std::cout << "\033[K"; }

//--------------------------------------------------------------------
// Постановка курсора в координаты _x и _y терминала.
// 
    void 
    gotoxy(
        __u16 _x, 
        __u16 _y
        )
    { 
        std::cout << "\033[" 
                  << _y 
                  << ";" 
                  << _x 
                  << "H";

        text._S_cur_x = _x;
        text._S_cur_y = _y;
    }

//--------------------------------------------------------------------
// Возвращает установленную координату text._S_cur_x.
// 
    __u16 
    where_x() 
    { return text._S_cur_x; }

//--------------------------------------------------------------------
// Возвращает установленную координату text._S_cur_y.
// 
    __u16 
    where_y() 
    { return text._S_cur_y; }

//--------------------------------------------------------------------
// Скрыть курсор.
// 
    void 
    hcrs() 
    { std::cout << "\033[?25l"; }

//--------------------------------------------------------------------
// Показать курсор.
// 
    void 
    scrs() 
    { std::cout << "\033[?25h"; }


#ifdef __linux__

//--------------------------------------------------------------------
// Получение символа с клавиатуры без ожидания нажатия enter.
// Аналог функции _getch() в стандартной библиотеке conio.h (Windows).
// Реализация данной функции предназначена для работы в терминале 
// ОС Linux. 
//
    __s32 
    _getch() 
    {
        __s32 buf = 0;
        struct termios old = { 0 };

        if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");

        old.c_lflag    &= ~ICANON;
        old.c_lflag    &= ~ECHO;
        old.c_cc[VMIN]  = 1;
        old.c_cc[VTIME] = 0;

        if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");

        if (read(0, &buf, 1) < 0)
            perror("read()");

        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;

        if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror("tcsetattr ~ICANON");

        return (buf);
    }

//--------------------------------------------------------------------
// Функция скрытого ввода в терминале ОС Linux.
//
std::string get_hidden_input() 
{
    struct termios oldt;
    struct termios newt;
    
    std::string strResult{};

    // Сохраняем текущие настройки терминала
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO; // Отключаем отображение ввода

    // Применяем новые настройки терминала
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Читаем ввод пользователя
    std::getline(std::cin, strResult);

    // Востанавливаем старые настройки терминала
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return strResult;
}

#endif // __linux__

} // namespace ptl

#endif // __PTL_PCONIO_H__
