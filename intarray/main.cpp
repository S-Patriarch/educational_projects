// main.cpp -*- C++ -*-

/*
 * Copyright (c) Patriarh, 2023
 *
 * Домашнее задание по 7-му модулю курса 'Разработчик С++'.
 * Контейнер данных Integer Array с использованием 
 * механизма исключений C++.
 */

#include "intarray.h"
#include "ptype.h"
#include "pconio.h"
#include <iostream>

/*
 * Точка входа...
 */
int
main()
{
  /** Объявляем контейнер из 10 элементов
   */
  IntArray array(10);

  /** Заполняем контейнер числами от 1 до 10
   */
  for (ptl::__s32 i{ 0 }; i < 10; ++i)
    array[i] = i + 1;

  ptl::setlocale_WIN32_rus();
  ptl::clear();
  
  std::cout
    << "Начальный контейнер:"
    << std::endl;
  for (ptl::__s32 i{ 0 }; i < array.GetLenght(); ++i)
    std::cout
      << array[i]
      << " ";
  std::cout
    << std::endl;

  /** Изменяем размер контейнера до 8 элементов
   */
  array.Resize(8);

  std::cout
    << "Контейнер уменьшен до 8-и элементов:"
    << std::endl;
  for (ptl::__s32 i{ 0 }; i < array.GetLenght(); ++i)
    std::cout
      << array[i]
      << " ";
  std::cout
    << std::endl;

  /** Вставляем число 20 перед элементом 5
   */
  array.InsertBefore(20, 5);

  std::cout
    << "Вставили число 20 перед 5-м элементом контейнера:"
    << std::endl;
  for (ptl::__s32 i{ 0 }; i < array.GetLenght(); ++i)
    std::cout
      << array[i]
      << " ";
  std::cout
    << std::endl;

  /** Удаляем элемент контейнера с индексом 3
   */
  array.Remove(3);

  std::cout
    << "Удалили элемент контейнера с индексом 3:"
    << std::endl;
  for (ptl::__s32 i{ 0 }; i < array.GetLenght(); ++i)
    std::cout
      << array[i]
      << " ";
  std::cout
    << std::endl;

  /** Добавляем 30 и 40 в конец и начало контейнера
   */
  array.InsertAtEnd(30);
  array.InsertAtBeginning(40);

  std::cout
    << "Добавили число 30 в конец и число 40 в начало контейнера:"
    << std::endl;
  for (ptl::__s32 i{ 0 }; i < array.GetLenght(); ++i)
    std::cout
      << array[i]
      << " ";
  std::cout
    << std::endl;

  /** Еще несколько тестов для обеспечения копирования
   *  построения / назначения контейнера, ничего не ломает
   */
  {
    IntArray b{ array };

    b     = array;
    b     = b;
    array = array;
  }

  /** Выводим элемент контейнера по заданному индексу
   */
  std::cout
    << "\nВыводим элемент контейнера по заданному индексу 5:\n"
    << array.GetElement(5)
    << std::endl;

  /** Выводим результат поиска элемента контейнера по значению
   */
  std::cout
    << "Выводим результат поиска - индекс элемента контейнера по " 
    << "значению 20:\n" 
    << array.FindElement(20)
    << std::endl 
    << std::endl;

  try
    {
      std::cout
        << "Выводим результат поиска - индекс элемента контейнера по " 
        << "значению 80:"
        << std::endl; 
      std::cout
        << array.FindElement(80)
        << std::endl;
    }
  catch (const char* ex)
    {
      std::cout
        << ex
        << std::endl;
    }

  try
    {
      std::cout
        << "Удаляем элемент контейнера с индексом 11:"
        << std::endl;
      array.Remove(11);
      for (ptl::__s32 i{ 0 }; i < array.GetLenght(); ++i)
        std::cout
          << array[i]
          << " ";
      std::cout
        << std::endl;
    }
  catch (const char* ex)
    {
      std::cout
        << ex
        << std::endl;
    }

  try
    {
      std::cout
        << "Создаем контейнер размером 0:"
        << std::endl;
      IntArray array(0);
    }
  catch (const char* ex)
    {
      std::cout
        << ex
        << std::endl;
    }

  return 0;
}
