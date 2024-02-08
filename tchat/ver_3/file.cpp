/*++

    Copyright (c) S-Patriarch, 2023

    Реализация функций работающих с файлами статического 
    хранилища чата.

--*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#ifdef __linux__
#include "ptl/pcolor.h"
#include "ptl/pexcept.h"
#elif _WIN32
#include "ptl\pcolor.h"
#include "ptl\pexcept.h"
#endif

#include "struct.h"

//////////////////////////////////////////////////////////////////////
namespace chat
{
//--------------------------------------------------------------------
    bool 
    file_test(
        const std::string& _fileName
        )
    {
        std::ifstream f(_fileName);

        if (!f.is_open()) {
            return false;
        }

        f.close();
        return true;
    }

//--------------------------------------------------------------------
    void 
    file_creat(
        const std::string& _fileName
        )
    {
        std::ofstream f(_fileName, std::ios::app);

        if (!f.is_open()) {
            throw
            ptl::pException("E: Не могу открыть файл."); 
        }

        f.close();
    }

//--------------------------------------------------------------------
    bool
    user_name_yn(
        const std::string& _iName
        )
    {
        std::string _str { };
        bool        _isReturn { false };

        std::ifstream f("pshadow");

        while (f) { // читаем до EOF или ошибки
            std::getline(f, _str, ':');
            std::getline(f, _str, ':');
            std::getline(f, _str, ':');
            std::getline(f, _str, ':');

            if (_str == _iName) {
                _isReturn = true;
                break;
            }
        }

        f.close();
        return _isReturn;
    }

//--------------------------------------------------------------------
    bool
    reading_user_data(
        chat::User&        user,
        const std::string& _iLogin
        )
    {
        bool _isReturn { false };

        std::ifstream f("pshadow");

        if (!f.is_open()) {
            return _isReturn;
        }

        std::string _str { };

        while (f) { // читаем до EOF или ошибки
            std::getline(f, _str, ':');

            if (_str == _iLogin) {
                user._M_userLogin = _str;
                
                std::getline(f, _str, ':');
                user._M_userId = std::stoul(_str);
                std::getline(f, _str, ':');
                user._M_userHashPassword = _str;
                std::getline(f, _str, ':');
                user._M_userName = _str;

                _isReturn = true;
                break;
            }
        }

        f.close();
        return _isReturn;
    }

//--------------------------------------------------------------------
    bool
    writing_user_data(
        chat::User& user
        )
    {
        bool _isReturn { false };

        std::ofstream f("pshadow", std::ios::app);

        if (f.is_open()) {
            f << user._M_userLogin        << ':'
              << user._M_userId           << ':'
              << user._M_userHashPassword << ':'
              << user._M_userName         << ':';

            f.close();
            _isReturn = true;
        } 

        return _isReturn;
    }

//--------------------------------------------------------------------
    bool
    edit_user_data(
        chat::User& user
        )
    {
        bool _isReturn { false };

        std::fstream f("pshadow", std::ios::in | std::ios::out);

        if (!f.is_open()) {
            return _isReturn;
        }

        std::string _str { };

        while (f) { // читаем до EOF или ошибки
            std::getline(f, _str, ':');

            if (_str == user._M_userLogin) {
                std::getline(f, _str, ':');

                f.seekp(f.tellg());
                f << user._M_userHashPassword;

                _isReturn = true;
                break;
            }
            else {
                std::getline(f, _str, ':');
                std::getline(f, _str, ':');
                std::getline(f, _str, ':');
            }
        }

        f.close();
        return _isReturn;
    }

//--------------------------------------------------------------------
    ptl::__u32 
    last_uid()
    {
        ptl::__u32 _lastId { 0 };

        std::ifstream f("pshadow");

        if (!f.is_open()) {
            return _lastId;
        }

        std::string _str { };

        while (f) { // читаем до EOF или ошибки
            for (ptl::__u16 i = 0; i < 4; ++i) {
                std::getline(f, _str, ':');
            }
            if (_str != "") {
                ++_lastId;
            }
        }

        f.close();
        return _lastId;
    }

//--------------------------------------------------------------------
    bool 
    mcheck(
        chat::User& user
        )
    {
        bool        _isReturn { false };
        std::string _str { };

        std::ifstream f("pmsg");

        while (f) { // читаем до EOF или ошибки
            std::getline(f, _str, ':');

            if (_str == user._M_userName) {
                _isReturn = true;
                break;
            }

            std::getline(f, _str, ':');
            std::getline(f, _str, ':');
        }

        f.close();
        return _isReturn;
    }

//--------------------------------------------------------------------
    void 
    mtout(
        chat::User& user
        )
    {
        ptl::pColor c;
        std::string _str { };

        std::ifstream f("pmsg");

        std::cout << c.esc_tb(ptl::Color::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Для вас есть сообщения..."
                  << std::endl;

        while (f) { // читаем до EOF или ошибки
            std::getline(f, _str, ':');

            if (_str == user._M_userName) {
                std::getline(f, _str, ':'); // от кого сообщение
                std::cout << c.esc_tb(ptl::Color::CYAN)
                          << _str
                          << c.esc_c();

                std::getline(f, _str, ':'); // сообщение
                std::cout << ": "
                          << _str
                          << std::endl;
            }
            else {
                std::getline(f, _str, ':');
                std::getline(f, _str, ':');
            }
        }

        f.close();
    }

//--------------------------------------------------------------------
    bool 
    mfout(
        chat::Message& msg
        )
    {
        bool _isReturn { false };

        std::ofstream f("pmsg", std::ios::app);

        if (f.is_open()) {
            f << msg._M_msgToWhom   << ':'
              << msg._M_msgFromWhom << ':'
              << msg._M_msgText     << ':';

            f.close();
            _isReturn = true;
        } 

        return _isReturn;
    }

//--------------------------------------------------------------------
    void
    mclear(
        chat::User&    user,
        chat::Message& msg
        )
    {
        std::ifstream pmsg("pmsg");
        std::ofstream tmsg("tmsg", std::ios::app);

        while (std::getline(pmsg, msg._M_msgToWhom, ':')) {
            std::getline(pmsg, msg._M_msgFromWhom, ':');
            std::getline(pmsg, msg._M_msgText, ':');

            if (msg._M_msgToWhom != user._M_userName) {
                tmsg << msg._M_msgToWhom   << ':'
                     << msg._M_msgFromWhom << ':'
                     << msg._M_msgText     << ':';
            }
        }

        pmsg.close();
        tmsg.close();

        std::remove("pmsg");
        std::rename("tmsg", "pmsg");
    }

} // namespace chat