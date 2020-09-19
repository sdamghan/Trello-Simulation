#ifndef User_H__
#define User_H__

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "ID_Generator.h"
using namespace std; 

const int Unfilter = 0;
const int filter = 1;

class Board;
class Card;
class List;
class Trello;

extern ID* id_generator_Board;
extern ID* id_generator_List;
extern ID* id_generator_Card;

extern stringstream in,out;

class User {
public:
	
	User() : curr_board(NULL){}
	User(string n) : curr_board(NULL){}
	User(string n, string u_n, string pass);
	void show_board(stringstream& out);
	void enter_board(int board_no);
	Board* find_b(int board_no);
	Board* find_m_b(int board_no);
	List* find_l(int list_no);
	Card* find_c(int card_no);

	int get_proxy();
	string get_password();
	string get_username();
	string get_name();
	Board* get_curr_board();
	vector<Board*>& get_member_in();
	vector<Board*>& get_manager();
	vector<Card*>& get_assign_in();

	void filtering(int state);
	void set_curr_board(Board* b);
	void set_password(string p);

	void add_to_assign_in(Card* c);
	void add_to_member_in (Board* b);
	void remove_from_member_in(Board* b);
	void remove_card_from_assign_in(Card* c);
	void remove_assign_in();
	bool member_in_board(Board* b);
  
protected:
	string name;
	string username;
	string password;
	vector <Board*> member_in;
	vector <Board*> manager;
	vector <Card*> assign_in;
	Board* curr_board;
	int board_number;
	int proxy;

};

#endif