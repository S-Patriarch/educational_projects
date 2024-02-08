/*++

    Copyright (c) S-Patriarch, 2023

    Терминальный чат.
    Версия с использованием STL.

--*/

#include "cst.h"
#include "user.h"

#ifdef __linux__
#include "ptl/ptype.h"
#include "ptl/pconio.h"
#include "ptl/pcolor.h"
#elif _WIN32
#include "ptl\ptype.h"
#include "ptl\pconio.h"
#include "ptl\pcolor.h"
#endif

#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <climits>
#include <vector>

typedef std::vector<chat::User> __v;

namespace chat
{
    ptl::__u32  ID{ 0 }; // ID пользователя

    void get_info();
    void user_authorization(__v&);
    void check_out_message(__v&);
    ptl::__u16 in_record_message(__v&);
    void user_edit(__v&);
} 

//////////////////////////////////////////////////////////////////////
int main()
{
    ptl::setconsole_WIN32_rus();

    chat::get_info();

    try {
        ptl::pColor  c;

        // создаем динамическое хранилище пользователей чата
        __v  _user(chat::ID+1);

        // добавляем одного (первого) пользователя с ID:1, чтоб был
        _user[chat::ID].set_user(
            "Patriarch", 
            "apsk0529-2@mail.ru", 
            "QQqq1122+", 
            chat::ID+1);

        ptl::clrscr();
        chat::get_info();

        // запускаем процедуру авторизации / регистрации пользователя
        chat::user_authorization(_user);

        bool        _flag{ true };
        ptl::__u16  _parametr{ chat::_Ok };

        while (_flag) {
            // приглашаем авторизовавшегося / зарегистрировавшегося 
            // пользователя к дальнейшей работе в чате

            if (_parametr != chat::_Help)
                ptl::clrscr();

            std::cout << c.esc_tb(ptl::GREEN)
                      << "chat"
                      << c.esc_c()
                      << ": Добро пожаловать "
                      << _user[chat::ID-1].get_user_name()
                      << "..."
                      << std::endl;

            // процесс обмена сообщениями
            do {
                std::cout << std::endl;
                chat::check_out_message(_user);
                _user[chat::ID-1].out_user_name();
                _parametr = chat::in_record_message(_user);
            }
            while (_parametr == chat::_Ok);

            // обработка управляющих параметров чата

            // помощь
            if (_parametr == chat::_Help) {
                ptl::clrscr();
                chat::get_info();
            }

            // смена пользователя
            if (_parametr == chat::_Change) {
                ptl::clrscr();
                chat::user_authorization(_user);
            }

            // редактирование данных пользователя
            if (_parametr == chat::_Edit) {
                chat::user_edit(_user);
            }

            // завершение работы чата
            if (_parametr == chat::_Quit) {
                std::cout << std::endl;
                std::cout << c.esc_tb(ptl::GREEN)
                          << "chat"
                          << c.esc_c()
                          << ": До новых встреч "
                          << _user[chat::ID-1].get_user_name()
                          << "..."
                          << std::endl;
                _flag = false;
            }
        }
    }
    catch (std::exception& ex) {
        std::cout << ex.what()
                  << std::endl;
    }

    return 0;
}

