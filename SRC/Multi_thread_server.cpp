#include "../headers/Multi_thread_server.h"


void Server_run::run() {

	Trello my_trello;
	Mutex m;

	char buffer[buffer_size];
	string result;

	m.lock();
	int interface_read = read(new_fd, buffer, buffer_size-1);
	if (interface_read == -1){
		cout << "Reading Error!\n";
		m.unlock();
		return;
	}

	strcpy(buffer,my_trello.Run((string) buffer).c_str());

	int interface_write = write(new_fd, buffer, strlen(buffer));
	if (interface_write == -1){
		cout << "Writing Error!\n";
		m.unlock();
		return;
	}

	m.unlock();

	while(true) {

		m.lock();
		
		bzero(buffer, sizeof(buffer));
		int Server_READ = read(new_fd, buffer, buffer_size-1);
		if (Server_READ == -1){
			cout << "Reading Error!\n";
			m.unlock();
			break;
		}

		m.unlock();


		m.lock();

		result = my_trello.Run((string) buffer);
		result += "\0";
		bzero(buffer, sizeof(buffer));
		strcpy(buffer,result.c_str());

		if (result.find("exit") != string::npos) { m.unlock(); break; }

		m.unlock();		


		m.lock();

		int Server_WRITE = write(new_fd, buffer, strlen(buffer));
		if (Server_WRITE == -1){
			cout << "Writing Error!\n";
			m.unlock();
			break;
		}

		if (Server_READ == 0){
			m.unlock();
			break;
		}
		if (result.find("disconnect") != string::npos) { m.unlock(); break; }

		m.unlock();
	}

	close (new_fd);
}