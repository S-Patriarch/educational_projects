// applianc.h -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Магазин электроники.
 * Заголовочный файл с описанием бытовой техники.
 * Иерархия классов:
 *   IElectronics
 *     Appliances
 *       Fridge         - холодильник
 *       WashingMachine - стиральная машина
 *       Microwave      - микроволновка
 *       Iron           - утюг
 *       Dishwasher     - посудомоечная машина
 */

#ifndef __Appliances__
#define __Appliances__

#include <string>
#include "ptype.h"

#include "ielectro.h"

/*
 * Базовый класс для бытовой техники
 */
class Appliances : public virtual IElectronics
{
public:
  Appliances(std::string title, std::string manufacturer, std::string color,
             ptl::__u16 power, double weight)
  : IElectronics(title, manufacturer, color), _power(power), _weight(weight)
  { }

  virtual
  ~Appliances() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;

protected:
  /** Потребляемая мощность (Вт)
   *  Вес (кг)
   */
  ptl::__u16       _power;
  double           _weight;
};

/*
 * Холодильник
 */
class Fridge final : public Appliances
{
public:
  Fridge(std::string title, std::string manufacturer, std::string color,
         ptl::__u16 power, double weight,
         ptl::__u16 volumeRefrigeratingChamber, 
         ptl::__u16 volumeZorozilnyChamber)
  : IElectronics(title, manufacturer, color),
  Appliances(title, manufacturer, color, power, weight),
  _volumeRefrigeratingChamber(volumeRefrigeratingChamber),
  _volumeZorozilnyChamber(volumeZorozilnyChamber)
  { }

  ~Fridge() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;

private:
  /** Объем холодильной камеры (литр)
   *  Объем морозильной камеры (литр)
   */
  ptl::__u16       _volumeRefrigeratingChamber;
  ptl::__u16       _volumeZorozilnyChamber;
};

/*
 * Стиральная машина
 */
class WashingMachine final : public Appliances
{
public:
  WashingMachine(std::string title, std::string manufacturer, std::string color, 
                 ptl::__u16 power, double weight,
                 std::string loadingLaundry, ptl::__u16 downloadVolume)
  : IElectronics(title, manufacturer, color),
  Appliances(title, manufacturer, color, power, weight), 
  _loadingLaundry(loadingLaundry), _downloadVolume(downloadVolume)
  { }

  ~WashingMachine() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;

private:
  /** Загрузка белья (горизонтальная, вертикальная)
   *  Объем загрузки белья (килограмм)
   */
  std::string       _loadingLaundry;
  ptl::__u16        _downloadVolume;
};

/*
 * Микроволновка
 */
class Microwave final : public Appliances
{
public:
  Microwave(std::string title, std::string manufacturer, std::string color, 
            ptl::__u16 power, double weight, ptl::__u16 cameraVolume) 
  : IElectronics(title, manufacturer, color),
  Appliances(title, manufacturer, color, power, weight),
  _cameraVolume(cameraVolume) 
  { }

  ~Microwave() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;

private:
  /** Объем камеры (литр)
   */
  ptl::__u16       _cameraVolume;
};

/*
 * Утюг
 */
class Iron final : public Appliances
{
public:
  Iron(std::string title, std::string manufacturer, std::string color, 
       ptl::__u16 power, double weight, std::string presenceSteam)
  : IElectronics(title, manufacturer, color),
  Appliances(title, manufacturer, color, power, weight),
  _presenceSteam(presenceSteam) 
  { }

  ~Iron() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;

private:
  /** Наличие пара (да, нет)
   */
  std::string       _presenceSteam;
};

/*
 * Посудомоечная машина
 */
class Dishwasher final : public Appliances
{
public:
  Dishwasher(std::string title, std::string manufacturer, std::string color, 
             ptl::__u16 power, double weight, 
             ptl::__u16 numberSets, ptl::__u16 waterConsumption)
  : IElectronics(title, manufacturer, color),
  Appliances(title, manufacturer, color, power, weight),
  _numberSets(numberSets), _waterConsumption(waterConsumption)
  { }

  ~Dishwasher() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;

private:
  /** Количество комплектов посуды (штук)
   *  Расход воды (литр)
   */
  ptl::__u16       _numberSets;
  ptl::__u16       _waterConsumption;
};

#endif // __Appliances__