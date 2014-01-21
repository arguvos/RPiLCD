#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int sfd=0;
struct sockaddr_in saddr;

void error(char msg[], char ctrl)
{
    printf("%s",msg);
    if (ctrl==1)
	{		
		close(sfd);
		printf("Program close.\n");	
		exit(0);
	}	
}

void con()
{	
	sfd = socket(AF_INET, SOCK_STREAM, 0);

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(3426);
    saddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    
    if (connect(sfd,(struct sockaddr *) &saddr,sizeof(saddr)) < 0) 
        error("ERROR connecting\n", 1);
}

void send_data(char str[])
{	
	int n=0;
	char ch='0';
	
	n = write(sfd,str,strlen(str));
    if (n < 0) 
         error("ERROR writing to socket", 0);
    else
		printf("Data send.\n");
    n=read(sfd, &ch, sizeof(ch));
    if (n < 0) 
         error("ERROR reading from socket", 0);
    else
		printf("Data delivered.\n\n");
}

int main()
{
    char str[44];//40 is max length of string on LCD + 4 for indetificated command
	
    con();
	
	do {
		printf("Your turn: ");
		bzero(str,44);
		fgets(str,44,stdin);
		
		if (strncmp(str,"com:",4)==0||strncmp(str,"str:",4)==0)
			send_data(str);
		else
			if (strncmp(str,"exit",4)!=0)
				error("ERROR, in input data\n", 0);
	} while (strncmp(str,"exit",4));
	
    close(sfd);
    return 0;
}
