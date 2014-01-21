#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "project.c"

	int sfd, cfd;
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
    saddr.sin_port=htons(3426);
    
    if (bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
		error("ERROR on binding", 1);
    listen(sfd, 1);
    cfd=accept(sfd, (struct sockaddr *) NULL, NULL);
    if (sfd < 0)
		error("ERROR on accept", 1); 
}

void recogniting_msg(char *str)
{
	int i;
	
	if (strncmp(str, "str:", 4)==0)
	{		
		for(i=4; str[i]!='\n'; i++)
			lcd_byte_4bit(str[i], LCD_CHR);
	}
	else
	{
		if (strncmp(str, "com:LINE_1", 10)==0)
			lcd_byte_4bit(LCD_LINE_1, LCD_CMD);
		if (strncmp(str, "com:LINE_2", 10)==0)
			lcd_byte_4bit(LCD_LINE_2, LCD_CMD);
		if (strncmp(str, "com:CLEAR", 10)==0)
			lcd_byte_4bit(0x01, LCD_CMD);
		if (strncmp(str, "com:SET_LINE_1", 10)==0)
			lcd_byte_4bit(0x20, LCD_CMD);
		if (strncmp(str, "com:SET_LINE_2", 10)==0)
			lcd_byte_4bit(0x28, LCD_CMD);
	}
}

int main()
{
	char str[44];
	char c='0';
	int n=0;
 
	con();
 	init();
	//init_LCD(1,1,0);

	do{
		bzero(str,44);		     
		n = read(cfd,str,44);
		if (n < 0) error("ERROR reading from socket", 0);
			recogniting_msg(str);
		n = write(cfd,&c,sizeof(c));
		if (n < 0) error("ERROR writing to socket", 0);    
	}while (strncmp(str,"com:CLOSE_SERVER",16));
	
    close(cfd);
    return 0; 
}
