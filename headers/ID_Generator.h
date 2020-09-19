#ifndef Id_GeNaRaToR_h__
#define Id_GeNaRaToR_h__

#include <cstdlib>
using namespace std;

class ID {
public:
	ID();

	int get_next_id();
	int get_id();

	void set_id(int x);

private:
	int id;

};



#endif