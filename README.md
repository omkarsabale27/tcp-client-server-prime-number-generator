# TCP/IP Client-Server Prime Number Communication

<div align="center">

# 🔢 TCP/IP Client-Server Prime Number Communication

**A TCP/IP socket programming project in C for Linux that identifies prime numbers using client-server communication**

[![Protocol](https://img.shields.io/badge/Protocol-TCP%2FIP-blue?style=for-the-badge)](https://en.wikipedia.org/wiki/Internet_protocol_suite)
[![Language](https://img.shields.io/badge/Language-C-brightgreen?style=for-the-badge\&logo=c)](https://en.wikipedia.org/wiki/C_%28programming_language%29)
[![Platform](https://img.shields.io/badge/Platform-Linux-orange?style=for-the-badge\&logo=linux)](https://www.linux.org/)
[![Networking](https://img.shields.io/badge/Socket-POSIX-yellow?style=for-the-badge)]()

</div>

---

## 📌 Overview

The **TCP/IP Client-Server Prime Number Communication** project demonstrates how a client and server communicate using **TCP socket programming in C**.

The client sends a number to the server through a TCP connection. The server receives the number, checks whether it is **prime or not**, and sends the result back to the client.

> 💡 This project is useful for understanding **TCP/IP networking, socket programming, client-server architecture, Linux system calls, data transmission, and C programming**.

---

## ✨ Features

| Feature                       | Description                                         |
| ----------------------------- | --------------------------------------------------- |
| 🌐 **TCP Communication**      | Uses `SOCK_STREAM` for reliable communication       |
| 🖥️ **Client Program**        | Sends a number to the server                        |
| 🛠️ **Server Program**        | Receives and processes the number                   |
| 🔢 **Prime Number Check**     | Server determines whether the number is prime       |
| 📤 **Data Transmission**      | Client sends number using `send()`                  |
| 📥 **Data Reception**         | Server receives number using `recv()`               |
| 📩 **Result Response**        | Server sends prime/non-prime result to client       |
| ❌ **Error Handling**          | Handles socket and connection errors                |
| 🚪 **Connection Termination** | Client and server close sockets after communication |

---

## 🏗️ System Architecture

```text
                    TCP/IP CONNECTION
        ┌─────────────────────────────────────┐
        │                                     │
        ▼                                     ▼

┌─────────────────┐                 ┌─────────────────┐
│   TCP CLIENT    │                 │   TCP SERVER    │
│                 │                 │                 │
│   socket()      │                 │   socket()      │
│      │          │                 │      │          │
│   connect() ───────────────────────►  bind()        │
│      │          │                 │      │          │
│   send(number) ──────────────────►  recv(number)    │
│      │          │                 │      │          │
│   recv(result) ◄──────────────────  prime check     │
│      │          │                 │      │          │
│   close()       │                 │   send(result)  │
└─────────────────┘                 └─────────────────┘
```

---

## 🔄 Communication Flow

```text
Client                                  Server
  │                                       │
  │ socket()                              │ socket()
  │                                       │
  │ connect() ───────────────────────────►│ bind()
  │                                       │ listen()
  │                                       │ accept()
  │                                       │
  │ Enter number                          │
  │                                       │
  │ send(number) ────────────────────────►│ recv(number)
  │                                       │
  │                                       │ Check prime
  │                                       │
  │ recv(result) ◄────────────────────────│ send(result)
  │                                       │
  │ Display result                        │
  │                                       │
  │ close()                               │ close()
```

---

## 🔧 Socket API Used

| Function    | Purpose                                           |
| ----------- | ------------------------------------------------- |
| `socket()`  | Creates a socket endpoint                         |
| `bind()`    | Associates server socket with IP address and port |
| `listen()`  | Places server socket into listening mode          |
| `accept()`  | Accepts an incoming client connection             |
| `connect()` | Establishes client-server connection              |
| `send()`    | Sends data through the socket                     |
| `recv()`    | Receives data through the socket                  |
| `close()`   | Closes the socket                                 |

---

## 📁 Project Structure

```text
tcpip_client_server_prime/
│
├── client.c                         ← TCP client program
├── server.c                         ← TCP server program
├── header.h                         ← Common socket/network headers
├── tcpip_client_server_prime.png    ← Architecture diagram
└── README.md
```

---

## ⚙️ How It Works

### 1️⃣ Server Initialization

```text
Create TCP socket
       ↓
   socket()
       ↓
Configure IP address + port
       ↓
     bind()
       ↓
    listen()
       ↓
Wait for client connection
       ↓
    accept()
```

### 2️⃣ Client Initialization

```text
Create TCP socket
       ↓
   socket()
       ↓
Read server IP + port
       ↓
    connect()
       ↓
Connection established
```

### 3️⃣ Prime Number Processing

```text
Client
  │
  │ Send number
  ▼
Server
  │
  │ Receive number
  ▼
Check whether number is prime
  │
  ├── Prime
  │
  └── Not Prime
  │
  ▼
Send result to client
  │
  ▼
Client displays result
```

---

## 🔢 Prime Number Logic

A number is considered **prime** if it is greater than `1` and has only two factors:

```text
1 and itself
```

Example:

```text
2  → Prime
3  → Prime
5  → Prime
7  → Prime
11 → Prime
```

Non-prime examples:

```text
1  → Not Prime
4  → Not Prime
6  → Not Prime
8  → Not Prime
9  → Not Prime
```

The server can check divisibility from `2` up to `number - 1`, or use the more efficient approach of checking up to `sqrt(number)`.

---

## 🖥️ Client Program

The client accepts the **server port** and **server IP address** through command-line arguments.

### Command Format

```bash
./client <server_port> <server_ip>
```

### Example

```bash
./client 5000 127.0.0.1
```

The client then:

1. Creates a TCP socket.
2. Converts the server IP using `inet_addr()`.
3. Converts the port using `htons()`.
4. Connects to the server using `connect()`.
5. Reads a number from the user.
6. Sends the number using `send()`.
7. Waits for the result using `recv()`.
8. Displays whether the number is prime.
9. Closes the connection.

---

## 🖥️ Server Program

The server accepts the **server port** from the command line.

### Command Format

```bash
./server <server_port>
```

### Example

```bash
./server 5000
```

The server then:

1. Creates a TCP socket.
2. Uses `INADDR_ANY` to accept connections through available local interfaces.
3. Binds the socket to the selected port.
4. Starts listening using `listen()`.
5. Accepts the client using `accept()`.
6. Receives the number.
7. Checks whether the number is prime.
8. Sends the result back to the client.
9. Closes the client connection.

---

## 🛠️ Compilation

### Compile Server

```bash
gcc server.c -o server
```

### Compile Client

```bash
gcc client.c -o client
```

If the project uses a separate header file, make sure `header.h` is available in the project directory.

---

## ▶️ Running the Project

### Terminal 1 — Start Server

```bash
./server 5000
```

Expected output:

```text
Creating server socket...
Server socket created
Binding server socket...
Bind successful
Server listening...
Waiting for client connection...
Client connected
```

### Terminal 2 — Start Client

```bash
./client 5000 127.0.0.1
```

Enter a number:

```text
Enter number:
17
Sending number to server...
Waiting for result...
17 is a prime number
```

---

## 🧪 Example Communication

### Example 1 — Prime Number

**Client:**

```text
Creating client socket...
Client socket created
Connecting to server...
Connected to server

Enter number:
17

Sending number to server...
Waiting for result...

Server Response: 17 is a prime number
Closing connection...
```

**Server:**

```text
Creating server socket...
Server socket created
Binding server socket...
Bind successful
Server listening...

Client connected

Received number: 17
Checking prime number...
17 is prime

Sending result to client...
Result sent
Closing client connection
```

---

### Example 2 — Non-Prime Number

**Client:**

```text
Enter number:
20

Sending number to server...
Waiting for result...

Server Response: 20 is not a prime number
```

**Server:**

```text
Received number: 20
Checking prime number...
20 is not prime

Sending result to client...
```

---

## 🧠 Important Networking Concepts

### IP Address

An IP address identifies a host on the network.

Example:

```text
127.0.0.1
```

is the localhost/loopback address.

### Port Number

A port number identifies the application/service endpoint.

Example:

```text
5000
```

### TCP

TCP is a **connection-oriented and reliable transport protocol** that provides ordered delivery of data.

### Socket

A socket is an endpoint used by applications for network communication.

---

## 🔍 Important Code Concepts

### Creating a TCP Socket

```c
socket(AF_INET, SOCK_STREAM, 0);
```

* `AF_INET` → IPv4
* `SOCK_STREAM` → TCP
* `0` → Automatically selects the appropriate protocol

### Setting the Port

```c
server_addr.sin_port = htons(atoi(argv[1]));
```

### Setting the Server IP

```c
server_addr.sin_addr.s_addr = inet_addr(argv[2]);
```

### Connecting Client to Server

```c
connect(fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
```

### Sending Number

```c
send(fd, &num, sizeof(num), 0);
```

### Receiving Number

```c
recv(fd, &num, sizeof(num), 0);
```

### Sending Result

```c
send(fd, result, strlen(result), 0);
```

### Receiving Result

```c
recv(fd, result, sizeof(result), 0);
```

---

## 🔢 Prime Checking Logic

A simple implementation on the server can be:

```c
int is_prime(int num)
{
    int i;

    if (num < 2)
        return 0;

    for (i = 2; i <= num / 2; i++)
    {
        if (num % i == 0)
            return 0;
    }

    return 1;
}
```

The function returns:

```text
1 → Prime
0 → Not Prime
```

---

## 🛡️ Error Handling

The program checks important socket system calls using `perror()`.

Example:

```c
if (fd < 0)
{
    perror("socket");
    return 0;
}
```

For connection errors:

```c
if (connect(fd, (struct sockaddr *)&server_addr,
            sizeof(server_addr)) < 0)
{
    perror("connect");
    return 0;
}
```

Error handling helps identify problems during:

* Socket creation
* Binding
* Listening
* Accepting
* Connecting
* Sending
* Receiving

---

## 🚀 Future Improvements

* 👥 Support multiple clients using threads
* 🔢 Send multiple numbers in one connection
* 📊 Find prime numbers within a range
* 🔍 Find the largest prime number in a range
* 💬 Implement continuous client-server communication
* 📁 Add file transfer functionality
* 🔐 Add client authentication
* 🔒 Implement encrypted communication
* 📝 Add server-side logging
* ⏱️ Add connection timeout handling

---

## 📚 Learning Outcomes

Through this project, I learned:

* TCP/IP fundamentals
* Client-server architecture
* Linux socket programming
* C system calls
* IPv4 addressing
* Port numbers
* TCP connection establishment
* TCP three-way handshake concept
* `socket()` system call
* `bind()` system call
* `listen()` system call
* `accept()` system call
* `connect()` system call
* Data transmission using `send()` and `recv()`
* Prime number logic in C
* Error handling in network programs

---

## 🛠️ Development Environment

| Tool            | Details              |
| --------------- | -------------------- |
| **Language**    | C                    |
| **OS**          | Linux                |
| **Compiler**    | GCC                  |
| **Protocol**    | TCP/IP               |
| **Network**     | IPv4                 |
| **Socket Type** | `SOCK_STREAM`        |
| **API**         | POSIX/BSD Socket API |

---

## 🚀 Quick Start

```bash
# Compile server
gcc server.c -o server

# Compile client
gcc client.c -o client

# Terminal 1 - Start server
./server 5000

# Terminal 2 - Start client
./client 5000 127.0.0.1
```

Then enter a number in the client:

```text
Enter number:
23
```

Output:

```text
Server Response: 23 is a prime number
```

---

<div align="center">

**Built with ❤️ using C | Linux | TCP/IP | Socket Programming**

</div>
