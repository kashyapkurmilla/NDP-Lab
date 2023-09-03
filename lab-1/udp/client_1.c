#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define myport 9090

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket Creation Error");
        exit(1);
    }
    printf("Socket Created\n");

    struct sockaddr_in server_addr;
    server_addr.sin_port = htons(myport);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    int size = sizeof(struct sockaddr);
    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Socket Connected\n");

    char buff[99];
    int len, a = 0, e = 0, i = 0, o = 0, u = 0;
    char result[20];

    while (1) {
        printf("Enter a string (or 'halt' to exit): ");
        scanf("%s", buff);

        if (strcmp(buff, "halt") == 0) {
            sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&server_addr, size);
            printf("Exiting...\n");
            close(sockfd);
            exit(0);
        }

        sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&server_addr, size);

        // Receive the result and other data from the server
        recvfrom(sockfd, result, sizeof(result), 0, (struct sockaddr *)&server_addr, &size);
        recvfrom(sockfd, &len, sizeof(len), 0, (struct sockaddr *)&server_addr, &size);
        recvfrom(sockfd, &a, sizeof(a), 0, (struct sockaddr *)&server_addr, &size);
        recvfrom(sockfd, &e, sizeof(e), 0, (struct sockaddr *)&server_addr, &size);
        recvfrom(sockfd, &i, sizeof(i), 0, (struct sockaddr *)&server_addr, &size);
        recvfrom(sockfd, &o, sizeof(o), 0, (struct sockaddr *)&server_addr, &size);
        recvfrom(sockfd, &u, sizeof(u), 0, (struct sockaddr *)&server_addr, &size);

        printf("Size of the string = %d\n", len);
        printf("%s\n", result);
        printf("Vowels count:\n");
        printf("A = %d\n", a);
        printf("E = %d\n", e);
        printf("I = %d\n", i);
        printf("O = %d\n", o);
        printf("U = %d\n", u);
    }

    return 0;
}
