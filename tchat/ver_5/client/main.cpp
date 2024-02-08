/*++

    Copyright (c) S-Patriarch, 2023

    Терминальный чат.
    Версия 5.0 CLIENT

    В этой версии реализована работа серверной части tchat с 
    использованием протокола TCP.
    
--*/

#include <iostream>
#include <exception>
#include <string>
#include <climits>
#include <iomanip>
#include <fstream>
#include <stdio.h>

#ifdef __linux__
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../ptl/ptype.h"
#include "../ptl/pconio.h"
#include "../ptl/pcolor.h"
#include "../ptl/psha.h"
#include "../ptl/pexcept.h"
#elif _WIN32
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

//////////////////////////////////////////////////////////////////////
void init_socket(); // создание сокета, 
                    // установка соединения с сервером

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
        ::init_socket();

        std::cout << c.esc_tb(ptl::Color::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Соединение с сервером установлено\n"
                  << std::endl;

        std::cin.ignore(INT_MAX, '\n');

        while (1) {
            bzero(chat::_msg, chat::MAXPACKETSIZE);

            chat::user_out_name(user);
            std::cout << std::endl;
            std::cout << "msg: ";

            ptl::scrs();
            fgets(chat::_msg, sizeof(chat::_msg), stdin);
            ptl::hcrs();

            if (std::strncmp("-q", chat::_msg, 2) == 0
                || std::strncmp("-Q", chat::_msg, 2) == 0) {
                write(chat::_socketFileDescriptor, 
                      chat::_msg, 
                      sizeof(chat::_msg)
                );

                std::cout << std::endl;
                std::cout << c.esc_tb(ptl::Color::GREEN)
                          << "chat"
                          << c.esc_c()
                          << ": До новых встреч "
                          << user._M_userName
                          << std::endl;

                break;
            }

            write(chat::_socketFileDescriptor, 
                  chat::_msg, 
                  sizeof(chat::_msg)
            );

            bzero(chat::_msg, chat::MAXPACKETSIZE);

            // Ждем ответа от сервера
            read(chat::_socketFileDescriptor, 
                 chat::_msg, 
                 sizeof(chat::_msg)
            );

            std::cout << std::endl;
            std::cout << c.esc_tb(ptl::Color::CYAN)
                      << "Server"
                      << c.esc_c()
                      << "\nmsg: "
                      << chat::_msg
                      << std::endl;
        }
    }
    catch (std::exception& ex) {
        std::cout << ex.what()
                  << std::endl;
    }

    // закрываем сокет, завершаем соединение
    close(chat::_socketFileDescriptor);

    ptl::scrs();
    return 0;
}

//--------------------------------------------------------------------
// Создание сокета, установка соединения с сервером.
//
void
init_socket()
{
    // создаем сокет
    chat::_socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (chat::_socketFileDescriptor == -1) {
        throw
        ptl::pException("E: Не удалось создать сокет."); 
    }

    // установка адреса сервера
    chat::serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // задаем номер порта для связи
    chat::serverAddress.sin_port = htons(chat::PORT);
    // используем IPv4
    chat::serverAddress.sin_family = AF_INET;

    // установка соединение с сервером
    chat::_connection = connect(chat::_socketFileDescriptor, 
                                (struct sockaddr*)& chat::serverAddress, 
                                sizeof(chat::serverAddress)
                        );
    if (chat::_connection == -1) {
        throw
        ptl::pException("E: Не удалось установить соединение с сервером."); 
    }
}