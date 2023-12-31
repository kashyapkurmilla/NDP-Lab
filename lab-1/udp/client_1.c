#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define myport 8080
#define maxsize 1024

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

    char buff[maxsize];
    int len, a = 0, e = 0, i = 0, o = 0, u = 0;
    char result[maxsize];

    while (1) {
        printf("Enter a string (or 'halt' to exit): ");
        fgets(buff, sizeof(buff), stdin);
        buff[strcspn(buff, "\n")] = '\0'; // Remove trailing newline

        if (strcmp(buff, "halt") == 0) {
            sendto(sockfd, buff, strlen(buff) + 1, 0, (struct sockaddr *)&server_addr, size);
            printf("Exiting...\n");
            close(sockfd);
            exit(0);
        }

        sendto(sockfd, buff, strlen(buff) + 1, 0, (struct sockaddr *)&server_addr, size);

        recvfrom(sockfd, result, sizeof(result), 0, (struct sockaddr *)&server_addr, &size);//refer terminal manual
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
