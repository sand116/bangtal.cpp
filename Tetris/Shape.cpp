#include "Shape.h"
#include "value.h"
#include "StageManager.h"
#include "Stage.h"
#include "windows.h"


CShape::CShape()
{	
	// ��������� �ʱ�ȭ
	m_iWidthCount = 0;
	m_iDir = RD_UP;
	for (int i = 0; i < 4; ++i) 
	{
		for (int j = 0; j < 4; j++) 
		{
			m_cShape[i][j] = '0';
		}
	}
}

CShape::~CShape()
{
}


int CShape::MoveDown()
{	
	class CStage* pStage = CStageManager::GenInst()->GetCurStage();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_cShape[i][j] == '1') //���϶��� üũ 
			{	
				//���� �ٷ� �Ʒ� ĭ Ȥ�� �� ĭ�� ������ üũ
				if (pStage->CheckBlock(m_tPos.x + j, m_tPos.y - (2 - i)))
				{
					//�ٴڿ� ���� �Ŀ� ���� ���� ����  �Ѻκ��̶� y��ǥ��
					// 0���� �۴ٸ� �����Ѵ�.
					for (int k = 0; k < 4; ++k)
					{
						for (int l = 0; l < 4; ++l)
						{
							if (m_cShape[k][l] == '1')
							{
								if (m_tPos.y - (3 - k) <= 0)
								{
									return 2;
								}
							}
						}
					}

					return 1;
				}
		
			}
		}
	}

	++m_tPos.y;
	return 0;
}

void CShape::MoveLeft()
{
	if (m_tPos.x == 0) return;

	class CStage* pStage = CStageManager::GenInst()->GetCurStage();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_cShape[i][j] == '1') //���϶��� üũ 
			{
				if (pStage->CheckBlock(m_tPos.x + j - 1, m_tPos.y - (3 - i)))
					return ;

			}
		}

	}
	--m_tPos.x;
}

void CShape::MoveRight()
{	// ���ΰ� �� ĭ������ ���� �޶���
	if (m_tPos.x + m_iWidthCount == STAGE_WIDTH) return;

	class CStage* pStage = CStageManager::GenInst()->GetCurStage();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_cShape[i][j] == '1') //���϶��� üũ 
			{
				if (pStage->CheckBlock(m_tPos.x + j + 1, m_tPos.y - (3 - i)))
					return;
			}
		}

	}
	++m_tPos.x;
}

bool CShape::Init()
{	// ���� ���� �Ʒ��� ���������� �����Ѵ�.
	m_tPivot.x = 0;
	m_tPivot.y = 3;
	return true;
}

void CShape::Rotation()
{
}

// �������� �ִ� ���� ���

/* 4X4 ĭ���� ���ذ��� X= 0, Y=3 �϶��̸� �ش� ���� �������� ���� ����
   ������ ������� �ܼ�â�� ����� ��ǥ ����
   i=3�϶�, m_tPos.y�� 4X4���� �ٴڰ��� ���� �ϰ�, UPDATE�ɶ����� +1�� Ŀ��(ȭ��� �Ʒ��� ������)
*/


void CShape::Render()
{
	class CStage* pStage = CStageManager::GenInst()->GetCurStage();

	//���� ��ġ�� ���� ���� 
	pStage->InitStage(STAGE_WIDTH, STAGE_HEIGHT,1);

		for (int i = 0; i < 4; ++i)
		{		
			int iYIndex = m_tPos.y - (3 - i);

			if (iYIndex < 0) continue; //����ȭ���� �Ѿ�� ��� ���� ó��

			for (int j = 0; j < 4; ++j)
			{	
				//���� ȭ�� ������ �Ѿ�� ��� ����ó��
				if (m_tPos.x + j >= STAGE_WIDTH)
					continue;

				// ���� ��ǥ�� �ش��ϸ� stage�� ���
				if (m_cShape[i][j] == '1') 
				{
					pStage->RenderShape(m_tPos.x + j, iYIndex, getColor());

				}
				
			}
			cout << endl;
		}
}

void CShape::RenderNext()
{
	class CStage* pStage = CStageManager::GenInst()->GetCurStage();
	
	//next���� ĭ �ʱ�ȭ
	pStage->InitStage(4, 4, 2);

	for (int i = 0; i < 4; ++i)
	{	
		//CCore::GenInst()->SetConsolePos(m_tPos.x, iYIndex);
		for (int j = 0; j < 4; ++j)
		{
			// 0�� ��찡 ������ �����ϴ� ����
			if (m_cShape[i][j] == '1') pStage->RenderNextShape(j, i);
		}
		//cout << endl;
	}

	
}
