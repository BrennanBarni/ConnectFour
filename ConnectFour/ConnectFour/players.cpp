#include "players.h"
#include "game.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

Player::Player() { }

int Player::getNextTurn(Game game) {
	return 1;
}

HumanPlayer::HumanPlayer() { }

int HumanPlayer::getNextTurn(Game game) 
{
	int temp;
	cin >> temp;
	return temp;
}

AiPlayer::AiPlayer() { }

int AiPlayer::getNextTurn(Game game)
{
	vector<int> possibleColumns;

	for (int col = 0; col <= game.BoardWidth; col++) {
		if (game(col, 0) == BoardField::Empty) {
			possibleColumns.push_back(col);
		}
	}
	int size = possibleColumns.size();

	// returns a random column out of all the columns that were valid for selection
	int column = rand() % size;
	cout << column + 1 << "\n";
	return (possibleColumns.at(column) + 1);
}