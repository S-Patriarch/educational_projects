// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для графа.
 */

/**
 *  (PTL) Patriarch library : pgraph.h
 */

#ifndef __PTL_PGRAPH_H__
#define __PTL_PGRAPH_H__

#include <iostream>

#ifndef __PTL_PEXCEPT_H__
#include "pexcept.h"
#endif

/*
 * Граф. 
 *
 * Методы:
 *   - is_exists_vertex() - проверка существования вершины графа
 *   - is_exists_edge() - проверка существования ребра графа
 *   - add_vertex() - добавление вершины графа
 *   - add_edge() - добавление ребра графа
 *   - del_vertex() - удаление вершины графа
 *   - del_edge() - удаление ребра графа
 *   - size() - размер графа
 *   - depth() - обход графа в глубину
 *   - width() - обход графа в ширину
 *   - count_paths() - поиск количества всех возможных путей
 *   - find_min_dd() - поиск кратчайшего расстояния от определенной вершины 
 *                     до всех других
 *   - find_min_df() - поиск кратчайшего расстояния между любой парой вершин
 */

#define SIZE       10
#define VERYBIGINT 1000000000

typedef signed int   __s32;
typedef unsigned int __u32;

namespace ptl
  {
//////////////////////////////////////////////////////////////////////
  /*
   * Граф.
   */
  class pgraph
    {
    private:
      __u32  _M_matrix[SIZE][SIZE]; // Матрица смежности
      __u32  _M_vertexes[SIZE];     // Хранилище вершин
      __u32  _M_vertex_count;       // Количество добавленных вершин

      auto
      depth_dfs( __u32 __current, bool __visited[] ) -> void
        {
        std::cout << "v"
                  << __current
                  << " -> ";

        __visited[__current] = true; // Помечаем как посещенную.

        for( __u32 __i{ 0 }; __i < SIZE; __i++ )
          {
          if( is_exists_edge( __current, __i ) && !__visited[__i] )
            /** Если существует ребро и вершина не посещаласть,
             *  то пройдем по нему в смежную вершину.
             */
            { depth_dfs( __i, __visited ); }
          }
        }
//--------------------------------------------------------------------
      auto
      count_paths_dfs(__u32 __from, __u32 __to, bool __visited[] ) -> __u32
        {
        /** Если источник и пункт назначения совпадают,
         *  то считаем путь найденным.
         */
        if( __from == __to )
          { return 1; }

        /** Помечаем как посещенную.
         */
        __visited[__from] = true;

        __u32  __count{ 0 };

        for( __u32 __i{ 0 }; __i < SIZE; __i++ )
          {
          if( is_exists_edge( __from, __i ) && !__visited[__i] )
            { __count += count_paths_dfs(  __i, __to, __visited ); }
          }

        /** Снимаем метку с текущей вершины перед возвратом.
         */
        __visited[__from] = false;

        return __count;
        }

    public:
      pgraph() 
        {
        for( __u32 __i{ 0 }; __i < SIZE; __i++ )
          {
          for( __u32 __j{ 0 }; __j < SIZE; __j++ )
            { _M_matrix[__i][__j] = 0; }
          }

        _M_vertex_count = 0;
        }

      ~pgraph() noexcept
        { }
//--------------------------------------------------------------------
// Проверка существования вершины графа.
// true  - есть такая вершина в графе.
// false - такой вершины в графе нет.
      auto
      is_exists_vertex( __u32 __vnumber ) -> bool
        {
        for( __u32 __i{ 0 }; __i < _M_vertex_count; __i++ )
          {
          if( _M_vertexes[__i] == __vnumber )
            { return true; }
          }
        return false;
        }
//--------------------------------------------------------------------
// Проверка существования ребра графа.
// true  - есть такое ребро в графе.
// false - такого ребра в графе нет.
      auto
      is_exists_edge( __u32 __v1, __u32 __v2 ) -> bool
        { return _M_matrix[__v1][__v2] > 0; }
//--------------------------------------------------------------------
// Добавление вершины графа.
      auto
      add_vertex( __u32 __vnumber ) -> void
        { _M_vertexes[_M_vertex_count++] = __vnumber; }
//--------------------------------------------------------------------
// Добавление ребра графа.
      auto
      add_edge( __u32 __v1, __u32 __v2, __u32 __weight = 1 ) -> void
        {
        _M_matrix[__v1][__v2] = __weight;
        _M_matrix[__v2][__v1] = __weight;
        }
//--------------------------------------------------------------------
// Удаление вершины графа.
      auto
      del_vertex( __u32 __vnumber ) -> void
        {
        if( !is_exists_vertex( __vnumber ) )
          { throw pexception("E: Такой вершины в графе нет."); }

        /** Обнуляем столбец и строку матрицы.
         */
        for( __u32 __i{ 0 }; __i < _M_vertex_count; __i++ )
          {
          _M_matrix[__i][__vnumber] = 0;
          _M_matrix[__vnumber][__i] = 0;
          }

        /** Удаляем вершину из списка вершин.
         */
        __s32  __index{ -1 };

        for( __s32 __i{ 0 }; 
             __i < static_cast<__s32>( _M_vertex_count ); 
             __i++ )
          {
          if( _M_vertexes[__i] == __vnumber )
            { __index = __i; }
          }

        --_M_vertex_count;

        for( __s32 __i{ __index }; 
             __i < static_cast<__s32>( _M_vertex_count ); 
             __i++ )
          { _M_vertexes[__i] = _M_vertexes[__i+1]; }
        }
//--------------------------------------------------------------------
// Удаление ребра графа.
      auto
      del_edge( __u32 __v1, __u32 __v2 ) -> void
        {
        _M_matrix[__v1][__v2] = 0;
        _M_matrix[__v2][__v1] = 0;
        }
//--------------------------------------------------------------------
// Размер графа.
      auto
      size() -> __u32
        { return ( _M_vertex_count - 1 ); }
//--------------------------------------------------------------------
// Обход графа в глубину.
      auto
      depth( __u32 __start ) -> void
        {
        bool  __visited[SIZE]; // Список посещенных вершин.

        // Инициализируем как не посещенные.
        for( __u32 __i{ 0 }; __i < SIZE; __i++ )
          { __visited[__i] = false; }

        depth_dfs( __start, __visited ); // Запуск алгоритма.
        }
//--------------------------------------------------------------------
// Обход графа в ширину.
      auto
      width( __u32 __start ) -> void
        {
        __u32  __queue_to_visit[SIZE]; // Очередь вершин для обхода.
        __u32  __queue_count{ 0 };

        bool   __visited[SIZE]; // Список посещенных вершин.

        // Инициализируем как не посещенные.
        for( __u32 __i{ 0 }; __i < SIZE; __i++ )
          { __visited[__i] = false; }

        // Кладем в очередь начальную вершину.
        __queue_to_visit[__queue_count++] = __start;

        while( __queue_count > 0 )
          {
          // Взятие из очереди вершины.
          __u32  __current = __queue_to_visit[0];
          __queue_count--;

          for( __u32 __i{ 0 }; __i < __queue_count; __i++ )
            { __queue_to_visit[__i] = __queue_to_visit[__i+1]; }

          __visited[__current] = true;

          std::cout << "v"
                    << __current
                    << " -> ";

          // Поиск смежных вершин и добавление их в очередь.
          for( __u32 __i{ 0 }; __i < SIZE; __i++ )
            {
            bool  __already_added{ false };

            for( __u32 __j{ 0 }; __j < __queue_count; __j++ )
              {
              if( __queue_to_visit[__j] == __i )
                {
                __already_added = true;
                break;
                }
              }

            if( !__already_added  
                && is_exists_edge( __current, __i ) 
                && !__visited[__i] )
              { __queue_to_visit[__queue_count++] = __i; }
            }
          }
        }
//--------------------------------------------------------------------
// Поиск количества всех возможных путей между двумя вершинами
// графа на основе графа матрицы смежности.
      auto
      count_paths( __u32 __from, __u32 __to ) -> __u32
        {
        bool   __visited[SIZE]; // Список посещенных вершин.

        // Инициализируем как не посещенные.
        for( __u32 __i{ 0 }; __i < SIZE; __i++ )
          { __visited[__i] = false; }       

        return count_paths_dfs(__from, __to, __visited ); // Запуск алгоритма.
        }
//--------------------------------------------------------------------
// Поиск кратчайшего расстояния от определенной вершины до всех
// других во взвешанном графе.
// Алгоритм Дейкстры.
      auto
      find_min_dd( __u32 __from_vert ) -> void
        {
        __u32  __distances[SIZE]; // Массив меток.

        for( __u32 __i{0}; __i < SIZE; __i++ )
          { __distances[__i] = VERYBIGINT; }

        __distances[__from_vert] = 0;

        bool  __passed[SIZE]; // Признак, что вершина окрашена.

        // Все неокрашены изначально.
        for( __u32  __i{0}; __i < SIZE; __i++ )
          { __passed[__i] = false; }

        // Принимаем стартовую вершину за текущую.
        __u32  __current_vertex_num = __from_vert;
        __u32  __min_dist           = 0;

        while( __min_dist != VERYBIGINT )
          {
          __passed[__current_vertex_num] = true; // Окрашиваем текущую.

          for( __u32  __i{0}; __i < SIZE; __i++ )
            {
            // Для смежных ребер пересчитываем метки.
            if( is_exists_edge( __current_vertex_num, __i )
                && __distances[__current_vertex_num] 
                   + _M_matrix[__current_vertex_num][__i] 
                   < __distances[__i] )
              { 
              __distances[__i] = __distances[__current_vertex_num]
                                 + _M_matrix[__current_vertex_num][__i];
              }
            }

          __min_dist = VERYBIGINT;

          for( __u32  __i{0}; __i < SIZE; __i++ )
            {
            // Выбираем новую текущую вершину.
            if( is_exists_vertex( __i )
                && !__passed[__i]
                && __distances[__i] < __min_dist )
              {
              __min_dist           = __distances[__i];
              __current_vertex_num = __i;
              }
            }
          }

        for( __u32 __i{0}; __i < _M_vertex_count; __i++ )
          { 
          std::cout << "v"
                    << __i
                    << ": "
                    << __distances[_M_vertexes[__i]]
                    << ", ";
          }
        }
//--------------------------------------------------------------------
// Поиск кратчайшего расстояния между любой парой вершин в графе.
// Алгоритм Флойда-Уоршелла (сокращенно - Флойда).
      auto
      find_min_df() -> void
        {
        __u32  __weight[SIZE][SIZE]; // Матрица путей.

        // Инициализация матрицы.
        for( __u32 i{0}; i < SIZE; i++ )
          {
          for( __u32 j{0}; j < SIZE; j++ )
            {
            if( i == j )
              // Путь до самой себя равен 0.
              { __weight[i][j] = 0; }
            else
              {
              if( !is_exists_edge( i, j ) )
                // Если ребра нет.
                { __weight[i][j] = VERYBIGINT; }
              else
                // Если ребро есть.
                { __weight[i][j] = _M_matrix[i][j]; }
              }
            }
          }

        for( __u32 k{0}; k < _M_vertex_count; k++ )
          {
          __u32  _ck = _M_vertexes[k]; // Возмем номер вершины.

          for( __u32 i{0}; i < _M_vertex_count; i++ )
            {
            if( i == k )
              { continue; }

            __u32  _ci = _M_vertexes[i];

            for( __u32 j{0}; j < _M_vertex_count; j++ )
              {
              if( j == k )
                { continue; }

              __u32  _cj = _M_vertexes[j];

              if( __weight[_ci][_ck] + __weight[_ck][_cj]
                  < __weight[_ci][_cj] )
                // Пересчет матрицы путей.
                { 
                __weight[_ci][_cj] = 
                  __weight[_ci][_ck] + __weight[_ck][_cj]; 
                }
              }
            }
          }

        for( __u32 i{0}; i < _M_vertex_count; i++ )
          // Вывод всех минимальных путей от вершины 0
          {
          std::cout << "v"
                    << i
                    << ": "
                    << __weight[0][_M_vertexes[i]]
                    << ", ";
          }
        }

    }; // class pgraph
  } // namespace ptl

#endif // __PTL_PGRAPH_H__