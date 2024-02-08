// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы со стеком.
 */

/**
 *  (PTL) Patriarch library : pstack.h
 */

#ifndef __PTL_PSTACK_H__
#define __PTL_PSTACK_H__

#ifndef __PTL_PNODE_H__
#include "pnode.h"
#endif

#ifndef __PTL_PEXCEPT_H__
#include "pexcept.h"
#endif

/*
 * Стек.
 * Реализован посредствам связанного списка.
 * (последний пришел, первый ушел)
 *
 * Методы:
 *   - is_empty() - проверяет стек на пустату (true - пуст, false - нет)
 *   - push() - добавляет элемент на вершину стека
 *   - pop() - удаляет элемент с вершины стека и возращает его значение
 *   - peek() - выводит значение элемента с вершины стека
 */

namespace ptl
  {
//////////////////////////////////////////////////////////////////////
  template <typename _Tp> 
  class pstack
    {
    private:
      pnode<_Tp>*  _M_top; // Указатель на вершину стека.

    public:
      pstack()
        : _M_top( nullptr )
        { }

      ~pstack() noexcept
        {
        while( _M_top )
          {
          pnode<_Tp>* 
          temp = _M_top;

          _M_top = _M_top->_M_next;

          delete temp;
          }
        }
//--------------------------------------------------------------------
      auto
      is_empty() -> bool
        { return _M_top == nullptr; }
//--------------------------------------------------------------------
      auto
      push( const _Tp& __data ) -> void
        {
        pnode<_Tp>* 
        temp = new pnode<_Tp>( __data );
        
        temp->_M_next = _M_top;
        _M_top = temp;
        }
//--------------------------------------------------------------------
      auto
      pop() -> _Tp
        {
        if( is_empty() )
          throw 
          pexception("W: Стек пуст.");

        _Tp  __result = _M_top->_M_data;

        pnode<_Tp>* 
        temp = _M_top;

        _M_top = _M_top->_M_next;

        delete temp;
        return __result;
        }
//--------------------------------------------------------------------
      auto
      peek() -> _Tp
        {
        if( is_empty() )
          throw 
          pexception("W: Стек пуст.");

        return _M_top->_M_data;
        }
    };

  } // namespace ptl

#endif // __PTL_PSTACK_H__