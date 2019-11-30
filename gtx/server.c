// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "select_rows.h" 
#define PORT 8080 

char compareStrings(char s1[],int slen, char s2[], int len){
	int i=0;

	for(i=0; i<len; i++){
		if(s1[i]!=s2[i]){
			return -1;
		}
	}
	return 0;
}


int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *suc = "success";  
	char *fail = "failure";
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
while(1){
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 

	valread = read( new_socket , buffer, 1024); 
	printf("%s\n",buffer ); 
 int i = 0;
    char *p = strtok (buffer, "@@");
    char *array[3];
    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, "@@");
    }
if(compareStrings(array[3],3,"two",3)!=0){

}else if(compareStrings(array[3],3,"one",3)!=0){
int j=mains(array[0],array[1]);
if(j==0){
	send(new_socket , fail , strlen(fail) , 0 ); 
	printf("login failure sent\n"); 
}else if(j==1){
	send(new_socket , suc , strlen(suc) , 0 ); 
	printf("login success sent\n"); 
}
}

}
	return 0; 
} 


