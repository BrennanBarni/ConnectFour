/*
Brennan Barni
ConnectFour
*/

#include "game.h"
#include "players.h"

// Constructor
Game::Game(Player &p1, Player &p2) 
{
	BoardHeight = 6;
	BoardWidth = 7;
	
	// initializing the 2D matrix
	board = new BoardField*[BoardHeight];
	for (int h = 0; h <= BoardHeight; h++)
	{
		board[h] = new BoardField[BoardWidth];
		for (int w = 0; w <= BoardWidth; w++)
		{
			board[h][w] = BoardField::Empty;
		}
	}

	// assigning pointers player1 and player2 to point to the addresses of p1 and p2
	player1 = &p1;
	player2 = &p2;
	
	// initialize running and gamestate
	running = true;
	state = GameState::TurnP1;
}

void Game::initBoard(int height, int width) 
{
	board = new BoardField*[height];
	for (int h = 0; h < height; h++) 
	{
		board[h] = new BoardField[width];
		for (int w = 0; w < width; w++)
		{
			board[h][w] = BoardField::Empty;
		}
	}
	BoardWidth = width;
	BoardHeight = height;
} // initializes an empty board

GameState Game::getState()
{
	return state;
}

bool Game::isRunning()
{
	return running;
}

BoardField Game::operator()(int row, int col) const 
{
	if (row > BoardHeight || col > BoardWidth || row < 0 || row < 0)
		return BoardField::Empty;

	return board[row][col];
} // operator overload

BoardField Game::getFieldAt(int row, int col) const
{
	if (row > BoardHeight || col > BoardWidth || row < 0 || row < 0)
		return BoardField::Empty;

	return board[row][col];
} // additional private method to allow for easy access of the board's fields

void Game::dropStone(int col)
{
	col -= 1;

	// if the selected column is out of bounds, return.
	if (col >= BoardWidth || col < 0)
		return;

	// iterates backwards up the row to simulate dropping a stone into the slot. Bottom-most empty index will be occupied.
	for (int row = 5; row > 0; row--)
	{
		if (getFieldAt(col, row) == BoardField::Empty) {
			switch (state)
			{
			case GameState::TurnP1:
				this->board[col][row] = BoardField::Player1;
				break;
			case GameState::TurnP2:
				this->board[col][row] = BoardField::Player2;
				break;
			}
			return;
		}
	}
}

bool Game::checkHorizontal(BoardField field) 
{
	for (int row = 0; row < BoardHeight; row++)
	{
		for (int col = 0; col < BoardWidth; col++)
		{
			if (getFieldAt(col, row) == field &&
				getFieldAt(col + 1, row) == field &&
				getFieldAt(col + 2, row) == field &&
				getFieldAt(col + 3, row) == field)
				return true;
		}
	}
	return false;
} // Checks for horizontal win conditions

bool Game::checkVertical(BoardField field)
{
	for (int col = 0; col < BoardWidth; col++)
	{
		for (int row = 0; row < BoardHeight; row++)
		{
			if (getFieldAt(col, row) == field &&
				getFieldAt(col, row + 1) == field &&
				getFieldAt(col, row + 2) == field &&
				getFieldAt(col, row + 3) == field)
				return true;
		}
	}
	return false;
} // Checks for vertical win conditions

bool Game::checkDiagonal(BoardField field)
{
	for (int col = 0; col < BoardWidth; col++)
	{
		for (int row = 0; row < BoardHeight; row++)
		{
			if ((getFieldAt(col, row) == field &&
				getFieldAt(col + 1, row + 1) == field &&
				getFieldAt(col + 2, row + 2) == field &&
				getFieldAt(col + 3, row + 3) == field)
				|| (getFieldAt(col, row) == field &&
					getFieldAt(col + 3, row) == field &&
					getFieldAt(col + 2, row + 1) == field &&
					getFieldAt(col, row + 3) == field))
				return true;
		}
	}
	return false;
} // Checks for diagonal win conditions

bool Game::checkWin() 
{
	BoardField curField;

	switch (state)
	{
	case GameState::TurnP1:
		curField = BoardField::Player1;
		break;
	case GameState::TurnP2:
		curField = BoardField::Player2;
		break;
	}

	// for every index, check to see if there are any vertical, horizontal, or diagonal winning board states for the active player
	for (int row = 0; row < BoardHeight; row++)
	{
		for (int col = 0; col < BoardWidth; col++)
		{
			if (checkHorizontal(curField) || checkVertical(curField) || checkDiagonal(curField))
				return true;
		}
	}
	return false;
}

bool Game::checkDraw()
{
	for (int col = 0; col < BoardWidth; col++)
	{
		// if the top row of every column is full and there has been no winner, it is a draw.
		if (getFieldAt(col, 0) == BoardField::Empty)
			return false;
	}
	return true;
}


void Game::nextTurn()
{
	int column;
	switch (state)
	{
	case GameState::TurnP1:
		column = player1->getNextTurn(*this);
		dropStone(column);
		// if P1 wins
		if (checkWin())
		{
			state = GameState::P1Won;
			running = false;
			return;
		}
		state = GameState::TurnP2;
		break;

	case GameState::TurnP2:
		column = player2->getNextTurn(*this);
		dropStone(column);
		// if P2 wins
		if (checkWin()) 
		{
			state = GameState::P2Won;
			running = false;
			return;
		}
		state = GameState::TurnP1;
		break;
	}
	
	// Every time neither wins, check for a draw...
	if (checkDraw()) {
		state = GameState::Draw;
		running = false;
		return;
	}
}

