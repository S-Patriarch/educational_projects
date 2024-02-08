// main.cpp -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Пример кода функции, которая проверяет, 
 * является ли строка кратной числу.
 */

#ifdef _WIN32
#include "ptl\ptype.h"
#include "ptl\pconio.h"
#include "ptl\pstring.h"
#else
#include "ptl/ptype.h"
#include "ptl/pconio.h"
#include "ptl/pstring.h"
#endif

#include <iostream>
#include <string>
//////////////////////////////////////////////////////////////////////
auto
is_kperiodic( ptl::pstring&, ptl::__u16 ) -> bool;
//////////////////////////////////////////////////////////////////////
auto
main() -> int
  {
  ptl::setlocale_WIN32_rus();
  ptl::clrscr();

  ptl::pstring s( "abcabcabcabc" );
  ptl::__u16   __k{ 3 };
  bool         __is{ ::is_kperiodic( s, __k ) };

  std::cout << "Строка: "
            << s.at()
            << std::endl;

  if( __is )
    {
    std::cout << "Строка кратна числу "
              << __k
              << std::endl;
    }
  else
    {
    std::cout << "Строка НЕ кратна числу "
              << __k
              << std::endl;
    }

  return 0;
  }
//--------------------------------------------------------------------
auto
is_kperiodic( ptl::pstring& s, ptl::__u16 __k ) -> bool
  {
  if( s.size() % __k != 0 )
    {
    return false;
    }

  char*  __s = s.at();
  
  for( ptl::__u16 __i{ __k }; __i < s.size(); __i += __k )
    {
    if( __s[ __i ] != __s[ 0 ] )
      {
      return false;
      }
    }

  return true;
  }
