// user.h -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Заголовочный файл с описанием класса реализующего 
 * работу с пользователем чата.
 */

#pragma once
#ifndef _CHAT_USER
#define _CHAT_USER

#include "cst.h"
#include <string>

namespace chat
{
  class User
  {
  private:
    std::string  _M_name{ };     // Имя пользователя
    std::string  _M_login{ };    // Логин пользователяo
    std::string  _M_password{ }; // Пароль пользователя
    ptl::__u32   _M_id{ };       // ID пользователя

    // Количество сообщений для пользователя
    ptl::__u16   _M_msg_quantity{ }; 

    struct Messages
    {
      std::string  _S_name{ }; // Имя отправителя сообщения
      std::string  _S_msg{ };  // Текст сообщения
    };

    Messages __msg[_Quantity_Messages];

  public:
    User() = default;
    ~User() = default;

    /** Устанавливает параметры пользователя
     */
    auto
    set_user(const std::string&, const std::string&, 
             const std::string&, ptl::__u32) -> void;

    auto
    set_user_password(const std::string& __password_new) -> void
    { _M_password = __password_new; }

    auto
    get_user_name() -> std::string
    { return _M_name; }

    auto
    get_user_login() -> std::string
    { return _M_login; }

    auto
    get_user_password() -> std::string
    { return _M_password; }

    auto
    get_user_id() -> ptl::__u32
    { return _M_id; }

    auto
    set_msg_quantity(ptl::__u16 __quantity) -> void
    { _M_msg_quantity = __quantity; }

    auto
    get_msg_quantity() -> ptl::__u16
    { return _M_msg_quantity; }

    auto
    clear_msg_quantity() -> void
    { _M_msg_quantity = 0; }

    /** Выводит в терминал (консоль) имя пользователя.
     */
    auto
    out_user_name() -> void;

    /** Записывает посланное __whom сообщение __what.
     */
    auto
    record_message(const std::string&, const std::string&) -> void;

    /** Вывод входящих сообщение.
     */
    auto
    out_message() -> void;
  };

} // namespace chat 

#endif // _CHAT_USER