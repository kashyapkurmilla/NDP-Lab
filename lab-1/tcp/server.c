#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>

#define myport 9091
int main()
{
	int sockfd =  socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		perror("Socket Creation error\n");
	}
	struct sockaddr_in client_address , server_address ;

	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(myport);
	memset(server_address.sin_zero,'\0',sizeof(server_address));

	bind(sockfd,(struct sockaddr *)&server_address,sizeof(server_address));
	printf("Binding successfull\n");

	listen(sockfd,10);
	printf("The server is listening !!\n");

	int size = sizeof(struct sockaddr);

	int afd = accept(sockfd,(struct sockaddr *)&client_address,&size);
	int buffer[10] ;
	int choice, n, temp;
	int odd[10] = {0};
	int even[10] = {0};
	int a =0, b = 0;
	while(1)
	{
		recv(afd, buffer, sizeof(buffer), 0);
		recv(afd, &n, sizeof(n), 0);
		recv(afd, &choice, sizeof(choice), 0);
		switch(choice)
		{
			case 1:
					for(int i=0 ; i<n-1 ; i++)
					{
						for(int j=0 ; j<n-1-i ; j++)
						{
							if(buffer[j]>buffer[j+1])
							{
								temp = buffer[j];
								buffer[j] = buffer[j+1];
								buffer[j+1] = temp;
							}
						}
					}
					send(afd, buffer, 40, 0);
					break;
			case 2:
					for(int i=0 ; i<n-1 ; i++)
					{
						for(int j=0 ; j<n-1-i ; j++)
						{
							if(buffer[j]<buffer[j+1])
							{
								temp = buffer[j];
								buffer[j] = buffer[j+1];
								buffer[j+1] = temp;
							}
						}
					}
					send(afd, buffer, 40, 0);
					break;
			case 3: 
					for(int i=0 ; i<n ; i++)
					{
						if(buffer[i]%2==0)
							even[a++] = buffer[i];
						else
							odd[b++] = buffer[i];					
					}
					send(afd, odd, sizeof(odd), 0);
					send(afd , &b, sizeof(b) ,0);
					send(afd, even, sizeof(even), 0);
					send(afd, &a, sizeof(a), 0);

					break;
			case 4:close(sockfd);
					exit(0);
					
			
		} 
	}

}
