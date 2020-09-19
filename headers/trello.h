#ifndef _TrElLo_H__
#define _TrElLo_H__


#include <sstream>
#include <fstream>
#include "manager.h"
#include "board.h"
#include "list.h"
#include "card.h"
#include "comment.h"
#include <string.h>

const int Nobody = 0;

extern ID* id_generator_Board;
extern ID* id_generator_List;
extern ID* id_generator_Card;

class Trello {
public:
	Trello();
	string Run(string input);
	Manager* get_curr_mangr();
	Board* get_curr_board();

	User* find_user_in_main(string username);
	Board* find_board_in_main(int board_number);
	List* find_list_in_main(int list_number);
	Card* find_card_in_main(int card_number);
	void input();
	void output();
	void signup (Manager*& curr_mngr,stringstream& in, stringstream& out);
	void signin (Manager*& curr_mngr,stringstream& in, stringstream& out); 
	void filter_input (vector <string>& f, stringstream& in);

	void input_conversion(string input);


private:
	class Bad_Exception {};
	int counter;
	int anyone_sign;
	string command;
	Manager* curr_mngr;
	Board* curr_board;

};


#endif