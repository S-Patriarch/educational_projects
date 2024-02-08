// main.cpp -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Поиск всех пар знакомств через три рукопожатия.
 * 
 * Сначала строится граф на основе введенных данных пользователя. 
 * Затем выполняем поиск в ширину для каждого узла графа с глубиной 
 * равной трем (то есть три рукопожатия). Если находится вершина на 
 * третьем уровне, она выводится как пара знакомства.
 */

#ifdef _WIN32
#include "ptl\ptype.h"
#include "ptl\pconio.h"
#else
#include "ptl/ptype.h"
#include "ptl/pconio.h"
#endif

#include <iostream>
#include <vector>
#include <queue>
//////////////////////////////////////////////////////////////////////
auto
findFriendPairs( const std::vector<std::vector<ptl::__s32>>&, 
                 ptl::__s32, 
                 ptl::__s32 ) -> void;
//////////////////////////////////////////////////////////////////////
auto
main() -> int
  {
  ptl::setlocale_WIN32_rus();
  ptl::clrscr();

  ptl::__s32  _numNodes;
  ptl::__s32  _numEdges;

  // формируем граф

  std::cout 
    << "Введите через пробел количество вершин (людей) и количество ребер (связей): "
    << std::endl;
  std::cin >> _numNodes 
           >> _numEdges;

  std::vector<std::vector<ptl::__s32>> _graph( _numNodes );

  std::cout 
    << "\nВведите через пробел ребра (связи) между вершинами (людьми): "
    << std::endl;

  for (ptl::__s32 i{0}; i < _numEdges; i++) 
    {
    ptl::__s32  _u;
    ptl::__s32  _v;

    std::cin >> _u 
             >> _v;

    // добавляем двустороннюю связь между узлами
    _graph[ _u ].push_back( _v );
    _graph[ _v ].push_back( _u );
    }

    for( ptl::__s32 i{0}; i < _numNodes; i++) 
      {
      std::cout << "\nПара знакомства для пользователя " 
                << i 
                << " : ";

      ::findFriendPairs( _graph, i, 3 );
      }

  return 0;
  }
//--------------------------------------------------------------------
auto
findFriendPairs( const std::vector<std::vector<ptl::__s32>>& _graph, 
                 ptl::__s32 _startNode, 
                 ptl::__s32 _depth ) -> void
  {
  std::vector<bool>  _visited( _graph.size(), false );
  std::queue<std::pair<ptl::__s32, ptl::__s32>>  _q;

  ptl::__s32  _level{ 0 };

  _q.push( std::make_pair( _startNode, _level ) );

  while( !_q.empty() ) 
    {
    std::pair<ptl::__s32, ptl::__s32> _node{ _q.front() };
    _q.pop();

    ptl::__s32  _currentNode{ _node.first };
    ptl::__s32  _currentLevel{ _node.second };

    if( _currentLevel == _depth ) 
      {
      std::cout << "( " 
                << _startNode 
                << ", " 
                << _currentNode 
                << " )" 
                << std::endl;
      continue;
      }

    _visited[ _currentNode ] = true;

    for( ptl::__s32 i{0}; i < _graph[ _currentNode ].size(); i++) 
      {
      ptl::__s32  _adjacentNode{ _graph[ _currentNode ][ i ] };

      if( !_visited[ _adjacentNode ]) 
        {
        _q.push( std::make_pair( _adjacentNode, _currentLevel + 1 ) );
        _visited[ _adjacentNode ] = true;
        }
      }
    }
  }
