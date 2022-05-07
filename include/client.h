#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int connect_client(char* ip_add);

void client_send_data(int new_socket, int* locs);

void client_recv_data(int new_socket, int* locs);
