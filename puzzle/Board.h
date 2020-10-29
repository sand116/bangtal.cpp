#pragma once
#include <bangtal>


using namespace bangtal;
class Board
{
private :
	Board();
	~Board();
private :
	static Board* m_pBoard;// static �����Ͽ� �� ���� ���� �����ϰ� �� 
private :
	ObjectPtr gameBoard[9];
	ObjectPtr initBoard[9];// �ʱ� �ε����� ���� ��ü �ּ� �����س��� : ���߿� gameBoard�� initBoard�� ����� ��ü�� �ּҰ� ������ ������ġ�� ����� ��
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
	// Ŭ���� �����ǿ� �¿����Ʒ��� ��ũ�� �ִ� ��� true ���� 
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

