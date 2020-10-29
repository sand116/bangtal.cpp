#pragma once
#include <bangtal>


using namespace bangtal;
class Board
{
private :
	Board();
	~Board();
private :
	static Board* m_pBoard;// static 선언하여 한 개만 생성 가능하게 함 
private :
	ObjectPtr gameBoard[9];
	ObjectPtr initBoard[9];// 초기 인덱스에 원래 객체 주소 저장해놓기 : 나중에 gameBoard와 initBoard에 저장된 객체의 주소가 같으면 원래위치에 저장된 것
	int blank = 8;
	ScenePtr m_scene;
public:
	static Board* getInst()
	{
		if(! m_pBoard) m_pBoard = new Board;
		return m_pBoard;
	}
public:
	void init(const ScenePtr scene);
	// 클릭된 보드판에 좌우위아래에 블랭크가 있는 경우 true 리턴 
	bool check(int clicked);
	void swap(int j);
	bool compare();
	int getBlank()const {
		return blank;
	}
	ObjectPtr getObject(int idx) const {
		return gameBoard[idx];
	}
};

