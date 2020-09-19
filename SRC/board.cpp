#include "../headers/manager.h"
#include "../headers/board.h"
#include "../headers/list.h"
#include "../headers/card.h"
#include "../headers/comment.h"

Board::Board() {
	List x = List("ToDo", 1);
	lists.push_back(&x); 
	x = List("Doing", 2);
	lists.push_back(&x); 
	x = List("Done", 3);
	lists.push_back(&x);
}

Board::Board(string n, int n_b, Manager* m) {
	name = n;
	number_of_board = n_b;
	MNGR = m;
	members.push_back(m);
	has_been_removed = 0;
}

void Board::set_num_of_board(int n_b) {
	number_of_board = n_b;
}

void Board::rename(string new_name) {
	name = new_name;
}

string Board::get_name() {
	return name;
}

void Board::set_member(User* u) {
	members.push_back(u);
}

void Board::set_list(List* l) {
	lists.push_back(l);
}

int Board::get_num_of_board() {
	return number_of_board;
}

vector <List*>& Board::get_lists() {
	return lists;

}

vector <User*>& Board::get_members() {
	return members;	
}

vector <Card*>& Board::get_board_cards() {
	return board_cards;
}


List* Board::find_l(int list_no){ 
	for (int i=0; i<lists.size(); ++i)
		if ( list_no == lists[i]->get_num_of_list() )
			return lists[i];
	return NULL;	
}

Card* Board::find_c(int card_no) {
	for (int i=0; i<board_cards.size(); ++i) 
		if (card_no == board_cards[i]->get_num_of_card())
			return board_cards[i];
		return	NULL;
}

User* Board::find_u(string user_name) {
	for (int i=0; i<members.size(); ++i) {
		if (user_name == members[i]->get_username()){
			return members[i];
		}
	}

	if (MNGR->get_username() == user_name)
		return MNGR;
	return NULL;
}


void Board::remove_u(string user_name) {
	for (int i=0; i<members.size(); ++i)
		if (user_name == members[i]->get_username())
			members.erase(members.begin()+i);
}


void Board::rename_list(int list_no, string new_name){
	find_l(list_no)->rename(new_name);

}


void Board::add_list(string list_name) {
	List* l = new List(list_name, id_generator_List->get_next_id());
	l->set_which_board(this);
	lists.push_back(l);
}


void Board::remove_list (int list_no) {
	for (int i=0; i<lists.size(); ++i) {
		if ( list_no == lists[i]->get_num_of_list() ){
			lists.erase(lists.begin()+i); break; 
		}
	}

	for (int i=0; i<lists.size(); ++i)	
		lists[i]->set_num_of_list(i+1);

}


void Board::move_card(int card_no, int des_list_no) {
	find_c(card_no)->get_list()->remove_card(card_no);
	find_c(card_no)->set_which_list(find_l(des_list_no));
	find_l(des_list_no)->add_card(find_c(card_no)->get_name());

}

void Board::remove_card(int card_no) {
	for (int i=0; i<board_cards.size(); ++i) {
		if (card_no == board_cards[i]->get_num_of_card()) {
			board_cards.erase(board_cards.begin()+i); break;
		}
	}
}

void Board::rename_card (int card_no, string new_name, stringstream& out) {
	Card* c = find_c(card_no);
	if (c == NULL){
		out << ">>Not found card with this number!<<" << endl;
		return;
	}
	c->rename(new_name);
}


void Board::edit_card_description(int card_no, string new_description, stringstream& out) {
	Card* c = find_c(card_no);
	if (c == NULL){
		out << ">>Not found card with this number!<<" << endl;
		return;
	}
	c->set_description(new_description);

}


void Board::edit_card_due_date(int card_no, string d, stringstream& out) {
	Card* c = find_c(card_no);
	if (c == NULL){
		out << ">>Not found card with this number!<<" << endl;
		return;
	}
	c->set_card_date(d);

}

void Board::show_cards(int list_no, stringstream& out) {
	List* tmp = find_l(list_no); 
	if (tmp == NULL){
		out << ">>Not found list with this number!<<" << endl;
		return;
	}
	vector <Card*> temp = tmp->get_cards();
	out << "Cards:" << endl;
	if (temp.size() == 0){
		out << "there is no card!" << endl;
		return;
	}
	for (int i=0; i<temp.size(); ++i) {
		temp[i]->show_card(out);
		out << endl;
	}
}

void Board::show_lists(stringstream& out) {
	out << "Lists:" << endl;
	if (lists.size() == 0){
		out << "there is no list!" << endl;
		return;
	}
	for (int i=0; i<lists.size(); ++i) {
		out << "  " << lists[i]->get_name() << ", No."
		     << lists[i]->get_num_of_list() << endl;
	}

}


void Board::comment(int card_no, Comment cm, stringstream& out) {
	Card* c = find_c(card_no);
	if (c == NULL){
		out << ">>Not found card with this number!<<" << endl;
		return;
	}
	c->add_comment(cm);

}


Manager* Board::get_MNGR() {
	return MNGR;
}

void Board::remove_users() {
	cerr << members.size() << endl;
	for (int i = 0; i < members.size(); ++i) {
		//vector<Board*> member_in = members[i]->get_member_in(); 
		cerr << "user name: " << members[i]->get_name() << endl;
		for (int j = 0; j < members[i]->get_member_in().size(); ++j) {
			if (members[i]->get_member_in()[j]->get_num_of_board() == this->get_num_of_board()){
				members[i]->get_member_in().erase(members[i]->get_member_in().begin()+j);cerr << "board name: " << members[i]->get_member_in()[j]->get_name() << endl << endl;}
		}
	}
	members.clear();
}

void Board::set_has_been_removed(int i) {
	has_been_removed = i;

}

int Board::get_has_been_removed() {
	return has_been_removed;
}