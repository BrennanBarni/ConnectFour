class Game;

class Player 
{
public:
	Player();
	virtual int getNextTurn(Game game) = 0;
};

class HumanPlayer : public Player 
{
public:
	HumanPlayer();
	int getNextTurn(Game game);
};

class AiPlayer : public Player 
{
public:
	AiPlayer();
	int getNextTurn(Game game);
};