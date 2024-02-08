// main.cpp -*- C++ -*-
//
// Copyright (c) S-Patriarch, 2023
// Модель чата в которой логин и хеш от пароля хранятся в хеш-таблице.
// То есть логин является ключом, хеш — значением, а вместе они 
// составляют пару. Хеш-функция для хеш-таблицы составлена методом 
// умножения. Хеш-таблица реализована методом квадратичного пробирования.

#ifdef _WIN32
#include "ptl\pconio.h"
#include "ptl\pexcept.h"
#else
#include "ptl/pconio.h"
#include "ptl/pexcept.h"
#endif

#include "sha1.h"
#include "chat.h"
#include <iostream>
#include <string>
//////////////////////////////////////////////////////////////////////
// Точка входа.
//
auto
main() -> int
  {
  ptl::setlocale_WIN32_rus();
  ptl::clrscr();

  bool  _flage{ false };

  try
    {
    Chat  ch;

    ch.reg( (char*)"user1", 
            (char*)"qwerty12345", 
            sizeof("qwerty12345") );

    ch.reg( (char*)"user2", 
            (char*)"asdfg",       
            sizeof("asdfg") );
    
    ch.reg( (char*)"user3", 
            (char*)"zsdrt",       
            sizeof("zsdrt") );
    
    ch.reg( (char*)"user4", 
            (char*)"pass",        
            sizeof("pass") );
    
    ch.reg( (char*)"user5", 
            (char*)"pass",        
            sizeof("pass") );
    
    ch.reg( (char*)"user6", 
            (char*)"pass",        
            sizeof("pass") );
    
    ch.reg( (char*)"user7", 
            (char*)"pass",        
            sizeof("pass") );

    ch.unreg( (char*)"user2" );
    ch.unreg( (char*)"user6" );

    if( !ch.login( (char*)"user1", 
                   (char*)"qwerty12345", 
                   sizeof("qwerty12345") ) )  
      throw pException( "E: Недопустимый вход user1." );

    if( !ch.login( (char*)"user3", 
                   (char*)"zsdrt", 
                   sizeof("zsdrt") ) )  
      throw pException( "E: Недопустимый вход user3." );

    if( !ch.login( (char*)"user4", 
                   (char*)"pass", 
                   sizeof("pass") ) )  
      throw pException( "E: Недопустимый вход user4." );

    if( !ch.login( (char*)"user5", 
                   (char*)"pass", 
                   sizeof("pass") ) )  
      throw pException( "E: Недопустимый вход user5." );

    if( !ch.login( (char*)"user7", 
                   (char*)"pass", 
                   sizeof("pass") ) )  
      throw pException( "E: Недопустимый вход user7." );

    if( !ch.login( (char*)"user2", 
                   (char*)"asdfg", 
                   sizeof("asdfg") ) )  
      throw pException( "E: Недопустимый вход user2." );

    if( !ch.login( (char*)"user6", 
                   (char*)"pass", 
                   sizeof("pass") ) )  
      throw pException( "E: Недопустимый вход user6." );

    _flage = true;
    }
  catch( std::exception& ex )
    {
    std::cout 
      << ex.what() 
      << std::endl;

    _flage = false;
    }

  if( _flage ) 
    {
    std::cout 
      << "Тесты пройдены" 
      << std::endl;
    }
  else 
    {
    std::cout 
      << "Тесты провалены" 
      << std::endl;
    }  

  return 0;
  }
