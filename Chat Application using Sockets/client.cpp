#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "common.h"

void startClient(const std::string &serverIP, int port) {
    SSL_CTX *ctx = createSSLContext();
    SSL *ssl;
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) != 0) {
        std::cerr << "Connection to server failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, clientSocket);
    if (SSL_connect(ssl) <= 0) {
        std::cerr << "SSL connection failed!" << std::endl;
        SSL_free(ssl);
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected to server. Enter messages to send:" << std::endl;
    char buffer[1024];
    while (true) {
        std::cin.getline(buffer, sizeof(buffer));
        SSL_write(ssl, buffer, strlen(buffer));
        int bytesRead = SSL_read(ssl, buffer, sizeof(buffer));
        buffer[bytesRead] = '\0';
        std::cout << "Server: " << buffer << std::endl;
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(clientSocket);
    SSL_CTX_free(ctx);
    cleanupSSL();
}

int main() {
    initializeSSL();
    startClient("127.0.0.1", 4444);
    return 0;
}
