/*++

    (c) S-Patriarch, 2023
    (PTL) Patriarch library : plogger.h

    Класс pLogger для обработки логов в многопоточной среде.

Методы:

    write() - запись строки в журнал логов
    read()  - чтение строки из журнала логов

--*/

#ifndef __PTL_PLOGGER_H__
#define __PTL_PLOGGER_H__

#include <fstream>
#include <iostream>
#include <string>
#include <shared_mutex>

////////////////////////////////////////////////////////////////////////////////
namespace ptl
{
//------------------------------------------------------------------------------
class pLogger
{
public:
    pLogger(const std::string& fileLogName_)
    {
        m_file.open(fileLogName_, std::ios::in | std::ios::out | std::ios::app);
        if (!m_file.is_open()) {
            std::cerr << "E: Не удалось открыть файла журнала.\n";
        }
    }

    ~pLogger()
    {
        if (m_file.is_open()) {
            m_file.close();
        }
    }

//------------------------------------------------------------------------------
// Запись строки в журнал логов.
//
    void
    write(const std::string& strMessageWrite_)
    {
        // Создание объекта lock типа std::unique_lock, который блокирует
        // мьютекс m_mutex в режиме монопольной (или уникальной) блокировки.
        // Это значит, что только один поток может иметь доступ к общему
        // ресурсу, защищенному m_mutex, в данный момент времени.
        // Объект lock будет автоматически освобожден при выходе из
        // области видимости.
        std::unique_lock<std::shared_mutex> lock(m_mutex);

        if (m_file.is_open()) {
            m_file << strMessageWrite_ << '\n';
        }
    }

//------------------------------------------------------------------------------
// Чтение строки из журнала логов.
//
    std::string
    read()
    {
        // Создание объекта lock типа std::shared_lock, который блокирует
        // мьютекс m_mutex в режиме совместной блокировки.
        // Это позволяет нескольким потокам иметь одновременный доступ к
        // общему ресурсу.
        // Объект lock будет автоматически освобожден при выходе из
        // области видимости.
        std::shared_lock<std::shared_mutex> lock(m_mutex);

        std::string strMessageRead_ {};
        if (m_file.is_open()) {
            std::getline(m_file, strMessageRead_);
        }

        return strMessageRead_;
    }

private:
    std::fstream      m_file;  // файловый поток
    std::shared_mutex m_mutex; // мьютекс
};

} // namespace ptl

#endif // __PTL_PLOGGER_H__
