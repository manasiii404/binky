#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cmath>
#include <string>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8083
#define BUFFER_SIZE 1024
#define PI 3.14159265358979323846

int main() {
    WSADATA wsaData;
    SOCKET serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];
    
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
    
    std::cout << "UDP Trigonometric Calculator Server listening on port " << PORT << "..." << std::endl;
    std::cout << "Waiting for calculations..." << std::endl;
    
    while (true) {
        // Receive request from client
        memset(buffer, 0, BUFFER_SIZE);
        int bytesReceived = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, 
                                      (struct sockaddr*)&clientAddr, &clientAddrLen);
        
        if (bytesReceived > 0) {
            std::string request(buffer);
            std::cout << "\nReceived request: " << request << std::endl;
            
            // Parse request: format is "operation angle"
            std::istringstream iss(request);
            std::string operation;
            double angle;
            
            if (!(iss >> operation >> angle)) {
                const char* errorMsg = "ERROR: Invalid format. Use: operation angle";
                sendto(serverSocket, errorMsg, strlen(errorMsg), 0, 
                       (struct sockaddr*)&clientAddr, clientAddrLen);
                continue;
            }
            
            // Convert angle to radians
            double radians = angle * PI / 180.0;
            double result;
            std::string resultStr;
            
            // Calculate based on operation
            if (operation == "sin") {
                result = sin(radians);
                resultStr = "sin(" + std::to_string(angle) + "°) = " + std::to_string(result);
            } else if (operation == "cos") {
                result = cos(radians);
                resultStr = "cos(" + std::to_string(angle) + "°) = " + std::to_string(result);
            } else if (operation == "tan") {
                result = tan(radians);
                resultStr = "tan(" + std::to_string(angle) + "°) = " + std::to_string(result);
            } else {
                resultStr = "ERROR: Unknown operation. Use: sin, cos, or tan";
            }
            
            std::cout << "Result: " << resultStr << std::endl;
            
            // Send result back to client
            sendto(serverSocket, resultStr.c_str(), resultStr.length(), 0, 
                   (struct sockaddr*)&clientAddr, clientAddrLen);
        }
    }
    
    // Cleanup (unreachable in this infinite loop, but good practice)
    closesocket(serverSocket);
    WSACleanup();
    
    return 0;
}
