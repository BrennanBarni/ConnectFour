enum class GameState { TurnP1, TurnP2, P1Won, P2Won, Draw };
enum class BoardField {Empty, Player1, Player2};
class Player;

class Game
{
public:
	int BoardWidth;
	int BoardHeight;

	Game(Player &p1, Player &p2);
	GameState getState();
	bool isRunning();
	
	void nextTurn();

	BoardField operator()(int row, int col) const;
	

private:
	BoardField** board;
	GameState state;
	bool running;
	Player *player1;
	Player *player2;

	BoardField getFieldAt(int row, int col) const;
	void initBoard(int height, int width);
	void dropStone(int col);
	bool checkHorizontal(BoardField field);
	bool checkVertical(BoardField field);
	bool checkDiagonal(BoardField field);
	bool checkWin();
	bool checkDraw();
};