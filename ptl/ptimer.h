/*++

    (c) S-Patriarch, 2023
    (PTL) Patriarch library : ptimer.h

    Класс pTimer для замера времени работы кода.

Компонентные функции:

    start() - начало замера
    stop()  - завершение замера

    duration_milliseconds() - результат замера в миллисекундах
    duration_seconds()      - результат замера в секундах

--*/

#ifndef __PTL_PTIMER_H__
#define __PTL_PTIMER_H__

#include <chrono>

////////////////////////////////////////////////////////////////////////////////
namespace ptl
{
//------------------------------------------------------------------------------
class pTimer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_endTime;
public:
    pTimer(): 
        m_startTime(std::chrono::high_resolution_clock::now())
    {}
    //--------------------------------------------------------------------------
    void start()
    { 
        m_startTime=std::chrono::high_resolution_clock::now(); 
    }
    //--------------------------------------------------------------------------
    void stop()
    { 
        m_endTime=std::chrono::high_resolution_clock::now(); 
    }
    //--------------------------------------------------------------------------
    float duration_milliseconds() const
    {
        std::chrono::duration<float,std::milli> duration=m_endTime-m_startTime;
        return duration.count();
    }
    //--------------------------------------------------------------------------
    float duration_seconds() const
    {
        std::chrono::duration<float> duration=m_endTime-m_startTime;
        return duration.count();
    }
};
} // namespace ptl

#endif // __PTL_PTIMER_H__
