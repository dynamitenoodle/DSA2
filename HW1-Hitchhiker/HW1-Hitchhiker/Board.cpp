#include "stdafx.h"
#include "Board.h"

Board::Board(int remove)
{
	xSpace = 4;
	ySpace = 4;
	swapsMade = 0;
	srand(time(NULL));
	stopSearch = false;

	boardStatesLC = new int*[1000000];
	boardStatesH = new int*[10000000];
	boardValuesLC = new int[1000000];
	boardValuesH = new int[1000000];

	boardStatesHC = new int*[1000000];
	totalChecks = 0;

	Init(remove);
}

// Destructionoid
Board::~Board()
{

}

// to swap the open space with another spot on the board
// North = 0 South = 1 East = 2 West = 3
// returns true if the swap worked, false if it did not
bool Board::Swap(int dir)
{
	// creating and populating the rows
	bool swap = false;
	int *row0, *row1, *row2, *row3;
	row0 = new int[4];
	row1 = new int[4];
	row2 = new int[4];
	row3 = new int[4];

	for (int i = 0; i < 4; i++)
		row0[i] = currentVerArray[i];

	for (int i = 0; i < 4; i++)
		row1[i] = currentVerArray[i + 4];

	for (int i = 0; i < 4; i++)
		row2[i] = currentVerArray[i + 8];

	for (int i = 0; i < 4; i++)
		row3[i] = currentVerArray[i + 12];

	switch (dir)
	{
	case 0: // north
		if (CheckNorth(row0, row1, row2, row3))
			swap = true;
		break;
	case 1: // south
		if (CheckSouth(row0, row1, row2, row3))
			swap = true;
		break;
	case 2: // east
		if (CheckEast(row0, row1, row2, row3))
			swap = true;
		break;
	case 3: // west
		if (CheckWest(row0, row1, row2, row3))
			swap = true;
		break;
	default:
		cout << "Incorrect direction" << endl;
		break;
	}

	delete [] row0;
	delete [] row1;
	delete [] row2;
	delete [] row3;

	return swap;
}

// Checking if we can swap north
bool Board::CheckNorth(int *row0, int *row1, int *row2, int *row3)
{
	// finding the current position
	int pos = 0;
	for (int i = 0; i < 4; i++)
	{
		if (row0[i] == 0)
			pos = i;

		if (row1[i] == 0)
			pos = i + 4;

		if (row2[i] == 0)
			pos = i + 8;

		if (row3[i] == 0)
			pos = i + 12;
	}

	// check to see if position is valid
	if (pos > 3)
	{
		// the swapping is valid, complete the swap
		currentVerArray[pos] = currentVerArray[pos - 4];
		currentVerArray[pos - 4] = 0;
		return true;
	}

	return false;
}

// Checking if we can swap south
bool Board::CheckSouth(int *row0, int *row1, int *row2, int *row3)
{
	// finding the current position
	int pos = 0;
	for (int i = 0; i < 4; i++)
	{
		if (row0[i] == 0)
			pos = i;

		if (row1[i] == 0)
			pos = i + 4;

		if (row2[i] == 0)
			pos = i + 8;

		if (row3[i] == 0)
			pos = i + 12;
	}

	// check to see if position is valid
	if (pos < 12)
	{
		// the swapping is valid, complete the swap
		currentVerArray[pos] = currentVerArray[pos + 4];
		currentVerArray[pos + 4] = 0;
		return true;
	}

	return false;
}

// Checking if we can swap east
bool Board::CheckEast(int *row0, int *row1, int *row2, int *row3)
{
	// finding the current position
	int pos = 0;
	for (int i = 0; i < 4; i++)
	{
		if (row0[i] == 0)
			pos = i;

		if (row1[i] == 0)
			pos = i + 4;

		if (row2[i] == 0)
			pos = i + 8;

		if (row3[i] == 0)
			pos = i + 12;
	}

	// check to see if position is valid
	if (pos != 3 && pos != 7 && pos != 11 && pos != 15)
	{
		// the swapping is valid, complete the swap
		currentVerArray[pos] = currentVerArray[pos + 1];
		currentVerArray[pos + 1] = 0;
		return true;
	}

	return false;
}

