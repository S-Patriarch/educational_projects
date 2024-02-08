/*++

    Copyright (c) S-Patriarch, 2023
    (PTL) Patriarch library : psha.h

    Описание библиотеки для работы с хэшированием.

Методы:

    sha1 - хэширование строки алгоритмом SHA-1

Использование:

    ptl::pSha    _sha;
    std::string  _passwd = "qwerty12345";
    std::string  _hash   = _sha.sha1(_passwd.c_str(), 
                                     sizeof(_passwd.c_str()) - 1);

--*/

#ifndef __PTL_SHA_H__
#define __PTL_SHA_H__

#ifdef _WIN32
#pragma once
#endif

#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>

#define one_block_size_bytes    64 // количество байт в блоке
#define one_block_size_uints    16 // количество 4байтовых в блоке
#define block_expend_size_uints 80 // количество 4байтовых в 
                                    // дополненном блоке

#define SHA1HASHLENGTHBYTES     20
#define SHA1HASHLENGTHUINTS     5

typedef unsigned int __u32;

typedef __u32*       Block;
typedef __u32        ExpendBlock[block_expend_size_uints];

//////////////////////////////////////////////////////////////////////
namespace ptl
{
    class pSha
    {
    public:
        pSha() = default;
        ~pSha() = default;

//--------------------------------------------------------------------
// Реализация алгоритма хэширования SHA-1.
// Возвращает строку с хэшем хэшированного массива символов.
//
        std::string
        sha1(
            const char* message, 
            __u32       msize_bytes
            ) 
        {
            // инициализация
            __u32 A = H[0];
            __u32 B = H[1];
            __u32 C = H[2];
            __u32 D = H[3];
            __u32 E = H[4];
    
            // подсчет целого числа блоков
            __u32  
            totalBlockCount = msize_bytes / one_block_size_bytes;
    
            // подсчет, сколько байт нужно, чтобы дополнить последний блок
            __u32  
            needAdditionalBytes = 
                one_block_size_bytes - 
                (msize_bytes - totalBlockCount * one_block_size_bytes);
        
            if (needAdditionalBytes < 8) {
                totalBlockCount += 2;
                needAdditionalBytes += one_block_size_bytes;
            } 
            else {
                totalBlockCount += 1;
            }
    
            // размер дополненного по всем правилам сообщения
            __u32  
            extendedMessageSize = msize_bytes + needAdditionalBytes;
    
            // выделяем новый буфер и копируем в него исходный
            unsigned char*
            newMessage = new unsigned char[extendedMessageSize];
            std::memcpy(
                newMessage, 
                message, 
                msize_bytes
            );
    
            // первый бит ставим '1', остальные обнуляем
            newMessage[msize_bytes] = 0x80;    
            std::memset(
                newMessage + msize_bytes + 1, 
                0, 
                needAdditionalBytes - 1
            );
    
            // задаем длину исходного сообщения в битах
            __u32*  
            ptr_to_size  = (__u32*)(newMessage + extendedMessageSize - 4); 
            *ptr_to_size =  bring_to_human_view(msize_bytes * 8);
    
            ExpendBlock  exp_block;
        
            // раунды поехали
            for (__u32 i = 0; i < totalBlockCount; i++) {
                // берем текущий блок и дополняем его
                unsigned char* 
                cur_p = newMessage + one_block_size_bytes * i;
            
                Block block = (Block)cur_p;
        
                // первые 16 4байтовых чисел
                for (__u32 j = 0; j < one_block_size_uints; j++) {
                    exp_block[j] = bring_to_human_view(block[j]);
                }

                // следующие 64...
                for (__u32 j = one_block_size_uints; j < block_expend_size_uints; j++) {
                    exp_block[j] = 
                        exp_block[j-3] ^ 
                            exp_block[j-8] ^ 
                                exp_block[j-14] ^ 
                                    exp_block[j-16];
                    exp_block[j] = cycle_shift_left(exp_block[j], 1);
                }
            
                // инициализация 
                __u32 a = H[0];
                __u32 b = H[1];
                __u32 c = H[2];
                __u32 d = H[3];
                __u32 e = H[4];

                // пересчитываем
                for (__u32 j = 0; j < block_expend_size_uints; j++) {
                    __u32 f;
                    __u32 k;
                
                    // в зависимости от раунда считаем по-разному
                    if (j < 20) {
                        f = (b & c) | ((~b) & d);
                        k = 0x5A827999;
                    } 
                    else if (j < 40) {
                        f = b ^ c ^ d;
                        k = 0x6ED9EBA1;
                    } 
                    else if (j < 60) {
                        f = (b & c) | (b & d) | (c & d);
                        k = 0x8F1BBCDC;
                    } 
                    else {
                        f = b ^ c ^ d;
                        k = 0xCA62C1D6;
                    }
        
                    // перемешивание
                    __u32  
                    temp = cycle_shift_left(a,5) + f + e + k + exp_block[j];
            
                    e = d;
                    d = c;
                    c = cycle_shift_left(b,30);
                    b = a;
                    a = temp;   
                }

                // пересчитываем
                A = A + a;
                B = B + b;
                C = C + c;
                D = D + d;
                E = E + e;
            }

            // чистим за собой
            delete[] newMessage;

            // конвертация промежуточных хэшей в строку
            std::stringstream ss;
  
            ss << std::hex << std::setfill('0') << std::setw(8) << A
               << std::hex << std::setfill('0') << std::setw(8) << B
               << std::hex << std::setfill('0') << std::setw(8) << C
               << std::hex << std::setfill('0') << std::setw(8) << D
               << std::hex << std::setfill('0') << std::setw(8) << E;

            return ss.str();
        }

    private:
        const __u32  
        H[5] { 
            0x67452301,
            0xEFCDAB89,
            0x98BADCFE,
            0x10325476,
            0xC3D2E1F0 
        }; // константы, согласно стандарту

//--------------------------------------------------------------------
        __u32 
        cycle_shift_left(
            __u32 val, 
            __u32 bit_count
            ) 
        { return (val << bit_count | val >> (32-bit_count)); }

//--------------------------------------------------------------------
        __u32 
        bring_to_human_view(
            __u32 val
            ) 
        {
            return ((val & 0x000000FF) << 24) | 
                   ((val & 0x0000FF00) << 8)  | 
                   ((val & 0x00FF0000) >> 8)  | 
                   ((val & 0xFF000000) >> 24);
        }
    };
    
} // namespace ptl

#endif // __PTL_SHA_H__