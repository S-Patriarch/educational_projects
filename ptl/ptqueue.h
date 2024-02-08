/*++

    (c) S-Patriarch, 2023
    (PTL) Patriarch library : ptqueue.h

    Потокобезопасная очередь с блокировкой и условными переменными.

Методы:

    push() - добавление элемента в очередь
    pop()  - удаление элемента из очереди
    size() - вычисление размера очереди

--*/

#ifndef __PTL_PTQUEUE_H__
#define __PTL_PTQUEUE_H__

#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <shared_mutex>

////////////////////////////////////////////////////////////////////////////////
namespace ptl
{
//------------------------------------------------------------------------------
template <typename T>
class pCVQueue
{
public:
//------------------------------------------------------------------------------
// Добавление элемента в очередь.
//
    void
    push(const T& value_)
    {
        std::unique_lock<std::shared_mutex> guard(m_mutex);

        m_internal.push(value_);

        // пробуждаем один ожидающий поток c вызовом pop(), если таковые имеются
        m_data_cond.notify_one();
    }

//------------------------------------------------------------------------------
// Удаление элемента из очереди.
//
    void
    pop()
    {
        std::unique_lock<std::shared_mutex> lock(m_mutex);

        // дожидаемся, пока в очередь добавят элемент
        m_data_cond.wait(lock, [this] { return !m_internal.empty(); });

        m_internal.pop();
    }

//------------------------------------------------------------------------------
// Вычисление размера очереди.
//
    auto
    size()
    {
        std::shared_lock<std::shared_mutex>(m_mutex);

        auto result_ = m_internal.size();

        return result_;
    }

private:
    std::queue<T>               m_internal;
    std::shared_mutex           m_mutex;
    std::condition_variable_any m_data_cond; // объект условной переменной для
                                             // синхронизации методов
};

} // namespace ptl

#endif // __PTL_PTQUEUE_H__
