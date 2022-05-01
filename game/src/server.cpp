// Server side C/C++ program to demonstrate Socket
// programming
// #include <netinet/in.h>
// #include <stdio.h>
// #include<iostream>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <unistd.h>
// #define PORT 8080
#include "server.h"

int connect_server()
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	std::cout<<"Done1\n";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
		== 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	std::cout<<"Done2\n";

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	std::cout<<"Done3\n";

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	std::cout<<"Done4\n";

	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	std::cout<<"Done5\n";

	if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	std::cout<<"Done6\n";

	return new_socket;
}

void server_send_data(int new_socket, int* locs) {
	int16_t* sdata = new int16_t(5);
	for(int i = 0; i<5; i++) {
		sdata[i] = (int16_t)locs[i];
	}
	send(new_socket, sdata, sizeof(int16_t)*5, 0);
}

void server_recv_data(int new_socket, int* locs) {
	int16_t buffer[5] = { 0 };
	int valread = read(new_socket, buffer, sizeof(int16_t)*5);
	for(int i = 0; i<5; i++) {
		locs[i] = (int)buffer[i];
	}
}

// 	bool end_connection = false;
// 	while(!end_connection) {
// 		// int sdata[5] = {5, 6, 7, 8, 9};
// 		int16_t* sdata = new int16_t(5);
// 		for(int16_t i = 5; i<10; i++) {
// 			sdata[i-5] = i;
// 		}
// 		std::cout<<buffer[0]<<" "<<buffer[1]<<" "<<buffer[2]<<" "<<buffer[3]<<" "<<buffer[4]<<std::endl;
// 		// std::cout<<buffer[1]<<" "<<buffer[2]<<std::endl;
// 		// send(new_socket, sdata, strlen(hello), 0);
// 		send(new_socket, sdata, sizeof(int16_t)*5, 0);

// 		// printf("Hello message sent\n");
// 		end_connection = true;
// 	}
// 	return 0;
// }
