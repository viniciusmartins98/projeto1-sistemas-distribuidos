#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h>    // htons(), inet_addr()
//#include <netdb.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
#define true 1
#define false 0

void func(int sockfd) 
{   
    char * k = malloc(MAX*sizeof(char));
    int n; 
    while (true) { 
        bzero(k, sizeof(k));
        printf("Digite o intervalo de discretização (0.0001, 0.00001 ou 0.000001) : ");
        n = 0;
        while ((k[n++] = getchar()) != '\n');
        write(sockfd, k, sizeof(k));
        bzero(k, sizeof(k)); 
        read(sockfd, k, sizeof(k)); 
        printf("From Server : %s", k); 
        if ((strncmp(k, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 
  
int main() 
{ 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    func(sockfd); 
  
    // close the socket 
    close(sockfd); 
} 