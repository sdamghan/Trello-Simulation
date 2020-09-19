#include "../headers/trello.h"

Trello::Trello() {
	counter = 0;
	anyone_sign = Nobody;
	command = "";
	curr_mngr = NULL;
	curr_board = NULL;
}

User* Trello::find_user_in_main(string username) {
	for (int i=0; i<system_user.size(); ++i) {
		if (username == system_user[i]->get_username())
			return system_user[i];
	}
	return NULL;	
}

Board* Trello::find_board_in_main(int board_number){
	for (int i = 0; i < system_user.size(); ++i) {
		Board* b = system_user[i]->find_m_b(board_number);
		if (b != NULL)
			return b;
	}
}

List* Trello::find_list_in_main(int list_number){
	for (int i = 0; i < system_user.size(); ++i) {
		List* l = system_user[i]->find_l(list_number);
		if (l != NULL)
			return l;
	}
}

Card* Trello::find_card_in_main(int card_number){
	for (int i = 0; i < system_user.size(); ++i) {
		Card* c = system_user[i]->find_c(card_number);
		if (c != NULL)
			return c;
	}
}

void Trello::input(){
	ifstream _Read_Details;
	_Read_Details.open("repository.txt");

	int i_g_b=0,i_g_l=0,i_g_c=0;
	_Read_Details >> i_g_b >> i_g_l >> i_g_c;
	id_generator_Board->set_id(i_g_b); id_generator_List->set_id(i_g_l); id_generator_Card->set_id(i_g_c);

	int system_users_size=0;
	_Read_Details >> system_users_size;
	for (int i = 0; i < system_users_size; ++i) {
		string n="",u_n="",p="";
		_Read_Details >> n >> u_n >> p;
		if (find_user_in_main(u_n) == NULL)
			system_user.push_back (new Manager (n, u_n, p));
	}
		
	for (int i = 0; i < system_users_size; ++i) {

		int member_size=0,manager_size=0;
		_Read_Details >> member_size >> manager_size ;

		string b_name=""; int b_number=0,b_l_number=0;
		for (int j = 0; j < manager_size; ++j) {
			_Read_Details >> b_name >> b_number >> b_l_number;
			if (find_board_in_main(b_number) == NULL){
				Board* b = new Board(b_name, b_number, (Manager*)system_user[i]);
				system_user[i]->get_manager().push_back(b);

				string l_name=""; int l_number=0,l_c_number=0;
				for (int k = 0; k < b_l_number; ++k){
						_Read_Details >> l_name >> l_number >> l_c_number;
						if (find_list_in_main(l_number) == NULL) { 
							List* l = new List (l_name, l_number);
							l->set_which_board(b);
							b->get_lists().push_back(l);

							string c_name="",c_des="",c_date=""; int c_number=0;
							for (int u = 0; u < l_c_number; ++u){
								_Read_Details >> c_name >> c_number >> c_date;
								getline(_Read_Details, c_des);

								if (find_card_in_main(c_number) == NULL) {
									Card* c = new Card (c_name, c_number);
									c->set_which_list(l);
									c->set_description(c_des);
									c->set_card_date(c_date);
									l->get_cards().push_back(c);
									b->get_board_cards().push_back(c);
									int cms_number=0;
									_Read_Details >> cms_number;
									string cm_name="",cm_comment="";
									for (int h = 0; h < cms_number; ++h) {
										_Read_Details >> cm_name;
										getline(_Read_Details, cm_comment);
										c->get_comments().push_back(*new Comment(cm_name, cm_comment));
									}

									int users_number=0;
									_Read_Details >> users_number;
									string u_name="";
									for (int h = 0; h < users_number; ++h) {
										_Read_Details >> u_name;
										c->get_who_to_do().push_back(find_user_in_main(u_name));
										find_user_in_main(u_name)->add_to_assign_in(c);
									}
								}
							}
						}
					}	
				}
			}


	}

	int mem_in_size=0,board_number=0; string u_name="";
	for (int i = 0; i < system_users_size; ++i) {
		_Read_Details >> mem_in_size;
		for (int j = 0; j < mem_in_size; ++j){
			_Read_Details >> board_number >> u_name;
			Board* b = find_board_in_main(board_number);
			User* u = find_user_in_main(u_name);
			bool bo = false, us = false;

			if (b != NULL && u != NULL){ 
				vector <Board*> member_in = u->get_member_in();
				vector <User*> users_of_board = b->get_members();

				for (int k = 0; k < member_in.size(); ++k) {
					if (member_in[k]->get_num_of_board() == board_number)
						bo = true;
				}

				for (int k = 0; k < users_of_board.size(); ++k) {
					if (users_of_board[k]->get_username() == u_name)
						us = true;
				}

				if (us == false && bo == false) {
					u->add_to_member_in(b);
					b->set_member(u);
				}
			}
		}
	}_Read_Details.close();
}

