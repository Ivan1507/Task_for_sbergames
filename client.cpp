#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <fstream>

#define DEFAULT_PORT 1600
#define BUF 1024
#define SERVER_IP "127.0.0.1"

int main(){
	int client;
	struct sockaddr_in server_address;
	client=socket(AF_INET,SOCK_STREAM,0);

	if(client<0){
		std::cout<<"Error!Server is busy...\n";
		exit(0);

	}
	
	server_address.sin_port=htons(DEFAULT_PORT);
	server_address.sin_family=AF_INET;
	inet_pton(AF_INET,SERVER_IP,&server_address.sin_addr);

	std::cout<<"=>CLient socket created!\n";
	int ret=connect(client,reinterpret_cast<struct sockaddr*>(&server_address),sizeof
			(server_address));

	if(ret==0){
		std::cout<<"=>Connection to server"<<inet_ntoa(server_address.sin_addr)
			<<"with port number "<<DEFAULT_PORT<<'\n';

	}
	char buffer[BUF];

	//std::cout<<"=>WAITING 123\n";
 	std::cout<<"=>Connecction is good!\n";
	std::string oper;
	recv(client,buffer,BUF,0);
	bool f=0;
	int i=2;
	while(i){
		if(!f) std::cout<<"Выберите команду:1)Создать файл;2)Удалить файл\n";
		std::cin.getline(buffer,BUF);
		if(buffer[0]=='\0'){//Check every time that we dont send blank buffer
			continue;
		}
		f=1;
		send(client,buffer,BUF,0);//Send our command

		recv(client,buffer,BUF,0);
		std::cout<<buffer;
		i--;
		
		
	}
	return 0;
}
