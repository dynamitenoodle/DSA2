#include "stdafx.h"
#include "Piece.h"


Piece::Piece()
{
}

Piece::~Piece()
{
}

bool Piece::SetNumber(int n)
{
	num = n;

	return true;
}

bool Piece::SetPosition()
{
	return false;
}
