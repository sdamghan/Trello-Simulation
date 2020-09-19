#ifndef LiSt_H__
#define LiSt_H__

#include <vector>
#include <string>
#include <sstream>
#include "ID_Generator.h"

using namespace std;

class Card;
class Board;
class Comment;

extern ID* id_generator_Board;
extern ID* id_generator_List;
extern ID* id_generator_Card;


extern stringstream in,out;

class List{
public:
	List(string n, int n_l);
	void rename (string new_name);
	Card* find_c(int card_no);

	int get_num_of_list();
	string get_name();
	Board* get_board();
	vector <Card*>& get_cards();

	void set_num_of_list(int n);
	void set_which_board(Board* x);
	void add_card(string card_name);
	void remove_card(int card_no);
	void move(Card* c);

private:
	string name;
	int number_of_list;
	vector <Card*> cards;
	Board* b;
};

#endif