#include "../headers/user.h"
#include "../headers/board.h"
#include "../headers/card.h"
#include "../headers/list.h"


User::User(string n, string u_n, string pass) {
	name = n;
	username = u_n;
	password = pass;
	curr_board = NULL;
	proxy = Unfilter;
}

Board* User::find_b(int board_no) {
	for (int i=0; i<member_in.size(); ++i) {
		if (board_no == member_in[i]->get_num_of_board())
			return member_in[i];
	}

	for (int i=0; i<manager.size(); ++i) {
		if (board_no == manager[i]->get_num_of_board())
			return manager[i];
	}

	return NULL;
}

Board* User::find_m_b(int board_no) {
	for (int i=0; i<manager.size(); ++i) {
		if (board_no == manager[i]->get_num_of_board())
			return manager[i];
	}

	return NULL;
}

List* User::find_l(int list_no) {
	for (int i=0; i<member_in.size(); ++i) {
		vector <List*> l = member_in[i]->get_lists();
		for (int j = 0; j < l.size(); ++j) {
			if (l[i]->get_num_of_list() == list_no)
				return l[i];
		}
	}

	for (int i=0; i<manager.size(); ++i) {
		vector <List*> l = manager[i]->get_lists();
		for (int j = 0; j < l.size(); ++j) {
			if (l[i]->get_num_of_list() == list_no)
				return l[i];
		}
	}

	return NULL;
}

Card* User::find_c(int card_no) {
	for (int i=0; i<member_in.size(); ++i) {
		vector <List*> l = member_in[i]->get_lists();
		for (int j = 0; j < l.size(); ++j) {
			vector <Card*> c = l[j]->get_cards();
			for (int k = 0; k < c.size(); ++k) {
				if (c[i]->get_num_of_card() == card_no)
					return c[i];
			}
		}
	}

	for (int i=0; i<manager.size(); ++i) {
		vector <List*> l = manager[i]->get_lists();
		for (int j = 0; j < l.size(); ++j) {
			vector <Card*> c = l[j]->get_cards();
			for (int k = 0; k < c.size(); ++k) {
				if (c[i]->get_num_of_card() == card_no)
					return c[i];
			}
		}
	}

	return NULL;
}

string User::get_password() {
	return password;
}

string User::get_username() {
	return username;
}

string User::get_name() {
	return name;
}

Board* User::get_curr_board() {
	return curr_board;
}

void User::set_curr_board(Board* b) {
	curr_board = b;
}

// int User::get_next_id() {
// 	return ++ID;
// }

void User::show_board(stringstream& out) {
	out << "Boards: " << endl;
	if (member_in.size() == 0 && manager.size() == 0){
		out << "there is no board!" << endl;
		return;
	}
	if (member_in.size() != 0){
		out << "  member_in:" << endl;
		for (int i=0; i<member_in.size(); ++i)
		out << "   -" << member_in[i]->get_name() << ", No." << member_in[i]->get_num_of_board() << endl;
	}

	if (manager.size() != 0){
		out << "  manager:" << endl;
	for (int i=0; i<manager.size(); ++i)
		out << "   -" << manager[i]->get_name() << ", No." << manager[i]->get_num_of_board() << endl;
	}
}

void User::enter_board(int board_no) {
	curr_board = find_b(board_no);
}

void User::set_password(string p) {
	password = p;
}

void User::add_to_member_in(Board* b){
	for (int i = 0; i < member_in.size(); ++i) {
		if (b->get_name() == member_in[i]->get_name() && b->get_num_of_board() == member_in[i]->get_num_of_board())
			return;
	}
	member_in.push_back(b);
}

bool User::member_in_board(Board* b) {
	for (int i = 0; i < member_in.size(); ++i) {
		if (b->get_name() == member_in[i]->get_name() && b->get_num_of_board() == member_in[i]->get_num_of_board())
			return true;
	}
	return false;
}

void User::remove_from_member_in(Board* b){
	for (int i = 0; i < member_in.size(); ++i) {
		if (b->get_name() == member_in[i]->get_name() && b->get_num_of_board() == member_in[i]->get_num_of_board()) {
			member_in.erase (member_in.begin()+i);
			return;
		}
	}
	return;
}

void User::add_to_assign_in(Card* c) {
	assign_in.push_back(c);
}

void User::remove_assign_in() {
	for (int i = 0; i < assign_in.size(); ++i) {
		assign_in[i]->remove_user(this);
	}
	for (int i = 0; i < assign_in.size(); ++i) {
		assign_in.erase(assign_in.begin()+i);
	}

}

void User::remove_card_from_assign_in(Card* c) {
	for (int i = 0; i < assign_in.size(); ++i) {
		if (c->get_num_of_card() == assign_in[i]->get_num_of_card()){
			assign_in[i]->remove_user(this); break;
		}
	}
	for (int i = 0; i < assign_in.size(); ++i) {
		if (c->get_num_of_card() == assign_in[i]->get_num_of_card()){
			assign_in.erase(assign_in.begin()+i); break;
		}
	}
}

void User::filtering(int state) {
	proxy = state;
}

int User::get_proxy() {
	return proxy;
}

vector <Board*>& User::get_member_in() {
	return member_in;
}

vector <Board*>& User::get_manager() {
	return manager;
}

vector <Card*>& User::get_assign_in() {
	return assign_in;
}