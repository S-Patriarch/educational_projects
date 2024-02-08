// applianc.cpp -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Магазин электроники.
 * Реализация методов.
 */

#include <iostream>

#include "applianc.h"

void 
Appliances::ViewSpecifications()
{
  std::cout 
    << "Название                   : " << _title        << "\n"
    << "Производитель              : " << _manufacturer << "\n"
    << "Цвет                       : " << _color        << "\n"
    << "Потребляемая мощность (Вт) : " << _power        << "\n"
    << "Вес (кг)                   : " << _weight
    << std::endl;
}

void 
Fridge::ViewSpecifications()
{
  std::cout 
    << "Название                     : " << _title                      << "\n"
    << "Производитель                : " << _manufacturer               << "\n"
    << "Цвет                         : " << _color                      << "\n"
    << "Потребляемая мощность (Вт)   : " << _power                      << "\n"
    << "Вес (кг)                     : " << _weight                     << "\n"
    << "Объем холодильной камеры (л) : " << _volumeRefrigeratingChamber << "\n"
    << "Объем морозильной камеры (л) : " << _volumeZorozilnyChamber
    << std::endl;
}

void 
WashingMachine::ViewSpecifications()
{
  std::cout 
    << "Название                   : " << _title          << "\n"
    << "Производитель              : " << _manufacturer   << "\n"
    << "Цвет                       : " << _color          << "\n"
    << "Потребляемая мощность (Вт) : " << _power          << "\n"
    << "Вес (кг)                   : " << _weight         << "\n"
    << "Загрузка белья             : " << _loadingLaundry << "\n"
    << "Объем загрузки белья (кг)  : " << _downloadVolume 
    << std::endl;
}

void 
Microwave::ViewSpecifications()
{
  std::cout 
    << "Название                   : " << _title        << "\n"
    << "Производитель              : " << _manufacturer << "\n"
    << "Цвет                       : " << _color        << "\n"
    << "Потребляемая мощность (Вт) : " << _power        << "\n"
    << "Вес (кг)                   : " << _weight       << "\n"
    << "Объем камеры (л)           : " << _cameraVolume
    << std::endl;
}

void 
Iron::ViewSpecifications()
{
  std::cout 
    << "Название                   : " << _title         << "\n"
    << "Производитель              : " << _manufacturer  << "\n"
    << "Цвет                       : " << _color         << "\n"
    << "Потребляемая мощность (Вт) : " << _power         << "\n"
    << "Вес (кг)                   : " << _weight        << "\n"
    << "Наличие пара               : " << _presenceSteam
    << std::endl;
}

void 
Dishwasher::ViewSpecifications()
{
  std::cout 
    << "Название                          : " << _title            << "\n"
    << "Производитель                     : " << _manufacturer     << "\n"
    << "Цвет                              : " << _color            << "\n"
    << "Потребляемая мощность (Вт)        : " << _power            << "\n"
    << "Вес (кг)                          : " << _weight           << "\n"
    << "Количество комплектов посуды (шт) : " << _numberSets       << "\n"
    << "Расход воды (л)                   : " << _waterConsumption
    << std::endl;
}