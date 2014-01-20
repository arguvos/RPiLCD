#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

	int sfd;
	struct sockaddr_in saddr;
        
void error(char msg[], char ctrl)
{
    printf("%s",msg);
    if (ctrl==1)
	{		
		close(sfd);
		printf("Program close.");	
		exit(0);
	}	
}

void con()
{
	sfd= socket(AF_INET, SOCK_STREAM, 0);
    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=htonl(INADDR_ANY);
    saddr.sin_port=htons(3425);
    
    if (bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
		error("ERROR on binding", 1);
    listen(sfd, 1);
    sfd=accept(sfd, (struct sockaddr *) NULL, NULL);
    if (sfd < 0)
		error("ERROR on accept", 1); 
}

int main()
{
	char str[44];
	char c='0';
	int n=0;
 
	con();
 
	do{
		bzero(str,44);		     
		n = read(sfd,str,44);
		if (n < 0) error("ERROR reading from socket", 0);
			printf("Here is the message: %s\n",str);
		n = write(sfd,&c,sizeof(c));
		if (n < 0) error("ERROR writing to socket", 0);    
	}while (strncmp(str,"com:close_server",16));
	
    close(sfd);
    return 0; 
}
