#include <bangtal>
#include <vector>
#include <time.h>
using namespace bangtal;
using namespace std;

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
typedef struct _Pos
{
	_Pos() {}
	_Pos(int _x, int _y) :x(_x), y(_y) {}
	int x,y;
}Pos;

// turn이 모든 메서드에서 쓰이니 일단 전역으로 생성
Turn turn = Turn::BLACK;
// 흰돌이 선택 가능한 좌표를 저장하는 함수
vector<Pos> whiteSelect;
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


// 재귀로 구현해보았다.
void reverseCheck(int x, int y, int dx, int dy, int count)
{
	if ((x < 0) || (y < 0) || (x > 8) || (y > 8)) return;

	if (board_state[y][x] == State::BLANK) return;

	if (turn == Turn::BLACK)
	{
		if (board_state[y][x] == State::WHITE) reverseCheck(x + dx, y + dy, dx, dy, count + 1);
		else if (board_state[y][x] == State::BLACK)
		{
			if (count != 0)
			{
				for (int i = count; i > 0; i--)
				{
					x = x - dx; y = y - dy;
					setState(x, y, State::BLACK);
				}

			}
			else return;
		}
	}

	else if (turn == Turn::WHITE)
	{
		if (board_state[y][x] == State::BLACK) reverseCheck(x + dx, y + dy, dx, dy, count + 1);
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
		reverseCheck(x + n[0], y + n[1], n[0], n[1], 0);
	}

	return;
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
Pos* randomSelect()
{
	int random = rand() % whiteSelect.size();
	return &(whiteSelect.at(random));
}

bool setBlackPossible()
{
	bool possible = false;
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{	//해당 X,Y에 놓을 수 있는지 확인하고 TRUE이면 변경
			if (checkPossible(x, y) )
			{
				setState(x, y, State::POSSIBLE);
				possible = true;
			}
		}
	}
	return possible;
}

bool setWhitePossible()
{
	bool possible = false;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (checkPossible(x, y))
			{
				whiteSelect.push_back(Pos(x,y));
			}
		}
	}

	if (!whiteSelect.empty())
	{
		Pos* random = randomSelect();
		setState(random->x, random->y, State::WHITE);
		reverse(random->x, random->y);
		whiteSelect.resize(0);
		possible = true;
		turn = Turn::BLACK;
	}

	return possible;
}


int main()
{
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);

	srand((unsigned int)time(NULL));
	srand(time(0));
	auto whiteTime = Timer::create(2.f);
	auto scene = Scene::create("Othello", "Images/background.png");

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[y][x] = Object::create("Images/blank.png",scene, 40+ x*80,40+ y*80);
			board_state[y][x] = State::BLANK;

			board[y][x]->setOnMouseCallback([&,x ,y](ObjectPtr object, int, int, MouseAction) ->bool
			{	// 돌을 선택할 수 있는 경우는 turn이 검은 돌일 때 뿐이다.
				if(board_state[y][x]==State::POSSIBLE && turn == Turn::BLACK)
				{		
					setState(x, y, State::BLACK);
					reverse(x,y);

					turn = Turn::WHITE;


					whiteTime->start();
					showTimer(whiteTime);
					// 흰색돌이 setWhitePossible함수에서 둘 수 있는 곳을 찾고 자동으로 둔 후 턴을 변경한다
					
					whiteTime->setOnTimerCallback([&](TimerPtr)->bool 
					{	//만약 흰색이 둘 수 있는 곳이 존재하지 않는 다면 검은 돌을 둘 곳을 탐색하고 둘 다 없다면 false.
							if (!setWhitePossible())
							{
								turn = Turn::BLACK;
								if (!setBlackPossible()) showMessage("게임 종료");
							}
							// 흰색이 돌을 두었다면 턴을 변경하고 검은 돌이 둘 수 있는 곳을 찾는다. 만약 존재하지 않는 다면 다시 흰색 돌을 둘 수 있는 곳을 찾고 둘 다 존재하지 않는 경우 게임종료.
							else
							{
								turn = Turn::BLACK;
								if (!setBlackPossible())
								{
									turn = Turn::WHITE;
									if (!setWhitePossible()) showMessage("게임 종료");
								}
							}
						whiteTime->set(2.f);
						return false;
					});
				
					
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

	setBlackPossible();
	startGame(scene);

}