#ifndef MaNaGeR_h__
#define MaNaGeR_h__

#include "user.h"

extern vector <User*> system_user;

class Manager : public User {
public:
	Manager () : User() {}
	Manager (string n, string u_n, string pass) : User (n, u_n, pass) {}

	User* find_user_in_global(string username);
	void create_board(string board_name);
	void remove_board(int board_number);
	void add_user(string username, stringstream& out);
	void remove_user_from_board(string username, stringstream& out);

	class Bad_Exception {};

};

#endif