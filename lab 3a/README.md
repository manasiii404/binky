# Network Programming - TCP and UDP Programs

This repository contains C++ implementations of TCP and UDP client-server programs demonstrating various network communication patterns.

## Programs Included

1. **TCP Hello World** - Simple message exchange over TCP
2. **UDP Hello World** - Simple message exchange over UDP
3. **TCP File Transfer** - Transfer files from server to client
4. **UDP Trigonometric Calculator** - Calculate sin, cos, tan values

## Prerequisites

- **Compiler**: MinGW GCC or any C++ compiler with Winsock support
- **Operating System**: Windows
- **Library**: ws2_32 (Winsock2)

## Compilation Instructions

All programs need to be compiled with the `-lws2_32` flag to link the Winsock library.

### Compile All Programs

```bash
# TCP Hello World
g++ -o tcp_hello_server.exe tcp_hello_server.cpp -lws2_32
g++ -o tcp_hello_client.exe tcp_hello_client.cpp -lws2_32

# UDP Hello World
g++ -o udp_hello_server.exe udp_hello_server.cpp -lws2_32
g++ -o udp_hello_client.exe udp_hello_client.cpp -lws2_32

# TCP File Transfer
g++ -o tcp_file_server.exe tcp_file_server.cpp -lws2_32
g++ -o tcp_file_client.exe tcp_file_client.cpp -lws2_32

# UDP Trigonometric Calculator
g++ -o udp_calc_server.exe udp_calc_server.cpp -lws2_32
g++ -o udp_calc_client.exe udp_calc_client.cpp -lws2_32
```

## Running the Programs

> **Note**: Always start the **server** first before running the **client**.

---

## 1. TCP Hello World

### How to Run

**Terminal 1 (Server):**
```bash
./tcp_hello_server.exe
```

**Terminal 2 (Client):**
```bash
./tcp_hello_client.exe
```

### Expected Output

**Server Output:**
```
TCP Server listening on port 8080...
Client connected!
Received from client: Hello from Client!
Sent: Hello from Server!
```

**Client Output:**
```
Connected to server!
Sent: Hello from Client!
Received from server: Hello from Server!
```

---

## 2. UDP Hello World

### How to Run

**Terminal 1 (Server):**
```bash
./udp_hello_server.exe
```

**Terminal 2 (Client):**
```bash
./udp_hello_client.exe
```

### Expected Output

**Server Output:**
```
UDP Server listening on port 8081...
Received from client: Hello from UDP Client!
Sent: Hello from UDP Server!
```

**Client Output:**
```
Sending message to UDP server...
Sent: Hello from UDP Client!
Received from server: Hello from UDP Server!
```

---

## 3. TCP File Transfer

### How to Run

**Terminal 1 (Server):**
```bash
./tcp_file_server.exe
```

**Terminal 2 (Client):**
```bash
./tcp_file_client.exe
```

When prompted by the client, enter the filename: `test_file.txt`

### Expected Output

**Server Output:**
```
TCP File Transfer Server listening on port 8082...
Client connected!
Client requested file: test_file.txt
Sending file...
File sent successfully! Total bytes: 231
```

**Client Output:**
```
Connected to file transfer server!
Enter filename to request: test_file.txt
Requested file: test_file.txt
Receiving file...
File received successfully!
Total bytes received: 231
Saved as: received_test_file.txt
```

### Notes
- The server must have the requested file in its current directory
- The client saves the received file with a `received_` prefix
- A sample `test_file.txt` is provided for testing

---

## 4. UDP Trigonometric Calculator

### How to Run

**Terminal 1 (Server):**
```bash
./udp_calc_server.exe
```

**Terminal 2 (Client):**
```bash
./udp_calc_client.exe
```

### Expected Output

**Server Output:**
```
UDP Trigonometric Calculator Server listening on port 8083...
Waiting for calculations...

Received request: sin 30
Result: sin(30.000000°) = 0.500000

Received request: cos 60
Result: cos(60.000000°) = 0.500000

Received request: tan 45
Result: tan(45.000000°) = 1.000000
```

**Client Output:**
```
UDP Trigonometric Calculator Client
=====================================
Available operations: sin, cos, tan
Format: operation angle_in_degrees
Example: sin 30
Type 'exit' to quit
=====================================

Enter calculation: sin 30
Result: sin(30.000000°) = 0.500000

Enter calculation: cos 60
Result: cos(60.000000°) = 0.500000

Enter calculation: tan 45
Result: tan(45.000000°) = 1.000000

Enter calculation: exit
Exiting...
```

### Usage
- Enter operation (sin, cos, or tan) followed by angle in degrees
- Example: `sin 30`, `cos 60`, `tan 45`
- Type `exit` to quit the client

---

## Port Configuration

| Program | Port |
|---------|------|
| TCP Hello World | 8080 |
| UDP Hello World | 8081 |
| TCP File Transfer | 8082 |
| UDP Trigonometric Calculator | 8083 |

All programs connect to `127.0.0.1` (localhost) by default.

## Troubleshooting

### Compilation Errors
- Ensure you have MinGW installed and in your PATH
- Make sure to include `-lws2_32` flag when compiling
- Use `g++ --version` to verify compiler installation

### Runtime Errors
- **"Bind failed"**: Port is already in use. Close any running servers or change the port number
- **"Connection failed"**: Make sure the server is running before starting the client
- **"File not found"**: Ensure the requested file exists in the server's directory

## File Structure

```
.
├── README.md
├── tcp_hello_server.cpp
├── tcp_hello_client.cpp
├── udp_hello_server.cpp
├── udp_hello_client.cpp
├── tcp_file_server.cpp
├── tcp_file_client.cpp
├── udp_calc_server.cpp
├── udp_calc_client.cpp
└── test_file.txt
```

## Technical Details

- **TCP**: Connection-oriented, reliable communication using `SOCK_STREAM`
- **UDP**: Connectionless, datagram-based communication using `SOCK_DGRAM`
- **File Transfer**: Uses 4KB buffer for efficient chunk-based transfer
- **Calculator**: Converts degrees to radians (angle × π / 180) before calculation

## License

This is educational code for learning network programming concepts.
