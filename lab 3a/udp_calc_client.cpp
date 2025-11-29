#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8083
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    int serverAddrLen = sizeof(serverAddr);
    char buffer[BUFFER_SIZE];
    
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }
    
    // Create UDP socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    
    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    
    // Convert IPv4 address from text to binary
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (serverAddr.sin_addr.s_addr == INADDR_NONE) {
        std::cerr << "Invalid address" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    
    std::cout << "UDP Trigonometric Calculator Client" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Available operations: sin, cos, tan" << std::endl;
    std::cout << "Format: operation angle_in_degrees" << std::endl;
    std::cout << "Example: sin 30" << std::endl;
    std::cout << "Type 'exit' to quit" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    while (true) {
        std::string request;
        std::cout << "\nEnter calculation: ";
        std::getline(std::cin, request);
        
        if (request == "exit") {
            break;
        }
        
        if (request.empty()) {
            continue;
        }
        
        // Send request to server
        sendto(clientSocket, request.c_str(), request.length(), 0, 
               (struct sockaddr*)&serverAddr, serverAddrLen);
        
        // Receive result from server
        memset(buffer, 0, BUFFER_SIZE);
        int bytesReceived = recvfrom(clientSocket, buffer, BUFFER_SIZE, 0, 
                                      (struct sockaddr*)&serverAddr, &serverAddrLen);
        
        if (bytesReceived > 0) {
            std::cout << "Result: " << buffer << std::endl;
        } else {
            std::cout << "No response from server" << std::endl;
        }
    }
    
    std::cout << "Exiting..." << std::endl;
    
    // Cleanup
    closesocket(clientSocket);
    WSACleanup();
    
    return 0;
}
