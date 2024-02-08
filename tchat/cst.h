// cst.h -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Заголовочный файл с определением констант.
 */

#pragma once
#ifndef _CHAT_CST
#define _CHAT_CST

#ifdef _WIN32
#include "ptl\ptype.h"
#else
#include "ptl/ptype.h"
#endif

namespace chat
{
  constexpr ptl::__u16
  _Quantity_Messages { 1000 }; // Количество сообщений для каждого пользователя

  constexpr ptl::__u16
  _Help   { 10 };              // Вывод информации об управляющих параметрах

  constexpr ptl::__u16
  _Change { 20 };              // Смена пользователя чата

  constexpr ptl::__u16
  _Quit   { 30 };              // Завершение работы чата

  constexpr ptl::__u16
  _Edit   { 40 };              // Редактирование данных пользователя чата

  constexpr ptl::__u16
  _Ok     { 1000 };            // Нормальный обмен сообщениями

} // namespace chat 

#endif // _CHAT_CST