#ifndef STRUCTURE_H
#define STRUCTURE_H
#include<vector>
#include<string>
using namespace std;

struct card{ 
	int suit;
	int face;  
	bool face_up;
};

struct profile{ 
	string name; 
	string User; 
	int chip;
	string password;
};

struct person{ 
	int bet;
	vector<card> cards;
	profile info;
};

#endif



