#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>  // For socket programming
#include <unistd.h>

// Global mutex for thread synchronization
std::mutex logMutex;

// Function to log server activities
void logMessage(const std::string &message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << message << std::endl;
}

// Function to handle client requests
void handleClient(int clientSocket, SSL *ssl) {
    // Buffer to store client request
    char buffer[1024] = {0};
    int bytesRead = SSL_read(ssl, buffer, sizeof(buffer));

    if (bytesRead > 0) {
        logMessage("Client Request: " + std::string(buffer));

        // Basic HTTP response
        std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from Multithreaded Web Server!";
        SSL_write(ssl, httpResponse.c_str(), httpResponse.length());
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(clientSocket);
}

// Function to initialize SSL/TLS
SSL_CTX* createSSLContext() {
    SSL_CTX *ctx;
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    const SSL_METHOD *method = SSLv23_server_method();
    ctx = SSL_CTX_new(method);

    if (!ctx) {
        std::cerr << "Error creating SSL context" << std::endl;
        exit(EXIT_FAILURE);
    }

    return ctx;
}

// Main server function
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
    listen(serverSocket, 10);

    logMessage("Server listening on port: " + std::to_string(port));

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
}

// Main function to start the server
int main() {
    int port = 8080; // You can change the port number if needed
    logMessage("Starting the Multithreaded Web Server...");
    startServer(port);
    return 0;
}
