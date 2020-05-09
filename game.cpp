#include<iostream>
#include<vector>
#include "structure.h"

#define SPADE "\xE2\x99\xA0" //to define the symbols needed to show the various cards
#define CLUB "\xE2\x99\xA3"
#define HEART "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

using namespace std;



void output(vector<card> cards)// this function displays all the cards of a player
{
	const string CARD_VALUES[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	for(int i=0;i<cards.size();i++){
		if(cards[i].face_up){
			cout << CARD_VALUES[(cards[i].face-1)];
			if (cards[i].suit==0)
				std::cout<<SPADE;
			else if (cards[i].suit==1)
				std::cout<<HEART;
			else if (cards[i].suit==2)
				std::cout<<DIAMOND;
			else
				std::cout<<CLUB;
			cout<< " "; 
		}
		else
			cout << "??" << " ";
	}
	cout << endl;
}


bool Ace_present(vector<card> cards)//this function checks whether ace is present or not
{
	for(int i = 0; i < cards.size(); i++){
		if(cards[i].face == 1)
			return true;
	}
	return false;
}

int total_value(vector<card> cards) // to calculate the sum of numbers on the cards
{
	int total = 0;
	for(int i = 0; i<cards.size();i++){
		if(cards[i].face < 10)
			total += cards[i].face;
		else
			total += 10; 
	}
	if(total <= 11 && Ace_present(cards))
		total+=10;

	return total;
}


card deal_card() //this function allots the player a card
{

	card random_card;
	int i = rand() % 52;
	if (0<=i && i<=12){
		random_card.face = i+1 ;
		random_card.suit = 0;
	}
	else if (13<=i && i<=25){
		random_card.face = i+1-13 ;
		random_card.suit = 1;
	}
	else if (26<=i && i<=38){
		random_card.face = i+1-26 ;
		random_card.suit = 2;
	}
	else{
		random_card.face = i+1-39 ;
		random_card.suit = 3;
	}
	
	random_card.face_up = true;
	return random_card;
} 


int payment(person house, person &user)//this function checks whether the user has won or lost and accordingly pays or retracts the amount
{
	
	if((total_value(user.cards) <= 21 && total_value(house.cards) > 21) || ((total_value(user.cards) <= 21) && (total_value(house.cards) < total_value(user.cards)))) // winning condition 
	{
		if(user.cards.size() == 2 && total_value(user.cards) == 21){
			user.info.chip += (user.bet*(3/2)); 
			cout << "CONGRATULATIONS "<<user.info.User << "! You WON!!!" << endl;
		}
		else{
			user.info.chip+= (user.bet*2);
			cout << "CONGRATULATIONS "<<user.info.User << "! You WON!!!" << endl;
		}
		return 1;
	}
	else if(total_value(house.cards) == total_value(user.cards)) //tie conditon
	{ 
		user.info.chip+= user.bet;
		cout << user.info.User << ", it's a TIE!" << endl;
		return 0;
	}
	else{//losing condition
		cout <<user.info.User << ", You Lost Your Amount!" << endl;
		return -1;
	}
}


bool Ace_present(vector<card>);
int payment(person, person&);

card deal_card();

void bet(person &user) // this function is used to input the amount the player wants to bet
{
	int bet;
	cout << user.info.User << endl;
	cout << "Place Your Bet! (Bet must be between " << 5 <<  " and " << user.info.chip << ")" << endl;
	cin >> bet;
	if (bet < 5 || bet > user.info.chip){
		while (bet < 5 ||  bet > user.info.chip){
			cout << user.info.User << endl;
			cout << "Place Bet! (Bet must be between " << 5 <<  " and " << user.info.chip << ")" << endl;
			cin >> bet;
		}
	}

	user.info.chip -= bet;
	user.bet = bet;
}

void game(vector<person> &players, int *arr) // game function
{
	char option;

	for(int i =1;i<players.size();i++){

		bet(players[i]);
		cout << "Amount left : " << players[i].info.chip << "    Bet : " << players[i].bet << endl<< endl;
	}
	
	for(int i = 0; i < players.size(); i++){ 
		players[i].cards.push_back(deal_card());
		players[i].cards.push_back(deal_card());
		if(i == 0)
			players[0].cards[0].face_up = false;
	}
	for(int i =0;i<players.size();i++){
		cout << players[i].info.User << "'s Cards : ";
		output(players[i].cards);
	}
	
	bool cond = true;
	for(int i = 1;i<players.size();i++){
		option='.';
		cout << endl;
		while(option != 'S' && option != 's'){
			if(total_value(players[0].cards) <= 21){

						cout << endl << players[i].info.User << "'s Total Value: " << total_value(players[i].cards) << endl;
						cout << "Enter H to hit (Recieve a Card) or S to stay : "; //asks the user whether he/she wants to hit or stay
						cin >> option;
					if (option=='h'||option=='H'){
						players[i].cards.push_back(deal_card()); 
						cout << players[i].info.User << "'s Cards : ";
						output(players[i].cards);

					}
					if(total_value(players[i].cards) > 21){
						cout << players[i].info.User << "'s Total Value: " << total_value(players[i].cards) << endl;
						option = 'S';
					}
			}
		}
	}
	cout << endl;
	while((total_value(players[0].cards) < 17) || (total_value(players[0].cards) == 17 && Ace_present(players[0].cards)))
		players[0].cards.push_back(deal_card());

	players[0].cards[0].face_up = true; 
	
	for(int i =0;i<players.size();i++){
		cout << players[i].info.User << "'s Total Value : " << total_value(players[i].cards) << endl <<" Cards : ";
		output(players[i].cards);
		cout << endl;
	}

	for(int i =1;i<players.size();i++){
		if(total_value(players[i].cards) > 21){ //busting condition
			cout << "BUST!!! ";
		}
		int a = payment(players[0],players[i]);
		players[i].cards.clear();
		if (a==1)
			arr[0+((i-1)*3)]++;
		else if (a==0)
			arr[1+((i-1)*3)]++;
		else
			arr[2+((i-1)*3)]++;
	}	

	players[0].cards.clear();
}

