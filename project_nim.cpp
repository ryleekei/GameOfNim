/*
 * Course: CS215-002
 * Project: Project 1
 *
 * Purpose: 
 *			This program creates a game where two players alternately take marbles from a pile. In each turn,
 *			a player must make a legal move taking at least one but at most half of the marbles from the pile and
 *			then let the other player take a turn. The player who is has to take the last marble loses the game.
 * 
 * Author: Rylee Hobbs
 */
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int PILE_MAX = 50;
const int PILE_MIN = 10;
const char MARBLE = static_cast<char>(232);  //use code 232 in ASCII Table to represent marble
const int WIDTH = 10;   // for layout purpose

// display marbles on the pile
void printMarbles(int pile);

// represent the legal move when it is the computer's turn to play the game
void computer_play(int& pile, bool smart);

void player_play(int& pile);

int main()
{
	cout << "*****************************************************" << endl;
	cout << "*                 The game of Nim                   *" << endl;
	cout << "*    Players alternate taking at least one but at   *" << endl;
	cout << "*    most half of the marbles in the pile.          *" << endl;
	cout << "*    The player who takes the last marble loses.    *" << endl;
	cout << "*    It is written by Rylee Hobbs                   *" << endl;
	cout << "*    I hope you beat the computer:)                 *" << endl;
	cout << "*    No matter what, have a great day.              *" << endl;
	cout << "*****************************************************" << endl;
	
	srand(time(NULL)); //To change the seed to the current time in epoch so we don't get the same numbers from rand() every time
	int pile = (rand()% PILE_MIN + 1)+ (PILE_MAX - PILE_MIN); //deciding the size of pile
	int decider = rand() %2; // who goes first
	bool smart;

	while (pile > 1) // each player takes turns until one must take the last marble
	{ 
	
		printMarbles(pile);

		if (decider == 1) //player plays
		{
			player_play(pile);
			
			decider = 0; // next play for computer
		}
		else
		{
			if ((rand() % 2) == 1)
			{
				smart = true;
			}
			else
			{
				smart = false;
			}

			computer_play(pile, smart);
			decider = 1; //next play player
		}

	}
	if (decider == 1) // next play must be the user
	{
		cout << "The computer leaves the last marble for you. The computer wins :(" << endl;
	}
	else
	{
		cout << "You leave the last marble for the computer. You Win! :)" << endl;
	}

	return 0;
}

/*
 * It displays the marbles on the pile: the number of marbles depends on passing in parameter
 *@param pile int: representing how many marbles are on the pile to display
 *@return: void function
 */

void printMarbles(int pile)
{
	cout << endl << "There are " << pile << " marbles in the pile" << endl;
	for (int i = 0; i < pile; i++)
		cout << setw(WIDTH) << MARBLE << endl;
}

	/** It represents the legal move when it is the computer's turn to play
	*    computer's legal move is under either smart-move or 
	*               non-smart-move depending on the parameter named smart
	*@param pile int&: the pile size before its turn and after its turn, call by reference 
	*@param smart bool: representing the computer takes smart move (if true) or non-smart move (if false)
	*@return: void function*/
	
	void computer_play(int& pile, bool smart) {
		int take = 0;
		bool pow_of_2n = false;
		int size_to_check = pile + 1;
		int counter = 1;
		//loop to check if the pile size is 2^n - 1
		while (size_to_check > counter)
		{
			counter = 2 * counter;
		}

		if (counter == size_to_check)
		{
			pow_of_2n = true;
		}
		// continue dividing by two until remainder or no remainder


		{//loop to make the size 2^n -1 such that 2^n -1 is smaller than the pile
			if (pow_of_2n == false && smart == true)
			{
				//pile - take = 2^n - 1 
				// pile-take = counter/2 -1 
				take = pile - ((counter / 2) - 1);
				cout << "The computer takes " << take << " marble(s)." << endl;
			}

			//if not, then non-smart
			else
			{
				take = 1 + rand() % (pile / 2); // taking at least one but at most half
				cout << "The computer takes " << take << " marble(s)." << endl;
			}

			pile = pile - take;

		}
	}

		/** It represents the legal move when it is the user's turn to play the game
		*    (it should repeatedly ask the user to enter how many marbles to take
		*                          until the user makes a legal move.)
		*@param pile int&: the pile size beforeuser's turn and after user's turn, call by reference
		*@return: void function*/

	void player_play(int& pile)
	{
		int input = 0;

		do{
			cout << "Your Turn! How many marbles do you want to take?" << endl;

			cin >> input;

			// validate input;
			if (!cin)
			{
				cout << "Invalid input... Try again." << endl;
			}
			else if (input > pile / 2 || input < 1)
			{
				cout << "You must take at least one marble but less than half! try again." << endl;			
			}
			cin.clear();
			cin.ignore(256, '\n');
		} while (input > pile / 2 || input < 1);
		
		cout << "you take " << input << " marbles" << endl;

		pile = pile - input;
	}







