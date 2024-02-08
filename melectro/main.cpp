// main.cpp -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Домашнее задание по 6-му модулю курса 'Разработчик С++'.
 * Магазин электроники.
 */

#include <iostream>
#include <string>
#include "pconio.h"

#include "const.h"
#include "mixed.h"

/*
 * Точка входа...
 */
int
main()
{
  ptl::setlocale_WIN32_rus();

  IElectronics* 
  app[cst::ARRAY_SIZE_APP];

  /** Загрузка склада бытовой техникой
   */
  app[0] = new 
  Fridge("Холодильник", "Indesit", "белый", 110, 52, 220, 78);
  app[1] = new 
  WashingMachine("Стиральная машина", "LG", "серый", 1006, 60, "горизонтальная", 6);
  app[2] = new
  Microwave("Микроволновка", "LG", "белый", 1000, 9, 20);
  app[3] = new
  Iron("Утюг", "Philips", "белый", 1100, 0.78, "да");
  app[4] = new
  Dishwasher("Посудомоечная машина", "Bosch", "черный", 800, 27, 8, 9);

  IElectronics* 
  pel[cst::ARRAY_SIZE_PEL];

  /** Загрузка склада портативной электроникой
   */
  pel[0] = new 
  Player("Проигрыватель", "Sony", "черный", 20, "MP3", "да");
  pel[1] = new 
  Smartphone("Смартфон", "Xiaomi", "синий", 8, 6, 128, "Android");
  pel[2] = new 
  CappuccinoMachine("Капучинатор", "ZDK", "черный", 6);
  pel[3] = new 
  Sharpener("Точилка", "Staff", "черный", 12);
  pel[4] = new 
  Watch("Часы", "Xiaomi", "синий", 576, "электронный");

  /** Загрузка склада смешенной техникой
   */
  IElectronics*  
  dispenser = new 
  Dispenser("Диспенсер", "Vatten", "розовый", 30, 0.2, 12, 2);

  bool openShop { true };
  
  std::string
  str1 { "Характеристики товара" };
  std::string 
  str2 { "----------------------------------------------------------" };

  /** Работа магазина электроники
   */
  while (openShop)
    {
      ptl::clear();

      std::cout
        << "МАГАЗИН ЭЛЕКТРОНИКИ\n"
        << str2
        << "\n"
        << std::endl;

      std::cout
        << "Бытовая техника:"
        << std::endl;

      for (ptl::__u16 i = 0; i < cst::ARRAY_SIZE_APP; ++i)
        {
          std::cout
            << i + 1
            << " "
            << app[i]->GetTitle()
            << std::endl;
        }

      std::cout << std::endl;

      std::cout
        << "Портативная электроника:"
        << std::endl;

      for (ptl::__u16 i = 0; i < cst::ARRAY_SIZE_PEL; ++i)
        {
          std::cout
            << i + 6
            << " "
            << pel[i]->GetTitle()
            << std::endl;
        }

      std::cout << std::endl;

      std::cout
        << "Иная техника:"
        << std::endl;

      std::cout
        << cst::ARRAY_SIZE_APP + cst::ARRAY_SIZE_PEL + 1
        << " "
        << dispenser->GetTitle()
        << std::endl;

      std::cout
        << "\n"
        << str2
        << std::endl;

      std::cout
        << "Выберите позицию товара от 1 до "
        << cst::ARRAY_SIZE_APP + cst::ARRAY_SIZE_PEL + 1
        << " или 0 для выхода : ";

      ptl::__u16 menuPosition { };
      std::cin.clear();
      std::cin 
        >> menuPosition;

      switch (menuPosition)
        {
          case 1  :
            ptl::clear();
            std::cout
              << str1
              << "\n"
              << str2
              << std::endl;

            app[0]->ViewSpecifications();
            break;

          case 2  :
            ptl::clear();
            std::cout
              << str1
              << "\n"
              << str2
              << std::endl;

            app[1]->ViewSpecifications();
            break;

          case 3  :
            ptl::clear();
            std::cout
              << str1
              << "\n"
              << str2
              << std::endl;

            app[2]->ViewSpecifications();
            break;

          case 4  :
            ptl::clear();
            std::cout
              << str1
              << "\n"
              << str2
              << std::endl;

            app[3]->ViewSpecifications();
            break;

          case 5  :
            ptl::clear();
            std::cout
              << str1
              << "\n"
              << str2
              << std::endl;

            app[4]->ViewSpecifications();
            break;

          case 6  :
            ptl::clear();
            std::cout
              << str1
              << "\n"
              << str2
              << std::endl;

            pel[0]->ViewSpecifications();
            break;

          case 7  :
            ptl::clear();
            std::cout
              << str1
              << "\n"
              << str2
              << std::endl;

            pel[1]->ViewSpecifications();
            break;

          case 8  :
            ptl::clear();
            std::cout
              << str1
              << "\n"
              << str2
              << std::endl;

            pel[2]->ViewSpecifications();
            break;

          case 9  :
            ptl::clear();
            std::cout
              << str1
              << "\n"
              << str2
              << std::endl;

            pel[3]->ViewSpecifications();
            break;

          case 10 :
            ptl::clear();
            std::cout
              << str1
              << "\n"
              << str2
              << std::endl;

            pel[4]->ViewSpecifications();
            break;

          case 11 :
            ptl::clear();
            std::cout
              << str1
              << "\n"
              << str2
              << std::endl;

            dispenser->ViewSpecifications();
            break;

          case 0 :
            openShop = false;

            std::cout
              << "До новых встреч..."
              << std::endl;

            delete dispenser;

            delete pel[4];
            delete pel[3];
            delete pel[2];
            delete pel[1];
            delete pel[0];

            delete app[4];
            delete app[3];
            delete app[2];
            delete app[1];
            delete app[0];
            
            return 0;
            break;
        }

      std::cout
        << "\nПродолжить работу [y/n] ";

      char anyKey { };
      std::cin.clear();
      std::cin
        >> anyKey;

      if (anyKey != 'y' && anyKey != 'Y')
        {
          std::cout
            << "До новых встреч..."
            << std::endl;

          openShop = false;
        }
    }

  delete dispenser;

  delete pel[4];
  delete pel[3];
  delete pel[2];
  delete pel[1];
  delete pel[0];

  delete app[4];
  delete app[3];
  delete app[2];
  delete app[1];
  delete app[0];

  return 0;
}