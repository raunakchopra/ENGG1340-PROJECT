#ifndef STRUCTURE_H
#define STRUCTURE_H
#include<vector>
#include<string>
using namespace std;

struct card{ //structure to store the cards
	int suit; //keeps track of the suit of the card
	int face; //keeps track of the value of the card
	bool face_up; //keeps track of whether the card is face up or face down
};

struct profile{ //structure to store the profile of each player
	string name; //name of the user
	string User; //username of the user
	int chip; //the amount the user has
	string password; //the password of the user
};

struct person{ //structure to store the Information for each player for the game 
	int bet; //the bet made by the person
	vector<card> cards; //the cards that the person has
	profile info; //the profile of the player 
};

#endif



