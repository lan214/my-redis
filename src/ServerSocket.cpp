//
// Created by Allan Rakotoarivony on 28/09/2026.
//

#include "../include/ServerSocket.hpp"

#include <format>
#include <system_error>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <utility>

#include "ClientSocket.hpp"

ServerSocket::ServerSocket(uint16_t port, int backlog) {
    fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ == -1) {
        throw std::system_error(errno, std::generic_category(), "Failed to create server socket");
    }

    const int reuse = 1;
    if (::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        cleanup();
        throw std::system_error(errno, std::generic_category(), "setsockopt failed");
    }

    const sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = {
            .s_addr = INADDR_ANY,
        }
    };

    if (::bind(fd_, reinterpret_cast<const sockaddr *>(&addr), sizeof(addr)) < 0) {
        cleanup();
        throw std::system_error(errno, std::generic_category(), std::format("Failed to bind to port {}", port));
    }

    if (::listen(fd_, backlog) < 0) {
        cleanup();
        throw std::system_error(errno, std::generic_category(), "listen failed");
    }
}

ServerSocket::~ServerSocket() noexcept {
    cleanup();
}

ServerSocket::ServerSocket(ServerSocket &&other) noexcept
    : fd_{std::exchange(other.fd_, -1)} {
}

ServerSocket &ServerSocket::operator=(ServerSocket &&other) noexcept {
    if (this != &other) {
        cleanup();
        fd_ = std::exchange(other.fd_, -1);
    }
    return *this;
}

ClientSocket ServerSocket::accept() const {
    const auto fd = ::accept(fd_, nullptr, nullptr);
    return ClientSocket(fd);
}

void ServerSocket::cleanup() noexcept {
    if (fd_ != -1) {
        ::close(fd_);
        fd_ = -1;
    }
}

bool ServerSocket::is_valid() const noexcept { return fd_ > -1; }

int ServerSocket::native_handle() const noexcept { return fd_; }
