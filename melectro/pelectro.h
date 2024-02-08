// pelectro.h -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Магазин электроники.
 * Заголовочный файл с описанием портативной электроники.
 * Иерархия классов:
 *   IElectronics
 *     PortableElectronics
 *       Player            - проигрыватель
 *       Smartphone        - смартфон
 *       CappuccinoMachine - капучинатор
 *       Sharpener         - точилка
 *       Watch             - часы
 */

#ifndef __PortableElectronics__
#define __PortableElectronics__

#include <string>
#include "ptype.h"

#include "ielectro.h"

/*
 * Базовый класс для портативной электроники
 */
class PortableElectronics : public virtual IElectronics
{
public:
  PortableElectronics(std::string title, std::string manufacturer, std::string color, 
                      ptl::__u16 batteryLife) 
  : IElectronics(title, manufacturer, color), _batteryLife(batteryLife) 
  { }

  virtual
  ~PortableElectronics() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;

protected:
  /** Продолжительность работы источника питания (часы)
   */
  ptl::__u16       _batteryLife;
};

/*
 * Проигрыватель
 */
class Player final : public PortableElectronics
{
public:
  Player(std::string title, std::string manufacturer, std::string color, 
         ptl::__u16 batteryLife, std::string mediaType, 
         std::string headphones)
  : IElectronics(title, manufacturer, color),
  PortableElectronics(title, manufacturer, color, batteryLife),
  _mediaType(mediaType), _headphones(headphones)
  { }

  ~Player() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;

private:
  /** Тип носителя (CD, flash, кассета...)
   *  Наличие подключения наушников (да, нет)
   */
  std::string       _mediaType;
  std::string       _headphones;
};

/*
 * Смартфон
 */
class Smartphone final : public PortableElectronics
{
public:
  Smartphone(std::string title, std::string manufacturer, std::string color, 
             ptl::__u16 batteryLife, ptl::__u16 screenSize,
             ptl::__u16 amountMemory, std::string operatingSystem)
  : IElectronics(title, manufacturer, color),
  PortableElectronics(title, manufacturer, color, batteryLife),
  _screenSize(screenSize), _operatingSystem(operatingSystem),
  _amountMemory(amountMemory)
  { }

  ~Smartphone() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;

private:
  /** Размер экрана (дюйм)
   *  Количество памяти (Гб)
   *  Операционная система
   */
  ptl::__u16        _screenSize;
  ptl::__u16        _amountMemory;
  std::string       _operatingSystem; 
};

/*
 * Капучинатор
 */
class CappuccinoMachine final : public PortableElectronics
{
public:
  CappuccinoMachine(std::string title, std::string manufacturer, std::string color, 
                    ptl::__u16 batteryLife)
  : IElectronics(title, manufacturer, color),
  PortableElectronics(title, manufacturer, color, batteryLife)
  { }

  ~CappuccinoMachine() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;
};

/*
 * Точилка
 */
class Sharpener final : public PortableElectronics
{
public:
  Sharpener(std::string title, std::string manufacturer, std::string color, 
            ptl::__u16 batteryLife)
  : IElectronics(title, manufacturer, color),
  PortableElectronics(title, manufacturer, color, batteryLife)
  { }

  ~Sharpener() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;
};

/*
 * Часы
 */
class Watch final : public PortableElectronics
{
public:
  Watch(std::string title, std::string manufacturer, std::string color, 
        ptl::__u16 batteryLife, std::string clockWork)
  : IElectronics(title, manufacturer, color),
  PortableElectronics(title, manufacturer, color, batteryLife),
  _clockWork(clockWork) 
  { }

  ~Watch() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;

private:
  /** Часовой механизм (электронный, аналоговый)
   */
  std::string       _clockWork;
};

#endif // __PortableElectronics__