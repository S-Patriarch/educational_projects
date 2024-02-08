/*++

    Copyright (c) S-Patriarch, 2023
    (PTL) Patriarch library : pTCPClient.h

Методы:

    setup() - создание сокета, подключение к серверу
    Send() - передача данных
    receive() - чтение данных строкой определенного размера
    read() - чтение данных по символьно
    exit() - закрытие сокета, завершение соединения

--*/

#ifndef __PTL_TCP_CLIENT_H__
#define __PTL_TCP_CLIENT_H__

#ifdef _WIN32
#pragma once
#endif

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "pexcept.h"

typedef signed int s32_t;

//////////////////////////////////////////////////////////////////////
namespace ptl
{
  class pTCPClient
  {
    private:
      s32_t       _M_sock; 
      s32_t       _M_port; 
      s32_t       _M_connection;
      s32_t       _M_maxPacketSize;
      std::string _M_ipAddressServer;
      
      struct sockaddr_in server;

    public:
      pTCPClient()
      {
        _M_sock            = -1;
        _M_port            = 0;
        _M_connection      = -1;
        _M_ipAddressServer = "";
        _M_maxPacketSize   = 4096;
      }

      ~pTCPClient() = default;

//--------------------------------------------------------------------
// Создание сокета и подключение к серверу.
// При успешной отработке возвращает true.
// В противном случае - бросает исключения.
//
      bool 
      setup(
        std::string _ipAddressServer, 
        s32_t       _port
        )
      {
        if (_M_sock == -1) {
          _M_sock = socket(AF_INET, 
                           SOCK_STREAM, 
                           0
                    );
          if (_M_sock == -1) {
            throw
            ptl::pException("E: Не удалось создать сокет.");
          }
        }

        _M_ipAddressServer = _ipAddressServer;
        _M_port            = _port;

        std::memset(&server, 
                    0, 
                    sizeof(server)
        );

        server.sin_addr.s_addr = inet_addr(_M_ipAddressServer.c_str());
        server.sin_port        = htons(_M_port);
        server.sin_family      = AF_INET;

        _M_connection = connect(_M_sock, 
                                (struct sockaddr*)&server, 
                                sizeof(server)
                        );
        if (_M_connection == -1) {
          throw
          ptl::pException("E: Не удалось установить соединение с сервером.");
        }

        return true;
      }

//--------------------------------------------------------------------
// Передача данных через созданный сокет.
//
      void
      Send(
        std::string _data
        )
      { send(_M_sock, _data.c_str(), std::strlen(_data.c_str()), 0); }

//--------------------------------------------------------------------
// Чтение (получение) данных строкой определенного размера.
// При успешном чтении (получении) возвращает std::string
// В противном случае - nullptr
//
      std::string
      receive()
      {
        std::string _reply { };
        char        _buffer[_M_maxPacketSize];

        std::memset(&_buffer[0], 
                    0, 
                    sizeof(_buffer)
        );

        if (recv(_M_sock, 
                 _buffer, 
                 _M_maxPacketSize, 
                 0
            ) < 0) {
          return nullptr;
        }

        _buffer[_M_maxPacketSize-1] = '\0';
        _reply                      = _buffer;

        return _reply;
      }

//--------------------------------------------------------------------
// Чтение (получение) данных по символьно.
// При успешном чтении (получении) возвращает std::string
// В противном случае - nullptr
//
      std::string
      read()
      {
        std::string _reply { };
        char        _buffer[1] { };

        while (_buffer[0] != '\n') {
          if (recv(_M_sock, 
                   _buffer, 
                   sizeof(_buffer), 
                   0
              ) < 0) {
            return nullptr;
          }
          _reply += _buffer[0];
        }

        return _reply;
      }

//--------------------------------------------------------------------
// Закрытие созданного сокета и 
// завершение установленного с сервером соединения.
//
      void 
      exit()
      { close(_M_sock); }

  };

} // namespace ptl

#endif // __PTL_TCP_CLIENT_H__