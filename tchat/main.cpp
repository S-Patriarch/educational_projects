// main.cpp -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Терминальный чат.
 *
 * Итоговый проект по блоку 'Основные конструкции С++'
 * курса SkillFactory 'Разработчик на С++'.
 *
 */

#include "cst.h"
#include "user.h"

#ifdef _WIN32
#include "ptl\ptype.h"
#include "ptl\pconio.h"
#include "ptl\pcolor.h"
#include "ptl\pvector.h"
#else
#include "ptl/ptype.h"
#include "ptl/pconio.h"
#include "ptl/pcolor.h"
#include "ptl/pvector.h"
#endif

#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <climits>

namespace chat
{
  ptl::__u32  ID{ 0 }; // ID пользователя

  /** Определение функций.
   */
  auto get_info() -> void;
  auto user_authorization(ptl::pvector<chat::User>&) -> void;
  auto check_out_message(ptl::pvector<chat::User>&) -> void;
  auto in_record_message(ptl::pvector<chat::User>&) -> ptl::__u16;
  auto user_edit(ptl::pvector<chat::User>&) -> void;

} // namespace chat 

/*
 * Точка входа...
 */ 
auto
main() -> int
{
  ptl::setconsole_WIN32_rus();

  chat::get_info();

  try
    {
      ptl::pcolor __c;

      /** Создаем динамическое хранилище пользователей чата.
       */
      ptl::pvector<chat::User> __user(chat::ID+1);

      /** Добавляем одного (первого) пользователя с ID:1, чтоб был.
       */
      __user[chat::ID].set_user(
          "Patriarch", 
          "apsk0529-2@mail.ru", 
          "QQqq1122+", 
          chat::ID+1);

      ptl::clrscr();
      chat::get_info();

      /** Запускаем процедуру авторизации / регистрации пользователя.
       */
      chat::user_authorization(__user);

      bool __flag{ true };
      ptl::__u16 __parametr{ chat::_Ok };

      while (__flag)
        {
          /** Приглашаем авторизовавшегося / зарегистрировавшегося 
           *  пользователя к дальнейшей работе в чате.
           */

          if (__parametr != chat::_Help)
            ptl::clrscr();

          std::cout
            << __c.esc_tb( ptl::GREEN )
            << "chat"
            << __c.esc_c()
            << ": Добро пожаловать "
            << __user[chat::ID-1].get_user_name()
            << "..."
            << std::endl;

          /** Процесс обмена сообщениями.
           */
          do
            {
              std::cout << std::endl;
              chat::check_out_message(__user);
              __user[chat::ID-1].out_user_name();
              __parametr = chat::in_record_message(__user);
            }
          while (__parametr == chat::_Ok);

          /**  Обработка управляющих параметров чата.
           */

          /** Помощь.
           */
          if (__parametr == chat::_Help) 
            {
              ptl::clrscr();
              chat::get_info();
            }

          /** Смена пользователя.
           */
          if (__parametr == chat::_Change) 
            {
              ptl::clrscr();
              chat::user_authorization(__user);
            }

          /** Редактирование данных пользователя.
           */
          if (__parametr == chat::_Edit) 
            {
              chat::user_edit(__user);
            }

          /** Завершение работы чата.
           */
          if (__parametr == chat::_Quit) 
            {
              std::cout << std::endl;
              std::cout
                << __c.esc_tb( ptl::GREEN )
                << "chat"
                << __c.esc_c()
                << ": До новых встреч "
                << __user[chat::ID-1].get_user_name()
                << "..."
                << std::endl;
              __flag = false;
            }
        }
    }
  catch (std::exception& __ex)
    {
      std::cout
        << __ex.what()
        << std::endl;
    }

  return 0;
}

namespace chat
{
  /* 
   * Функция выводит информацию об управляющих
   * параметрах работы чата.
   */
  auto
  get_info() -> void
  {
    std::cout
      << "tchat 1.0\n"
      << "Использование:\n"
      << "  User\n"
      << "  к: [имя пользователя] или [параметр]\n"
      << "  ч: [сообщение для пользователя] или [параметр]\n\n"
      << "Параметры:\n"
      << "  -h, -?  вызов информации о параметрах чата\n"
      << "  -c      сменить пользователя чата\n"
      << "  -e      редактировать данные пользователя чата\n"
      << "  -q      завершить работу чата\n"
      << "  --all   сообщение для всех пользователей чата\n"
      << std::endl;
  }

