// -*- C++ -*-

/*
 * Copyright (c) Patriarh, 2023
 *
 * Описание библиотеки для работы с консолью (терминалом)
 */

/**
 *  (PTL) Patriarch library : pconio.h
 */

#ifndef __ptl_pconio_h__
#define __ptl_pconio_h__

namespace ptl
{
  /** 
   *  Локализация терминала ОС Windows 'Russian'
   */ 
  void
  setlocale_WIN32_rus();
  
  /** 
   *  Очистка терминала и постановка курсора в 
   *  верхний левый угол
   */
  void
  clear(); 
} // namespace ptl

#endif // __ptl_pconio_h__