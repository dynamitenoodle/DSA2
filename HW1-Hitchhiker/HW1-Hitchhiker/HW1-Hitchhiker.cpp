// HW1-Hitchhiker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Board.h"

int main()
{
	Board* board = new Board(9);
	board->PrintBoard();

    return 0;
}

