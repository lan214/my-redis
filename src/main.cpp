#include <iostream>

#include "ServerSocket.hpp"

int main(int argc, char **argv) {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  try {
      const ServerSocket serverSocket(6379);

      std::cout << "Waiting for a client to connect...\n";

      // You can use print statements as follows for debugging, they'll be visible when running tests.
      std::cout << "Logs from your program will appear here!\n";

      serverSocket.accept();
      std::cout << "Client connected\n";

      return 0;
  } catch (std::exception &e) {
      std::cerr << e.what() << '\n';
  }
}
