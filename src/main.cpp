#include <iostream>
#include <thread>

#include "ServerSocket.hpp"

void handleClient(ClientSocket clientSocket) {
    try {
        while (true) {
            if (const auto bytesReceived = clientSocket.receive(); bytesReceived <= 0) {
                break;
            }
            clientSocket.send("+PONG\r\n");
        }
        std::cout << std::this_thread::get_id() << ": Client disconnected\n";
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

int main(int argc, char **argv) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    try {
        const ServerSocket serverSocket(6379);

        std::cout << "Waiting for a client to connect...\n";

        while (true) {
            auto clientSocket = serverSocket.accept();
            std::cout << "Client connected\n";

            std::thread t(handleClient, std::move(clientSocket));
            t.detach();
        }

        std::cout << "Bye\n";
        return 0;
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}
