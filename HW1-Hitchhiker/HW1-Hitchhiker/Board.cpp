#include "stdafx.h"
#include "Board.h"


Board::Board(int remove)
{
	xSpace = 3;
	ySpace = 3;

	Init(remove);
}


Board::~Board()
{
}

bool Board::Swap()
{
	return false;
}

bool Board::IsSolved()
{
	return false;
}

bool Board::Shuffle()
{
	return false;
}

bool Board::GenerateHeuristics()
{
	return false;
}

bool Board::GenerateLowestCosts()
{
	return false;
}

bool Board::PrintBoard()
{
	cout << "Printing Board..." << endl;
	cout << currentVerArray[0].num << " " << currentVerArray[1].num << " " << currentVerArray[2].num << endl;
	cout << currentVerArray[3].num << " " << currentVerArray[4].num << " " << currentVerArray[5].num << endl;
	cout << currentVerArray[6].num << " " << currentVerArray[7].num << " " << currentVerArray[8].num << endl;

	return true;
}

// for use of initialization
bool Board::Init(int remove)
{
	Piece pieces[9];

	for (int i = 0; i < (xSpace * ySpace); i++)
	{
		// set up the numbers
		pieces[i].SetNumber(i+1);

		// remove a tile from the board
		if (pieces[i].num == remove)
			pieces[i].SetNumber(0);
	}

	// set the removed number and arrays
	removed = remove;
	startVerArray = currentVerArray = completeVerArray = pieces;

	return true;
}
