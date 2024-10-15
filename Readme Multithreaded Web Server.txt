# Multithreaded Web Server with SSL/TLS

This project is a simple multithreaded web server implemented in C++ with SSL/TLS support using OpenSSL. The server handles multiple client connections concurrently using threads and provides secure communication through SSL/TLS encryption.

## Prerequisites

Before you begin, ensure that you have the following installed on your system:

- **g++ compiler** (to compile the code)
- **OpenSSL** library (for SSL/TLS functionality)
- **libssl-dev** (development package for OpenSSL)

To install these on a Debian-based system like Ubuntu, use:

sudo apt update sudo apt install g++ openssl libssl-dev

## Setting Up SSL/TLS Certificates

You need an SSL certificate and a private key to set up secure communication. Follow these steps to create them:

1. Open your terminal and run the following command:

openssl req -x509 -newkey rsa:4096 -keyout server.key -out server.crt -days 365 -nodes

2. Follow the prompts to fill in details for your certificate (you can leave them blank if desired).

This will generate two files in your current directory:
- `server.crt` - The SSL certificate
- `server.key` - The private key

## Compiling the Program

Use the following command to compile the code:

g++ multithreaded_web_server.cpp -o web_server -lssl -lcrypto -pthread

### Explanation
- `-lssl`: Links the SSL library.
- `-lcrypto`: Links the Crypto library.
- `-pthread`: Enables multithreading support.

## Running the Server

After successful compilation, run the web server using the following command:

./web_server

You should see a message indicating that the server is listening on the specified port.

### Default Port

The server listens on port `8080` by default. You can modify the port number in the code if required.

## Testing the Server

To test if your server is running correctly, open a new terminal window and use `curl` or your web browser.

### Using curl:

curl -k https://localhost:8080

The `-k` flag tells `curl` to ignore SSL certificate warnings since we're using a self-signed certificate.

### Expected Output
You should see a response like:

Hello from Multithreaded Web Server!


## Code Explanation

- **Multithreading:** Each client connection is handled by a separate thread to enable concurrent processing.
- **SSL/TLS:** The server uses OpenSSL to secure communication with the clients.
- **Logging:** The server logs activities using a global mutex to ensure thread-safe access.

## Stopping the Server

To stop the server, press `Ctrl + C` in the terminal where the server is running.

## License

This project is open-source and free to use. You can modify and distribute it as needed.
