//
// Created by Allan Rakotoarivony on 29/09/2026.
//

#pragma once
#include <string>
#include <unistd.h>
#include <utility>

class ClientSocket {
public:
    explicit ClientSocket(const int fd) : fd_{fd} {
    }

    ~ClientSocket() noexcept {
        cleanup();
    }

    ClientSocket(const ClientSocket &) = delete;
    ClientSocket &operator=(const ClientSocket &) = delete;

    ClientSocket(ClientSocket &&other) noexcept {
        fd_ = std::exchange(other.fd_, -1);
    }

    ClientSocket &operator=(ClientSocket &&other) noexcept {
        if (this != &other) {
            cleanup();
            fd_ = std::exchange(other.fd_, -1);
        }
        return *this;
    }

    void send(const std::string &message) const;
    ssize_t receive() const;

    [[nodiscard]] int native_handle() const noexcept { return fd_; }

private:
    void cleanup() noexcept {
        if (fd_ != -1) {
            close(fd_);
            fd_ = -1;
        }
    }

    int fd_{-1};
};
