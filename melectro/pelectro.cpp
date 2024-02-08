// pelectro.cpp -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Магазин электроники.
 * Реализация методов.
 */

#include <iostream>

#include "pelectro.h"

void 
PortableElectronics::ViewSpecifications()
{
  std::cout 
    << "Название                     : " << _title        << "\n"
    << "Производитель                : " << _manufacturer << "\n"
    << "Цвет                         : " << _color        << "\n"
    << "Продолжительность работы (ч) : " << _batteryLife
    << std::endl;
}

void 
Player::ViewSpecifications()
{
  std::cout 
    << "Название                      : " << _title        << "\n"
    << "Производитель                 : " << _manufacturer << "\n"
    << "Цвет                          : " << _color        << "\n"
    << "Продолжительность работы (ч)  : " << _batteryLife  << "\n"
    << "Тип носителя                  : " << _mediaType    << "\n"
    << "Наличие подключения наушников : " << _headphones
    << std::endl;
}

void 
Smartphone::ViewSpecifications()
{
  std::cout 
    << "Название                     : " << _title           << "\n"
    << "Производитель                : " << _manufacturer    << "\n"
    << "Цвет                         : " << _color           << "\n" 
    << "Продолжительность работы (ч) : " << _batteryLife     << "\n"
    << "Размер экрана (дюйм)         : " << _screenSize      << "\n"
    << "Количество памяти (Гб)       : " << _amountMemory    << "\n"
    << "Операционная система         : " << _operatingSystem
    << std::endl;
}

void 
CappuccinoMachine::ViewSpecifications()
{
  std::cout 
    << "Название                     : " << _title        << "\n"
    << "Производитель                : " << _manufacturer << "\n"
    << "Цвет                         : " << _color        << "\n"
    << "Продолжительность работы (ч) : " << _batteryLife
    << std::endl;
}

void 
Sharpener::ViewSpecifications()
{
  std::cout 
    << "Название                     : " << _title        << "\n"
    << "Производитель                : " << _manufacturer << "\n"
    << "Цвет                         : " << _color        << "\n"
    << "Продолжительность работы (ч) : " << _batteryLife
    << std::endl;
}

void 
Watch::ViewSpecifications()
{
  std::cout 
    << "Название                     : " << _title        << "\n"
    << "Производитель                : " << _manufacturer << "\n"
    << "Цвет                         : " << _color        << "\n"
    << "Продолжительность работы (ч) : " << _batteryLife  << "\n"
    << "Часовой механизм             : " << _clockWork
    << std::endl;
}