// Checking if we can swap west
bool Board::CheckWest(int *row0, int *row1, int *row2, int *row3)
{
	// finding the current position
	int pos = 0;
	for (int i = 0; i < 4; i++)
	{
		if (row0[i] == 0)
			pos = i;

		if (row1[i] == 0)
			pos = i + 4;

		if (row2[i] == 0)
			pos = i + 8;

		if (row3[i] == 0)
			pos = i + 12;
	}

	// check to see if position is valid
	if (pos != 0 && pos != 4 && pos != 8 && pos != 12)
	{
		// the swapping is valid, complete the swap
		currentVerArray[pos] = currentVerArray[pos - 1];
		currentVerArray[pos - 1] = 0;
		return true;
	}

	return false;
}

// setting the current
bool Board::SetCurrent(int tempSize, bool isLC)
{
	// check if it is the lowest cost or nahwt
	if (isLC) 
	{
		for (int i = 0; i < xSpace * ySpace; i++)
			*(currentVerArray + i) = *(boardStatesLC[tempSize] + i);
	}

	else
	{
		for (int i = 0; i < xSpace * ySpace; i++)
			*(currentVerArray + i) = *(boardStatesH[tempSize] + i);
	}

	return true;
}

// setting the board
bool Board::SetBoard(int tempSize, bool isLC)
{
	// this method took like a hour to come up with alone, it ended up being that forcing the values into the array was the only way for it to work
	// Doing it any other way resulted in it only taking the first value
	// Also the debugger did not work when seeing what was in the array, it only showed the first value, which made this even harder to debug
	if (isLC)
	{
		boardStatesLC[tempSize] = new int[16];
		for (int i = 0; i < xSpace * ySpace; i++)
			*(boardStatesLC[tempSize] + i) = *(currentVerArray + i);
	}

	else
	{
		boardStatesH[tempSize] = new int[16];
		for (int i = 0; i < xSpace * ySpace; i++)
			*(boardStatesH[tempSize] + i) = *(currentVerArray + i);
	}

	return true;
}

// is the array solved?
bool Board::IsSolved(bool isLC)
{
	if (isLC) 
	{
		for (int i = 0; i < 16; i++)
		{
			if (completeVerArray[i] != currentVerArray[i])
				return false;
		}
		cout << "Lowest costs found!" << endl;

	}

	else
	{
		for (int i = 0; i < 16; i++)
		{
			if (startVerArray[i] != currentVerArray[i])
				return false;
		}
		cout << "Heuristics found!" << endl;

	}

	return true;
}

// Shufflingo
bool Board::Shuffle(int toSwap)
{
	// Shuffling
	cout << "Shuffling Board..." << endl;

	for (int i = 0; i < toSwap; i++)
	{
		int random = rand() % 4;
		if (Swap(random))
			swapsMade++;
		else
			i--;
	}

	for (int i = 0; i < (xSpace * ySpace); i++)
	{
		startVerArray[i] = currentVerArray[i];
	}

	return true;
}

// solving with A star
bool Board::AstarSolve()
{
	GenerateLowestCosts();
	GenerateHeuristics();

	/*
	bool inputCheck = false;
	do
	{
		cout << "Would you like to see the path (y/n)?" << endl;
		char input;
		cin >> input;

		switch (input)
		{
		case 'y':
			inputCheck = true;
			PrintPathAstar();
			break;
		case 'n':
			inputCheck = true;
			break;
		default:
			cout << "Not y or n";
			break;
		}
	} while (!inputCheck);
	*/

	// reset for looks
	for (int i = 0; i < xSpace * ySpace; i++)
		currentVerArray[i] = startVerArray[i];

	return true;
}

// Creating the heuristics for board states
bool Board::GenerateHeuristics()
{
	stopSearch = false;

	// set the current to the complete state
	for (int i = 0; i < xSpace * ySpace; i++)
		currentVerArray[i] = completeVerArray[i];

	SetBoard(0, false);
	boardValuesH[0] = 0;
	sizeH = 1;

	for (int i = 1; i <= swapsMade; i++)
	{
		if (!stopSearch)
			CreateH(i);
	}
	
	return true;
}

