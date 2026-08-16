/* tcp_client.c */
#include "headers.h"

int main(int argc,char **argv)
{
	if(argc<3)
	{
		puts("cmdline input format is wrong");
		puts("cmdline input format: client.exe server_port server_ip");
		return 0;
	}

	puts("Creating client Socket...");
	int fd;
	fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd<0)
	{
		perror("socket");
		return 0;     
	}
	puts("Client Socket Created Successfully");

	puts("Binding & Connecting :");
	puts("Associating/Mapping IP Address+Client_PortNo with Socketk File Descriptor");
	puts("And Also initiating a 3-Way Handshake for Connection Establishment");

	struct sockaddr_in addr;
	int len=sizeof(addr);

	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(argv[2]);
	addr.sin_port=htons(atoi(argv[1]));
	if(connect(fd,(const struct sockaddr *)&addr,len)<0)
	{
		perror("connect");
		close(fd);
		return 0;     
	}
	puts("Bound & Connection With Server Success");  

	char *buff=calloc(1,100);// just allocating 100 bytes 
	int i,status;

	puts("Enter any message to send to server");
	gets(buff);
	puts("sending message to server...");
	if(send(fd,buff,strlen(buff)+1,0)<0)
	{
		perror("send");	   
	}
	printf("sent message to server : %s\n",buff);

	bzero(buff,100);// storing/ inserting null bytes in buffer by using bzero function

	puts("waiting for echo reply from server...");
	status=recv(fd,buff,100,0); // collecting result from server.
        //It may gives , result or ERROR message
        
	if(status<0)
	{
		perror("recv");
	}   
	else if(status==0)
	{
		puts("Server Abruptly/Suddently terminated");	   
	}
	else if(strcmp(buff,"result not found")==0) // testing received MSG , if matches , ERROR MSg printing
	{
		printf("\n%s\n",buff);	   
		while(1);
	}
	else// If above  conditions failed means , prime numbers received.
	{
	// but buffer is , char pointer.
	// Now we are assigning to int pointer.
	// reason: every 4 bytes of data for one prime number , and by using int pointer only we can get data.
	
		int *p=buff;
		for(i=0;i<10;i++)
			printf("%d , ",p[i]);

		printf("\b\b\b.\n");
	}

	puts("closing connection with server...");
	close(fd);
	puts("client going down...");
	sleep(3);
}
