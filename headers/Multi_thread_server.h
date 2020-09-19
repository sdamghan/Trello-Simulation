#ifndef M_t_SeRvEr_H__
#define M_t_SeRvEr_H__

#include <Poco/Thread.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "trello.h"

using namespace Poco;

#define buffer_size (10000)

class Server_run : public Runnable {
public:
	Server_run(int n_fd) : new_fd(n_fd) {}
	virtual void run();

private:
	int new_fd;

};





#endif