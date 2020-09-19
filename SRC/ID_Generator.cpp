#include "../headers/ID_Generator.h"

ID::ID() {
	id = 0;
}

int ID::get_id() {
	return id;
}

int ID::get_next_id() {
	return ++id;
}

void ID::set_id(int x) {
	id = x;
}