// Generate the heuristic for the current number
bool Board::CreateH(int currentDepth)
{
	// loop through an array
	int tempSize = sizeH;
	for (int i = 0; i < sizeH; i++)
	{
		// find the currentdepth levels, and set up their next level
		if (boardValuesH[i] == currentDepth - 1)
		{
			SetCurrent(i, false);

			// checking which directions we can go from here
			for (int i = 0; i < 4; i++)
			{
				// if we can get a swap, save it to array with new value
				if (Swap(i))
				{
					// create the values and swap back
					if (IsSolved(false))
					{
						cout << "Iteration: " << tempSize << endl;
						stopSearch = true;
					}

					SetBoard(tempSize, false);
					boardValuesH[tempSize] = currentDepth;

					if (!stopSearch)
					{
						switch (i)
						{
						case 0:
							Swap(1);
							break;
						case 1:
							Swap(0);
							break;
						case 2:
							Swap(3);
							break;
						case 3:
							Swap(2);
							break;
						default:
							cout << "This should never happen..." << endl;
						}

						tempSize++;
					}
				}
			}
		}
	}
	sizeH = tempSize;
	return true;
}

// Generating the lowest cost for board states
bool Board::GenerateLowestCosts()
{
	stopSearch = false;

	// set the current to the start
	for (int i = 0; i < xSpace * ySpace; i++)
		currentVerArray[i] = startVerArray[i];

	SetBoard(0, true);
	boardValuesLC[0] = 0;
	sizeLC = 1;

	for (int i = 0; i <= swapsMade; i++)
	{
		if (!stopSearch)
			CreateLC(i);
	}

	return true;
}

// Generate the lowest cost for the current number
bool Board::CreateLC(int currentDepth)
{
	// loop through an array
	int tempSize = sizeLC;
	for (int i = 0; i < sizeLC; i++)
	{
		// find the currentdepth levels, and set up their next level
		if (boardValuesLC[i] == currentDepth - 1)
		{
			SetCurrent(i, true);

			// checking which directions we can go from here
			for (int i = 0; i < 4; i++)
			{
				// if we can get a swap, save it to array with new value
				if (Swap(i))
				{
					// create the values and swap back
					if (IsSolved(true))
					{
						cout << "Iteration: " << tempSize << endl;
						stopSearch = true;
					}
					SetBoard(tempSize, true);
					boardValuesLC[tempSize] = currentDepth;

					if (!stopSearch)
					{
						switch (i)
						{
						case 0:
							Swap(1);
							break;
						case 1:
							Swap(0);
							break;
						case 2:
							Swap(3);
							break;
						case 3:
							Swap(2);
							break;
						default:
							cout << "This should never happen..." << endl;
						}

						tempSize++;
					}
				}
			}
		}
	}
	sizeLC = tempSize;
	return 0;
}

// Prints the board out
bool Board::PrintBoard()
{
	cout << "Printing Board..." << endl;
	cout << endl << "   ----------------------- " << endl;
	for (int i = 0; i < 16; i += 4)
	{
		cout << "    |  ";

		for (int j = 0; j < 4; j++)
		{
			if (currentVerArray[i + j] < 10)
				cout << currentVerArray[i + j] << "   ";
			else
				cout << currentVerArray[i + j] << "  ";

		}
		cout << " | " << endl;
	}
	cout << "   ----------------------- " << endl << endl;

	return true;
}

// Reset the board to normal
bool Board::ResetBoard()
{
	cout << "Resetting board..." << endl;

	for (int i = 0; i < 16; i++)
		currentVerArray[i] = startVerArray[i];

	swapsMade = 0;
	DeletePtrs();
	totalChecks = 0;

	sizeLC = 0;
	sizeHC = 0;
	sizeH = 0;

	return true;
}

// delete all of the pointers
bool Board::DeletePtrs()
{
	delete [] boardStatesLC;
	delete [] boardValuesLC;
	delete [] boardStatesH;
	delete [] boardValuesH;
	delete [] boardStatesHC;

	return false;
}

