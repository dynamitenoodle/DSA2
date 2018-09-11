#pragma once
class Piece
{
public:
	int num;
	int xPos;
	int yPos;

	Piece();
	~Piece();

	bool SetNumber(int n);
	bool SetPosition();
};

