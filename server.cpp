#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#define DEFAULT_PORT 1600
#define BUF 1024
int main(){
	int client;
	int server;
	struct sockaddr_in server_address;
	client=socket(AF_INET, SOCK_STREAM,0);
	if(client<0){
		std::cout<<"ERROR!";
		exit(0);
	}

	std::cout<<"Server was created!";

	server_address.sin_port=htons(DEFAULT_PORT);
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htons(INADDR_ANY);

	int ret=bind(client,reinterpret_cast<struct sockaddr*>(&server_address),sizeof(server_address));

	if(ret<0){
		std::cout<<"Our server in establishing!";//Its when such port in using
		return -1;
	}

	socklen_t size=sizeof(server_address);
	std::cout<<"SERver: "<<"Listening clients\n";
	listen(client,1);

	server=accept(client,reinterpret_cast<struct sockaddr*>(&server_address),&size);
	if(server<0)
		std::cout<<"Cant hear anything!\n";

	char buffer[BUF];//Our buffer where we store our messages
	bool isExit=false;
	while(true){
		strcpy(buffer,"Выберите команду:1)Создать файл;2)Удалить файл");//We can offer only two operations create and delete. So client will make choise.
		send(server,buffer,BUF,0);
		recv(server,buffer,BUF,0);
		char t=buffer[0];
		if(t=='1'){
			send(server,"Введите название файла!",BUF,0);
		}
		else if(t=='2'){
			send(server,"Введите название файла для удаления!",BUF,0);
		}
			recv(server,buffer,BUF,0);
			std::cout<<buffer;

		if(t=='1'){
			std::ofstream out(buffer);
			out.close();
			send(server,"Файл был успешно создан!",BUF,0);
		}
		else{
			if(remove(buffer)!=0)
				send(server,"Файл с таким названием не существует",BUF,0);
			else
				send(server,"Файл успешно удален!",BUF,0);

		}

		
		
	

	}
	close(server);
	return 0;
}

