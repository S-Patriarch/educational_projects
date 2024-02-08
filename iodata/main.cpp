/*++

    Copyright (c) S-Patriarch, 2023

    Программа пишит в файл при своей загрузке и считывает из файла
    состояние объектов классов User и Message (для каждого класса
    свой файл).
    
--*/

#include <iostream>
#include <fstream>
#include <string>

// Требуется компилятор поддерживающий стандарт C++17
//#include <filesystem>

#ifdef __linux__
#include "ptl/pconio.h"
#include "ptl/pexcept.h"
#elif _WIN32
#include "ptl\pconio.h"
#include "ptl\pexcept.h"
#endif

// Требуется компилятор поддерживающий стандарт C++17
//namespace fs = std::filesystem;

//////////////////////////////////////////////////////////////////////
class User
{
public:
    User(
        std::string _login,
        std::string _pass,
        std::string _name
        )
    : _M_login(_login)
    , _M_pass(_pass)
    , _M_name(_name)
    { }

    ~User() = default;

    std::string get_user_login() { return _M_login; }
    std::string get_user_pass()  { return _M_pass; }
    std::string get_user_name()  { return _M_name; }

    void set_user_login(std::string _str) { _M_login = _str; }
    void set_user_pass(std::string _str)  { _M_pass = _str; }
    void set_user_name(std::string _str)  { _M_name = _str; }

private:
    std::string _M_login; // логин пользователя
    std::string _M_pass;  // пароль пользователя
    std::string _M_name;  // имя пользователя
};

//--------------------------------------------------------------------
class Message
{
public:
    Message(
        std::string _sender,
        std::string _receiver,
        std::string _text
        )
    : _M_sender(_sender)
    , _M_receiver(_receiver)
    , _M_text(_text)
    { }

    ~Message() = default;

    std::string get_mess_sender()   { return _M_sender; }
    std::string get_mess_receiver() { return _M_receiver; }
    std::string get_mess_text()     { return _M_text; }

    void set_mess_sender(std::string _str)   { _M_sender = _str; }
    void set_mess_receiver(std::string _str) { _M_receiver = _str; }
    void set_mess_text(std::string _str)     { _M_text = _str; }

private:
    std::string _M_sender;   // отправитель сообщения
    std::string _M_receiver; // приемник сообщения
    std::string _M_text;     // текст сообщения
};

//////////////////////////////////////////////////////////////////////
int main()
{
    ptl::setlocale_WIN32_rus();
    ptl::clrscr();

    User    ou("alex", "alex123", "Алексей");
    Message om("Алексей", "Patriarch", "Тестовое сообщение...");

    try {
        std::string _str { };

        //
        // Отписываем данные в файл users.
        //

        std::ofstream ofsu("users", std::ios::app);

        // Устанавливаем права доступа к файлу.
        // Требуется компилятор поддерживающий стандарт C++17
        //
        //fs::permissions(
        //    "users",
        //    fs::perms::owner_read | fs::perms::owner_write,
        //    fs::perm_options::replace
        //);

        if (!ofsu.is_open()) {
            throw 
            ptl::pException("E: Файл users не открыт.");
        }

        std::cout << "Отписываем данные в файл users...\n";
        ofsu << ou.get_user_login() << ':'
             << ou.get_user_pass()  << ':'
             << ou.get_user_name()  << ':';
        std::cout << "Данные отписаны.\n";

        ofsu.close();

        //
        // Отписываем данные в файл messages.
        //

        std::ofstream ofsm("messages", std::ios::app);

        // Устанавливаем права доступа к файлу.
        // Требуется компилятор поддерживающий стандарт C++17
        //
        //fs::permissions(
        //    "messages",
        //    fs::perms::owner_read | fs::perms::owner_write,
        //    fs::perm_options::replace
        //);

        if (!ofsm.is_open()) {
            throw 
            ptl::pException("E: Файл messages не открыт.");
        }

        std::cout << "Отписываем данные в файл messages...\n";
        ofsm << om.get_mess_sender()   << ':'
             << om.get_mess_receiver() << ':'
             << om.get_mess_text()     << ':';
        std::cout << "Данные отписаны.\n";

        ofsm.close();

        //
        // Считываем данные из файла users.
        //

        std::ifstream ifsu("users");

        if (!ifsu.is_open()) {
            throw 
            ptl::pException("E: Файл users не открыт.");
        }

        std::cout << "Считываем данные из файла users...\n";
        std::getline(ifsu, _str, ':');
        ou.set_user_login(_str);
        std::getline(ifsu, _str, ':');
        ou.set_user_pass(_str);
        std::getline(ifsu, _str, ':');
        ou.set_user_name(_str);
        std::cout << "Данные считаны.\n";

        ifsu.close();
        
        //
        // Считываем данные из файла messages.
        //

        std::ifstream ifsm("messages");

        if (!ifsm.is_open()) {
            throw 
            ptl::pException("E: Файл messages не открыт.");
        }

        std::cout << "Считываем данные из файла messages...\n";
        std::getline(ifsm, _str, ':');
        om.set_mess_sender(_str);
        std::getline(ifsm, _str, ':');
        om.set_mess_receiver(_str);
        std::getline(ifsm, _str, ':');
        om.set_mess_text(_str);
        std::cout << "Данные считаны.\n";

        ifsm.close();

        //
        // Удаляем файлы данных.
        //

        std::remove("users");
        std::remove("messages");

        //
        // Выводим считанные данные в терминал.
        //

        std::cout << "\nДанные файла users:\n";
        std::cout << ou.get_user_login() << " : "
                  << ou.get_user_pass()  << " : "
                  << ou.get_user_name()  << '\n';

        std::cout << "\nДанные файла messages:\n";
        std::cout << om.get_mess_sender()   << " : "
                  << om.get_mess_receiver() << " : "
                  << om.get_mess_text()     << '\n';
    }
    catch (std::exception& ex) {
        std::cout << ex.what() 
                  << std::endl;
    }

    return 0;
}