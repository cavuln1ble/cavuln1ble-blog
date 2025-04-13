#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>

char* handleIncomingRequest(SOCKET s, struct sockaddr_in* saddr)
{
    while (1) {
        SOCKET client = accept(s, 0, 0);

        if(client<0) {
            perror("Accept failed!");
            continue;
        }

        char* in_msg = malloc(sizeof(char) * 100);
        if (recv(client, in_msg, strlen(in_msg), 0) < 0) {
            perror("Couldn't receive information");
            continue;
        
        return in_msg;
        }
    }
}

int main() {
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    char request_ok[] = "HTTP/1.1 200 OK\r\n\r\nRequested path: <the path>\r\n";
    char request_failed[] = "HTTP/1.1 404 NOT FOUND\r\n\r\n";

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) 
    {
        perror("Couldn't connect to socket");
        exit(EXIT_FAILURE);
    } 

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = 0;
    server_addr.sin_port = htons(8080);

    if (bind(s, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("Bind failed!");
        exit(EXIT_FAILURE);
    }

    if (listen(s, 10) < 0) 
    {
        perror("Listen failed!");
        exit(EXIT_FAILURE);
    }

    char* msg = handleIncomingRequest(s, &server_addr);
    free(msg);
    return 0;
}