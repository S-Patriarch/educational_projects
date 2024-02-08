// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для бинарного дерева.
 */

/**
 *  (PTL) Patriarch library : pbtree.h
 */

#ifndef __PTL_PBTREE_H__
#define __PTL_PBTREE_H__

/*
 * Бинарное дерево. 
 *
 * Методы:
 *   - add_int() - добавление нового элемента
 */

#define SIZE 10

typedef signed int __s32;

namespace ptl
  {
//////////////////////////////////////////////////////////////////////
  class pbtree
    {
    privet:
      Node*  _M_root;         // корневой узел

    public:
      struct Node // структура узла бинарного дерева
        {
        Node( __s32 _d, Node* _p = nullptr )
          : _S_data( _d ),
            _S_parent( _p )
          {
          _S_leftChild  = nullptr;
          _S_rightChild = nullptr;
          }

        ~Node()
          {
          if( _S_rightChild != nullptr )
            { delete _S_rightChild; }
          if( _S_leftChild != nullptr )
            { delete _S_leftChild; }
          }

        Node*  _S_parent;     // родительский узел

        Node*  _S_leftChild;  // левый узел
        Node*  _S_rightChild; // правый узел

        __s32  _S_data;       // данные узла

        }; // struct Node
      
      pbtree()
        { _M_root = nullptr; }

      ~pbtree() noexcept
        {
        if( _M_root != nullptr )
          { delete _M_root; }
        }
//--------------------------------------------------------------------
// Добавление нового элемента.
      auto
      add_int(  __s32 _newData ) -> void
        {
        if( _M_root == nullptr )
          // если дерево пустое, то новый элемент станет корнем
          { _M_root = new Node( _newData ); }
        else
          {
          Node*  _current = _M_root; // начинаем с корня
          Node*  _newNode = nullptr;

          while( _newNode == nullptr )
            {
            if( _current->_S_data >= _newData )
              // если элемент меньше текущего, идем влево
              {
              if( _current->_S_leftChild != nullptr )
                {
                _current = _current->_S_leftChild;
                continue;
                }
              // если левого узла нет, то нашли место для нового элемента
              _newNode = new Node( _newData, _current );
              _current->_S_leftChild = _newNode;
              }
            else
              // если елемент меньше текущего, идем вправо
              {
              if( _current->_S_rightChild != nullptr )
                {
                _current = _current->_S_rightChild;
                continue;
                }
              // если правого узла нет, то нашли место для нового элемента
              _newNode = new Node( _newData, _current );
              _current->_S_rightChild = _newNode;
              }
            }
          }        
        }

    }; // class pbtree
  } // namespace ptl

#endif // __PTL_PBTREE_H__