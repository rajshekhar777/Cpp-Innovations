#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <arpa/inet.h>
#include <unistd.h>
#include "common.h"

std::mutex logMutex; // Mutex for synchronized logging

void logMessage(const std::string &message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << message << std::endl;
}

void handleClient(int clientSocket, SSL *ssl) {
    char buffer[1024] = {0};
    while (true) {
        int bytesRead = SSL_read(ssl, buffer, sizeof(buffer));
        if (bytesRead <= 0) break;

        logMessage("Received message: " + std::string(buffer));
        SSL_write(ssl, buffer, bytesRead); // Echo back to client
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(clientSocket);
}

void startServer(int port) {
    SSL_CTX *ctx = createSSLContext();
    SSL_CTX_use_certificate_file(ctx, "server.crt", SSL_FILETYPE_PEM);
    SSL_CTX_use_PrivateKey_file(ctx, "server.key", SSL_FILETYPE_PEM);

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);
    logMessage("Server is listening on port " + std::to_string(port));

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        SSL *ssl = SSL_new(ctx);
        SSL_set_fd(ssl, clientSocket);

        if (SSL_accept(ssl) <= 0) {
            logMessage("SSL handshake failed.");
            SSL_free(ssl);
            close(clientSocket);
        } else {
            std::thread(handleClient, clientSocket, ssl).detach();
        }
    }

    close(serverSocket);
    SSL_CTX_free(ctx);
    cleanupSSL();
}

int main() {
    initializeSSL();
    startServer(4444);
    return 0;
}
