# ENGG1340 PROJECT
 
# GROUP 112
# Group Members: Chopra Raunak (3035663514) and Kumar Aryak (3035663136)

# TEXT BASED GAME: BLACKJACK 

# IDEA AND IMPLEMENTATION


Two cards are dealt to the player. The dealer shows one card face up, and the other is face down. The player gets to see both of his or her cards and the total of them is added. Aces are worth 1 or 11 points, Face cards (Kings, Queens, Jacks) are worth 10 points, and all other cards are worth their face value. The goal of the game is to get as close to 21 (“Blackjack”) without going over, which is known as a “Bust.” 

The player goes first, making his or her decisions based on the single dealer card showing. The player has two basic choices: Hit or Stand. Hit means to take another card. Stand means that the player wishes no more cards, and ends the turn, allowing for the dealer to play.

The dealer only has limited option, that is to hit until their card total is less than 17 (or a soft 17), and must stand if it is 17 or higher. 

If the dealer gets closest to 21 without exceeding it, wins.

If both the player and the dealer have the same value, it is known as a push unless one had a Blackjack with the two cards given in the start, in which case that person wins.

If the player has two cards of the same value, he can split the cards and use each set of card as a seperate bet.

For this Project we are going to use each of the following features:

1) Generation of random game sets or events:
	For every card that is drawn from the deck, we use the random function for a set of numbers between 1 and 13 to find the card that is drawn.

2) Data structures for storing game status:
	We will be using data structures to store the set of cards and the choices of the player and the total of his value.

3) Dynamic memory management:
	Dynamic memory management will be implemented for the dynamic array which will keep tab of the cards used and the bet value of the player and whether he is loosing or winning.
	
4)File input/output (e.g., for loading/saving game status):
	Each draw of cards will be displayed in the game file and the user can input his choice over there while also viewing the bet value.
	
Program codes in multiple files:
	There will be two files, one for the functions and the data structures while the other file would implement these ideas and output the game. 


