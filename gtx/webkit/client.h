// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h> 
#define PORT 8080 
int res=-1;
char* concat(const char *s1, const char *s2)
{
const char *del="@@";
const char *command="one";

    char *result = malloc(strlen(s1) +strlen(del) + strlen(s2)+strlen(del) + strlen(command) + 1); 
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result,del);
    strcat(result, s2);
    strcat(result,del);
    strcat(result, command);
    return result;
}
int compareStrings(char s1[],int slen, char s2[], int len){
	int i=0;
	for(i=0; i<len; i++){
		if(s1[i]!=s2[i]){
			return -1;
		}
	}
	return 0;
}
void mainlogin(char *id,char *password) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char *hello = concat(id,password); 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		//return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		//return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		//return -1; 
	} 
	send(sock , hello , strlen(hello) , 0 ); 
	printf("Hello message sent\n"); 
	valread = read( sock , buffer, 1024); 
	free(hello);
	printf("%s\n",buffer ); 
        printf(" print %d \n ",res);
        res=compareStrings(buffer,7,"success",7);
	 
} 

