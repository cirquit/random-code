/* damit inet_aton() deklariert wird */
#define _BSD_SOURCE

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUF 256

/*
Main-Funktion
*/
int main(int argc,char**argv){

  printf("Chat\n\n\n");
  char *buffer = (char*) malloc(sizeof(char)*BUF);
  ssize_t size;

  // Socket vorbereiten
  struct sockaddr_in address;
  int sock = socket(PF_INET,SOCK_STREAM,0);
  int new_socket;     
  address.sin_family = AF_INET;
  address.sin_port = htons(4711);

  //  Wenn das Programm ohne Argument gestartet wird, verhaelt es sich als Server  
  if (argc < 2) {

    printf("Warte auf Client\n");
    address.sin_addr.s_addr=INADDR_ANY;
    if (bind(sock,(struct sockaddr*) &address, sizeof(address)) != 0) {
        printf("Port belegt!\n");  
    }

    // Auf Anfragen warten & eingehende Verbindung behandeln
    listen(sock, 5);  
    struct sockaddr_in client;
    int client_len = sizeof(client);
    new_socket = accept(sock,( struct sockaddr*) &client, (socklen_t*) &client_len);
    if (new_socket > 0) {
      printf("Verbindung mit %s hergestellt.\n", inet_ntoa(address.sin_addr));
    }

    do {
      // Der Server sendet die erste Nachricht
      printf("Ich: ");
      fgets(buffer,BUF,stdin);
      send(new_socket,buffer,strlen(buffer),0);

      // Warten auf Nachricht vom Client
      size = recv(new_socket, buffer, BUF-1, 0);
      if (size > 0) buffer[size]='\0';
      printf("Du: %s",buffer);

      // Abbruch des Chats mit der Eingabe von "quit"
    } while (strcmp (buffer, "quit\n")!=0);

    // Socket schliessen
    close(new_socket);
    close(sock);
  }

  //  Wenn das Programm mit IP-Adresse als Argument gestartet wird, verhaelt es sich als Client  
  else {

    // Mit Server verbinden
    sock = socket(AF_INET, SOCK_STREAM, 0);  
    inet_aton(argv[1], &address.sin_addr);
    if(connect(sock,(struct sockaddr*) &address, sizeof(address)) == 0) {
      printf("Verbindung mit %s hergestellt.\n",inet_ntoa(address.sin_addr));
    }

    do {
      // Der Client wartet auf die erste Nachricht des Servers
      size = recv(sock, buffer, BUF-1, 0);
      if (size > 0) buffer[size]='\0';
      printf("Du: %s", buffer);

      // Wenn die empfangene Nachricht nicht "quit" ist, geht der Chat weiter
      if(strcmp(buffer,"quit\n")) {
        printf("Ich: ");
        fgets(buffer, BUF, stdin);
        send(sock,buffer,strlen(buffer),0);
      }

    // Abbruch des Chats mit der Eingabe von "quit"
    } while (strcmp(buffer,"quit\n") != 0);

    // Socket schliessen
    close(sock);
  }

  // Speicher freigeben und Ende
  free(buffer);
  return EXIT_SUCCESS;
}
