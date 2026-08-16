/* tcp_server.c */
#include "headers.h"
int testMSG(char *);
void collectNS(char * , int * , int *);
int *primeNumbers(int , int);

int main(int argc,char **argv)
{
	if(argc<2)
	{
		puts("cmdline input format: server.exe server_port");
		return 0;
	}

	puts("Creating Server Socket...");
	int sfd;
	char *q;
	int N=0,S=0,*primeData;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	{
		perror("socket");
		return 0;     
	}
	puts("Server Socket Created Successfully");

	puts("Binding : Associating/Mapping IP Address+Serve_PortNo with Socket/Netowrk File Descriptor");
	struct sockaddr_in saddr;
	int slen=sizeof(saddr);

	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=inet_addr("0.0.0.0");
	saddr.sin_port=htons(atoi(argv[1]));
	if(bind(sfd,(const struct sockaddr *)&saddr,slen)<0)
	{
		perror("bind");
		close(sfd);
		return 0;     
	}
	puts("Bind Success");  

	puts("Creating Connection Queue of Size 1 ONLY...");
	if(listen(sfd,1)<0)
	{
		perror("listen");
		close(sfd);
		return 0;     
	}
	puts("Connection Queue Created");


	puts("waiting for 3-Way Handshake to initiated by any client...");
	struct sockaddr_in caddr;
	int clen=sizeof(caddr);
	int cfd;
	cfd=accept(sfd,(struct sockaddr *)&caddr,&clen);
	if(cfd<0)
	{
		perror("accept");
		close(sfd);
		return 0;     
	}
	puts("Connection with some client accepted");
	puts("Whose Client Information is :");
	unsigned short int clientPortNo=ntohs(caddr.sin_port);
	char *clientIP = inet_ntoa(caddr.sin_addr);
	printf("Client's Ephemeral Port is : %d\n",clientPortNo);
	printf("Client's IPv4 Address   is : %s\n",clientIP);

	char buff[100];
	int status;

	puts("Waiting for some message/request from connected client...");
	//status=read(cfd,buff,100);
	status=recv(cfd,buff,100,0);
	if(status<0)
	{
		perror("read");	   
	}
	else if(status==0)
	{
		puts("Connected Client abruptly/suddenly/without 3-Way Handshake for Connection Termination terminated");	   
	}
	else
	{
		if(testMSG(buff)) // for testing MSG is valid or not
		{
			collectNS(buff,&N,&S);// converting START value and no.of PRIME numbers value

			if(N<=0 || S<=0)
			{
				puts("sending ERROR MSG to client...\n");
				send(cfd,"result not found",17,0);
				sleep(1);
			}
			else
			{
				puts("sending result to client...\n");
				primeData=primeNumbers(N,S);// calling function to generate N prime numbers from S
				send(cfd,primeData,N*sizeof(int),0);// result echoing back to  client 
				sleep(1);
				puts("sent result to client...\n");

			}

		}
		else
		{
			puts("sending ERROR MSG to client...\n");
			send(cfd,"result not found",17,0);// if invalid MSG , sending ERROR MSG to client
			sleep(1);
		}

	}

	puts("Closing Connection With Connected Client");
	close(cfd);

	puts("Server going down");
	close(sfd);


}



int testMSG(char *msg)
{
// testing received string , whether it following STD format or not.

	char str[100];
	strcpy(str,msg);
	char *p=str;

	while(*p)
	{
	// removing all spaces and non-alpha

		if((*p==32) || ((*p)>=48 && (*p<=57)))
		{
			memmove(p,p+1,strlen(p+1)+1);
			p--;
		}
		p++;
	}

        // testing remaining data
	if(strcmp(str,"primenumbersfrom")==0)
		return 1;
	else
		return 0;

}

void collectNS(char *buff , int *N , int *S)
{
	char *p,*q;

	p=buff;
	p=strtok(p," ");
	*N=atoi(p);// first word of string converting into int type.


	p=strtok(NULL," ");
	while(p!=NULL) 
	{
	// traveling in loop to reach last word
	 
	 	q=p;// present word location assigning to another pointer to use at last for converting last word into int type
	 	    // Because , P will reach NULL while terminating loop , and Q will point at last word
	 	    
    		p=strtok(NULL," ");
		if(p!=NULL && (atoi(q)))
		{
		// In our string only first and last word must be int data
	        // in-between ( except first and last ) , if we found any non-ascii data , string is invalid.
	        // So, breaking loop.
			break;
		}


	}
	
	// P==NULL , meaning is , our string is following STD format.
	if(p==NULL)
		*S=atoi(q); // last word converting into int type. last word address available in pointer Q

}


int testprime(int n)
{
	int i=2;
	for(i;i<=n/2;i++)
		if(n%i==0)
			return 0;
	return 1;
}



int *primeNumbers(int N , int S)
{
// finding PRIME numbers from S and storing in dynamic block by using DMA.
	int *p,i=0;
	p=calloc(N,sizeof(int));

	if(S%2==0)
		S++;

	while(i<N)
	{
		if(testprime(S)==1)
			p[i++]=S;
		S+=2;
	}
	return p;
}


