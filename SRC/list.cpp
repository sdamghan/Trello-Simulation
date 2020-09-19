#include "../headers/list.h"
#include "../headers/card.h"
#include "../headers/board.h"
#include "../headers/comment.h"
#include "../headers/card.h"
#include "../headers/ID_Generator.h"


List::List(string n, int n_l) {
	name = n;
	number_of_list = n_l;

} 

void List::rename (string new_name) {
	name = new_name;
}

void List::set_num_of_list(int n) {
	number_of_list = n; 
}

int List::get_num_of_list() {
	return number_of_list;
}

Board* List::get_board() {
	return b;
}

void List::set_which_board(Board* x) {
	b = x;
}


Card* List::find_c(int card_no){ 
	for (int i=0; i<cards.size(); ++i)
		if ( card_no == cards[i]->get_num_of_card() )
			return cards[i];
	return NULL;	
}



void List::add_card(string card_name) {
	Card* c = new Card(card_name, id_generator_Card->get_next_id());
	c->set_which_list (this);
	cards.push_back(c);
	b->get_board_cards().push_back(c);
}


void List::remove_card (int card_no) {
	for (int i=0; i<cards.size(); ++i) {
		if (card_no == cards[i]->get_num_of_card()) {
			cards.erase(cards.begin()+i); break; 
		}
	}

}

void List::move(Card* c) {
	cards.push_back(c);
}


string List::get_name() {
	return name;
}

vector <Card*>& List::get_cards() {
	return cards;
}