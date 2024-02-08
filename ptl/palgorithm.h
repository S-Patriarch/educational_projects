/*++

    Copyright (c) S-Patriarch, 2023
    (PTL) Patriarch library : palgorithm.h

    Описание библиотеки для работы с алгоритмами.

Функции:

    get_max - нахождение максимального элемента массива
    swap - обмен значениями двух объектов
    quick_sort - быстрая сортировка
    bubble_sort - пузырьковая сортировка
    merge_sort - сортировка слиянием
    insertion_sort - сортировка вставками
    selection_sort - сортировка выбором

--*/

#ifndef __PTL_PALGORITHM_H__
#define __PTL_PALGORITHM_H__

#include <utility>

typedef signed int   __s32;
typedef unsigned int __u32;

//////////////////////////////////////////////////////////////////////
namespace ptl
{
//--------------------------------------------------------------------
// Нахождение максимального элемента массива.
//
    template <typename _Tp> 
    _Tp 
    get_max(
        _Tp*  __array, 
        __u32 __size_array
        )
    {
        _Tp __max { __array[0] };

        for (__u32 __i = 0; __i < __size_array; __i++) {
            if (__array[__i] > __max) {
                __max = __array[__i];
            }
        }

        return __max;
    }

//--------------------------------------------------------------------
// Обмен значениями двух объектов.
// 
// Эта функция включает в себя конструкцию копирования и две
// операции присваивания, что может быть не самым эффективным
// способом замены содержимого классов, хранящих большие объемы
// данных, поскольку каждая из этих операций обычно работает в 
// линейном времени над их размером.
// 
// Примечательно, что все стандартные контейнеры специализируются
// таким образом, что вместо всего их содержимого меняются местами
// только несколько внутренних указателей, что заставляет их
// работать в реальном времени.
// 
// @code
//   int x=10, y=20;                // x:10 y:20
//   ptl::swap(x,y);                // x:20 y:10
// 
//   int foo[3];                    // foo: ?  ?  ?
//   int bar[] = {10,20,30};        // foo: ?  ?  ?   bar: 10 20 30
//   ptl::swap(foo,bar);            // foo: 10 20 30  bar: ?  ?  ?
// 
//   std::cout << "foo contains:";
//   for (int i: foo) std::cout << ' ' << i;
//   std::cout << '\n';
// @endcode
//
    template <typename _Tp> 
    void 
    swap(
        _Tp& __a, 
        _Tp& __b
        )
    { 
        _Tp __c { std::move(__a) }; 

        __a = std::move(__b); 
        __b = std::move(__c); 
    }

//--------------------------------------------------------------------
// Быстрая сортировка.
// Данный алгоритм сортировки разработан Ч.Э.Р. Хоаром в 1960 году
// 
// @code
//   ptl::quick_sort<int>(__array, 0, cst::_Size_Array-1);
// @endcode
//
    template <typename _Tp>
    void 
    quick_sort(
        _Tp*  __array, 
        __u32 __low, 
        __u32 __high
        )
    {
        __u32 __i { __low };
        __u32 __j { __high };
        _Tp   __y { };
        _Tp   __z { __array[(__low + __high) / 2] }; // опорный элемент
      
        do {
            while (__array[__i] < __z) __i++;
            while (__array[__j] > __z) __j--;

            if (__i <= __j) {
                if (__array[__i] > __array[__j]) {
                    __y          = __array[__i];
                    __array[__i] = __array[__j];
                    __array[__j] = __y;
                }
                __i++;
                __j--;
            }
        }
        while (__i <= __j);

        // рекурсия
        if (__low < __j)  quick_sort(__array, __low, __j);
        if (__i < __high) quick_sort(__array, __i, __high);
    }

//--------------------------------------------------------------------
// Пузырьковая сортировка.
// 
// @code
//   ptl::bubble_sort<int>(__array, cst::_Size_Array);
// @endcode
//
    template <typename _Tp>
    void 
    bubble_sort(
        _Tp*  __array, 
        __u32 __size_array
        )
    {
        for (__u32 __i = 0; __i < __size_array; __i++) {
            bool __flag { true };

            for (__u32 __j = 0; __j < __size_array - (__i+1); __j++) {
                if (__array[__j] > __array[__j+1]) {
                    __flag = false;

                    _Tp __b { __array[__j] };

                    __array[__j]   = __array[__j+1];
                    __array[__j+1] = __b;
                }
            }

            if (__flag) break;  
        }
    }

//--------------------------------------------------------------------
    void 
    merge(
        __s32* __array, 
        __s32  __l, 
        __s32  __m, 
        __s32  __r
        )
    {
        __s32 __nl { __m - __l + 1 };
        __s32 __nr { __r - __m };

        // создаем временные массивы
        __s32 __left[__nl];
        __s32 __right[__nr];

        // копируем данные во временные массивы
        for (__s32 __i = 0; __i < __nl; __i++)
            __left[__i] = __array[__l + __i];

        for (__s32 __j = 0; __j < __nr; __j++)
            __right[__j] = __array[__m + 1 + __j];

        __s32 __i { 0 }; 
        __s32 __j { 0 };
        __s32 __k { __l }; // начало левой части

        while (__i < __nl && __j < __nr) {
            // записываем минимальные элементы обратно во 
            //  входной массив
            if (__left[__i] <= __right[__j]) {
                __array[__k] = __left[__i];
                __i++;
            }
            else {
                __array[__k] = __right[__j];
                __j++;
            }
            __k++;
        }

        // записываем оставшиеся элементы левой части
        while (__i < __nl) {
            __array[__k] = __left[__i];
            __i++;
            __k++;
        }

        // записываем оставшиеся элементы правой части
        while (__j < __nr) {
            __array[__k] = __right[__j];
            __j++;
            __k++;
        }
    }

//--------------------------------------------------------------------
// Сортировка слиянием.
//
    void 
    merge_sort(
        __s32* __array, 
        __s32  __l, 
        __s32  __r
        )
    {
        if (__l >= __r)
            return; // выход из рекурсии

        __s32 __m { (__l + __r - 1) / 2 };

        merge_sort(__array, __l, __m);
        merge_sort(__array, __m+1, __r);

        merge(__array, __l, __m, __r);
    }

//--------------------------------------------------------------------
// Сортировка вставками.
// Хорошо работает с небольшим набором данных, хоть и меет достаточно
// большую вычислительную сложность на большом объеме данных.
// 
// @code
//   ptl::insertion_sort<int>(__array, cst::_Size_Array);
// @endcode
//
    template <typename _Tp>
    void 
    insertion_sort(
        _Tp*  __array, 
        __u32 __size_array
        ) 
    { 
        for (__u32 __i = 1; __i < __size_array; __i++) {
            _Tp   __key { __array[__i] }; 
            __u32 __j { __i - 1 }; 
       
            // сдвигаем элементы __array[0..__i-1], которые больше чем
            //  __key, на одну позицию вперед
            while (__j >= 0 && __array[__j] > __key) {
                __array[__j+1] = __array[__j];
                __j = __j - 1;
            }

            __array[__j+1] = __key;
        }
    }

//--------------------------------------------------------------------
// Сортировка выбором.
// Это гибрид между пузырьковой сортировкой и сортировкой вставками.
// 
// @code
//   ptl::selection_sort<int>(__array, cst::_Size_Array);
// @endcode
//
    template <typename _Tp>
    void 
    selection_sort(
        _Tp*  __array, 
        __u32 __size_array
        )
    {
        __u32 __i;
        __u32 __j;
        __u32 __min_idx;
  
        // перебираем все элементы массива
        for (__i = 0; __i < __size_array-1; __i++) {
            // находим минимальный элемент в оставшейся части массива
            __min_idx = __i;

            for (__j = __i+1; __j < __size_array; __j++)
                if (__array[__j] < __array[__min_idx])
                    __min_idx = __j;
  
            // меняем найденный минимальный элемент со значением 
            // текущего элемента
            _Tp __temp = __array[__min_idx];

            __array[__min_idx] = __array[__i];
            __array[__i] = __temp;
        }
    }

} // namespace ptl

#endif // __PTL_PALGORITHM_H__