//
// Created by Allan Rakotoarivony on 29/09/2026.
//

#include "../include/ClientSocket.hpp"

#include <stdexcept>
#include <system_error>
#include <sys/socket.h>

void ClientSocket::send(const std::string& message) const {
    ::send(this->fd_, message.data(), message.length(), 0);
}

ssize_t ClientSocket::receive() const {
    char buffer[1024];
    auto bytes_read = ::recv(this->fd_, buffer, sizeof(buffer), 0);
    if (bytes_read < 0) {
        throw std::system_error(errno, std::generic_category(), "ClientSocket::read() failed");
    }
    return bytes_read;
}