  /*
   * Функция авторизации пользователя.
   * Устанавливает ID авторизованного или вновь зарегистрированного
   * пользователя.
   */
  auto
  user_authorization(ptl::pvector<chat::User>& __user) -> void
  {
    std::string __name{ };
    std::string __login{ };
    std::string __password{ };

    ptl::pcolor __c;

    chat::ID = 0;

    std::cout
      << __c.esc_tb( ptl::GREEN )
      << "chat"
      << __c.esc_c()
      << ": Авторизация пользователя..."
      << std::endl;

    /** Ввод логина пользователя.
     */
    std::cout
      << "Логин: ";

    std::cout << __c.esc_tb( ptl::WHITE );
    std::cin.clear();
    std::cin >> __login;
    std::cout << __c.esc_c();

    /** Проверка введенного логина на наличие.
     */
    for (ptl::__u32 __i{0}; __i < __user.size(); ++__i)
      {
        bool __flag{ false };
        if (__user[__i].get_user_login() == __login)
          {
            chat::ID = __user[__i].get_user_id();
            __flag   = true;
          }

        if (__flag) break;
      }

    if (chat::ID != 0)
      {
        /** Если введенный логин найден среди зарегистрированных
         *  пользователей чата, то проводим идентификацию пароля
         *  данного пользователя.
         */

        /** Ввод пароля пользователя.
         */
        std::cout
          << "Пароль: ";

        std::cout << __c.esc_tb( ptl::WHITE );
        std::cin.clear();
        std::cin >> __password;
        std::cout << __c.esc_c();

        /** Проверка введенного пароля на идентичность.
         */
        while (__user[chat::ID-1].get_user_password() != __password)
          {
            std::cout
              << __c.esc_tb( ptl::GREEN )
              << "\nchat"
              << __c.esc_c()
              << ": Пароль введен не верно..."
              << std::endl;

            std::cout
              << "Пароль: ";

            std::cout << __c.esc_tb( ptl::WHITE );
            std::cin.clear();
            std::cin >> __password;
            std::cout << __c.esc_c();
          }
      }
    else
      { 
        /** Если введенный логин не найден среди зарегистрированных
         *  пользователей чата, то проводим процедуру регистрацию в
         *  качестве нового пользователя.
         */

        std::cout
          << __c.esc_tb( ptl::GREEN )
          << "\nchat"
          << __c.esc_c()
          << ": Пользователь с таким логином не зарегистрирован.\n"
          << "Пройдите регистрацию в качестве нового пользователя..."
          << std::endl;

        std::cout
          << __c.esc_tb( ptl::GREEN )
          << "\nchat"
          << __c.esc_c()
          << ": Регистрация пользователя..."
          << std::endl;

        /** Ввод имени и его проверка на наличие.
         */
        bool __flag{ false };
        do
          {
            std::cout
              << "Имя: ";
            std::cout << __c.esc_tb( ptl::WHITE );
            std::cin.clear();
            std::cin >> __name;
            std::cout << __c.esc_c();

            for (ptl::__u32 __i{0}; __i < __user.size(); ++__i)
              {
                if (__user[__i].get_user_name() != __name)
                  {
                    __flag = true;
                  }
                else
                  {
                    std::cout
                      << __c.esc_tb( ptl::GREEN )
                      << "\nchat"
                      << __c.esc_c()
                      << ": Такое имя уже существует..."
                      << std::endl;

                    __flag = false;
                    break;
                  }
              }
          }
        while (!__flag);

        /** Ввод логина и его проверка на наличие.
         */
        __flag = false;
        do
          {
            std::cout
              << "Логин: ";
            std::cout << __c.esc_tb( ptl::WHITE );
            std::cin.clear();
            std::cin >> __login;
            std::cout << __c.esc_c();

            for (ptl::__u32 __i{0}; __i < __user.size(); ++__i)
              {
                if (__user[__i].get_user_login() != __login)
                  {
                    __flag = true;
                  }
                else
                  {
                    std::cout
                      << __c.esc_tb( ptl::GREEN )
                      << "\nchat"
                      << __c.esc_c()
                      << ": Такой логин уже существует..."
                      << std::endl;

                    __flag = false;
                    break;
                  }
              }
          }
        while (!__flag);

        std::cout
          << "Пароль: ";
        std::cout << __c.esc_tb( ptl::WHITE );
        std::cin.clear();
        std::cin >> __password;
        std::cout << __c.esc_c();

        /** Прописываем нового пользователя в динамическое
         *  хранилище пользователей.
         */
        __user.resize(__user.size() + 1);
        chat::ID = __user.size();
        __user[chat::ID-1].set_user(__name, __login, __password, chat::ID);
      }
  }

  /*
   * Функция проверяет наличие сообщений для авторизованного 
   * пользователя и при их наличии выводит в терминал.
   */
  auto
  check_out_message(ptl::pvector<chat::User>& __user) -> void
  {
    ptl::pcolor __c;

    if (__user[chat::ID-1].get_msg_quantity() != 0)
      {
        std::cout
          << __c.esc_tb( ptl::GREEN )
          << "chat"
          << __c.esc_c()
          << ": Для вас есть сообщения..."
          << std::endl;

        __user[chat::ID-1].out_message();
        __user[chat::ID-1].clear_msg_quantity();
      }
    else
      {
        std::cout
          << __c.esc_tb( ptl::GREEN )
          << "chat"
          << __c.esc_c()
          << ": Для вас нет сообщений..."
          << std::endl;
      }
  }

