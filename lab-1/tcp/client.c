#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include<stdlib.h>
# include<netinet/in.h>
#include<string.h>

#define myport 8080
int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket creation error\n");
		exit(0);
	}
	printf("Socket created\n");

	struct sockaddr_in client_address ;

	client_address.sin_port = htons(myport);
	client_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	client_address.sin_family = AF_INET;
	memset(client_address.sin_zero,'\0',sizeof(client_address));

	int size = sizeof(struct sockaddr);

	connect(sockfd,(struct sockaddr *)&client_address,sizeof(client_address));
	printf("Connection successfull\n");

	int choice ,n ,a , b;
	int buffer[10];
	int odd[10] = {0};
	int even[10] = {0};
	
	while (1)
	{
		printf("\nChoose one :\n");
		printf("1.Ascending order\n");
		printf("2.descending order\n");
		printf("3.Split into odd and even arrays\n");
		printf("4.Exit\n");
		printf(">");
		scanf("%d",&choice);
		switch(choice)
		{
		case 1 :
			printf("Enter number of elements : ");
			scanf("%d",&n);
			
			printf("Enter elements :\n");
			for(int i=0;i<n;i++)
				scanf("%d",&buffer[i]);
			send(sockfd,buffer,sizeof(buffer),0);
			send(sockfd,&n,sizeof(n),0);
			send(sockfd,&choice,sizeof(choice),0);
			recv(sockfd,buffer,sizeof(buffer),0);
			printf("Ascending order : \n");
			for (int i = 0; i < n; i++)
			{
				printf("%d ",buffer[i]);
			}
			break;
		case 2 :
			printf("Enter number of elements : ");
			scanf("%d",&n);
			
			printf("Enter elements :\n");
			for(int i=0;i<n;i++)
				scanf("%d",&buffer[i]);
			send(sockfd,buffer,sizeof(buffer),0);
			send(sockfd,&n,sizeof(n),0);
			send(sockfd,&choice,sizeof(choice),0);
			recv(sockfd,buffer,sizeof(buffer),0);
			printf("Descending order : \n");
			for (int i = 0; i < n; i++)
			{
				printf("%d ",buffer[i]);
			}
			break;
		case 3 :
			printf("\nEnter the no of elements in array:");
					scanf("%d", &n);
					
					printf("\nEnter the elements in array:");
					for(int i=0 ; i<n ; i++)
						scanf("%d", &buffer[i]);
					send(sockfd, buffer, 40, 0);
					send(sockfd, &n, 4, 0);
					send(sockfd, &choice, 4, 0);

					recv(sockfd, odd, 40,0);
					recv(sockfd, &b, 4, 0);
					recv(sockfd, even, 40, 0);
					recv(sockfd, &a, 4, 0);
					printf("\nThe odd elements in the array \n");
					for(int i=0 ; i<b ; i++)
						printf("%d ", odd[i]);
					printf("\nThe odd elements in the array \n");
					for(int i=0 ; i<a ; i++)
						printf("%d ", even[i]);
					break;
		case 4 :
			close(sockfd);
			exit(0);
			break;
		default :
			printf("Invalid choice");
			break;
		}

	}
	
}
