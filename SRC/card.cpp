#include "../headers/card.h"
#include "../headers/list.h"
#include "../headers/user.h"
#include <sstream>


Card::Card (string n, int n_c) {
	name = n;
	number_of_card = n_c;
	date.set_date(1,1,1);
	description = "!@#$^&*()Z";

}

void Card::rename(string new_name) {
	name = new_name;
}

string Card::get_name() {
	return name;
}

string Card::get_description() {
	return description;
}

int Card::get_num_of_card() {
	return number_of_card;
}

void Card::set_name(string n) {
	name = n;
}

void Card::set_num_of_card(int n) {
	number_of_card = n;
}

void Card::set_label(int n) {
	label = n;
}

void Card::set_which_list(List* x) {
	l = x;
}

void Card::set_description(string s) {
	description = s;
}

List* Card::get_list() {
	return l;
}

Date Card::get_date() {
	return date;
}

void Card::assign_user(User* u) {
	for (int i=0; i<who_to_do_it.size(); ++i) {
		if (who_to_do_it[i]->get_username() == u->get_username()) 
			return;
	}
	who_to_do_it.push_back(u);
	u->add_to_assign_in(this);

}


void Card::remove_user(User* u) {
	for (int i=0; i<who_to_do_it.size(); ++i) {
		if (who_to_do_it[i]->get_username() == u->get_username()) {
			who_to_do_it.erase(who_to_do_it.begin()+i); 
			u->remove_card_from_assign_in(this); break;
		}
	}

}

void Card::set_card_date(string d) {
	date.str_to_date(d);
}


void Card::add_comment(Comment cm) {
	comments.push_back(cm);
}

void Card::show_card(stringstream& out) {
	Date d(1,1,1);
	out << "Card name: " << name << endl
	     << "Card number: " << number_of_card << endl
	     << "Card List: " << get_list()->get_name() << endl;
	     if (!date.equals(d)){
	     	out << "Card Date: "; 
	     	date.print_date();
	     	out << endl;
	     } 
	     if (who_to_do_it.size() != 0) {
	     	out << "assigned users:\n" ;
	     	for (int i = 0; i < who_to_do_it.size(); ++i) {
	     		out << "  #" << i+1 << ": " << who_to_do_it[i]->get_username() << endl;
	     	}
	     }
	     
	     if (description.find("!@#$^&*()Z") > 100) {
	     	out << "Card Description:\n  " << description << endl;
	     }
	     if (comments.size() != 0) {
	     	out << "Comments:\n";
	     	for (int i = 0; i < comments.size(); ++i) {
	     		out <<"  " << comments[i].name << ": " << comments[i].comment << endl;
	     	}
	     }

	     //descriptions & comments
}

vector<Comment>& Card::get_comments() {
	return comments; 
}

vector<User*>& Card::get_who_to_do() {
	return who_to_do_it; 
}
