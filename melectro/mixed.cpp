// mixed.cpp -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Магазин электроники.
 * Реализация методов.
 */

#include <iostream>

#include "mixed.h"

void 
Dispenser::ViewSpecifications()
{
  std::cout 
    << "Название                       : " << _title                << "\n"
    << "Производитель                  : " << _manufacturer         << "\n"
    << "Цвет                           : " << _color                << "\n"
    << "Потребляемая мощность (Вт)     : " << _power                << "\n"
    << "Вес (кг)                       : " << _weight               << "\n"
    << "Продолжительность работы (час) : " << _batteryLife          << "\n"
    << "Количество режимов работы (шт) : " << _numberOperatingModes
    << std::endl;
}