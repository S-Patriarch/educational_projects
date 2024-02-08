// pconio.cpp -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 * (PTL) Patriarch Library
 *
 * Реализация функций библиотеки
 */

#include <clocale>
#include <iostream>
#include "pconio.h"

namespace ptl
{
  void 
  setlocale_WIN32_rus()
  {
    #ifdef _WIN32
      setlocale(LC_ALL, "Russian");
    #endif
  }

  void 
  clear()
  { std::cout << "\033[2J\033[1;1H"; }
} // namespace ptl