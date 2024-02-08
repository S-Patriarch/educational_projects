/*++

    Copyright (c) S-Patriarch, 2023

    Терминальный чат.
    Версия 6.0 CLIENT

--*/

#include <iostream>
#include <exception>
#include <string>
#include <cstring>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <sstream>

#include "ptl/pTCPClient.h"
#include "ptl/ptype.h"
#include "ptl/pconio.h"
#include "ptl/pcolor.h"
#include "ptl/pexcept.h"

#include "../cst.h"
#include "../sct.h"
#include "../info.h"

ptl::pTCPClient tcp;

//--------------------------------------------------------------------
// Функция удаляет последний символ '\n' из переданной строки.
//
std::string Substr(std::string str_)
{
    // находим позицию последнего символа, отличного от '\n'
    std::size_t found_ = str_.find_last_not_of("\n");

    // если такой символ найден, удаляем символы после него
    if (found_ != std::string::npos) {
        str_ = str_.substr(0, found_+1);
    }

    return str_;
}

//////////////////////////////////////////////////////////////////////
int main()
{
    ptl::pColor c;
    chat::User  user;

    try {
        ptl::clrscr();
        chat::get_logo();

        // CLIENT
        // создание сокета,
        // установка соединения с сервером
        tcp.setup("127.0.0.1", 53333);

        std::cout << c.esc_tb(ptl::Color::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Соединение с сервером установлено\n"
                  << std::endl;

        std::string strRead_ {};
        std::string strSend_ {};

        std::cout << c.esc_tb(ptl::Color::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Авторизация пользователя..."
                  << std::endl;

        // ввод логина пользователя
        std::cout << "Электронная почта: ";

        std::memset(&chat::msg_[0], 0, sizeof(chat::msg_));

        std::cout << c.esc_tb(ptl::Color::WHITE);
        fgets(chat::msg_, sizeof(chat::msg_), stdin);
        std::cout << c.esc_c();

        strSend_ = ::Substr(chat::msg_) + "|";

        // ввод пароля
        std::cout << "Пароль: ";

        std::memset(&chat::msg_[0], 0, sizeof(chat::msg_));

        std::cout << "\033[?25l";
        std::cout << c.esc_tr(c.getbkgcolor());
        fgets(chat::msg_, sizeof(chat::msg_), stdin);
        std::cout << c.esc_c();
        std::cout << "\033[?25h";

        strSend_ += ::Substr(chat::msg_) + "|";

        tcp.Send(strSend_);

        // получаем ответ сервера
        strRead_ = tcp.read();

        // разбиваем полученную строку от сервера на подстроки
        std::vector<std::string> subStrings_ {};
        std::istringstream iss(strRead_);
        std::string subString_ {};

        while (std::getline(iss, subString_, '|')) {
            subStrings_.push_back(subString_);
        }

        user.s_userID     = subStrings_[0];
        user.s_userName   = subStrings_[1];
        user.s_userFamaly = subStrings_[2];

        ptl::hcrs();

        std::cout << std::endl;
        std::cout << c.esc_tb(ptl::Color::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Добро пожаловать "
                  << user.s_userName
                  << " "
                  << user.s_userFamaly
                  << std::endl;

        tcp.Send(chat::GIVE_ME_MESSAGES_FROM_THE_DATABASE);

        strRead_ = tcp.read();

        if (strRead_ != "E:") {
            std::cout << std::endl;
            std::cout << c.esc_tb(ptl::Color::GREEN)
                      << "chat"
                      << c.esc_c()
                      << ": Для Вас есть сообщения..."
                      << std::endl;

            // разбиваем полученную строку от сервера на подстроки
            std::vector<std::string> subStrings__ {};
            std::istringstream iss_(strRead_);
            std::string subString__ {};

            while (std::getline(iss_, subString__, '|')) {
                subStrings__.push_back(subString__);
            }

            for (const auto& sub : subStrings__) {
                std::cout << sub << std::endl;
            }
        }

        tcp.Send("-q");

    }
    catch (std::exception& ex) {
        std::cout << ex.what()
                  << std::endl;
    }

    // закрываем сокет, завершаем соединение
    tcp.exit();

    std::cout << std::endl;
    std::cout << c.esc_tb(ptl::Color::GREEN)
              << "chat"
              << c.esc_c()
              << ": До новых встреч "
              << user.s_userName
              << " "
              << user.s_userFamaly
              << std::endl;

    ptl::scrs();
    return 0;
}
