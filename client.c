// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
  
int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread, i;
    struct sockaddr_in serv_addr;
    char msg[1024];
    char buffer[1024] = {0};
    int count = 0;

    strcpy(msg, argv[2]);
    for(i = 3; i < argc; i++){
      strcat(msg, " ");
      strcat(msg, argv[i]);
    }

    do {
      if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      {
        printf("\n Socket creation error \n");
        return -1;
      }

      memset(&serv_addr, '0', sizeof(serv_addr));

      serv_addr.sin_family = AF_INET;
      serv_addr.sin_port = htons(PORT);

      // Convert IPv4 and IPv6 addresses from text to binary form
      if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) 
      {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
      }

      if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      {
        printf("\nConnection Failed \n");
        return -1;
      }
      printf("send request\n");
      send(sock , msg , strlen(msg) , 0 );
      if(msg[0] == 'r' && msg[1] == 't' && msg[1] == 't'){
        count++;
      } else {
        count = 11;
      }
      printf("Wait from server\n");
      valread = read( sock , buffer, 1024);
      printf("%s\n",buffer );
    }while(count <= 10);
    return 0;
}

