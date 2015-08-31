#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>

#define PORT 4711
#define MSGL 256

int create_socket()
{   
    int fd;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        printf("Could not create socket");
        exit(1);
    }
    printf("socket created...\n");
    return fd;
}

void bind_socket(int sock, struct sockaddr_in serv_addr)
{   
    int n;
    n = bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (n < 0)
    {
        printf("ERROR on binding");
        exit(1);
    }
    printf("socket bound...\n");
}

void get_message(int sock, char* msg)
{
    int n;
    n = read(sock, msg, MSGL);
    if (n < 0)
    {
        printf("ERROR reading from socket");
        exit(1);
    }
}

void send_message(int sock, char* msg)
{   
    int n;
    n = write(sock, msg, MSGL);
    if (n < 0)
    {
        printf("ERROR writing to socket");
        exit(1);
    }
    
}

int accept_connection(int sock, struct sockaddr_in cli_addr)
{
    int fd;
    int cli_addr_len = sizeof(cli_addr);
    fd = accept(sock, (struct sockaddr *)&cli_addr, &cli_addr_len);
    if (fd < 0) 
    {
        printf("ERROR on accept");
        exit(1);
    }
    printf("connection accepted...\n");
    return fd;
}

int main(int argc, char const *argv[])
{

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    int socket_server;
    int socket_client;

    char in_buf[MSGL];
    char out_buf[MSGL];

    bzero(in_buf, MSGL);
    bzero(out_buf, MSGL);


    socket_server = create_socket();


    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);


    bind_socket(socket_server, server_addr);


    listen(socket_server, 5);


    socket_client = accept_connection(socket_server, client_addr);




    while(1)
    {   
        //wait for reply
        printf("waiting for reply...\n");
        bzero(in_buf, MSGL);
        get_message(socket_client, in_buf);
        printf("client sayz: %s\n", in_buf);

        //get input
        printf("Message to client: ");
        bzero(out_buf, MSGL);
        fgets(out_buf, MSGL, stdin);
        if (strcmp(out_buf,"quit\n") == 0){
            break;
        }

        //send input
        printf("sending: %s\n", out_buf);
        send_message(socket_client, out_buf);
    }


    close(socket_client);
    close(socket_server);


    return 0;
}