// for use of initialization
bool Board::Init(int remove)
{
	int pieces[16];

	for (int i = 0; i < (xSpace * ySpace); i++)
	{
		// set up the numbers
		pieces[i] = (i+1);

		// remove a tile from the board
		if (pieces[i] == remove)
			pieces[i] = 0;

		// set the arrays
		startVerArray[i] = currentVerArray[i] = completeVerArray[i] = pieces[i];
	}
	 
	// set the removed number
	removed = remove;

	return true;
}

// Printing the path
bool Board::PrintPathAstar()
{
	// set the current to the start
	for (int i = 0; i < xSpace * ySpace; i++)
		currentVerArray[i] = startVerArray[i];

	cout << "Step 0" << endl;
	PrintBoard();

	bool finishCheck = false;
	while (!finishCheck)
	{
		// checking to see if we are done printing path
		for (int i = 0; i < 16; i++)
		{
			if (completeVerArray[i] != currentVerArray[i])
				finishCheck = true;
		}

		// Get the next step
		int** boardStates = new int*[1000000];
		int *boardValuesTotal = new int[1000000];
		int boardNum = 0;

		// set up the total board, starting with LC
		for (int i = 0; i < sizeLC; i++)
		{
			boardStates[i] = new int[16];
			boardValuesTotal[i] = boardValuesLC[i];
			for (int x = 0; x < xSpace * ySpace; x++)
				*(boardStates[i] + x) = *(boardStatesLC[i] + x);
			boardNum++;
		}

		// Ensure the comparing
		for (int i = 0; i < sizeH; i++)
		{
			for (int j = 0; j < boardNum; j++)
			{

			}
		}
	}

	return true;
}

// Solving with hill climbing
bool Board::HillClimbingSolve()
{
	maxDive = swapsMade + 1; // how many steps allowed to solve
	hillComplete = false;

	// set the current to the start
	for (int i = 0; i < xSpace * ySpace; i++)
		currentVerArray[i] = startVerArray[i];

	AddCurrentHC();
	NodeCheck(0);

	cout << "Completed Hill Climb with " << totalChecks << " attempts!" << endl;

	return true;
}

// Recursively loop through each option til we win!
bool Board::NodeCheck(int depth)
{
	if (hillComplete)
		return true;

	// See if we completed the Check
	if (CheckCompleteHC())
	{
		hillComplete = true;
		return true;
	}

	// up how many we have made
	totalChecks++;
	depth++;

	// checking which directions we can go from here
	if (depth < maxDive)
	{
		for (int i = 0; i < 4; i++)
		{
		// if we can get a swap, save it to array with new value
			if (Swap(i))
			{
				if (!HCContainsCurrent())
				{
					AddCurrentHC();
					NodeCheck(depth);
				}
				switch (i)
				{
				case 0:
					Swap(1);
					break;
				case 1:
					Swap(0);
					break;
				case 2:
					Swap(3);
					break;
				case 3:
					Swap(2);
					break;
				default:
					cout << "This should never happen..." << endl;
				}
			}
		}
	}

	return true;
}

// add the current state to the seen "list"
bool Board::AddCurrentHC()
{
	boardStatesHC[sizeHC] = new int[16];
	for (int i = 0; i < xSpace * ySpace; i++)
		*(boardStatesHC[sizeHC] + i) = *(currentVerArray + i);

	sizeHC++;
	return true;
}

// Does the "list" contain the current array?
bool Board::HCContainsCurrent()
{
	bool check = true;
	for (int i = 0; i < sizeHC; i++)
	{
		for (int j = 0; j < xSpace * ySpace; j++)
		{
			if (*(boardStatesHC[i] + j) != *(currentVerArray + j) && check)
				check = false;
		}
	}

	return check;
}

// check if the HC is completed
bool Board::CheckCompleteHC() 
{
	for (int i = 0; i < xSpace * ySpace; i++)
	{
		if (*(completeVerArray + i) = *(currentVerArray + i))
			return false;
	}

	return true;
}
