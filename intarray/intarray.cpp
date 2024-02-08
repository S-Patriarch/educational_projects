// intarray.cpp -*- C++ -*-

/*
 * Copyright (c) Patriarh, 2023
 *
 * Реализация контейнера данных 
 */

#include "intarray.h"
#include "ptype.h"
#include <cassert>

IntArray::IntArray(ptl::__s32 lenght)
: _m_lenght{ lenght }
{
  //assert(lenght >= 0);
  if (lenght <= 0)
    throw "E: Размер контейнера не приемлем.";

  if (lenght > 0)
    _m_data = new ptl::__s32[lenght] { };
}

int IntArray::GetLenght() const
{
  return _m_lenght;
}

int IntArray::GetElement(ptl::__s32 index) const
{
  return _m_data[index];
}

IntArray::IntArray(const IntArray& a)
{
  /** Устанавливаем размер контейнера соответствующим образом
   */
  Reallocate(a.GetLenght());

  /** Копируем элементы
   */
  for (ptl::__s32 index{ 0 }; index < _m_lenght; ++index)
    _m_data[index] = a._m_data[index];
}

IntArray::~IntArray()
{
  /** Здесь не нужно устанавливать _m_data равный nullptr или _m_lenght
   *  равный 0, поскольку объект в любом случае будет уничтожен
   *  сразу после выполнения этого деструктора
   */
  delete[] _m_data;
}

void IntArray::Erase()
{
  delete[] _m_data;

  /** Нам нужно убедиться, что мы установили _m_data в nullptr, иначе он
   *  останется указывающим на освобожденную память
   */
  _m_data   = nullptr;
  _m_lenght = 0;
}

ptl::__s32& IntArray::operator[](ptl::__s32 index)
{
  //assert(index >= 0 && index < _m_lenght);
  if (index < 0 || index >= _m_lenght)
    throw "E: Значение индекса контейнера не приемлемо.";
  
  return _m_data[index];
}

IntArray& IntArray::operator=(const IntArray& a)
{
  /** Проверка самоназначения
   */
  if (&a == this)
    return *this;

  /** Устанавливаем размер нового контейнера соответствующим образом
   */
  Reallocate(a.GetLenght());

  /** Копируем элементы
   */
  for (ptl::__s32 index{ 0 }; index < _m_lenght; ++index)
    _m_data[index] = a._m_data[index];

  return *this;
}

/* 
 * Изменяет размер контейнера.
 * Все существующие элементы контейнера будут уничтожены.
 */
void IntArray::Reallocate(ptl::__s32 newLenght)
{
  /** Удалаяем все существующие элементы
   */
  Erase();

  /** Если контейнер пустой, то возвращаемся сюдаже
   */
  if (newLenght <= 0)
    return;

  /** Выделяем новые элементы
   */
  _m_data   = new ptl::__s32[newLenght];
  _m_lenght = newLenght;
}

/*
 * Изменяет размер контейнера.
 * Все существующие элементы контейнера будут сохранены.
 */
