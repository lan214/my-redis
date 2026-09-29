#include <iostream>

#include "ServerSocket.hpp"

int main(int argc, char **argv) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    try {
        const ServerSocket serverSocket(6379);

        std::cout << "Waiting for a client to connect...\n";

        const auto clientSocket = serverSocket.accept();
        std::cout << "Client connected\n";

        while (true) {
            if (const auto bytesReceived = clientSocket.receive(); bytesReceived <= 0) {
                break;
            }
            clientSocket.send("+PONG\r\n");
        }

        std::cout << "Bye\n";
        return 0;
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}
