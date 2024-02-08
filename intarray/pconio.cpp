// -*- C++ -*-

/*
 * Copyright (c) Patriarh, 2023
 *
 * Реализация функций библиотеки
 */

/**
 *  (PTL) Patriarch library : pconio.cpp
 */

#include "pconio.h"
#include <clocale>
#include <iostream>

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