#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
using namespace std;

// Server side
int main(int argc, char *argv[])
{
    // For the server, we only need to specify a port number
    int port = 8080;
    char msg[1500];

    // Setup a socket and connection tools
    sockaddr_in servAddr;
    bzero((char *)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    // Open stream-oriented socket with internet address
    // Also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }

    // Bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if (bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    cout << "Waiting for a client to connect..." << endl;

    // Listen for up to 5 requests at a time
    listen(serverSd, 5);

    // Receive a request from the client using accept
    // We need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);

    // Accept, create a new socket descriptor to
    // Handle the new connection with the client
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if (newSd < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }

    cout << "Connected with client!" << endl;

    // Let's keep track of the session time
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);

    // Also keep track of the amount of data sent as well
    int bytesRead, bytesWritten = 0;

    // Open the chat history file for writing
    ofstream chatFile("chat_history_server.txt", ios::out | ios::app);
    if (!chatFile.is_open())
    {
        cerr << "Error opening chat history file on the server." << endl;
        exit(0);
    }
    while (1)
    {
        // Receive a message from the client (listen)
        cout << "Awaiting client response..." << endl;
        memset(&msg, 0, sizeof(msg)); // Clear the buffer
        bytesRead += recv(newSd, (char *)&msg, sizeof(msg), 0);

        if (!strcmp(msg, "exit"))
        {
            cout << "Client has quit the session" << endl;
            break;
        }

        cout << "Client: " << msg << endl;

        // Write the client's message to the chat history file
        chatFile << "Client: " << msg << endl;

        cout << ">";
        string data;
        getline(cin, data);

        // Clear the buffer and copy the server's response
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());

        if (data == "exit")
        {
            // Send to the client that the server has closed the connection
            send(newSd, (char *)&msg, strlen(msg), 0);
            break;
        }

        // Write the server's response to the chat history file
        chatFile << "Server: " << msg << endl;

        // Send the message to the client
        bytesWritten += send(newSd, (char *)&msg, strlen(msg), 0);
    }

    // We need to close the socket descriptors and the chat history file after we're all done
    gettimeofday(&end1, NULL);
    close(newSd);
    close(serverSd);
    chatFile.close();

    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) << " secs" << endl;
    cout << "Connection closed..." << endl;

    return 0;
}
