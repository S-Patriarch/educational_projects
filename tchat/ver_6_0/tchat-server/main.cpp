/*++

    Copyright (c) S-Patriarch, 2023

    Терминальный чат.
    Версия 6.0 SERVER
    
--*/

#include <iostream>
#include <exception>
#include <string>
#include <cstring>
#include <iomanip>
#include <vector>
#include <sstream>

#include "/usr/include/mysql/mysql.h"

#include "ptl/pTCPServer.h"
#include "ptl/ptype.h"
#include "ptl/pconio.h"
#include "ptl/pcolor.h"
#include "ptl/psha.h"
#include "ptl/pexcept.h"

#include "../cst.h"
#include "../info.h"

ptl::pTCPServer tcp;

//////////////////////////////////////////////////////////////////////
int main()
{
    MYSQL      mysql; // структура, представляющая дескриптор соединения
    MYSQL_RES* res;   // структура, содержащая результат запроса
    MYSQL_ROW  row;   // структура, представляющая данные одной строки

    ptl::pColor c;
    ptl::pSha   sha;

    try {
        ptl::clrscr();
        chat::get_logo();

        std::cout << c.esc_tb(ptl::Color::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Жду подключения клиента..."
                  << std::endl;

        // SERVER
        // создание сокета, привязка сокета, 
        // постановка сервера на прием данных
        tcp.setup(53333);

        std::cout << c.esc_tb(ptl::Color::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Клиент подключен"
                  << std::endl;

        std::string queryString_ {};
        std::string idUser_ {};
        std::string userName_ {};
        std::string userFamaly {};

        std::string strSend_ {"E:"};
        std::string strRead_ {};

        // ждем запрос клиента
        // на соответствие логина клиента
        strRead_ = tcp.read();

        if (std::strncmp("-q", strRead_.c_str(), 2) == 0 ||
            std::strncmp("-Q", strRead_.c_str(), 2) == 0) {

            std::cout << std::endl;
            std::cout << c.esc_tb(ptl::Color::GREEN)
                      << "chat"
                      << c.esc_c()
                      << ": Клиент покинул чат\n"
                      << c.esc_tb(ptl::Color::GREEN)
                      << "chat"
                      << c.esc_c()
                      << ": Сервер завершает работу..."
                      << std::endl;

            std::cout << std::endl;
            std::cout << c.esc_tb(ptl::Color::GREEN)
                      << "chat"
                      << c.esc_c()
                      << ": До новых встреч "
                      << std::endl;

            // закрываем сокет, завершаем соединение
            tcp.exit();

            ptl::scrs();
            return 0;
        }

        // разбиваем полученную строку от клиента на подстроки
        std::vector<std::string> subStrings_ {};
        std::istringstream iss(strRead_);
        std::string subString_ {};

        while (std::getline(iss, subString_, '|')) {
            subStrings_.push_back(subString_);
        }

        std::cout << c.esc_tb(ptl::Color::GREEN)
                  << "chat"
                  << c.esc_c()
                  << ": Вход пользователя "
                  << subStrings_[0]
                  << "..."
                  << std::endl;

        std::string iHash_ = sha.sha1(
                                 subStrings_[1].c_str(),
                                 sizeof(subStrings_[1].c_str()) - 1
                             );

        // инициализируем базу данных и
        // устанавливаем соединение с tchatdb

        mysql_init(&mysql);

        mysql_real_connect(
            &mysql,
            "127.0.0.1", "root", "ZZzz1122+", "tchatdb", 0, NULL, 0
        );

        mysql_set_character_set(&mysql, "utf8");

        queryString_ =
            "SELECT * FROM пользователь "
            "WHERE email_пользователя = \'" + subStrings_[0] + "\'";

        mysql_query(&mysql, queryString_.c_str());

        res = mysql_store_result(&mysql);
        row = mysql_fetch_row(res);

        if (row != NULL) {
            if (subStrings_[0] == row[3]) {
                idUser_    = row[0];
                userName_  = row[1];

                if (row[2] != NULL) {
                    userFamaly = row[2];
                }

                mysql_free_result(res);

                queryString_ =
                    "SELECT * FROM shadow "
                    "WHERE id_пользователя = " + idUser_;

                mysql_query(&mysql, queryString_.c_str());

                res = mysql_store_result(&mysql);
                row = mysql_fetch_row(res);

                if (row[1] == iHash_) {
                    strSend_ = (idUser_ + "|" + userName_ + "|" + userFamaly + "|");
                    std::cout << c.esc_tb(ptl::Color::GREEN)
                              << "chat"
                              << c.esc_c()
                              << ": Успешно"
                              << std::endl;
                }

                mysql_free_result(res);
            }
        }

        tcp.Send(strSend_);

        strRead_ = tcp.read();

        if (strRead_ == chat::GIVE_ME_MESSAGES_FROM_THE_DATABASE) {
            queryString_ =
                "SELECT * FROM сообщение "
                "WHERE id_получателя = " + idUser_;

            mysql_query(&mysql, queryString_.c_str());

            std::string str1_ {};
            std::string str2_ {};

            strSend_ = "";
            if (res = mysql_store_result(&mysql)) {
                while (row = mysql_fetch_row(res)) {
                    str1_ = row[4];
                    str2_ = row[3];
                    strSend_ += (str1_ + " : " + str2_ + "|");
                }
            }
            else {
                strSend_ = "E:";
            }

            mysql_free_result(res);

            tcp.Send(strSend_);
        }

        mysql_close(&mysql);

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
              << ": Сервер завершает работу...\n"
              << c.esc_tb(ptl::Color::GREEN)
              << "chat"
              << c.esc_c()
              << ": До новых встреч "
              << std::endl;

    ptl::scrs();
    return 0;
}
