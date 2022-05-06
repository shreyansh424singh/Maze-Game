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
	std::
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
		== 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	std::
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
	std::
	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	std::
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	std::
	if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	std::
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