// pconio.h -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 * (PTL) Patriarch Library
 *
 * Описание библиотеки для работы с консолью (терминалом)
 */

#ifndef __ptl_pconio_h__
#define __ptl_pconio_h__

namespace ptl
{
  /** Локализация терминала ОС Windows 'Russian'
   */ 
  void
  setlocale_WIN32_rus();
  
  /** Очистка терминала и постановка курсора в 
   *  верхний левый угол
   */
  void
  clear(); 
} // namespace ptl

#endif // __ptl_pconio_h__