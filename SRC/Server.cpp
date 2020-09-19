#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <Poco/Thread.h>
#include "../headers/Multi_thread_server.h"

using namespace std;

vector <User*> system_user;

ID* id_generator_Board = new ID();
ID* id_generator_List = new ID();
ID* id_generator_Card = new ID();


#define MY_PORT 8888
#define buffer_size (10000)

const int NUM_OF_CONNECTIONS = 10;


int main() {

	struct sockaddr_in serv_addr;

	int Server_fd;
	Server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (Server_fd == -1){
		cout << "Socket Error." << endl;
		return 0;
	}		

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(MY_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int Server_BIND = bind(Server_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	if (Server_BIND == -1){
		cout << "Bind Error." << endl;
		return 0;
	}

	int Server_LISTEN = listen(Server_fd, NUM_OF_CONNECTIONS);
	if (Server_LISTEN == -1){
		cout << "Listening Error!\n";
		return 0;
	}


	struct sockaddr_in client_addr;
	unsigned int client_number = sizeof(client_addr);

	vector <Thread*> threads;
	int counter=0;

	while(true) {
		int new_fd = accept (Server_fd, (struct sockaddr*) &client_addr, &client_number);
		if (new_fd < 0) {
			cout << "Accept Error!" << endl;
			break;
		}

		Server_run* new_program = new Server_run (new_fd);
		threads.push_back( new Thread() );
		threads[counter]->start(*new_program);

		counter++;
	}

	for (int j = 0; j < threads.size(); ++j) {
		threads[j]->join();
	}

	close (Server_fd);

	return 0;
}
