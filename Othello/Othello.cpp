#include <bangtal>
using namespace bangtal;



ObjectPtr board[8][8];

// 보드 생성

enum class State
{
	BLANK,
	POSSIBLE,
	BLACK,
	WHITE

};

State board_state[8][8];

enum class Turn
{
	BLACK,
	WHITE
};

// turn이 모든 메서드에서 쓰이니 일단 전역으로 생성
Turn turn = Turn::BLACK;

void setState(int x, int y, State state)
{
	switch (state)
	{
	case State::BLANK: board[y][x]->setImage("Images/blank.png"); break;
	case State::WHITE: board[y][x]->setImage("Images/white.png"); break;
	case State::BLACK: board[y][x]->setImage("Images/black.png"); break;
	case State::POSSIBLE: board[y][x]->setImage(turn == Turn::BLACK ? "Images/black possible.png" : "Images/white possible.png"); break;
	} 

	//현재 상태를 저장
	board_state[y][x] = state;

}
bool check(int x, int y, int dx, int dy,bool isIn)
{
	if ( (x<0) || (y<0) || (x > 8) || (y > 8)) return false;

	if (board_state[y][x] == State::BLANK) return false;

	if (turn == Turn::BLACK)
	{
		if (board_state[y][x] == State::WHITE)
		{
			return check(x+dx , y + dy, dx, dy, true);
	
		}
		else if(board_state[y][x] == State::BLACK)
		{
			if (isIn) return true;
			else return false;
		}
	}

	else if(turn == Turn::WHITE)
	{
		if (board_state[y][x] == State::BLACK)
		{
			return check(x+dx, y+dy, dx, dy, true);
		}
		else if (board_state[y][x] == State::WHITE)
		{
			if (isIn) return true;
			else return false;
		}
	}
	return false;
}
bool checkPossible(int x, int y)
{

	// 각 방향에 대한 배열을 만들고 각 방향에 대해서 탐색한다
	int delta[8][2] = { {0,1},{1,0},{-1,0},{0,-1},{1,1} ,{-1,-1},{1,-1},{-1,1} };
	
	if (board_state[y][x] == State::BLACK) return false;
	if (board_state[y][x] == State::WHITE) return false;

	//놓여진 상태가 아니면 블랭크로 변경하고 체크하기
	setState(x, y, State::BLANK);

	for (auto n : delta)
	{
		if (check(x+n[0] , y+n[1] , n[0], n[1], false)) return true;
	}
	

	return false;
}

//8x8 놓을 수 있는 곳 표시 
bool setPossible()
{
	bool possible = false;
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{	//해당 X,Y에 놓을 수 있는지 확인하고 TRUE이면 변경
			if (checkPossible(x, y))
			{
				setState(x, y, State::POSSIBLE);
				possible = true;

			}
		}
	}
	return possible;
}

void reverseCheck(int x, int y, int dx, int dy, int count)
{
	if ((x < 0) || (y < 0) || (x > 8) || (y > 8)) return;

	if (board_state[y][x] == State::BLANK) return;

	if (turn == Turn::BLACK)
	{
		if (board_state[y][x] == State::WHITE) reverseCheck(x + dx, y + dy, dx, dy,count+1);
		else if (board_state[y][x] == State::BLACK)
		{
			if (count != 0)
			{
				for (int i = count; i > 0; i--)
				{
					x = x - dx; y = y - dy;
					setState( x, y , State::BLACK);
				}

			}
			else return;
		}
	}

	else if (turn == Turn::WHITE)
	{
		if (board_state[y][x] == State::BLACK) reverseCheck(x + dx, y + dy, dx, dy, count+1);
		else if (board_state[y][x] == State::WHITE)
		{
			if (count != 0)
			{
				for (int i = count; i > 0; i--)
				{
					x = x - dx; y = y - dy;
					setState(x, y, State::WHITE);
				}

			}
			else return;
		}
	}
	return;
}
void reverse(int x, int y)
{
	// 각 방향에 대한 배열을 만들고 각 방향에 대해서 탐색한다
	int delta[8][2] = { {0,1},{1,0},{-1,0},{0,-1},{1,1} ,{-1,-1},{1,-1},{-1,1} };

	for (auto n : delta)
	{
		reverseCheck(x+n[0], y+n[1], n[0], n[1], 0);
	}

	return;
}

int main()
{
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	auto scene = Scene::create("Othello", "Images/background.png");

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[y][x] = Object::create("Images/blank.png",scene, 40+ x*80,40+ y*80);
			board_state[y][x] = State::BLANK;

			board[y][x]->setOnMouseCallback([&,x ,y](ObjectPtr object, int, int, MouseAction) ->bool
			{if(board_state[y][x]==State::POSSIBLE)
				{
					if (turn == Turn::BLACK)
					{
						setState(x, y, State::BLACK);
						reverse(x,y);
						turn = Turn::WHITE;
					}
					else
					{
						setState(x, y, State::WHITE);
						reverse(x,y);
						turn = Turn::BLACK;
					}
					if (!setPossible())
					{
						turn == Turn::BLACK ? Turn::WHITE : Turn::WHITE;
						if (!setPossible()) showMessage("게임 종료");
					}
				}
				
				
				// 새롭게 정의한 콜백함수에서 기능을  정의하지 않아서 기본적인 기능이 동작했으면 좋겠는 경우 false, 더이상 진행 안했으면 좋겠으면 true  리턴
				return true;
			});
		}

	}
	setState(3, 3, State::BLACK);
	setState(4, 4, State::BLACK);
	setState(3, 4, State::WHITE);
	setState(4, 3, State::WHITE);

	setPossible();
	startGame(scene);

}