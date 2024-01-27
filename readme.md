# Simple Client-Server Chat Application

A basic client-server chat application implemented in C++ using sockets.

## Overview

This project provides a simple client-server chat application using C++ sockets. The server listens for incoming connections, and the client connects to the server to exchange messages. The chat history is logged in a file.

## Features

- Client-server communication: The client and server can communicate by sending text messages alternatively.
- Chat history logging: The messages of the chat are stored in a text file named 'chat_history.txt' in the same directory where the cpp files are present.
- Graceful handling of client and server disconnection: When 'exit' is received as message by either client or server, the chat session terminates.

## Executing the code:

### Clone the repository:

1. Server code
   ```bash
   git clone https://github.com/your-username/your-repository.git
   cd your-repository

2. Client code
   ```bash
   git clone https://github.com/your-username/your-repository.git
   cd your-repository

- Replace "your-username" and "your-repository" with your actual GitHub username and repository name. Adjust the file and folder structure if necessary.

### Compilation of code:
   
      
      g++ s.cpp -o server
      g++ c.cpp -o client


- Running Executable files

1. Write this in one terminal for server
   ```bash
   ./server

2. Write this in a separate terminal for client
   ```bash
   ./client

- Now the client and server can communicate by sending messages alternatively.
- In order to end the chat session, type 'exit' as a message.
- The chat history can be accessed in the chat_history.txt file created in the current directory. 
   


  
