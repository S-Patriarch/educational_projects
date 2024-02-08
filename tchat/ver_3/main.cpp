/*++

    Copyright (c) S-Patriarch, 2023

    Терминальный чат.
    Версия 3.0

    В этой версии реализована концепция хранения данных когда-либо
    зарегистрированных пользователей чата во внешнем (статическом)
    хранилище данных - файле pshadow.

    Так же реализована концепция хранения не отправленных (готовых
    к получению) сообщений для пользователей, которые в данный
    момент не в чате, во внешнем хранилище - файл pmsg.

    Кроме того, реализован "скрытый" ввод пароля.
    
--*/

#include <iostream>
#include <exception>
#include <string>
#include <iomanip>
#include <fstream>

#ifdef __linux__
#include "ptl/ptype.h"
#include "ptl/pconio.h"
#include "ptl/pcolor.h"
#include "ptl/psha.h"
#elif _WIN32
#include "ptl\ptype.h"
#include "ptl\pconio.h"
#include "ptl\pcolor.h"
#include "ptl\psha.h"
#endif

#include "cst.h"
#include "struct.h"
#include "info.h"
#include "file.h"
#include "user.h"

//////////////////////////////////////////////////////////////////////
int main()
{
    ptl::setconsole_WIN32_rus();

    try {
        ptl::pColor c;

        chat::User    user;
        chat::Message msg;

        bool       _isFlagChat { true };
        ptl::__u16 _parametr { chat::Parametr::OK };

        ptl::clrscr();
        chat::get_logo();

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

        while (_isFlagChat) {
            // приглашаем авторизовавшегося / зарегистрировавшегося 
            // пользователя к дальнейшей работе в чате

            if (_parametr != chat::Parametr::HELP) {
                ptl::clrscr();
                chat::get_info();
            }

            std::cout << c.esc_tb(ptl::Color::GREEN)
                      << "chat"
                      << c.esc_c()
                      << ": Добро пожаловать "
                      << user._M_userName
                      << "..."
                      << std::endl;

            // проверка наличия поступивших пользователю
            // сообщений и при их наличии вывод на экран
            if (chat::mcheck(user)) {
                std::cout << std::endl;

                chat::mtout(user);
            
                // очистка хранилища сообщений от прочитанных
                // пользователем сообщений
                chat::mclear(user, msg);
            }

            do {
                std::cout << std::endl;

                // вывод имени пользователя                
                chat::user_out_name(user);

                // ввод сообщения
                _parametr = chat::mtin(user, msg);

                // отписываем введенное сообщение в хранилище
                // сообщений - pmsg
                if (_parametr == chat::Parametr::OK) {
                    chat::mfout(msg);
                }

                // обработка управляющих параметров чата

                // помощь
                if (_parametr == chat::Parametr::HELP) {
                    ptl::clrscr();
                    chat::get_help();
                }

                // редактирование данных пользователя
                if (_parametr == chat::Parametr::EDIT) {
                    chat::user_edit(user);
                }

                // завершение работы чата
                if (_parametr == chat::Parametr::QUIT) {
                    std::cout << std::endl;
                    std::cout << c.esc_tb(ptl::Color::GREEN)
                              << "chat"
                              << c.esc_c()
                              << ": До новых встреч "
                              << user._M_userName
                              << "..."
                              << std::endl;
                    _isFlagChat = false;
                }
            }
            while (_parametr == chat::Parametr::OK);
        }
    }
    catch (std::exception& ex) {
        std::cout << ex.what()
                  << std::endl;
    }

    return 0;
}