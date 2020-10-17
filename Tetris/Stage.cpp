#include "Stage.h"
#include "value.h"
#include "Shape.h"


CStage::CStage() :
	m_scene(NULL),score(0)
{
}

CStage::~CStage() 
{
}


bool CStage::Init(const ScenePtr scene)
{	
	m_scene = scene;
	//스테이지 내부 변수 초기화 15x10
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
			m_Stage[i][j] = '0';
	}

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			m_objectStage[i][j] = Object::create("picture/0.png", scene, 322 + 40 * j, 623-40*i);
			m_objectStage[i][j]->hide();
		}
	}

	//next 칸 내부 오브젝트 초기화 

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_nextShape[i][j] = Object::create("picture/0.png", scene, 780 + 40 * j, 623 - 40 * i);
			m_nextShape[i][j]->hide();
		}
	}

	return true;
}

//스테이지 내부 블럭처리된 부분 출력
bool CStage::Render()
{	
	
	for (int i = 0; i < STAGE_HEIGHT ; ++i) {

		for (int j = 0; j < STAGE_WIDTH ; ++j) 
		{
			if (m_Stage[i][j] == '0')
				m_objectStage[i][j]->hide();

			if (m_Stage[i][j] == '2')
			{
				m_objectStage[i][j]->setImage("picture/0.png");
				m_objectStage[i][j]->show();
			}
				
		}

	}
	if (score == 1) return true;
	return false;
	
}

// SHAPE::MOVEDOWN()이 TRUE이면 스테이지에 블럭 추가
void CStage::AddBlock(CShape* pShape, const POSITION& tPos)
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
		{
			// 실제 블록인 경우에만
			if (pShape->GetBlock(j,i)=='1')
			{	//스테이지에 해당 블록 위치 출력
				m_Stage[tPos.y - (3 - i)][tPos.x + j] = '2';

				//현재 블록이 채운 줄을 체크한다
				bool bLine = true;
				for (int k = 0; k < STAGE_WIDTH; ++k)
				{
					if (m_Stage[tPos.y - (3 - i)][k] != '2')
					{
						bLine = false;
						break;
					}
				}
				//현재 블럭이 채워진 줄이 모두 블럭이라면 한줄 지워준다.
				// 위의 블럭들을 한칸씩 내려준다.
				if (bLine)
				{
					score++;
					
					//현재줄부터 윗줄까지 싸그리 내려준다.
					for (int k = tPos.y - (3 - i); k > 0; k--)
					{
						for (int l = 0; l < STAGE_WIDTH; ++l)
						{
							m_Stage[k][l] = m_Stage[k - 1][l];
						}
					}
				}
				
			}
		}

	}
}

// 해당 x,y는 현재 내려오는 도형 좌표값들의 바로 아랫칸을 나타낸다.
bool CStage::CheckBlock(int x, int y)
{	
	//바닥에 닿았을 경우 처리 
	if (y >= STAGE_HEIGHT) return true;
	//옆면에 닿았을 경우 처리
	else if (x < 0 || x >= STAGE_WIDTH) return true;

	return m_Stage[y][x] == '2';
}


void CStage::RenderShape(int x, int y, int color)
{
	m_Stage[y][x] = '1';
	m_objectStage[y][x]->setImage("picture/" + to_string(color + 1)+".png");
	m_objectStage[y][x]->show();
}

void CStage::InitStage(int width, int height, int Case)
{
	if(Case == 1) {
		for (int i = 0; i < height; ++i) {

			for (int j = 0; j < width; ++j)
			{
				if (m_Stage[i][j] == '1')
				{
					m_objectStage[i][j]->hide();
					m_Stage[i][j] = '0';
				}
			}
		}
	}
	if (Case == 2)
	{
		for (int i = 0; i < height; ++i) {

			for (int j = 0; j < width; ++j)
			{
				if (m_next[i][j] == '1')
				{
					m_nextShape[i][j]->hide();
					m_next[i][j] = '0';
				}
			}
		}

	}
}

void CStage::RenderNextShape(int x, int y)
{
	m_next[y][x] = '1';
	m_nextShape[y][x]->show();
}

const ScenePtr CStage::GetScene()
{
	return m_scene;
}