void IntArray::Resize(ptl::__s32 newLenght)
{
  /** Если контейнер уже имеет нужную длинну, то заканчиваем
   */
  if (newLenght == _m_lenght)
    return;

  /** Если изменяется размер до пустого контейнера, то 
   *  сделаем это и заканчиваем
   */
  if (newLenght <= 0)
    {
      Erase();
      return;
    }

  /** Теперь мы можем предположить, что newLenght - это, как минимум,
   *  1-н элемент.
   *  Этот алгоритм работаеи следующим образом:
   *  Сначало мы выделяем новый контейнер. Затем мы копируем элементы из
   *  существующего контейнера в новый контейнер. Как только это будет
   *  сделано, мы можем уничтожить старый контейнер и заставить _m_data
   *  указывать на новый контейнер.
   */

  /** Выделяем новый контейнер
   */
  ptl::__s32* 
  data 
  { new ptl::__s32[newLenght] };

  /** Затем мы должны выяснить, сколько элементов скопировать из
   *  существующего контейнера в новый контейнер. Мы хотим скопировать
   *  столько элементов, сколько есть в меньшем из двух контейнеров.
   */
  if (_m_lenght > 0)
    {
      ptl::__s32 
      elementsToCopy 
      { (newLenght > _m_lenght) 
        ? _m_lenght 
        : newLenght };

      /** Теперь скопируем элементы один за другим
       */
      for (ptl::__s32 index{ 0 }; index < _m_lenght; ++index)
        data[index] = _m_data[index];
    }

  /** Теперь мы можем удалить старый контейнер, потому что
   *  он нам больше не нужен
   */
  delete[] _m_data;

  /** Используем вместо старого контейнера новый контейнер.
   *  Это приводит к тому, что _m_data указывает на тот же адрес, 
   *  что и новый контейнер. Потому что данные были распределены 
   *  динамически, они не будут уничтожены, когда выйдут за пределы 
   *  области видимости.
   */
  _m_data   = data;
  _m_lenght = newLenght;
}

void IntArray::InsertBefore(ptl::__s32 value, ptl::__s32 index)
{
  /** Проверка значения индекса на вменяемость
   */
  //assert(index >= 0 && index <= _m_lenght);
  if (index < 0 || index > _m_lenght)
    throw "E: Значение индекса контейнера не приемлемо.";

  /** Создаем новый контейнер на 1-н элемент больше чем старый контейнер
   */
  ptl::__s32* 
  data 
  { new ptl::__s32[_m_lenght+1] };

  /** Копируем все элементв вплоть до индекса
   */
  for (ptl::__s32 before{ 0 }; before < index; ++before)
    data[before] = _m_data[before];

  /** Вставляем новый элемент в новый контейнер
   */
  data[index] = value;

  /** Копируем все значения после вставленного элемента
   */
  for (ptl::__s32 after{ index }; after < _m_lenght; ++after)
    data[after+1] = _m_data[after];

  /** Удаляем старый контейнер и используем вместо него новый контейнер
   */
  delete[] _m_data;
  _m_data = data;
  ++_m_lenght;
}

void IntArray::Remove(ptl::__s32 index)
{
  /** Проверка значения индекса на вменяемость
   */
  //assert(index >= 0 && index < _m_lenght);
  if (index < 0 || index >= _m_lenght)
    throw "E: Значение индекса контейнера не приемлемо.";

  /** Если это последний оставшийся элемент в контейнере, то 
   *  устанавливаем для контейнера значение empty и извлекаем его
   */
  if (_m_lenght == 1)
    {
      Erase();
      return;
    }

  /** Создаем новый контейнер на один элемент меньше чем старый 
   *  контейнер
   */
  ptl::__s32* 
  data 
  { new ptl::__s32[_m_lenght-1] };

  /** Копируем все элементы вплоть до индекса
   */
  for (ptl::__s32 before{ 0 }; before < index; ++before)
    data[before] = _m_data[before];

  /** Копируем все значения после удаленного элемента
   */
  for (ptl::__s32 after{ index+1 }; after < _m_lenght; ++after)
    data[after-1] = _m_data[after];

  /** Удаляем старый контейнер и используем вместо него новый контейнер
   */
  delete[] _m_data;
  _m_data = data;
  --_m_lenght;
}

void IntArray::InsertAtBeginning(ptl::__s32 value)
{
  InsertBefore(value, 0);
}

void IntArray::InsertAtEnd(ptl::__s32 value)
{
  InsertBefore(value, _m_lenght);
}

int IntArray::FindElement(ptl::__s32 value) const
{
  /** Перебираем каждый элемент контейнера, сравнивая его с заданным
   *  значением. Если присутствует совпадение, то возвращаем индекс,
   *  под которым распологается в контейнере заданное значение.
   */
  for (ptl::__s32 i{ 0 }; i < _m_lenght; ++i)
    if (_m_data[i] == value)
      return i;

  throw "E: Заданное значение в контейнере не найдено.";
}
