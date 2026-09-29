//
// Created by Allan Rakotoarivony on 29/09/2026.
//

#include "../include/ClientSocket.hpp"

#include <sys/socket.h>

void ClientSocket::send(const std::string& message) const {
    ::send(this->fd_, message.data(), message.length(), 0);
}
