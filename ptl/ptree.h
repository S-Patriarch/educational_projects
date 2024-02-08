// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для дерева.
 */

/**
 *  (PTL) Patriarch library : ptree.h
 */

#ifndef __PTL_PTREE_H__
#define __PTL_PTREE_H__

/*
 * Дерево. 
 *
 * Методы:
 *   - ptree::Node::add_child() - добавление в массив детей узла нового элемента
 *   - ptree::Node::del_child() - удаление дочернего узла из Node
 *   - set_root() - установка корневого узла
 *   - add_node() - добавление нового узла дерева
 *   - get_node_by_number() - поиск вершины Node по ее номеру
 *   - del_node() - удаление узла из дерева
 */

#define SIZE 10

typedef signed int __s32;

namespace ptl
  {
//////////////////////////////////////////////////////////////////////
  class ptree
    {
    struct Node // структура узла дерева
      {
      Node( __s32 _number, Node* _parent = nullptr )
        : _S_number( _number ),
          _S_parent( _parent ),
          _S_childCount( 0 )
        { }

      ~Node()
        {
        for( __s32 i{0}; i < _S_childCount; i++ )
          { delete _S_children[ i ]; }
        }

      __s32  _S_number;           // номер вершины дерева

      Node*  _S_parent;           // указатель на родительскую вершину дерева
      Node*  _S_children[ SIZE ]; // список указателей дочерних вершин дерева
      __s32  _S_childCount;       // количество детей дерева
//--------------------------------------------------------------------
// Добавление в массив детей узла нового элемента.
      auto
      add_child( Node* _newChild ) -> void
        { _S_children[ _S_childCount++ ] = _newChild; }
//--------------------------------------------------------------------
// Удаление дочернего узла из Node.
      auto
      del_child( Node* _child ) -> void
        {
        __s32  _foundIndex = -1;

        for( __s32 i{0}; i < _S_childCount; i++ )
          {
          if( _S_children[ i ] == _child )
            // нашли индекс удаляемой вершины в массиве
            { _foundIndex = i; }
          }

        delete _S_children[ _foundIndex ]; // удалили вершину

        _S_childCount--; // удалили ее из массива

        for( __s32 i{_foundIndex}; i < _S_childCount; i++ )
          { _S_children[ i ] = _S_children[ i + 1 ]; }
        }
      };

    private:
      Node*  _M_root;             // указатель на корневую вершину дерева

    public:
      ptree()
        { _M_root = nullptr; }

      ~ptree()
        {
        if( _M_root != nullptr )
          { delete _M_root; }
        }
//--------------------------------------------------------------------
// Установка корневого узла дерева.
      auto
      set_root( __s32 _number ) -> void
        {
        if( _M_root != nullptr )
          {
          // удаляем корень, если он был
          delete _M_root;
          _M_root = nullptr;
          }

        _M_root = new Node( _number ); // устанавливаем новый корень
        }
//--------------------------------------------------------------------
// Добавление нового узла дерева.
      auto
      add_node( __s32 _parentNumber, __s32 _newNodeNumber ) -> void
        {
        // нашли родителя
        Node*  _parentNode = get_node_by_number( _parentNumber, _M_root );
        // создали новую вершину
        Node*  _newNode    = new Node( _newNodeNumber, _parentNode );

        // добавили к родителю
        _parentNode->add_child( _newNode );
        }
//--------------------------------------------------------------------
// Поиск вершины Node по ее номеру.
      auto 
      get_node_by_number( __s32 _number, Node* _current ) -> Node*
        {
        if( _current->_S_number == _number )
          // если нашли вершину с нужным узлом, возвращаем
          { return _current; }

        for( __s32 i{0}; i < _current->_S_childCount; i++ )
          {
          // обходим в глубину, пока не найдем искомую
          Node*  _found = get_node_by_number( _number, 
                                              _current->_S_children[ i ] );
          if( _found )
            { return _found; }
          }

        return nullptr;
        }
//--------------------------------------------------------------------
// Удаление узла из дерева.
      auto
      del_node( __s32 _number ) -> void
        {
        // нашли вершину для удаления
        Node*  _node   = get_node_by_number( _number, _M_root );

        // перебросили всех детей удаляемой вершины ее родителю
        for( __s32 i{0}; i < _node->_S_childCount; i++ )
          { _node->_S_parent->add_child( _node->_S_children[ i ] ); }

        // указатели, что у удаляемой вершины, больше нет детей
        _node->_S_childCount = 0;
        // удалить вершину
        _node->_S_parent->del_child( _node );
        }

    }; // class ptree
  } // namespace ptl

#endif // __PTL_PTREE_H__