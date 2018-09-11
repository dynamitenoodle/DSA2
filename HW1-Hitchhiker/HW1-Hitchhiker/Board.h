#pragma once
#include "Piece.h"

class Board
{
public:
	Board(int remove); // to create the 3x3 board take in 3 and 3
	~Board();

	Piece* startVerArray;
	Piece* currentVerArray;
	Piece* completeVerArray;

	bool Swap();
	bool IsSolved();
	bool Shuffle();
	bool GenerateHeuristics();
	bool GenerateLowestCosts();
	bool PrintBoard();

private:
	bool Init(int remove);
	int xSpace;
	int ySpace;
	int removed;
};