  /*
   * Функция запрашивает для кого сообщение, само сообщение и
   * пулученную информацию отписывает пользователю для
   * которого она предназначена.
   * Возвращает chat::_Ok при нормальном завершении работы или
   * один из управляющих параметров.
   */
  auto
  in_record_message(ptl::pvector<chat::User>& __user) -> ptl::__u16
  {
    std::string __whom{ }; // Кому предназначено сообщение
    std::string __what{ }; // Текст сообщения

    ptl::pcolor __c;

    std::cout << std::endl;

    bool __flag{ true };
    do
      {
        /** Ввод имени пользователя для которого преднозначено
         *  сообщение.
         */
        std::cout << "к: ";
        std::cin.clear();
        std::cin >> __whom;

        /** Обработка введенных управляющих параметров.
         */
        if (__whom == "-h" || __whom == "-H" || __whom == "-?")
          return chat::_Help;

        if (__whom == "-c" || __whom == "-C")
          return chat::_Change;

        if (__whom == "-e" || __whom == "-E")
          return chat::_Edit;

        if (__whom == "-q" || __whom == "-Q")
          return chat::_Quit;

        /** Проверка введенного имени пользователя на наличие/
         */
        if (__whom == "--all")
          {
            __flag = false;
          }
        else
          for (ptl::__u32 __i{0}; __i < __user.size(); ++__i)
            {
              if (__user[__i].get_user_name() == __whom)
                {
                  __flag = false;
                  break;
                }
            }

        if (__flag == true)
          {
            std::cout
              << __c.esc_tb( ptl::GREEN )
              << "chat"
              << __c.esc_c()
              << ": Пользователя с таким именем нет..."
              << std::endl;            
          }
      }
    while (__flag);

    /** Ввод сообщения.
     */
    std::cout << "ч: ";
    std::cin.ignore(INT_MAX, '\n');
    std::getline(std::cin, __what);

    /** Повторная обработка введенных управляющих параметров.
     */
    if (__what == "-h" || __what == "-H" || __what == "-?")
      return chat::_Help;

    if (__what == "-c" || __what == "-C")
      return chat::_Change;

    if (__what == "-e" || __what == "-E")
      return chat::_Edit;

    if (__what == "-q" || __what == "-Q")
      return chat::_Quit;

    /** Проверка логина и запись сообщения.
     */
    if (__whom == "--all")
      {
        for (ptl::__u32 __i{0}; __i < __user.size(); ++__i)
          {
            if (__user[__i].get_user_name() != __user[chat::ID-1].get_user_name())
              {
                __user[__i].record_message(
                    __user[chat::ID-1].get_user_name(), 
                    __what);
              }
          }
      }
    else 
      {
        bool __flag{ false };
        for (ptl::__u32 __i{0}; __i < __user.size(); ++__i)
          {
            if (__user[__i].get_user_name() == __whom)
              {
                __user[__i].record_message(
                    __user[chat::ID-1].get_user_name(), 
                    __what);

                __flag = true;
              }

            if (__flag) break;
          }
      }

    return chat::_Ok;
  }

  /*
   * Функция редактирует данные пользователя.
   * Редактирование заключается в смене пароля пользователя.
   */
  auto
  user_edit(ptl::pvector<chat::User>& __user) -> void
  {
    std::string __password_old{ };
    std::string __password_new{ };

    ptl::pcolor __c;

    std::cout
      << '\n'
      << __c.esc_tb( ptl::GREEN )
      << "chat"
      << __c.esc_c()
      << ": Редактирование данных пользователя "
      << __user[chat::ID-1].get_user_name()
      << "..."
      << std::endl;

    /** Запрос старого пароля пользователя.
     */
    std::cout
      << "Старый пароль: ";

    std::cout << __c.esc_tb( ptl::WHITE );
    std::cin.clear();
    std::cin >> __password_old;
    std::cout << __c.esc_c();

    /** Проверка введенного пароля на идентичность.
     */
    while (__user[chat::ID-1].get_user_password() != __password_old)
      {
        std::cout
          << __c.esc_tb( ptl::GREEN )
          << "\nchat"
          << __c.esc_c()
          << ": Пароль введен не верно..."
          << std::endl;

        std::cout
          << "Старый пароль: ";

        std::cout << __c.esc_tb( ptl::WHITE );
        std::cin.clear();
        std::cin >> __password_old;
        std::cout << __c.esc_c();
      }

    /** Запрос нового пароля пользователя.
     */
    std::cout
      << "Новый пароль: ";

    std::cout << __c.esc_tb( ptl::WHITE );
    std::cin.clear();
    std::cin >> __password_new;
    std::cout << __c.esc_c();
    
    /** Отписываем в хранилище измененные данные пользователя.
     */
    __user[chat::ID-1].set_user_password(__password_new);
  }

} // namespace chat