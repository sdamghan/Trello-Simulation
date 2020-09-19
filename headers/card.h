#ifndef CaRd_H__
#define CaRd_H__

#include <sstream>
#include <vector>
#include <string>
#include "comment.h"
#include "date.h"
using namespace std;

const int none = 0;
const int green = 1;
const int yellow = 2;
const int orange = 3;
const int red = 4;
const int violet = 5;
const int blue = 6;


class List;
class User;

class Card{
public:
	Card (string n, int n_c); 
	Card ();
	void rename(string new_name) ;
 
 	string get_name();
 	string get_description();
	int get_num_of_card();
	Date get_date();
	List* get_list();
	vector<Comment>& get_comments();
	vector<User*>& get_who_to_do();

	void set_name(string n);
	void set_num_of_card(int n);
	void set_label(int n);
	void set_which_list(List* x);
	void set_description(string s);
	void set_card_date(string d); 
	void add_comment(Comment cm);

	void show_card(stringstream& out);
	void assign_user(User* u);
	void remove_user(User* u); 



private:
	string name;
	string description;
	int number_of_card;
	int label;
	Date date;
	
	List* l;
	vector <Comment> comments;
	vector <User*> who_to_do_it;

};

#endif