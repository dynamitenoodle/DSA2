/*
Coehl Gleckner
DSA 2
HW - Sliding Puzzle
9/17/2018

Resources
I didn't use any online resources, I relied mostly on how I thought the problem could be solved and a couple of reccomendations from other students
in the labs on how to do certain things (The bit shifting I used was from my friend and I trying to figure out for a long time how to fix an issue,
he isn't in our section of DSA 2, I believe he is in Alberto's)

General
I started with creating a working puzzle, that could shuffle randomly n(set by player) times and be able to swap accordingly.
Double pointers allow creation of a pointer of arrays, so that we can keep track of board states we have seen.
You can also Reset the board at anytime.
I've also included improvements I could make, if in the future I want to get better at C++ and don't want to start something from scratch.

Naming
LC = Lowest Cost
H = Heuristic
HC = HillClimbing

Astar
Checks with lowest cost outwards from the starting array of values, then proceeds to check heuristics
Similar to Sonar, checks outwards
Returns how many checks it does to find the completed array

Hillclimbing
Checks a certain direction to a certain depth
Continues on that depth and searches all possible nodes, then recursively jumps back up
Returns how many checks it had to find the completed array


-------IMPROVEMENTS TO BE MADE IN THE FUTURE---------
1) Convert to exclusive pointers, no arrays
2) Clean memory progressively
3) Inside both lowest cost and heuristics, if the exact graph exists don't make a new one, especially if the number is lower
4) Finish Printing A Star
5) Implemenate changing the size of the array
6) All the bonuses I didn't complete
*/
#include "stdafx.h"
#include "Board.h"

int main()
{
	// starting of program
	bool quitCheck = true;

	Board board(16);

	cout << "Welcome to the first homework of DSA 2" << endl;
	cout << "0 represents the empty space" << endl;

	// Game loop
	while (quitCheck)
	{
		// make and print the first board
		cout << board.swapsMade << " swaps have been made" << endl;
		board.PrintBoard();
		cout << "Enter keys to perform tasks" << endl;
		cout << "s to shuffle" << endl << "a to solve with A*" << endl << "h for Hill Climbing" << endl << "r to reset" << endl << "q to quit" << endl;
		char input;
		cin >> input;
		cout << endl;

		// input check
		switch (input) {
		case 's':
			cout << "How many times would you like to shuffle (please enter an int)" << endl;
			int num;
			cin >> num;
			cout << endl;

			if (num == (int)num)
				board.Shuffle(num);
			else
				cout << "That is not a number" << endl;
			break;
		case 'a':
			board.AstarSolve();
			break;
		case 'h':
			board.HillClimbingSolve();
			break;
		case 'r':
			board.ResetBoard();
			break;
		case 'q':
			quitCheck = false;
			break;
		default:
			cout << input << " is not valid input." << endl;
			break;
		}

		cout << endl;
	}

	board.DeletePtrs();
	cout << "Goodbye!" << endl;

    return 0;
}

