// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

int command(char* string){
  if(strlen(string) < 3){
    return -1;
  }

  if(string[0] == 'r' && string[1] == 's' && string[2] == 'v'){
    return 1;
  } else if(string[0] == 'r' && string[1] == 't' && string[2] == 't'){
    return 0;
  }

  return -1;
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    struct tm *hour;
    time_t now;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char resp[1024];
 
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    do{
      memset(buffer, 0, 1024);
      if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
              (socklen_t*)&addrlen))<0)
      {
        perror("accept");
        exit(EXIT_FAILURE);
      }
      valread = read(new_socket , buffer, 1024);
      switch(command(buffer)){
        case 0:
          now = time(NULL);
          hour = localtime(&now);
          strcpy(resp, "Rrtt: ");

          char hourHH[3];
          sprintf(hourHH, "%d", hour->tm_hour);    
          strcat(resp, hourHH);
          strcat(resp, ":");
          
          char hourMM[3];
          sprintf(hourMM, "%d", hour->tm_min);    
          strcat(resp, hourMM);
          strcat(resp, ":");

          char hourSS[3];
          sprintf(hourSS, "%d", hour->tm_sec);    
          strcat(resp, hourSS);
          break;
        case 1:
          strcpy(resp, "dns ");
          strcpy(resp, buffer);
          break;
        default:
          strcpy(resp, "Comando inválido");
          break;
      }
//      printf("%s\n",buffer );
      send(new_socket , resp , strlen(resp) , 0 );
//      printf("Hello message sent\n");
    } while(1);
    return 0;
}
