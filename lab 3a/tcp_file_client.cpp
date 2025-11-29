#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8082
#define BUFFER_SIZE 4096

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    std::string filename;
    std::string outputFilename;
    
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }
    
    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
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
    
    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    
    std::cout << "Connected to file transfer server!" << std::endl;
    
    // Get filename from user
    std::cout << "Enter filename to request: ";
    std::getline(std::cin, filename);
    
    // Send filename to server
    send(clientSocket, filename.c_str(), filename.length(), 0);
    std::cout << "Requested file: " << filename << std::endl;
    
    // Create output filename
    outputFilename = "received_" + filename;
    std::ofstream outFile(outputFilename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to create output file" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    
    // Receive file in chunks
    std::cout << "Receiving file..." << std::endl;
    int totalBytesReceived = 0;
    int bytesReceived;
    
    while ((bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0)) > 0) {
        // Check for error message
        if (totalBytesReceived == 0 && bytesReceived < 100) {
            std::string firstChunk(buffer, bytesReceived);
            if (firstChunk.find("ERROR") != std::string::npos) {
                std::cerr << "Server error: " << firstChunk << std::endl;
                outFile.close();
                remove(outputFilename.c_str());
                closesocket(clientSocket);
                WSACleanup();
                return 1;
            }
        }
        
        outFile.write(buffer, bytesReceived);
        totalBytesReceived += bytesReceived;
    }
    
    outFile.close();
    
    if (totalBytesReceived > 0) {
        std::cout << "File received successfully!" << std::endl;
        std::cout << "Total bytes received: " << totalBytesReceived << std::endl;
        std::cout << "Saved as: " << outputFilename << std::endl;
    } else {
        std::cout << "No data received" << std::endl;
        remove(outputFilename.c_str());
    }
    
    // Cleanup
    closesocket(clientSocket);
    WSACleanup();
    
    return 0;
}
