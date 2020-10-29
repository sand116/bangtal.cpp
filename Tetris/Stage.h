#pragma once
#include "value.h"
#include <bangtal>
using namespace bangtal;
class CStage
{
	// �ش� Ŭ���� �ۿ��� ���� ����
public:
	CStage();
	~CStage();

private:
	ScenePtr m_scene;
	friend class CStageManager;
	char m_Stage[STAGE_HEIGHT][STAGE_WIDTH];
	ObjectPtr m_objectStage[STAGE_HEIGHT][STAGE_WIDTH];
	
	char m_next[4][4];
	ObjectPtr m_nextShape[4][4];

	int score; // ���� : 3�� �̻� ���� �� ����
public:

	bool Init(const ScenePtr scene);
	bool Render();
	void AddBlock(class CShape* pShape, const POSITION& tPos);
	bool CheckBlock(int x, int y);
	void RenderShape(int x, int y,int color);
	void InitStage(int height, int width, int Case);
	void RenderNextShape(int x, int y);
	const ScenePtr GetScene(); 
};

