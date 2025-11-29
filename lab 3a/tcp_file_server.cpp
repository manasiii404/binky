#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8082
#define BUFFER_SIZE 4096

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];
    char filename[256];
    
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }
    
    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    
    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    
    // Bind socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    // Listen for connections
    if (listen(serverSocket, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    std::cout << "TCP File Transfer Server listening on port " << PORT << "..." << std::endl;
    
    // Accept connection
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    std::cout << "Client connected!" << std::endl;
    
    // Receive filename from client
    memset(filename, 0, sizeof(filename));
    int bytesReceived = recv(clientSocket, filename, sizeof(filename) - 1, 0);
    if (bytesReceived <= 0) {
        std::cerr << "Failed to receive filename" << std::endl;
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    std::cout << "Client requested file: " << filename << std::endl;
    
    // Open file
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "File not found: " << filename << std::endl;
        const char* errorMsg = "ERROR: File not found";
        send(clientSocket, errorMsg, strlen(errorMsg), 0);
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    // Send file in chunks
    std::cout << "Sending file..." << std::endl;
    int totalBytesSent = 0;
    while (file.read(buffer, BUFFER_SIZE) || file.gcount() > 0) {
        int bytesToSend = file.gcount();
        int bytesSent = send(clientSocket, buffer, bytesToSend, 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
            break;
        }
        totalBytesSent += bytesSent;
    }
    
    file.close();
    std::cout << "File sent successfully! Total bytes: " << totalBytesSent << std::endl;
    
    // Cleanup
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    
    return 0;
}