void Trello::output() {
	ofstream _Save_Details;
	_Save_Details.open("repository.txt");

	_Save_Details << id_generator_Board->get_id() << "\t" << id_generator_List->get_id() << "\t" << id_generator_Card->get_id() << endl;

	_Save_Details << system_user.size() << endl;
	for (int i = 0; i < system_user.size(); ++i) {
		_Save_Details << system_user[i]->get_name() << " " 
					  << system_user[i]->get_username() << " " 
					  << system_user[i]->get_password() << endl;
	}
	_Save_Details << endl;

	for (int i = 0; i < system_user.size(); ++i) {

		vector<Board*> me=system_user[i]->get_member_in(),ma=system_user[i]->get_manager();
		_Save_Details << me.size() << " " << ma.size() << endl;

		//show boards 
		for (int j = 0; j < ma.size(); ++j) {
			vector <List*> ma_l = ma[j]->get_lists();
			_Save_Details << ma[j]->get_name() << " " << ma[j]->get_num_of_board() << endl << ma_l.size() << "\t";
			
			//show lists of board
			for (int k = 0; k < ma_l.size(); ++k) { 
				vector<Card*> ma_l_c = ma_l[k]->get_cards();
				_Save_Details << ma_l[k]->get_name() << " " << ma_l[k]->get_num_of_list() << endl << ma_l_c.size() << "\t\t";
				
				//show cards of list 
				for (int u = 0; u < ma_l_c.size(); ++u)	{
					_Save_Details << ma_l_c[u]->get_name() << " " << ma_l_c[u]->get_num_of_card() << " " 
								  <<  ma_l_c[u]->get_date().show_date() << " " << ma_l_c[u]->get_description() << endl;

					vector<Comment> cms = ma_l_c[u]->get_comments();
					_Save_Details << cms.size() << "\t";
					for (int l = 0; l < cms.size(); ++l) {
						_Save_Details << cms[l].name << " " << cms[l].comment << "\n";
					}
					_Save_Details << endl;

					vector<User*> users = ma_l_c[u]->get_who_to_do();
					_Save_Details << users.size() << "\t";
					for (int l = 0; l < users.size(); ++l) {
						_Save_Details << users[l]->get_username() << "\t";
					}
					_Save_Details << endl;

					_Save_Details << endl << " \t\t";
				}
			}
		} 

		_Save_Details << endl;
	}

	_Save_Details << endl;

	for (int i = 0; i < system_user.size(); ++i) {
		vector<Board*> mem_in = system_user[i]->get_member_in();
	
		_Save_Details << mem_in.size() << "\t";
		for (int j = 0; j < mem_in.size(); ++j) {
			_Save_Details << mem_in[j]->get_num_of_board() << " " << system_user[i]->get_name() << "\t";
		}

		_Save_Details << endl;
	}
	
	_Save_Details << endl;

	_Save_Details.close();
} 

void Trello::signup (Manager*& curr_mngr,stringstream& in, stringstream& out) {
	string name="",username="",password="",temp="";
	getline (in, temp);
	stringstream ss;
	ss << temp;
	temp = "";
	vector <string> v;
	while (ss >> temp){
		v.push_back(temp);
	}
	username = v[v.size()-2];
	password = v[v.size()-1];

	for (int i = 0; i < v.size()-2; ++i) {
		name += v[i];
		name += " ";
	} 
	if (find_user_in_main(username) != NULL){
		out << "\n>>Invalid Username,Try again!<<" << endl;
		throw Bad_Exception ();
	}

	curr_mngr = new Manager (name, username, password); 
	system_user.push_back(curr_mngr);
}

