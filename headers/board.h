#ifndef BoArD_h__
#define BoArD_h__

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class List;
class Card;
class User;
class Manager;
class Comment;

class Board {
public:
	Board();
	Board(string n, int n_b, Manager* m); 
	void rename(string new_name);
	Card* find_c(int card_no);
	List* find_l(int list_no);
	User* find_u(string username);

	string get_name() ;
	int get_num_of_board();
	int get_has_been_removed();
	Manager* get_MNGR();
	vector <List*>& get_lists();
	vector <User*>& get_members();
	vector <Card*>& get_board_cards();

	void set_num_of_board(int n_b);
	void set_member(User* u);
	void set_list(List* l);
	void set_has_been_removed(int i);

	void show_cards(int list_no, stringstream& out);
	void show_lists(stringstream& out);
	void rename_list(int list_no, string new_name);
	void rename_card(int card_no, string new_name,stringstream& out);
	void add_list(string list_name);
	void remove_list(int list_no);
	void remove_card(int card_no);
	void remove_u (string user_name);
	void remove_users();
	void move_card(int card_no, int des_list_no);
	void edit_card_description(int card_no, string new_description, stringstream& out);
	void edit_card_due_date(int card_no, string d, stringstream& out);
	void comment(int card_no, Comment cm, stringstream& out);

private:
	string name;
	int number_of_board, has_been_removed;
	vector <List*> lists;
	Manager* MNGR;
	vector <User*> members;
	vector <Card*> board_cards;


};

#endif