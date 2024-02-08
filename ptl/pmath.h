/*++

    Copyright (c) S-Patriarch, 2023
    (PTL) Patriarch library : pmath.h

    Описание библиотеки для работы с математическими функциями.

Функции:

    factorial - вычисление факториала заданного числа
    harmonic_mean - вычисление среднего гармонического
    add - сложение двух значений между собой

--*/

#ifndef __PTL_PMATH_H__
#define __PTL_PMATH_H__

#ifndef __PTL_PEXCEPT_H__
#include "pexcept.h"
#endif

typedef unsigned long long int __u64;

//////////////////////////////////////////////////////////////////////
namespace ptl
{
//--------------------------------------------------------------------
// Вычисление факториала заданного числа.
// Формула: N! = N * (N-1)!
// Принимает: 
//   - число, факториал которого необходимо вычислить
// Возвращает: 
//   - факториал переданного числа
//
    __u64 
    factorial(
        __u64 __number_factorial
        )
    {
        if (__number_factorial == 0) return 0; // Факториал 0 равен 0
        if (__number_factorial == 1) return 1; // Факториал 1 равен 1
        return __number_factorial * factorial(__number_factorial - 1);
    }

//--------------------------------------------------------------------
// Вычисление среднего гармонического.
// Формула: Xгарм = n / (Sum + 1.0 / Xn)
// Принимает:
//   - массив чисел
//   - размер массива
// Возвращает:
//   - среднее гармоническое
//
    template <typename _Tp>
    double 
    harmonic_mean(
        _Tp   __array[], 
        __u64 __size_array
        )
    {
        if (__size_array == 0) {
            throw 
            pexception("E: ptl::harmonic_mean() : "
                       "Передан нулевой массив.");
        }

        double __sum { };

        for (__u64 i = 0; i < __size_array; i++) {
            if (__array[i] == static_cast<_Tp>(0)) {
                throw 
                pexception("E: ptl::harmonic_mean() : "
                           "Элемент массива равен нулю.");
            }
        
            __sum = __sum + 1.0 / __array[i];
        }

        if ((__sum < 0.0001) && (__sum > -0.0001)) {
            throw 
            pexception("E: ptl::harmonic_mean() : "
                       "Сумма элементов массива равна нулю.");
        }

        return __size_array / __sum;
    }

//--------------------------------------------------------------------
// Сложение двух значений между собой.
//
    template <typename _Tp, typename _Up>
    auto 
    add(
        _Tp __a, 
        _Up __b
        ) -> decltype(__a + __b)
    { 
        return __a + __b; 
    }

} // namespace ptl

#endif // __PTL_PMATH_H__