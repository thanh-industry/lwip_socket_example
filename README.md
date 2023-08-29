# LWIP Socket Send and Receive Example for STM32

## Introduction

This repository contains an example project that demonstrates how to use the LWIP (Lightweight IP) library on an STM32 microcontroller to send and receive data using socket API. The example showcases the setup and usage of LWIP to establish network communication over Ethernet and demonstrates both server and client functionality.

## Getting Started

### Prerequisites

Before you begin, ensure that you have the following prerequisites:

- STM32 development board with Ethernet connectivity.
- STM32CubeIDE for STM32 development.
- LWIP library installed in your development environment.
- Router with Ethernet ports to configure IP for STM32 development board and server

### Installation

1. Clone this repository to your local machine.
2. Open the project in your preferred STM32 development environment.
3. Configure the necessary settings such as microcontroller selection, linker script, and system clock.

## Project Structure

The project is organized as follows:

- `Core/Src/` : Contains the source code files.
  - `main.c` : Entry point of the application, containing the initialization and main loop .
  - `ethernetif.c` : Ethernet interface initialization and management.
  - `freertos.c` : Freertos application that creates tasks for client to communicate with the server
  - Other application-specific source files.

- `Core/Inc/` : Contains the header files.
  - `main.h` : Main header file with function prototypes and global definitions.
  - Other application-specific header files.

- `LWIP` : Implementing the networking stack and the Ethernet interface .
  - `lwip.c`  : Entry point for initializing and managing the LWIP networking stack.
  - `ethernetif.c`  :  Implement the Ethernet interface for LWIP.

- `MiddleLevel/Network/` : Contains the application code of client example.
  - `socket_client.c` : Demonstrates a client implementation for create a socket, connect to socket server, sending and receiving data over a socket using LWIP.
  - `socket_client.h` : Header file defines data structures, constants, and function prototypes related to the client-side implementation of socket communication using LWIP.

- `MiddleLevel/TestData/test_data.h` : Header file defines data for testing function socket client send.
  
- `SocketServer` : Contains the server socket code file.
  - `socket_server.py` : Create a basic a GUI-based TCP socket server application for handling connections, message exchange, and information display.
  
## Usage

1. Open the project in STM32CubeIDE.
2. Configure the IP address server settings for the client applications in the `socket_client.c` file and the `socket_server.py` file.
3. Build and flash the server and client applications to separate STM32 development boards.
4. Run python socket_server.py or use Hercules SETUP utility to run server application.
5. Use debugging tools to monitor the status of the communication.

## Testing result

### Testing client
![image](https://github.com/phuntp040902/stm32_lwip_tcp/assets/130150674/f358347f-35ff-4e7b-8e3e-11c9be0cc4ed)

### Testing server

1. Hercules
![image](https://github.com/phuntp040902/stm32_lwip_tcp/assets/130150674/6af86771-4bf9-4b69-9ffd-91dc4e02883f)

2. Python application
![image](https://github.com/phuntp040902/stm32_lwip_tcp/assets/130150674/ef827beb-dd87-4e5c-bad8-7e386a2b6a24)

## Reference