void Trello::signin (Manager*& curr_mngr,stringstream& in, stringstream& out) {
	string username="",password="";
	in >> username; getline(in, password);
	for (int i=0; i<system_user.size(); ++i) {
		if (username == system_user[i]->get_username() && password == system_user[i]->get_password()){
			curr_mngr = (Manager*) system_user[i]; return;
		}

		else if (username == system_user[i]->get_username() && password != system_user[i]->get_password()){
			out << "Wrong Password!" << endl;
			throw Bad_Exception();
		}

	}

	out << "Sorry! You don't have a account!\ntry signup" << endl;
	curr_mngr = NULL;
	throw Bad_Exception();
}

void Trello::filter_input (vector <string>& f, stringstream& in){
	stringstream ss;
	string temp;
	string line;
	getline (in, line);
	ss<<line;
	while(ss>>temp){
		f.push_back(temp);
	}

}


string Trello::Run(string INPUT){

	stringstream in,out;
	in << INPUT;

	while (command != "exit") {

		input();
		if (counter == 0) {
			    out << "Welcome" << endl;
				// greating
				out << "-signin Username Password" << endl;
				out << "-Don't have an account? join us.." << endl;
				out << "-signup Realname Username Password" << endl;
				out << "Trello@";
				if (curr_mngr != NULL)
					out << curr_mngr->get_name()<< ":$ ";
				else
					out << "Nobody:$ ";

				counter++;
				string outstr (out.str()); 
				return outstr;
			}
		
		if (curr_mngr == NULL){
			in >> command;
			
			
 			if (command.find("disconnect") != string::npos) {
				counter =0;
				out << "You are Disconnected!" << endl;
				string outstr (out.str()); 
				return outstr;
			}

			//signup
			if (command.find("signup") != string::npos) {
				try {
					signup (curr_mngr, in, out);
				}catch (Bad_Exception signup) {break;}

				anyone_sign = 1;
				output();
				out << "Hi " << curr_mngr->get_name() << " !" << endl;
				continue;
 			}
			//sign in
			else if (command.find("signin") != string::npos) {
				try {
					signin(curr_mngr, in, out);
				}catch(Bad_Exception signin) {break;}

				anyone_sign = 1;
				if (curr_mngr != NULL) 
					out << "Hi " << curr_mngr->get_name() << " !" << endl;
				continue;

			}
			// wrong command
			else if (command != "exit") {
					out << "Wrong command!" << endl;
					string n="";
					getline(in, n);
					break;
				}
		}
		

	

		else {
			if (anyone_sign == 1) {
				out << "Choose a command:" << endl;
				out << "-signout" << endl;
				out << "-or write a command!" << endl;
				anyone_sign++;
				break;
			}



			in >> command;
			
			if (command.find("signout") != string::npos) {
				curr_mngr = NULL;
				curr_board = NULL;
				anyone_sign = Nobody;
				counter = 0;
				continue;
			}

			
			else if (command.find("show_boards") != string::npos) {
				curr_mngr->show_board(out);
				break;

			}

			else if (command.find("enter_board") != string::npos) {
				int board_number=0;
				in >> board_number;
				Board* b = find_board_in_main (board_number);
				try {
					if (b == NULL){
						out << ">>Not found Board with this ID!<<" << endl;
						throw Bad_Exception();
					}

				}catch (Bad_Exception enter_board) {break;}
				curr_mngr->set_curr_board(curr_mngr->find_b(board_number));
				curr_board = curr_mngr->get_curr_board();
				break;
			}


			else if (command.find("add_user") != string::npos) {
				string u_name="";
				try {
					if (curr_mngr->member_in_board(curr_board)) {
						in >> u_name;
						out << ">>You Don't have premission to do this!<<" << endl;
						throw Bad_Exception();
					}

					in >> u_name;

					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}
				}catch(Bad_Exception add_user) {break;}

				curr_mngr->add_user(u_name, out);
				output();
				out << "User " << u_name << " added to current board!" << endl;
				break;
			}

			else if (command.find("remove_user_from_board") != string::npos) {
				string u_name="";
				try {
					if (curr_mngr->member_in_board(curr_board)) {
						in >> u_name;
						out << ">>You Don't have premission to do this!<<" << endl;
						throw Bad_Exception();
					}

					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}
				}catch(Bad_Exception remove_user_from_board) {break;}

				in >> u_name;
				curr_mngr->remove_user_from_board(u_name, out);
				output();
				out << "User " << u_name << " removed to current board!" << endl;
				break;
			}

			else if (command.find("show_lists") != string::npos) {
				try {
					if(curr_board == NULL){
						out << ">>you must enter board at first!<<" << endl;
						throw Bad_Exception();
					}
				}catch (Bad_Exception show_lists) {break;}

				curr_board->show_lists(out);
				break;
			}

			else if (command.find("show_cards") != string::npos) {
				int l_number=0;
				in >> l_number;
				List* l = curr_board->find_l(l_number); 

				try {	
					if (curr_board == NULL){
						out << ">>You must enter board first!<<";
						throw Bad_Exception();
					}

					if (l == NULL){
						out << ">>Not found list with this number!<<" << endl;
						throw Bad_Exception();
					}
				}catch (Bad_Exception show_cards) {break;}

				curr_board->show_cards(l_number, out);
				break;
			}

			else if (command.find("show_card") != string::npos) {
				int c_number=0;
				in >> c_number;
				Card* c = curr_board->find_c(c_number);

				try {
					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}

					if (c == NULL) {
						out << ">>Not found card with this number!<<" << endl;
						throw Bad_Exception();
					}
				}catch (Bad_Exception show_card) {break;}

				c->show_card(out);
				break;
			}

			else if (command.find("create_board") != string::npos) {
				string b_name="";
				in >> b_name;
				curr_mngr->create_board(b_name);
				curr_board = curr_mngr->get_curr_board();
				output();
				out << "Board " << b_name << " Created!" << endl;
				break;
			}

			else if (command.find("remove_board") != string::npos) {
				int b_number=0;
				in >> b_number;
				Board* b = curr_mngr->find_b(b_number);

				try {
					if (b == NULL) {
						out << ">>Not found this board!<<" << endl;
						throw Bad_Exception();
					}

					if (curr_mngr->member_in_board(b)) {
				    	out << ">>You Don't have premission to do this!<<" << endl;
						throw Bad_Exception();
					}
				}catch (Bad_Exception remove_board) {break;}

				find_board_in_main(b_number)->set_has_been_removed(1);
				find_board_in_main(b_number)->remove_users();
				curr_mngr->remove_board(b_number);
				output();
				out << "Board with ID " << b_number << " removed!" << endl;
				break;
			}

			else if (command.find("add_list") != string::npos) {
				string l_name="";
				in >> l_name;

				try {
					if (curr_board == NULL){
						out << ">>You must enter to board at first!<<" << endl;
						throw Bad_Exception();
					}
				}catch (Bad_Exception add_list) {break;}
				
				curr_board->add_list(l_name);
				output();
				out << "List " << l_name << " Created!" << endl;
				break;
			}

			else if (command.find("remove_list") != string::npos) {
				int l_number=0;
				in >> l_number;
				List* l = curr_board->find_l(l_number);

				try {
					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}
 
					if (l == NULL){
						out << ">>Not found list with this number!<<" << endl;
						throw Bad_Exception();
					}
				}catch (Bad_Exception remove_list) {break;}

				curr_board->remove_list(l_number);
				output();
				out << "List with ID " << l_number << " removed!" << endl;
				break;
			}

			else if (command.find("add_card") != string::npos) {
				string c_name="";
				int l_number=0;
				in >> c_name >> l_number;
				List* l = curr_board->find_l(l_number); 

				
				try {
					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}

					if (l == NULL ){
						out << ">>Not found list with this number!<<" << endl;
						throw Bad_Exception();
					}

					l->add_card(c_name);
					output();
				}catch (Bad_Exception b) {break;}


				out << "Card " << c_name << " Created!" << endl;
				break;
			}

			else if (command.find("remove_card") != string::npos) {
				int c_number=0;
				in >> c_number;
				Card* c = curr_board->find_c(c_number);

				try {
					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}

					if (c == NULL) {
						out << ">>Not found card with this number!<<" << endl;
						throw Bad_Exception();
					}
				}catch (Bad_Exception remove_card) {break;}

				c->get_list()->remove_card(c_number);
				curr_board->remove_card(c_number);
				output();
				out << "Card with ID " << c_number << " removed!" << endl;
				break;
			}

			else if (command.find("move_card") != string::npos) {
				int c_number=0,l_number=0;
				in >> c_number >> l_number;
				Card* c = curr_board->find_c(c_number);
				List* l = curr_board->find_l(l_number); 

				try {
					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}

					if (c == NULL){
						out << ">>Not found card with this number!<<" << endl;
						throw Bad_Exception();
					}

					if (l == NULL){
						out << ">>Not found list with this number!<<" << endl;
						throw Bad_Exception();
					}
				}catch (Bad_Exception move_card) {break;}

				c->get_list()->remove_card(c_number);
				c->set_which_list(l);
				l->move(c);	
				output();	
				out << "Card with ID " << c_number << " moved to List with ID " << l_number << " !\n";
				break;
			}

			else if (command.find("rename_card") != string::npos) {
				int c_number=0;
				string new_name="";
				in >> c_number >> new_name;
				Card* c = curr_board->find_c(c_number);

				try {
					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}

					if (c == NULL){
						out << ">>Not found card with this number!<<" << endl;
						throw Bad_Exception();
					}
				}catch (Bad_Exception rename_card) {break;}

				curr_board->rename_card(c_number, new_name, out);
				output();
				out << "Card with ID " << c_number << " renamed!" << endl;
				break;
			}

			else if (command.find("edit_card_description") != string::npos) {
				int c_number=0;
				string new_des="";
				in >> c_number;
				getline(in, new_des);

				try {
					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}
				}catch (Bad_Exception edit_card_description) {break;}

				curr_board->edit_card_description(c_number, new_des, out);
				output();
				out << "Description of Card with ID " << c_number << " edited!" << endl;
				break;
			}

			else if (command.find("edit_card_due_date") != string::npos) {
				int c_number=0;
				string date="";
				in >> c_number >> date;

				try {
					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}
				}catch (Bad_Exception edit_card_due_date) {break;}

				curr_board->edit_card_due_date(c_number, date, out);
				output();
				out << "Due date of Card with ID " << c_number << " edited!" << endl;
				break;
			}

			else if (command.find("assign_user") != string::npos) {
				int c_number=0;
				string username;
				in >> c_number >> username;
				Card* c = curr_board->find_c(c_number); 
				User* u = curr_board->find_u(username);

				try {
					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}

					if (c == NULL ){
						out << ">>Not found card with this number!<<" << endl;
						throw Bad_Exception();
					}

					if (u == NULL) {
						out << ">>there is nobody with this username!<<" << endl;
						throw Bad_Exception();
					}
				}catch (Bad_Exception assign_user) {break;}
				c->assign_user(u);
				output();
				out << "User " << username << " assigned to Card with ID " << c_number << " !" << endl;
				break;
			}

			else if (command.find("remove_user") != string::npos) {
				int c_number=0;
				string username;
				in >> c_number >> username;
				Card* c = curr_board->find_c(c_number); 
				User* u = curr_board->find_u(username);

				try {
					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}

					if (c == NULL ){
						out << ">>Not found card with this number!<<" << endl;
						throw Bad_Exception();
					}

					if (u == NULL) {
						out << ">>there is nobody with this username!<<" << endl;
						throw Bad_Exception();
					}	
				}catch (Bad_Exception remove_user) {break;}

				c->remove_user(u);
				output();
				out << "User " << username << " removed from Card with ID " << c_number << " !" << endl;
				break;
			}

			else if (command.find("comment") != string::npos) {
				int c_number=0;
				string name;
				Comment cm(curr_mngr->get_name(), "");
				in >> c_number;

				try {
					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}
				}catch (Bad_Exception comment) {break;}
				getline(in, cm.comment);
				curr_board->comment(c_number, cm, out);
				output();
				out << "Comment Recieved!" << endl;
				break;

			}

			else if (command.find("filter") != string::npos) {
				vector <string> filtered;
				filter_input(filtered, in);

				try {
					if (curr_board == NULL){
						out << ">>You must enter board at first!<<";
						throw Bad_Exception();
					}
				}catch (Bad_Exception filter) {break;}

				vector <User*> m = curr_board->get_members();
				for (int i = 0; i < m.size(); ++i) {
					m[i]->filtering(Unfilter);
				}


				for (int i = 0; i < filtered.size(); ++i) {
					User* u = curr_board->find_u(filtered[i]);
					if(u != NULL)
						u->filtering(filter);
				}

				if (filtered.size() == 0) {
					for (int i = 0; i < m.size(); ++i) {
						m[i]->filtering(filter);
					}
					vector <List*> l = curr_board->get_lists();
					for (int i = 0; i < l.size(); ++i) {
						vector<Card*> c = l[i]->get_cards();
						for (int j=0; j<c.size(); ++i){
							c[j]->show_card(out);
						}
					}
					break;
				}

				for (int i = 0; i < m.size(); ++i)	{
					if (m[i]->get_proxy() == filter){
						vector <Card*> c = m[i]->get_assign_in();
						for (int j = 0; j < c.size(); ++j) {
							c[j]->show_card(out);
						}
					}
				}
				break;

			}

			if (command.find("disconnect") != string::npos) {
				counter =0;
				out << "You are Disconnected!" << endl;
				string outstr (out.str()); 
				return outstr;
			}

			// wrong command
			else if (command != "exit"){
				out << "Wrong command!" << endl;
				string n="";
				getline(in, n);
				break;
			}


		}
	}


	if (command.find("exit") != string::npos){ 
		out << "GoodBye!";

		if (curr_mngr != NULL && curr_board != NULL) {

			for (int j=0; j < curr_mngr->get_member_in().size(); ++j) {
				for (int i = 0; i < curr_mngr->get_member_in()[j]->get_board_cards().size(); ++i) {
					delete curr_mngr->get_member_in()[j]->get_board_cards()[i];
				}
			}


			for (int j=0; j < curr_mngr->get_manager().size(); ++j) {
				for (int i = 0; i < curr_mngr->get_manager()[j]->get_board_cards().size(); ++i) {
					delete curr_mngr->get_manager()[j]->get_board_cards()[i];
				}
			}


			for (int j=0; j < curr_mngr->get_manager().size(); ++j) {
				for (int i = 0; i < curr_mngr->get_manager()[j]->get_lists().size(); ++i) {
					delete curr_mngr->get_manager()[j]->get_lists()[i];
				}
			}

			for (int j=0; j < curr_mngr->get_member_in().size(); ++j) {
				for (int i = 0; i < curr_mngr->get_member_in()[j]->get_lists().size(); ++i) {
					delete curr_mngr->get_member_in()[j]->get_lists()[i];
				}
			}

			for (int j=0; j < curr_mngr->get_manager().size(); ++j) {
				delete curr_mngr->get_member_in()[j];
			}

			for (int j=0; j < curr_mngr->get_manager().size(); ++j) {
				delete curr_mngr->get_manager()[j];
			}

			for (int j=0; j < system_user.size(); ++j) {
				delete system_user[j];
			}
		}

	string outstr(out.str());
	return outstr;

	}


	if (curr_board != NULL){
		if (curr_board->get_has_been_removed() == 0)
			out << "\n\n-Current Board: " << curr_board->get_name() << endl;
	}

	out << "\nTrello@";
	if (curr_mngr != NULL)
		out << curr_mngr->get_name() << ":$ ";
	else
		out << "Nobody:$ ";

	
	


	
	string outstr(out.str());
	return outstr;
}
