#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <memory.h>
using namespace std;

#define SERVER_FIFO_NAME "../res/s_fifo"
#define CLIENT_FIFO_NAME "../res/c_%d_fifo"

#define BUFFER_SIZE 70

typedef struct DATA{
	pid_t client_pid;
	char data[BUFFER_SIZE-1];
	char menu[2][4][50];
	int changenum;
	int couponnum;
	bool address[4];
	bool result;
}data_t;

#endif