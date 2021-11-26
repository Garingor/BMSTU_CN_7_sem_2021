#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "convert.h"

#define PORT    8080
#define MAXLINE 1024

int sockfd = 0;
int flag_sigint = 0;

void sigint_handler(int signum) {
    close(sockfd);
    printf("\nSocket is closed");
    flag_sigint = 1;
}

int main(){
    struct sockaddr_in server, client;
    char msg[MAXLINE];

    // AF_INET - это семейство адресов, которое используется для обозначения типа адресов,
    // с которыми ваш сокет может взаимодействовать (IP V4)

    //UDP ( SOCK_DGRAM)-это протокол на основе дейтаграмм.
    // Вы отправляете одну дейтаграмму и получаете один ответ, а затем соединение прекращается.

    // IPPROTO_UDP для сокетов UDP

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server, 0, sizeof(server));

    server.sin_family    = AF_INET; // IPv4
    server.sin_addr.s_addr = INADDR_ANY; // связывает сокет со всеми доступными интерфейсами
    server.sin_port = htons(PORT); // host-to-network short

    if (bind(sockfd, (const struct sockaddr *)&server,
              sizeof(server)) < 0 ) // присваивает адрес, указанный в addr, сокету, на который ссылается
                                    // дескриптором файла sockfd
    {
        close(sockfd);
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int sizeclient = sizeof(client);
    int n;

    memset(&client, 0, sizeclient);

    signal(SIGINT, sigint_handler);

    n = recvfrom(sockfd, (char *)msg, MAXLINE,
                 MSG_WAITALL, ( struct sockaddr *) &client,
                 &sizeclient); // используется для получения сообщений из сокетa

    if (flag_sigint)
    {
        exit(EXIT_SUCCESS);
    }

    if (n < 0) {
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    msg[n] = '\0';

    int number = atoi(msg);

    printf("10 - %d "
           "\n2 - %s  "
           "\n8 - %s  "
           "\n16 - %s "
           "\n18 - %s"
           "\n",
           number,
           convert(number, 2),
           convert(number, 8),
           convert(number, 16),
           convert(number, 18));

    close(sockfd);

    return 0;
}
