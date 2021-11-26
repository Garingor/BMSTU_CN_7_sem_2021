#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE 1024

int sockfd = 0;

int main(){
    struct sockaddr_in server, client;
    char msg[MAXLINE];
    int sent_size = 0;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server, 0, sizeof(server));

    server.sin_family    = AF_INET; // IPv4
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    int number;
    printf("Input decimal number: ");

    if (scanf("%d", &number) != 1){
        printf("Wrong input\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    };

    sprintf(msg, "%d", number);

    sent_size = sendto(sockfd, (const char*)msg, strlen(msg),
                           MSG_CONFIRM, (const struct sockaddr*)&server,
                           sizeof(server));

    close(sockfd);

    if (sent_size != strlen(msg)){
        printf("Error sent\n");
        exit(EXIT_FAILURE);
    };

    return 0;
}
