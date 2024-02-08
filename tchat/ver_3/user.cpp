/*++

    Copyright (c) S-Patriarch, 2023

    Реализация функций работы с пользователями чата.

--*/

#include <iostream>
#include <fstream>
#include <climits>

#ifdef __linux__
#include "ptl/ptype.h"
#include "ptl/pcolor.h"
#include "ptl/psha.h"
#elif _WIN32
#include "ptl\ptype.h"
#include "ptl\pcolor.h"
#include "ptl\psha.h"
#endif

#include "cst.h"
#include "struct.h"
#include "file.h"

//////////////////////////////////////////////////////////////////////
namespace chat
{
//--------------------------------------------------------------------
    void
    user_authorization(
        chat::User& user
        )
    {
        std::string _name { };
        std::string _login { };
        std::string _password { };

        ptl::pColor c;
        ptl::pSha   sha;

        std::cout << c.esc_tb(ptl::Color::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Авторизация пользователя..."
                  << std::endl;

        // ввод логина пользователя чатом
        std::cout << "Логин: ";

        std::cout << c.esc_tb(ptl::Color::WHITE);
        std::cin.clear();
        std::cin >> _login;
        std::cout << c.esc_c();

        // проверка введенного логина на наличие в 
        // статическом хранилище данных

        if (chat::reading_user_data(user, _login)) {

            // если введенный логин найден среди зарегистрированных
            // пользователей чата, то проводим идентификацию пароля
            // данного пользователя

            // ввод пароля пользователя
            std::cout << "Пароль: ";

            std::cout << "\033[?25l";
            std::cout << c.esc_tr(c.getbkgcolor());
            std::cin.clear();
            std::cin >> _password;
            std::cout << c.esc_c();
            std::cout << "\033[?25h";

            std::string _iHash = sha.sha1(
                                    _password.c_str(), 
                                    sizeof(_password.c_str()) - 1
                                 );

            // проверка введенного пароля на идентичность в
            // статическом хранилище данных

            while (_iHash != user._M_userHashPassword) {
                std::cout << c.esc_tb(ptl::Color::GREEN)
                          << "\nchat"
                          << c.esc_c()
                          << ": Пароль введен не верно..."
                          << std::endl;

                std::cout << "Пароль: ";

            std::cout << "\033[?25l";
            std::cout << c.esc_tr(c.getbkgcolor());
            std::cin.clear();
            std::cin >> _password;
            std::cout << c.esc_c();
            std::cout << "\033[?25h";

                _iHash = sha.sha1(
                             _password.c_str(), 
                             sizeof(_password.c_str()) - 1
                         );
            }
        }
        else {
            // если введенный логин не найден среди зарегистрированных
            // пользователей чата, то проводим процедуру регистрацию в
            // качестве нового пользователя

            std::cout << c.esc_tb(ptl::Color::GREEN)
                      << "\nchat"
                      << c.esc_c()
                      << ": Пользователь с таким логином не зарегистрирован.\n"
                      << "Пройдите регистрацию в качестве нового пользователя..."
                      << std::endl;

            std::cout << c.esc_tb(ptl::Color::GREEN)
                      << "\nchat"
                      << c.esc_c()
                      << ": Регистрация пользователя..."
                      << std::endl;

            // ввод имени и его проверка на наличие в
            // статическом хранилище данных

            bool _isFlag { false };

            do {
                std::cout << "Имя: ";

                std::cout << c.esc_tb(ptl::Color::WHITE);
                std::cin.clear();
                std::cin >> _name;
                std::cout << c.esc_c();

                std::string _fName { };

                std::ifstream f("pshadow");

                if (f.is_open()) {
                    while (f) { // читаем до EOF или ошибки
                        std::getline(f, _fName, ':');
                        if (_fName == _name) {
                            std::cout << c.esc_tb(ptl::Color::GREEN)
                                      << "\nchat"
                                      << c.esc_c()
                                      << ": Такое имя уже существует..."
                                      << std::endl;
                            _isFlag = false;
                            break;
                        }
                        else {
                            _isFlag = true;
                        }
                    }
                   f.close();
                }
            }
            while (!_isFlag);

            // ввод логина и его проверка на наличие в
            // статическом хранилище данных

            _isFlag = false;

            do {
                std::cout << "Логин: ";

                std::cout << c.esc_tb(ptl::Color::WHITE);
                std::cin.clear();
                std::cin >> _login;
                std::cout << c.esc_c();

                std::string _fLogin { };

                std::ifstream f("pshadow");

                if (f.is_open()) {
                    while (f) { // читаем до EOF или ошибки
                        std::getline(f, _fLogin, ':');
                        if (_fLogin == _login) {
                            std::cout << c.esc_tb(ptl::Color::GREEN)
                                      << "\nchat"
                                      << c.esc_c()
                                      << ": Такой логин уже существует..."
                                      << std::endl;
                            _isFlag = false;
                            break;
                        }
                        else {
                            _isFlag = true;
                        }
                    }
                   f.close();
                }
            }
            while (!_isFlag);

            // вводим пароль

            std::cout << "Пароль: ";

            std::cout << "\033[?25l";
            std::cout << c.esc_tr(c.getbkgcolor());
            std::cin.clear();
            std::cin >> _password;
            std::cout << c.esc_c();
            std::cout << "\033[?25h";

            // прописываем нового пользователя в 
            // динамическое хранилище данных

            user._M_userLogin        = _login;
            user._M_userId           = (chat::last_uid() + 1);
            user._M_userHashPassword = sha.sha1(
                                           _password.c_str(), 
                                           sizeof(_password.c_str()) - 1
                                       );
            user._M_userName         = _name;

            // прописываем нового пользователя в 
            // статическое хранилище данных

            chat::writing_user_data(user);
        }
    }

//--------------------------------------------------------------------
    void 
    user_out_name(
        chat::User& user
        )
    {
        ptl::pColor c;

        std::cout << c.esc_tb(ptl::Color::WHITE)
                  << user._M_userName
                  << c.esc_c();
    }

//--------------------------------------------------------------------
    ptl::__u16
    mtin(
        chat::User&    user,
        chat::Message& msg
        )
    {
        ptl::pColor c;

        std::string _msgToWhom { }; // Кому предназначено сообщение
        std::string _msgText { };   // Текст сообщения
        bool        _isFlag { false };

        std::cout << std::endl;

        do {
            // ввод имени пользователя для которого преднозначено
            // сообщение
            std::cout << "к: ";
            std::cin.clear();
            std::cin >> _msgToWhom;

            // обработка введенных управляющих параметров
            if (_msgToWhom == "-h" || 
                _msgToWhom == "-H" || 
                _msgToWhom == "-?") {
                return chat::Parametr::HELP;
            }
            
            if (_msgToWhom == "-e" || 
                _msgToWhom == "-E") {
                return chat::Parametr::EDIT;
            }

            if (_msgToWhom == "-q" || 
                _msgToWhom == "-Q") {
                return chat::Parametr::QUIT;
            }

            // проверка наличия регистрации пользователя
            // для которого преднозначено сообщение
            if (chat::user_name_yn(_msgToWhom)) {
                // ввод сообщения
                std::cout << "ч: ";
                std::cin.ignore(INT_MAX, '\n');
                std::getline(std::cin, _msgText);

                // обработка введенных управляющих параметров
                if (_msgText == "-h" || 
                    _msgText == "-H" || 
                    _msgText == "-?") {
                    return chat::Parametr::HELP;
                }
            
                if (_msgText == "-e" || 
                    _msgText == "-E") {
                    return chat::Parametr::EDIT;
                }

                if (_msgText == "-q" || 
                    _msgText == "-Q") {
                    return chat::Parametr::QUIT;
                }

                msg._M_msgToWhom   = _msgToWhom;
                msg._M_msgFromWhom = user._M_userName;
                msg._M_msgText     = _msgText;

                _isFlag = true;
            }
            else {
                std::cout << c.esc_tb(ptl::Color::GREEN)
                          << "chat"
                          << c.esc_c()
                          << ": Пользователя с таким именем нет..."
                          << std::endl;            
                _isFlag = false;
            }
        }
        while (!_isFlag);

        return chat::Parametr::OK;
    }

//--------------------------------------------------------------------
    void 
    user_edit(
        chat::User& user
        )
    {
        std::string _passOld { };
        std::string _passNew { };

        ptl::pColor c;
        ptl::pSha   sha;

        std::cout << "\n"
                  << c.esc_tb(ptl::Color::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Редактирование данных пользователя "
                  << user._M_userName
                  << "..."
                  << std::endl;

        // запрос старого пароля пользователя
        std::cout << "Старый пароль: ";

        std::cout << "\033[?25l";
        std::cout << c.esc_tr(c.getbkgcolor());
        std::cin.clear();
        std::cin >> _passOld;
        std::cout << c.esc_c();
        std::cout << "\033[?25h";

        std::string _iHash = sha.sha1(
                                _passOld.c_str(), 
                                sizeof(_passOld.c_str()) - 1
                             );

        // проверка введенного старого пароля на идентичность
        while (_iHash != user._M_userHashPassword) {
            std::cout << c.esc_tb(ptl::Color::GREEN)
                      << "\nchat"
                      << c.esc_c()
                      << ": Пароль введен не верно..."
                      << std::endl;

            std::cout << "Старый пароль: ";

            std::cout << "\033[?25l";
            std::cout << c.esc_tr(c.getbkgcolor());
            std::cin.clear();
            std::cin >> _passOld;
            std::cout << c.esc_c();
            std::cout << "\033[?25h";

            _iHash = sha.sha1(
                        _passOld.c_str(), 
                        sizeof(_passOld.c_str()) - 1
                     );
        }

        // запрос нового пароля пользователя
        std::cout << "Новый пароль: ";

        std::cout << "\033[?25l";
        std::cout << c.esc_tr(c.getbkgcolor());
        std::cin.clear();
        std::cin >> _passNew;
        std::cout << c.esc_c();
        std::cout << "\033[?25h";

        std::string _oHash = sha.sha1(
                                _passNew.c_str(), 
                                sizeof(_passNew.c_str()) - 1
                             );
        user._M_userHashPassword = _oHash;

        // отписываем в хранилище измененные данные пользователя 
        chat::edit_user_data(user);
    }

} // namespace chat