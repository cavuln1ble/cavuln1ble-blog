#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int server_fd;
struct sockaddr_in server_addr;

int isRequestValid(SOCKET* request) 
{
    char* tmp = strtok(request, " ");
    if (strcmp(tmp, "GET HTTP/1.1")) {
        tmp = strtok(tmp, "\r");
        return strcmp(tmp, "200 OK");
    }
    return 0;    
}

char* handleIncomingRequest(struct sockaddr_in* socket)
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int* client_fd = malloc(sizeof(int)); 
    while (1) {
        SOCKET request = accept(client_fd, (struct sockaddr_in*) &client_addr, client_addr_len);

        if(request<0) {
            perror("Accept failed!");
            continue;
        }

        if (isRequestValid(&request)) {
            perror("Request invalid");
            continue;
        }
        char* in_msg = malloc(sizeof(char) * 100);
        if (recv(request, in_msg, strlen(in_msg), 0) < 0) {
            perror("Couldn't receive information");
            continue;
        
        return in_msg;
        }
    }
}

int main() {
    char* request_ok[] = "HTTP/1.1 200 OK\r\n\r\nRequested path: <the path>\r\n";
    char* request_failed[] = "HTTP/1.1 404 NOT FOUND\r\n\r\n";
    
    if (server_fd = socket(AF_INET, SOCK_STREAM, 0) < 0) 
    {
        perror("Couldn't connect to socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(80); 

    if (bind(server_fd, (struct sockaddr_in*) &server_addr, sizeof(server_addr.sin_addr)) < 0) 
    {
        perror("Bind failed!");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) 
    {
        perror("Listen failed!");
        exit(EXIT_FAILURE);
    }

    char* msg = handleIncomingRequest(&server_addr);
    
    return 0;
}