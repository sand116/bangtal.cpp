#include "Board.h"
#include <bangtal>

using namespace bangtal;


Board* Board::m_pBoard = NULL;

Board::~Board()
{
}

void Board::init(ScenePtr scene)
{
	m_scene = scene;
	for (int i = 0; i < 9;)
	{
		gameBoard[i] = Object::create("Images/" + std::to_string(i + 1) + ".jpg", scene, 188 + (i % 3) * 302, 435 - (i / 3) * 150);
		initBoard[i] = gameBoard[i];
	}
}

bool Board::check(int clicked)
{
	return ((clicked % 3 > 0 && clicked - 1 == blank) ||
		(clicked % 3 < 2 && clicked + 1 == blank) ||
		(clicked > 2 && clicked - 3 == blank) ||
		(clicked < 6 && clicked + 3 == blank));
}

void Board::swap(int j)
{	
	gameBoard[j]->locate(m_scene, 188 + (blank % 3) * 302, 435 - (blank / 3) * 150);
	gameBoard[blank]->locate(m_scene, 188 + (j % 3) * 302, 435 - (j / 3) * 150);

	ObjectPtr temp = gameBoard[j];
	gameBoard[j] = gameBoard[blank];
	gameBoard[blank] = temp;

	blank = j;
}

bool Board::compare()
{
	bool rtn = true;
	for (int i = 0; i < 9; i++)
	{
		if (gameBoard[i] != initBoard[i])
		{
			rtn = false;
			break;
		}
	}
	return rtn;

}