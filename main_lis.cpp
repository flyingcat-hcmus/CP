#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "12345"

#include <bits/stdc++.h>

using namespace std;

int main()
{

    //----------------------
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = 0;

    SOCKET ListenSocket = INVALID_SOCKET;
    sockaddr_in service;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup() failed with error: %d\n", iResult);
        return 1;
    }
    //----------------------
    // Create a SOCKET for listening for incoming connection requests.
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port for the socket that is being bound.
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(12345);

    iResult = bind(ListenSocket, (SOCKADDR *) & service, sizeof (service));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"bind function failed with error %d\n", WSAGetLastError());
        iResult = closesocket(ListenSocket);
        if (iResult == SOCKET_ERROR)
            wprintf(L"closesocket function failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //----------------------
    // Listen for incoming connection requests
    // on the created socket
    char sendbuf []{"this is a test"};
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    string s("\n"); int i = 0;
    while (recvbuf[0] != '4') {
        if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
            wprintf(L"listen function failed with error: %d\n", WSAGetLastError());
        SOCKET ClientSocket = INVALID_SOCKET;

        cout << "Listening for a connection...\n";

        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
//            printf("accept failed: %d\n", WSAGetLastError());
//            closesocket(ListenSocket);
//            WSACleanup();
//            return 1;
        }
        else {
            do {
                iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
                if ( iResult > 0 ) {
                    if (recvbuf[0] == '4') break;
                    if (recvbuf[0] == '3') {
                        string k("a"); k[0] = ++i + 48;
                        s = k + s;
                    } else {
                        string k("a"); k[0] = i + 48;
                        s = k + s;
                    }
                }
                else if ( iResult == 0 )
                    printf("Connection closed\n");
                else {
                    printf("recv failed: %d\n", WSAGetLastError());
                }
                iResult = send( ClientSocket, s.c_str(), s.size(), 0 );
                if (iResult == SOCKET_ERROR) {
                    printf("send failed: %d\n", WSAGetLastError());
                    break;
                }
            } while( iResult > 0 );
            closesocket(ClientSocket);
        }
//        recvbuf[0] = '4';
    }

    iResult = closesocket(ListenSocket);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"closesocket function failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    WSACleanup();
    return 0;
}
