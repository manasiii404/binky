#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8081
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE] = {0};
    
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }
    
    // Create UDP socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
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
    
    std::cout << "UDP Server listening on port " << PORT << "..." << std::endl;
    
    // Receive message from client
    int bytesReceived = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, 
                                  (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (bytesReceived > 0) {
        std::cout << "Received from client: " << buffer << std::endl;
        
        // Send response
        const char* response = "Hello from UDP Server!";
        sendto(serverSocket, response, strlen(response), 0, 
               (struct sockaddr*)&clientAddr, clientAddrLen);
        std::cout << "Sent: " << response << std::endl;
    }
    
    // Cleanup
    closesocket(serverSocket);
    WSACleanup();
    
    return 0;
}