namespace chat
{
//-------------------------------------------------------------------- 
// Функция выводит информацию об управляющих
// параметрах работы чата.
//
    void 
    get_info()
    {
        std::cout << "tchat 2.0\n"
                     "Использование:\n"
                     "  User\n"
                     "  к: [имя пользователя] или [параметр]\n"
                     "  ч: [сообщение для пользователя] или [параметр]\n\n"
                     "Параметры:\n"
                     "  -h, -?  вызов информации о параметрах чата\n"
                     "  -c      сменить пользователя чата\n"
                     "  -e      редактировать данные пользователя чата\n"
                     "  -q      завершить работу чата\n"
                     "  --all   сообщение для всех пользователей чата\n";
    }

//--------------------------------------------------------------------
// Функция авторизации пользователя.
// Устанавливает ID авторизованного или вновь зарегистрированного
// пользователя.
//
    void 
    user_authorization(
        __v& _user
        )
    {
        std::string  _name{};
        std::string  _login{};
        std::string  _password{};

        ptl::pColor  c;

        chat::ID = 0;

        std::cout << c.esc_tb(ptl::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Авторизация пользователя..."
                  << std::endl;

        // ввод логина пользователя
        std::cout << "Логин: ";

        std::cout << c.esc_tb(ptl::WHITE);
        std::cin.clear();
        std::cin >> _login;
        std::cout << c.esc_c();

        // проверка введенного логина на наличие
        for (ptl::__u32 i{ 0 }; i < _user.size(); ++i) {
            bool  _flag{ false };

            if (_user[i].get_user_login() == _login) {
                chat::ID = _user[i].get_user_id();
                _flag    = true;
            }

            if (_flag) break;
        }

        if (chat::ID != 0) {
            // если введенный логин найден среди зарегистрированных
            // пользователей чата, то проводим идентификацию пароля
            // данного пользователя

            // ввод пароля пользователя
            std::cout << "Пароль: ";

            std::cout << c.esc_tb(ptl::WHITE);
            std::cin.clear();
            std::cin >> _password;
            std::cout << c.esc_c();

            // проверка введенного пароля на идентичность
            while (_user[chat::ID-1].get_user_password() != _password) {
                std::cout << c.esc_tb(ptl::GREEN)
                          << "\nchat"
                          << c.esc_c()
                          << ": Пароль введен не верно..."
                          << std::endl;

                std::cout << "Пароль: ";

                std::cout << c.esc_tb(ptl::WHITE);
                std::cin.clear();
                std::cin >> _password;
                std::cout << c.esc_c();
            }
        }
        else { 
            // если введенный логин не найден среди зарегистрированных
            // пользователей чата, то проводим процедуру регистрацию в
            // качестве нового пользователя

            std::cout << c.esc_tb(ptl::GREEN)
                      << "\nchat"
                      << c.esc_c()
                      << ": Пользователь с таким логином не зарегистрирован.\n"
                      << "Пройдите регистрацию в качестве нового пользователя..."
                      << std::endl;

            std::cout << c.esc_tb(ptl::GREEN)
                      << "\nchat"
                      << c.esc_c()
                      << ": Регистрация пользователя..."
                      << std::endl;

            // ввод имени и его проверка на наличие
            bool _flag{ false };

            do {
                std::cout << "Имя: ";

                std::cout << c.esc_tb(ptl::WHITE);
                std::cin.clear();
                std::cin >> _name;
                std::cout << c.esc_c();

                for (ptl::__u32 i{ 0 }; i < _user.size(); ++i) {
                    if (_user[i].get_user_name() != _name) {
                        _flag = true;
                    }
                    else {
                        std::cout << c.esc_tb(ptl::GREEN)
                                  << "\nchat"
                                  << c.esc_c()
                                  << ": Такое имя уже существует..."
                                  << std::endl;

                        _flag = false;
                        break;
                    }
                }
            }
            while (!_flag);

            // ввод логина и его проверка на наличие
            _flag = false;

            do {
                std::cout << "Логин: ";

                std::cout << c.esc_tb(ptl::WHITE);
                std::cin.clear();
                std::cin >> _login;
                std::cout << c.esc_c();

                for (ptl::__u32 i{ 0 }; i < _user.size(); ++i) {
                    if (_user[i].get_user_login() != _login) {
                        _flag = true;
                    }
                    else {
                        std::cout << c.esc_tb(ptl::GREEN)
                                  << "\nchat"
                                  << c.esc_c()
                                  << ": Такой логин уже существует..."
                                  << std::endl;

                        _flag = false;
                        break;
                    }
                }
            }
            while (!_flag);

            std::cout << "Пароль: ";

            std::cout << c.esc_tb(ptl::WHITE);
            std::cin.clear();
            std::cin >> _password;
            std::cout << c.esc_c();

            // прописываем нового пользователя в динамическое
            // хранилище пользователей
            _user.resize(_user.size() + 1);
            chat::ID = _user.size();
            _user[chat::ID-1].set_user(_name, _login, _password, chat::ID);
        }
    }

//--------------------------------------------------------------------
// Функция проверяет наличие сообщений для авторизованного 
// пользователя и при их наличии выводит в терминал.
//
    void 
    check_out_message(
        __v& _user
        )
    {
        ptl::pColor  c;

        if (_user[chat::ID-1].get_msg_quantity() != 0) {
            std::cout << c.esc_tb(ptl::GREEN)
                      << "chat"
                      << c.esc_c()
                      << ": Для вас есть сообщения..."
                      << std::endl;

          _user[chat::ID-1].out_message();
          _user[chat::ID-1].clear_msg_quantity();
        }
        else {
            std::cout << c.esc_tb(ptl::GREEN)
                      << "chat"
                      << c.esc_c()
                      << ": Для вас нет сообщений..."
                      << std::endl;
        }
    }

//--------------------------------------------------------------------
// Функция запрашивает для кого сообщение, само сообщение и
// пулученную информацию отписывает пользователю для
// которого она предназначена.
// Возвращает chat::_Ok при нормальном завершении работы или
// один из управляющих параметров.
//
    ptl::__u16 
    in_record_message(
        __v& _user
        )
    {
        std::string  _whom{}; // Кому предназначено сообщение
        std::string  _what{}; // Текст сообщения
        bool         _flag{ true };

        ptl::pColor  c;

        std::cout << std::endl;

        do {
            // ввод имени пользователя для которого преднозначено
            // сообщение
            std::cout << "к: ";
            std::cin.clear();
            std::cin >> _whom;

            // обработка введенных управляющих параметров
            if (_whom == "-h" || _whom == "-H" || _whom == "-?")
                return chat::_Help;

            if (_whom == "-c" || _whom == "-C")
                return chat::_Change;

            if (_whom == "-e" || _whom == "-E")
                return chat::_Edit;

            if (_whom == "-q" || _whom == "-Q")
                return chat::_Quit;

            // проверка введенного имени пользователя на наличие
            if (_whom == "--all") {
                _flag = false;
            }
            else
                for (ptl::__u32 i{ 0 }; i < _user.size(); ++i) {
                    if (_user[i].get_user_name() == _whom) {
                        _flag = false;
                        break;
                    }
                }

                if (_flag == true) {
                    std::cout << c.esc_tb(ptl::GREEN)
                              << "chat"
                              << c.esc_c()
                              << ": Пользователя с таким именем нет..."
                              << std::endl;            
                }
        }
        while (_flag);

        // ввод сообщения
        std::cout << "ч: ";
        std::cin.ignore(INT_MAX, '\n');
        std::getline(std::cin, _what);

        // повторная обработка введенных управляющих параметров
        if (_what == "-h" || _what == "-H" || _what == "-?")
            return chat::_Help;

        if (_what == "-c" || _what == "-C")
            return chat::_Change;

        if (_what == "-e" || _what == "-E")
            return chat::_Edit;

        if (_what == "-q" || _what == "-Q")
            return chat::_Quit;

        // проверка логина и запись сообщения
        if (_whom == "--all") {
            for (ptl::__u32 i{ 0 }; i < _user.size(); ++i) {
                if (_user[i].get_user_name() != 
                    _user[chat::ID-1].get_user_name()) {
                    _user[i].record_message(
                        _user[chat::ID-1].get_user_name(), 
                        _what);
                }
            }
        }
        else {
            bool  _flag{ false };

            for (ptl::__u32 i{ 0 }; i < _user.size(); ++i) {
                if (_user[i].get_user_name() == _whom) {
                    _user[i].record_message(
                        _user[chat::ID-1].get_user_name(), 
                        _what);

                    _flag = true;
                }

                if (_flag) break;
            }
        }

        return chat::_Ok;
    }

//--------------------------------------------------------------------
// Функция редактирует данные пользователя.
// Редактирование заключается в смене пароля пользователя.
//
    void 
    user_edit(
        __v& _user
        )
    {
        std::string  _password_old{};
        std::string  _password_new{};

        ptl::pColor  c;

        std::cout << "\n"
                  << c.esc_tb(ptl::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Редактирование данных пользователя "
                  << _user[chat::ID-1].get_user_name()
                  << "..."
                  << std::endl;

        // запрос старого пароля пользователя
        std::cout << "Старый пароль: ";

        std::cout << c.esc_tb(ptl::WHITE);
        std::cin.clear();
        std::cin >> _password_old;
        std::cout << c.esc_c();

        // проверка введенного пароля на идентичность
        while (_user[chat::ID-1].get_user_password() != _password_old) {
            std::cout << c.esc_tb(ptl::GREEN)
                      << "\nchat"
                      << c.esc_c()
                      << ": Пароль введен не верно..."
                      << std::endl;

            std::cout << "Старый пароль: ";

            std::cout << c.esc_tb(ptl::WHITE);
            std::cin.clear();
            std::cin >> _password_old;
            std::cout << c.esc_c();
        }

        // запрос нового пароля пользователя
        std::cout << "Новый пароль: ";

        std::cout << c.esc_tb(ptl::WHITE);
        std::cin.clear();
        std::cin >> _password_new;
        std::cout << c.esc_c();
    
        // отписываем в хранилище измененные данные пользователя
        _user[chat::ID-1].set_user_password(_password_new);
    }
}
