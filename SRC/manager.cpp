#include "../headers/manager.h"
#include "../headers/board.h"
#include "../headers/ID_Generator.h"

void Manager::create_board(string board_name) {
	Board* tmp = new Board(board_name, id_generator_Board->get_next_id(), this);
	curr_board = tmp;
	manager.push_back(tmp);
}

void Manager::remove_board(int board_number) {
	for (int i=0; i<manager.size(); ++i) {
		if (board_number == manager[i]->get_num_of_board()) {
			manager.erase(manager.begin()+i); break;
		}
	}
    return;
}

void Manager::remove_user_from_board(string user_name, stringstream& out) {
	User* u = find_user_in_global(user_name);
	if ( u == NULL ) {
		out << "ERROR:There is nobody with this ID" << endl;
		return;
	}
	u->get_name();//remove_assign_in();
	u->remove_from_member_in(curr_board);
	curr_board->remove_u(user_name);
}

User* Manager::find_user_in_global(string username) {
	for (int i=0; i<system_user.size(); ++i) {
		if (username == system_user[i]->get_username())
			return system_user[i];
	}
	return NULL;	
}

void Manager::add_user(string user_name, stringstream& out) {
	User* u = find_user_in_global(user_name);
	if ( u == NULL ) {
		out << "ERROR:There is nobody with this ID" << endl;
		throw Bad_Exception();
	}

	else {
		u->add_to_member_in(curr_board);
		curr_board->set_member(u);
	}

}