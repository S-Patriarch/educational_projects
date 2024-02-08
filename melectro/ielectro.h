// ielectro.h -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Магазин электроники.
 * Заголовочный файл с описанием абстрактного базового класса.
 */

#ifndef __IElectronics__
#define __IElectronics__

#include <string>

class IElectronics
{
public:
  IElectronics(std::string title, std::string manufacturer, std::string color)
  : _title(title), _manufacturer(manufacturer), _color(color)
  { }

  virtual 
  ~IElectronics() = default;

  /** Просмотр характеристик
   */
  virtual 
  void 
  ViewSpecifications() = 0;

  /** Получить название товара
   */
  std::string
  GetTitle() const
  { return _title; }

protected:
  /** Название
   *  Производитель
   *  Цвет
   */
  std::string       _title;
  std::string       _manufacturer;
  std::string       _color;
};

#endif // __IElectronics__