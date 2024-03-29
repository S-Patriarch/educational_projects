/*++

    Copyright (c) S-Patriarch, 2023

    Определение функций, реализующих работу с файлами статического
    хранилища чата.

--*/

#ifndef __CHAT_FILE_H__
#define __CHAT_FILE_H__

#ifdef _WIN32
#pragma once
#endif

//////////////////////////////////////////////////////////////////////
namespace chat
{
//--------------------------------------------------------------------
// Функция проверяет наличие интересующего файла.
// Если файл существует, возвращает true. В противном случае false. 
// 
    bool 
    file_test(
        const std::string&
    );

//--------------------------------------------------------------------
// Функция создает интересующий файл.
// 
    void 
    file_creat(
        const std::string&
    );

//--------------------------------------------------------------------
// Функция проверяет наличие введенного логина в статическом 
// хранилище данных. Есть - true. Нет - false.
//
    bool
    user_name_yn(
        const std::string&
    );

//--------------------------------------------------------------------
// Функция проверяет введенный пользователем логин на наличие в 
// статическом хранилище данных.
// По факту успешного поиска логина, функция считывает все данные 
// пользователя и возвращает true. В противном случае - false.
//
    bool
    reading_user_data(
        chat::User&,
        const std::string&
    );

//--------------------------------------------------------------------
// Функция отписывает данные пользователя в статическое хранилище 
// данных.
// По факту успешной записи функция возвращает true. 
// В противном случае - false.
//
    bool
    writing_user_data(
        chat::User&
    );

//--------------------------------------------------------------------
// Функция отписывает новые данные пользователя в статическое
// хранилище данных.
// По факту успешной записи функция возвращает true. 
// В противном случае - false.
//
    bool
    edit_user_data(
        chat::User&
    );

//--------------------------------------------------------------------
// Функция подсчиьывает количество зарегистрированных пользователей
// в статическом хранилище данных и возвращает последний
// номер зарегистрированного uid.
// Если хранилище пустое или что-то пошло не так, то функция 
// возвращает 0.
//
    ptl::__u32
    last_uid();

//--------------------------------------------------------------------
// Функция проверяет наличие поступивших пользователю сообщений. 
// При их наличии возвращает true. В противном случае - false.
//
    bool
    mcheck(
        chat::User&
    );

//--------------------------------------------------------------------
// Функция выводит на экран поступившие сообщения.
//
    void 
    mtout(
        chat::User&
    );

//--------------------------------------------------------------------
// Функция отписывает введенное пользователем сообщение в 
// хранилище сообщений - pmsg.
    bool 
    mfout(
        chat::Message&
    );

//--------------------------------------------------------------------
// Функции очищает хранилище сообщений от прочитанных 
// пользователем сообщений.
//
    void
    mclear(
        chat::User&,
        chat::Message&
    );

} // namespace chat

#endif // __CHAT_FILE_H__