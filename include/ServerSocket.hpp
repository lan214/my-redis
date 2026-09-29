//
// Created by Allan Rakotoarivony on 28/09/2026.
//
#pragma once

#include <cstdint>

#include "ClientSocket.hpp"

class ServerSocket {
public:
    explicit ServerSocket(uint16_t port, int backlog=5);
    ~ServerSocket() noexcept;

    ServerSocket(const ServerSocket&) = delete;
    ServerSocket& operator=(const ServerSocket&) = delete;

    ServerSocket(ServerSocket&&) noexcept;
    ServerSocket& operator=(ServerSocket&&) noexcept;

    ClientSocket accept() const;

    [[nodiscard]] int native_handle() const noexcept;
    [[nodiscard]] bool is_valid() const noexcept;

private:
    void cleanup() noexcept;
    int fd_{-1};
};
