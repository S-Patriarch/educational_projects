/*++

    Copyright (c) S-Patriarch, 2023

    Терминальный чат.
    Версия 5.1 CLIENT

--*/

#include <iostream>
#include <exception>
#include <string>
#include <cstring>
#include <climits>
#include <iomanip>
#include <fstream>
#include <stdio.h>

#ifdef __linux__
#include "../ptl/pTCPClient.h"
#include "../ptl/ptype.h"
#include "../ptl/pconio.h"
#include "../ptl/pcolor.h"
#include "../ptl/psha.h"
#include "../ptl/pexcept.h"
#elif _WIN32
#include "..\ptl\pTCPClient.h"
#include "..\ptl\ptype.h"
#include "..\ptl\pconio.h"
#include "..\ptl\pcolor.h"
#include "..\ptl\psha.h"
#include "..\ptl\pexcept.h"
#endif

#include "cst.h"
#include "struct.h"
#include "info.h"
#include "file.h"
#include "user.h"

ptl::pTCPClient tcp;

//////////////////////////////////////////////////////////////////////
int main()
{
    ptl::setconsole_WIN32_rus();

    try {
        ptl::clrscr();
        chat::get_logo();

        ptl::pColor c;

        chat::User    user;
        chat::Message msg;

        // проверка наличия файлов статических хранилищ
        // если их нет, то хранилища создаются
        if (!chat::file_test("pshadow")) {
            chat::file_creat("pshadow");
        }
        if (!chat::file_test("pmsg")) {
            chat::file_creat("pmsg");
        }

        // запускаем процедуру авторизации / регистрации пользователя
        chat::user_authorization(user);

        ptl::hcrs();

        ptl::clrscr();
        chat::get_logo();
        chat::get_info();

        std::cout << c.esc_tb(ptl::Color::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Добро пожаловать "
                  << user._M_userName
                  << std::endl;

        // CLIENT
        // создание сокета, 
        // установка соединения с сервером
        tcp.setup("127.0.0.1", 53333);

        std::cout << c.esc_tb(ptl::Color::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Соединение с сервером установлено\n"
                  << std::endl;

        std::cin.ignore(INT_MAX, '\n');

        while (1) {
            std::memset(&chat::_msg[0], 
                        0, 
                        sizeof(chat::_msg)
            );

            chat::user_out_name(user);
            std::cout << std::endl;
            std::cout << "msg: ";

            ptl::scrs();
            fgets(chat::_msg, sizeof(chat::_msg), stdin);
            ptl::hcrs();

            if (std::strncmp("-q", chat::_msg, 2) == 0
                || std::strncmp("-Q", chat::_msg, 2) == 0) {

                std::string __strSend(chat::_msg);
                tcp.Send(__strSend);

                std::cout << std::endl;
                std::cout << c.esc_tb(ptl::Color::GREEN)
                          << "chat"
                          << c.esc_c()
                          << ": До новых встреч "
                          << user._M_userName
                          << std::endl;

                break;
            }

            std::string _strSend(chat::_msg);
            tcp.Send(_strSend);

            std::memset(&chat::_msg[0], 
                        0, 
                        sizeof(chat::_msg)
            );

            // Ждем ответа от сервера
            std::string _strRead = tcp.read();

            std::cout << std::endl;
            std::cout << c.esc_tb(ptl::Color::CYAN)
                      << "Server"
                      << c.esc_c()
                      << "\nmsg: "
                      << _strRead
                      << std::endl;
        }
    }
    catch (std::exception& ex) {
        std::cout << ex.what()
                  << std::endl;
    }

    // закрываем сокет, завершаем соединение
    tcp.exit();

    ptl::scrs();
    return 0;
}