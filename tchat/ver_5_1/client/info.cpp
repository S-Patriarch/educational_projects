/*++

    Copyright (c) S-Patriarch, 2023

    Реализация функций информационного механизма чата.

--*/

#include <iostream>

#ifdef __linux__
#include <sys/utsname.h>
#include "../ptl/pcolor.h"
#elif _WIN32
#include "..\ptl\pcolor.h"
#endif

//////////////////////////////////////////////////////////////////////
namespace chat
{
//--------------------------------------------------------------------
    void
    get_logo()
    {
        std::cout << "tchat 5.1 CLIENT\n";

        #ifdef __linux__
            struct utsname sysinfo;
            uname(&sysinfo);

            std::cout << "- "
                      << sysinfo.sysname
                      << '\n'
                      << "- "
                      << sysinfo.version
                      << std::endl;
        #elif _WIN32
            std::cout << "- Windows\n";
        #endif

        std::cout << std::endl;
    }

//--------------------------------------------------------------------
    void
    get_info()
    { 
        ptl::pColor c;
        std::cout << "Usage:\n"
                  << "  msg: [сообщение для пользователя] или [параметр]\n"
                  << "Parameters:\n"
                  << c.esc_tb(ptl::Color::WHITE)
                  << "  -q"
                  << c.esc_c()
                  << ", "
                  << c.esc_tb(ptl::Color::WHITE)
                  << "-Q"
                  << c.esc_c()
                  << "  завершить работу чата\n\n";
    }

//--------------------------------------------------------------------
    void 
    get_help()
    {
        std::cout << "tchat 5.1\n"
                     "Usage: к: [имя пользователя] или [параметр]\n"
                     "       ч: [сообщение для пользователя] или [параметр]\n"
                     "Parameters: -h, -? вызов информации о параметрах чата\n"
                     "            -e     редактировать данные пользователя чата\n"
                     "            -q     завершить работу чата\n\n";
                     //" --all  сообщение для всех пользователей чата\n\n";
    }

} // namespace chat