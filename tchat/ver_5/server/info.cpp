/*++

    Copyright (c) S-Patriarch, 2023

    Реализация функций информационного механизма чата.

--*/

#include <iostream>

#ifdef __linux__
#include <sys/utsname.h>
#endif

//////////////////////////////////////////////////////////////////////
namespace chat
{
//--------------------------------------------------------------------
    void
    get_logo()
    {
        std::cout << "tchat 5.0 SERVER\n";

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
        std::cout << "Usage:\n"
                     "  msg: [сообщение для пользователя]\n\n";
    }

//--------------------------------------------------------------------
    void 
    get_help()
    {
        std::cout << "tchat 5.0\n"
                     "Usage: к: [имя пользователя] или [параметр]\n"
                     "       ч: [сообщение для пользователя] или [параметр]\n"
                     "Parameters: -h, -? вызов информации о параметрах чата\n"
                     "            -e     редактировать данные пользователя чата\n"
                     "            -q     завершить работу чата\n\n";
                     //" --all  сообщение для всех пользователей чата\n\n";
    }

} // namespace chat