// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread, i;
    struct sockaddr_in serv_addr;
    char msg[1024];
    char buffer[1024] = {0};
    int count = 0;
    struct timespec time_send, time_receive;

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

      //Get current time in send request
      #ifdef TIME_UTC
         timespec_get(&time_send, TIME_UTC);
      #endif

      //Send Request
      printf("send request\n");
      send(sock , msg , strlen(msg) , 0 );

      //Waiting response from server
      printf("Wait from server\n");
      valread = read( sock , buffer, 1024);

      //Get current time to receive msg
      #ifdef TIME_UTC
         timespec_get(&time_receive, TIME_UTC);
      #endif


      // Diferent print for command
      if(msg[0] == 'r' && msg[1] == 't' && msg[1] == 't'){
        count++;
        printf("%s -- time: %dns\n",buffer, time_receive.tv_nsec - time_send.tv_nsec);
      } else {
        count = 11;
        if(msg[0] == 'r' && msg[1] == 't' && msg[2] == 't'){
          printf("dns\n");
        } else {
          printf("%s\n", buffer);
        }
      }
    }while(count <= 10);
    return 0;
}
