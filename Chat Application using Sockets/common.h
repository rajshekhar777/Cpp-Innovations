#ifndef COMMON_H
#define COMMON_H

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <iostream>

// Function to initialize SSL
void initializeSSL() {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

// Function to clean up SSL
void cleanupSSL() {
    EVP_cleanup();
}

// Function to create SSL context
SSL_CTX* createSSLContext() {
    const SSL_METHOD *method = SSLv23_method();
    SSL_CTX *ctx = SSL_CTX_new(method);

    if (!ctx) {
        std::cerr << "Unable to create SSL context" << std::endl;
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    return ctx;
}

#endif // COMMON_H
