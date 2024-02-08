// main.cpp -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 * Пример кода функции, которая выполняет автодополнение
 * введенного слова по изначально заданному словарю.
 */

#ifdef _WIN32
#include "ptl\ptype.h"
#include "ptl\pconio.h"
#include "ptl\pexcept.h"
#else
#include "ptl/ptype.h"
#include "ptl/pconio.h"
#include "ptl/pexcept.h"
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
//////////////////////////////////////////////////////////////////////
// Структура, описывающая слово в словаре.
//
struct word
  {
  std::string  _S_word;      // слово
  ptl::__s32   _S_frequency; // частота встречаемости слова

  word( std::string _word,
        ptl::__s32  _frequency )
    : _S_word( _word ),
      _S_frequency( _frequency )
    { }
  };
//////////////////////////////////////////////////////////////////////
auto
autoComplete( std::string,
              std::vector<word>& ) -> std::vector<std::string>;
//////////////////////////////////////////////////////////////////////
// Точка входа.
//
auto
main() -> int
  {
  ptl::setlocale_WIN32_rus();
  ptl::setconsole_WIN32_rus();
  ptl::clrscr();

  try
    {
    std::vector<word>  _dic;

    // формируем словарь автодополнения, посредством чтения
    // слов и частот встречаемости из вайла dic.txt

    std::fstream _fdic;
    _fdic.open( "dic.txt", std::fstream::in );

    if( !_fdic )
      {
      throw
      ptl::pexception( "E: Не могу открыть файл словаря." );
      }
    else
      {
      std::string  _w{ };
      ptl::__s32   _f{ };

      while( !_fdic.eof() )
        {
        _fdic
          >> _w
          >> _f;
        _dic.push_back( word( _w, _f ) );
        }

      _fdic.close();
      }

    while( true )
      {
      // просим пользователя ввести слово, которое будем автодополнять
      std::cout
        << "Введите слово или букву слова на русском языке.\n"
        << "Для выхода из программы введите - q"
        << std::endl;

      std::string  _word_input{ };

      std::cin.clear();
      std::cin
        >> _word_input;

      if( _word_input == "q" )
        {
        std::cout << std::endl;
        return 0;
        }

      // выполняем автодополнение, введенного пользователем слова и
      // выводим результат
      std::vector<std::string>  _suggestions;
      _suggestions = ::autoComplete( _word_input, _dic );

      std::cout
        << "\nПредлагаемые слова автодополнения..."
        << std::endl;

      for( const auto& _index : _suggestions )
        {
        std::cout
          << _index
          << std::endl;
        }

      std::cout << std::endl;
      }
    }
  catch( std::exception& _ex )
    {
    std::cout
      << _ex.what()
      << std::endl;

    return 0;
    }
  }
//--------------------------------------------------------------------
auto
autoComplete( std::string _w_input,
              std::vector<word>& _w_dic ) -> std::vector<std::string>
  {
  std::vector<std::string>  _suggestions;

  // сортировка словаря в порядке убывания частоты встречаемости слов
  std::sort( _w_dic.begin(),
             _w_dic.end(),
             [](const word& _a, const word& _b)
    {
    return _a._S_frequency > _b._S_frequency;
    } );

  // ищем слова в словаре, которые начинаются с введенного
  // пользователем слова, буквы (префикса)
  for( const auto& _index : _w_dic )
    {
    if( _index._S_word.find( _w_input ) == 0 )
      {
      _suggestions.push_back( _index._S_word );
      }
    }

  return _suggestions;
  }
