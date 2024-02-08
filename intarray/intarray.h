// intarray.h -*- C++ -*-

/*
 * Copyright (c) Patriarh, 2023
 *
 * Заголовочный файл с описанием контейнера данных 
 */

#ifndef __IntegerArray__
#define __IntegerArray__

#include "ptype.h"

class IntArray
{
private:
  /** Размер контейнера
   *  Указатель для хранения данных
   */
  ptl::__s32        _m_lenght{ };
  ptl::__s32*       _m_data{ };

public:
  /** Конструктор, который строит пустой контейнер
   */
  IntArray() = default;

  /** Конструктор, который позволит построить контейнер заданного
   *  размера
   */
  IntArray(ptl::__s32);

  /** Конструктор копирования
   */
  IntArray(const IntArray&);

  /** Деструктор, который освобождает любые динамически выделенные
   *  данные
   */
  ~IntArray();

  /** Метод, возвращающий длину контейнера
   */
  int GetLenght() const;

  /** Метод возвращает значение элемента контейнера по заданному 
   *  индексу контейнера.
   */
  int GetElement(ptl::__s32) const;

  /** Метод стирающий контейнер и устанавливающий длину равную 0
   */
  void Erase();

  /** Перегрузка оператора [] для получения доступа к элементам
   *  контейнера
   */
  ptl::__s32& operator[](ptl::__s32);

  /** Перегрузка оператора =, чтобы мы могли скопировать контейнер
   */ 
  IntArray& operator=(const IntArray&);

  /** Метод уничтожает все существующие элементы в контейнере при
   *  изменении его размера
   */
  void Reallocate(ptl::__s32);

  /** Метод сохраняет все существующие элементы в контейнере при
   *  изменении его размера
   */
  void Resize(ptl::__s32);

  /** Метод вставлет элемент контейнера
   */
  void InsertBefore(ptl::__s32, ptl::__s32);

  /** Метод удаляет элемент контейнера
   */
  void Remove(ptl::__s32);

  /** Метод вставляет элемент в начало контейнера
   */
  void InsertAtBeginning(ptl::__s32);

  /** Метод вставляет элемент в конец контейнера
   */
  void InsertAtEnd(ptl::__s32);

  /** Метод поиска элемента контейнера по значению.
   *  Возвращает индекс, под которым находится искомый элемент 
   *  контейнера.
   */
  int FindElement(ptl::__s32) const;
};

#endif // __IntegerArray__