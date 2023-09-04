#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h> 
#define myport 8080
#define maxsize 1024

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket Creation Error");
        exit(1);
    }
    printf("Socket Created\n");

    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_port = htons(myport);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding error");
        close(sockfd);
        exit(1);
    }
    printf("Binding Successful\n");

    int size = sizeof(struct sockaddr);
    char buff[maxsize];
    int len, a = 0, e = 0, i = 0, o = 0, u = 0;
    char result[maxsize];

    while (1) {
        printf("Waiting for a string from the client...\n");

        recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&client_addr, &size);

        if (strcmp(buff, "halt") == 0) {
            printf("Exiting...\n");
            close(sockfd);
            exit(0);
        }

        len = strlen(buff);
        a = e = i = o = u = 0;
        for (int k = 0; k < len; k++) {
            char c = tolower(buff[k]);
            switch (c) {
                case 'a':
                    a++;
                    break;
                case 'e':
                    e++;
                    break;
                case 'i':
                    i++;
                    break;
                case 'o':
                    o++;
                    break;
                case 'u':
                    u++;
                    break;
                default:
                    break;
            }
        }
        int is_palindrome = 1;
        for (int k = 0; k < len / 2; k++) {
            if (tolower(buff[k]) != tolower(buff[len - k - 1])) {
                is_palindrome = 0;
                break;
            }
        }

        if (is_palindrome) {
            strcpy(result, "Palindrome");
        } else {
            strcpy(result, "Not a palindrome");
        }
        sendto(sockfd, result, strlen(result), 0, (struct sockaddr *)&client_addr, size);
        sendto(sockfd, &len, sizeof(len), 0, (struct sockaddr *)&client_addr, size);
        sendto(sockfd, &a, sizeof(a), 0, (struct sockaddr *)&client_addr, size);
        sendto(sockfd, &e, sizeof(e), 0, (struct sockaddr *)&client_addr, size);
        sendto(sockfd, &i, sizeof(i), 0, (struct sockaddr *)&client_addr, size);
        sendto(sockfd, &o, sizeof(o), 0, (struct sockaddr *)&client_addr, size);
        sendto(sockfd, &u, sizeof(u), 0, (struct sockaddr *)&client_addr, size);
    }

    return 0;
}
