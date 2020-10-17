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
	//�������� ���� ���� �ʱ�ȭ 15x10
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

	//next ĭ ���� ������Ʈ �ʱ�ȭ 

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

//�������� ���� ��ó���� �κ� ���
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

// SHAPE::MOVEDOWN()�� TRUE�̸� ���������� �� �߰�
void CStage::AddBlock(CShape* pShape, const POSITION& tPos)
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
		{
			// ���� ����� ��쿡��
			if (pShape->GetBlock(j,i)=='1')
			{	//���������� �ش� ��� ��ġ ���
				m_Stage[tPos.y - (3 - i)][tPos.x + j] = '2';

				//���� ����� ä�� ���� üũ�Ѵ�
				bool bLine = true;
				for (int k = 0; k < STAGE_WIDTH; ++k)
				{
					if (m_Stage[tPos.y - (3 - i)][k] != '2')
					{
						bLine = false;
						break;
					}
				}
				//���� ���� ä���� ���� ��� ���̶�� ���� �����ش�.
				// ���� ������ ��ĭ�� �����ش�.
				if (bLine)
				{
					score++;
					
					//�����ٺ��� ���ٱ��� �α׸� �����ش�.
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

// �ش� x,y�� ���� �������� ���� ��ǥ������ �ٷ� �Ʒ�ĭ�� ��Ÿ����.
bool CStage::CheckBlock(int x, int y)
{	
	//�ٴڿ� ����� ��� ó�� 
	if (y >= STAGE_HEIGHT) return true;
	//���鿡 ����� ��� ó��
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
