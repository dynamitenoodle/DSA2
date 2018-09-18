#pragma once

class Board
{
public:
	Board(int remove); // to create the 3x3 board take in 3 and 3
	~Board();

	int startVerArray[16];
	int currentVerArray[16];
	int completeVerArray[16];

	int swapsMade;

	// general methods
	bool Swap(int dir);
	bool IsSolved(bool isLC);
	bool Shuffle(int toSwap);
	bool PrintBoard();
	bool ResetBoard();
	bool DeletePtrs();

	// A* stuff
	bool AstarSolve();

	// hillclimbing stuff
	bool HillClimbingSolve();

private:
	bool Init(int remove);
	int xSpace;
	int ySpace;
	int removed;

	// General methods
	bool CheckNorth(int *row0, int *row1, int *row2, int *row3);
	bool CheckSouth(int *row0, int *row1, int *row2, int *row3);
	bool CheckEast(int *row0, int *row1, int *row2, int *row3);
	bool CheckWest(int *row0, int *row1, int *row2, int *row3);
	bool SetCurrent(int tempSize, bool isLC);
	bool SetBoard(int tempSize, bool isLC);
	bool PrintPathAstar();

	// A* stuff
	int** boardStatesLC;
	int *boardValuesLC;
	int **boardStatesH;
	int *boardValuesH;

	bool stopSearch; 
	int sizeLC;
	int sizeH;

	bool GenerateHeuristics();
	bool GenerateLowestCosts();
	bool CreateLC(int currentDepth);
	bool CreateH(int currentDepth);
	
	// hillclimbing stuff
	bool NodeCheck(int depth);
	bool AddCurrentHC();
	bool HCContainsCurrent();
	bool CheckCompleteHC();

	int** boardStatesHC;

	int totalChecks;
	int sizeHC;
	int maxDive;
	bool hillComplete;

};

