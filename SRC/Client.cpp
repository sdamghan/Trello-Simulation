#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define MY_PORT 8888
#define buffer_size (20000)


int main() {

	string co="",IP="",tem="";
	int port=0;

	while (cin >> co) {
		
		if (co.find("connect") != string::npos) {
			cin >> IP >> port;

			if (port == MY_PORT){
				
				int Server_fd;
				Server_fd = socket(AF_INET, SOCK_STREAM, 0);
				if (Server_fd == -1){
					cout << "Socket Error!\n";
					return 0;
				}		
				struct sockaddr_in serv_addr;
			
				serv_addr.sin_family = AF_INET;
				serv_addr.sin_port = htons(MY_PORT);
				inet_aton(IP.c_str(), &(serv_addr.sin_addr));
			
				char buffer[buffer_size];
				int c=0;
			
				int Client_CONNECTION = connect(Server_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
				if (Client_CONNECTION == -1){
					cout << "Connection Error!\n";
					return 0;
				}




				buffer[0] = 'c';
				write(Server_fd, buffer, strlen(buffer));
				read(Server_fd, buffer, buffer_size-1);
				cout << buffer;


				while(true){
					bzero(buffer, sizeof(buffer));
					fgets(buffer,buffer_size-1,stdin);
					tem = (string) buffer;

					if (tem.find("exit") != string::npos) {
						c=-2;
						break;
					}
					
					if (tem.size() == 1 || tem.size() == 0) continue; 

					if (tem.find("disconnect") != string::npos){
						write(Server_fd, "disconnect", 10);
						read (Server_fd, buffer, buffer_size-1);
						c=-1;
						break;
					}

					int Client_WRITE = write(Server_fd, buffer, strlen(buffer));
			
					if (Client_WRITE == -1){
						cout << "Writing Error!\n";
						break;
					}
					bzero(buffer, sizeof(buffer));
					int Client_READ = read (Server_fd, buffer, buffer_size-1);
					if (Client_READ == -1){
						cout << "Reading Error!\n";
						break;
					}
					if (Client_READ == 0) {
			 			break;
					}
					
					cout << endl << buffer;
			
				}

				if (c==-1){
					cout << buffer << endl;
					bzero(buffer, sizeof(buffer));
					close(Server_fd);
					continue;
				}

				if (c==-2) {
					close(Server_fd);
					bzero(buffer, sizeof(buffer));
					return 0;
				}
			}


			else {
				cout << "Invalid Port\nYour Port must be " << MY_PORT << ", try again!" << endl;
				continue;
			}
		}

		else if (co.find("exit") != string::npos) break;

		else {
			string t;
			getline(cin, t);
			cout << "Invalid Command, Please Connect to Server!" << endl;
			continue;
		}

	}

	return 0;
}
