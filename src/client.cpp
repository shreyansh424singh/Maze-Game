// Client side C/C++ program to demonstrate Socket
// programming
// #include <arpa/inet.h>
// #include <stdio.h>
// #include <string.h>
// #include <iostream>
// #include <sys/socket.h>
// #include <unistd.h>
// #define PORT 8080
#include "client.h"

int connect_client(char* ip_add)
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	// char* ip = "127.0.0.1";
	char* ip = ip_add;

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, ip, &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	return sock;
}

void client_send_data(int new_socket, int* locs) {
	int16_t* sdata = new int16_t(6);
	for(int i = 0; i<6; i++) {
		sdata[i] = (int16_t)locs[i];
	}
	send(new_socket, sdata, sizeof(int16_t)*6, 0);
}

void client_recv_data(int new_socket, int* locs) {
	int16_t buffer[6] = { 0 };
	int valread = read(new_socket, buffer, sizeof(int16_t)*6);
	for(int i = 0; i<6; i++) {
		locs[i] = (int)buffer[i];
	}
}

// 	bool end_connection = false;
// 	while(!end_connection) {
// 		int16_t buffer[5] = { 0 };
// 		int16_t* cdata = new int16_t(5);
// 		for(int16_t i = 0; i<5; i++) {
// 			cdata[i] = i;
// 		}
// 		send(sock, cdata, sizeof(int16_t)*5, 0);
// 		// printf("Hello message sent\n");
// 		valread = read(sock, buffer, sizeof(int16_t)*5);
// 		// printf("%s\n", buffer);
// 		std::cout<<buffer[0]<<" "<<buffer[1]<<" "<<buffer[2]<<" "<<buffer[3]<<" "<<buffer[4]<<std::endl;
		
// 		end_connection = true;
// 	}
// 	return 0;
// }
