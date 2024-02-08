// mixed.h -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Магазин электроники.
 * Заголовочный файл с описанием устройств относящихся
 * как к бытовой технике, так и к портативной электронике.
 * Иерархия классов:
 *   IElectronics
 *     Appliances
 *       Dispenser - диспенсер
 *     PortableElectronics
 *       Dispenser - диспенсер
 */

#ifndef __Appliances_PortableElectronics__
#define __Appliances_PortableElectronics__

#include <string>
#include "ptype.h"

#include "applianc.h"
#include "pelectro.h"

/*
 * Диспенсер
 */
class Dispenser final : public Appliances, PortableElectronics
{
public:
  Dispenser(std::string title, std::string manufacturer, std::string color, 
            ptl::__u16 power, double weight, ptl::__u16 batteryLife, 
            ptl::__u16 numberOperatingModes)
  : IElectronics(title, manufacturer, color),
  Appliances(title, manufacturer, color, power, weight), 
  PortableElectronics(title, manufacturer, color, batteryLife),
  _numberOperatingModes(numberOperatingModes) 
  { }

  ~Dispenser() = default;

  /** Перегрузка метода просмотра характеристик
   *  АБК IElectronics
   */
  void
  ViewSpecifications() override;

private:
  /** Количество режимов работы (штук)
   */
  ptl::__u16       _numberOperatingModes;
};

#endif // __Appliances_PortableElectronics__