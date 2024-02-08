// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы со 
 * связанным списком данных.
 */

/**
 *  (PTL) Patriarch library : plist.h
 */

#ifndef __PTL_PLIST_H__
#define __PTL_PLIST_H__

#include <iostream>

#ifndef __PTL_PNODE_H__
#include "pnode.h"
#endif

/*
 * Связанный список данных. 
 *
 * Методы:
 *   - push() - вставка в конец списка
 *   - push_front() - вставка в начало списка
 *   - insert() - вставка в середину списка
 *   - remove() - удаление узла списка по значению
 *   - remove_position() - удаление узла списка по позиции
 *   - show() - вывод содержимого списка через пробел
 *   - clear() - удаление всего списка
 *   - find() - поиск элемента в списке (найден - true, нет - false)
 *
 * @code
 *   ptl::plist<ptl::__s32> list;
 *   list. ...;
 * @endcode
 */

typedef unsigned int __u32;

namespace ptl
  {
//////////////////////////////////////////////////////////////////////
  /*
   * Связанный список, который хранит узлы, а также 
   * предоставляет методы для управления данными.
   */
  template <typename _Tp> 
  class plist
    {
    private:
      pnode<_Tp>*  _M_head; // Начало связанного списка данных.

    public:
      plist() 
        : _M_head( nullptr )
        { }

      ~plist() noexcept
        { clear(); }
//--------------------------------------------------------------------
      auto
      push( _Tp __data ) -> void
        {
        /** Создаем новый узел.
         */
        pnode<_Tp>* node = new pnode<_Tp>( __data );

        /** Если список пуст, то возвращаем узел.
         */
        if( _M_head == nullptr )
          {
          _M_head = node;
          return;
          }

        /** Ищем последний элемент списка.
         */
        pnode<_Tp>* last = _M_head;
        while( last->_M_next != nullptr )
          {
          last = last->_M_next;
          }

        /** Обновляем указатель _M_next последнего узла на 
         *  указатель на новый узел.
         */
        last->_M_next = node;
        return;
        }
//--------------------------------------------------------------------
      auto
      push_front( _Tp __data ) -> void
        {
        pnode<_Tp>* node = new pnode<_Tp>( __data );
        node->_M_next = _M_head;
        _M_head = node;
        }
//--------------------------------------------------------------------
      auto
      insert( __u32 __position, _Tp __data ) -> void
        {
        /** Создаем новый узел.
         */
        pnode<_Tp>* new_node = new pnode<_Tp>( __data );

        /** Если список пуст, то новый узел и будет началом списка.
         */
        if( _M_head == nullptr )
          {
          _M_head = new_node;
          return;
          }

        if( __position == 0)
          {
          /** Крайний случай - вставка в начало списка.
           */
          new_node->_M_next = _M_head;
          _M_head = new_node;
          return;
          }

        __u32  __curr_pos{ 0 };

        pnode<_Tp>* currend = _M_head;

        /** Идем по списку, пока список не кончится, или
         *  пока не дойдем до позиции.
         */
        while( __curr_pos < __position - 1 && currend->_M_next != nullptr )
          {
          currend = currend->_M_next;
          __curr_pos++;
          }

        /** Меняем указатель на следующий узел на
         *  указатель на новый узел.
         */
        pnode<_Tp>* next = currend->_M_next;
        currend->_M_next = new_node;

        /** Связываем список обратно, меняем указатель на узел,
         *  следующий после нового узла, на указатель на узел,
         *  следующий за current.
         */
        new_node->_M_next = next;
        }
//--------------------------------------------------------------------
      auto
      remove( _Tp __data ) -> void
        {
        pnode<_Tp>* temp = _M_head;
        pnode<_Tp>* prev = nullptr;

        /** Крайний случай - удаляем начало списка.
         */
        if( temp && temp->_M_data == __data )
          {
          _M_head = temp->_M_next;
          delete temp;
          return;
          }

        /** Идем по списку, пока не найдем узел со
         *  значением данных, равных ключу.
         */
        while( temp && temp->_M_data != __data )
          {
          prev = temp;
          temp = temp->_M_next;
          }

        /** Если узел не найден, возвращаем.
         */
        if( !temp )
          return;

        /** Меняем указатель следующего узла для предыдущего узла на 
         *  узел, следующий за удаляемым узлом, и удаляем узел с
         *  данными.
         */
        prev->_M_next = temp->_M_next;
        delete temp;
        }
//--------------------------------------------------------------------
      auto
      remove_position( __u32 __position ) -> void
        {
        pnode<_Tp>* temp = _M_head;
        pnode<_Tp>* prev = nullptr;

        /** Крайний случай - удаляем начало списка.
         */
        if( __position == 0 )
          {
          _M_head = temp->_M_next;
          delete temp;
          return;
          }

        __u32  __curr_pos{ 0 };

        while( temp != nullptr && __curr_pos < __position )
          {
          prev = temp;
          temp = temp->_M_next;
          __curr_pos++;
          }

        /** Если узел не найден, возвращаем.
         */
        if( !temp )
          return;

        /** Меняем указатель следующего узла для предыдущего узла на 
         *  узел, следующий за удаляемым узлом, и удаляем узел с
         *  данными.
         */
        prev->_M_next = temp->_M_next;
        delete temp;
        }
//--------------------------------------------------------------------
      auto
      show() -> void
        {
        pnode<_Tp>* currend = _M_head;

        while( currend != nullptr )
          {
          std::cout << currend->_M_data
                    << " ";
          currend = currend->_M_next;
          }
        }
//--------------------------------------------------------------------
      auto
      clear() -> void
        {
        pnode<_Tp>* currend = _M_head;

        while( currend != nullptr )
          {
          pnode<_Tp>* temp = currend->_M_next;
          delete currend;
          currend = temp;
          }

        _M_head = nullptr;
        }
//--------------------------------------------------------------------
      auto
      find( _Tp __data) -> bool
        {
        pnode<_Tp>* currend = _M_head;        

        while( currend != nullptr )
          {
          if( currend->_M_data == __data )
            return true;
          currend = currend->_M_next;
          }

        return false;
        }
    };

  } // namespace ptl

#endif // __PTL_PLIST_H__