// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int connect_server();

void server_send_data(int new_socket, int* locs);

void server_recv_data(int new_socket, int* locs);

