#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include "structure.h"
using namespace std;

#define SPADE "\xE2\x99\xA0"
#define CLUB "\xE2\x99\xA3"
#define HEART "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

int total_value(vector<card>);
bool Ace_present(vector<card>);
void bet(person&);
int payment(person, person&);
void output(vector<card>);
void game(vector<person> &players, int *arr);
card deal_card();


void save(person user){ //saves the user data in the assigned binary filer
	ofstream output;
	string filename = user.info.User + ".dat";
	output.open(filename, ios::out);
	output << user.info.User << endl << user.info.password << endl << user.info.name << endl  << endl << user.info.chip;
	output.close();
}

profile sign_up() // this function creates a new player to store user's data in a binary file 
{
	profile user;	

	fstream option;
	string filename;

	cout << "Please enter Username : " << endl;
	cin >> user.User;

	filename = user.User + ".dat";
	option.open(filename); //creates and opens a data file with username as the name of the file, to store user data

	while(option.fail()==false){//asks for a new username if the entered username already exists.
		cout << "Username already exists. Enter a unique Username : " << endl;
		cin >> user.User;
		
			filename = user.User + ".dat";
			option.open(filename);
		
	}

	cout << "Please enter a password : " << endl;
	cin >> user.password;

	cout << "Please enter your name : " << endl;
	cin >> user.name;

	cout << "Please enter how much money you'd like to deposit : " << endl;
	cin >> user.chip;

	option.close();
	return user;
}


profile log_in() //this function is used to open a existing player record
{
	string User, password, filename;
	profile user;
	ifstream option;

		cout << "Enter Your Username : " << endl;
		cin >> User;
		filename = User + ".dat"; 
		option.open(filename); //opens a pre existing binary file
		bool exist = option.fail();
		while(exist){
			cout << "Please Enter Valid Username : " << endl;
			cin >> User;
				filename = User + ".dat";
				option.open(filename);
				exist = option.fail();
		}

	getline(option, user.User);
	getline(option, user.password);

		cout << "Please enter Password : " << endl; //confirms the password of the user file
		cin >> password;
		while (password != user.password){
			cout << "Please enter Correct Password : " << endl;
			cin >> password;
		}

	getline(option, user.name);
	option >> user.chip;
	option.close();
	return user;
}

int *arr = NULL;

int main(){ //driver function

	unsigned int time_seed = time(0);
	srand(time_seed);

	person user,house;
	vector<person> players;

	house.info.User = "House"; 
	players.push_back(house);

	int opt;
	cout << "Blackjack 21!" << endl;
	cout << "Select an Option to Continue." << endl;
	cout << "Enter 1. for the Rules" << endl;
	cout << "Enter 2. to  Play" << endl; 
	cin >> opt;
	char option;
	
while(opt != 2){
	if(opt == 1){
		cout << "Blackjack is a game where you have to come up with a higher total score than the dealer nearest to 21 but without exceeding it. Face cards like Joker, Queen, King have a value of 10. Aces have a variable value of 1 or 11, depending on whichever benefits the total value. Each player is dealt two cards, and the dealer takes two himself, one face-up and the other face-down. When you need a card, you hit or press ‘H’. If you are satisfied with your result, you can stay by pressing ’S’. If you exceed 21, you lose irrespective of what you or the dealer had. If during the card dealing part, i.e. in the very beginning, you have two cards summing up to a value of 21, you won Blackjack. Blackjack implements that you will win 2.5 times of your bet. The dealer can hitOr take cards until he reach 17, after which he has to stay. Best of Luck !!!"<< endl<< endl;
		cout << "Blackjack 21!" << endl;
		cout << "Select an Option to Continue." << endl;
		cout << "Enter 1. for the Rules" << endl;
		cout << "Enter 2. to  Play" << endl; 
		cin >> opt;
	}
	else{ 
			cout << "Please enter 1 or 2" << endl; 
			cin >> opt;
		}

}
				cout << "Enter the number of players: " << endl; 
				int num; 
				cin >> num; 
				arr = new int [num*3];
				for (int i = 0; i < num*3; i++)
					arr[i]=0;

				for(int i = 0;i< num;i++){ 
					cout << endl << "If you are an existing Player Enter E or Enter N to create new profile?" << endl;
					cin >> option;

					if(option == 'E' || option == 'e'){
						user.info = log_in();
						players.push_back(user);
					}

					else if(option == 'N' || option == 'n'){
						user.info = sign_up();
						save(user);
						players.push_back(user);
					}
					else{
						while(option != 'E'||option != 'e'||option != 'N'|| option == 'n'){
						cout << endl << "If you are an existing Player Enter E or Enter N to create new profile?" << endl;
						cin >> option;
					}
					}
				}
	
	int flag = 0;
	while(players.size() > 1){
		for(int i =1;i<players.size();i++){
			if(players[i].info.chip < 5){ //checks if user has balance lower than minimum value
				cout << players[i].info.User << " is out of money. Game Over !" << endl;
					save(players[i]);
					players.erase(players.begin() + (i));
					i--;
					if (i==0)
						i=1;

				}

			if(flag == 1 && players.size() > 1){
				cout << endl << players[i].info.User << ", Enter L to Leave or S to Stay ?" << endl;
				cin >> option;
				if(option == 'L' || option == 'l'){
					cout << "You won " << arr[0+((i-1)*3)] << " times, Tied "<< arr[1+((i-1)*3)] << " times and lost " << arr[2+((i-1)*3)] <<" times." << endl;
					save(players[i]);
					players.erase(players.begin() + (i));
					i--;

				}
			}
		}
		if (players.size()>1){
			cout << endl;
		game(players, arr);
		flag = 1;}
	}

	return 0;
	delete[] arr;
}

