#include "Shape.h"
#include "value.h"
#include "StageManager.h"
#include "Stage.h"
#include "windows.h"


CShape::CShape()
{	
	// 빈공간으로 초기화
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
			if (m_cShape[i][j] == '1') //블럭일때만 체크 
			{	
				//도형 바로 아래 칸 혹은 옆 칸이 블럭인지 체크
				if (pStage->CheckBlock(m_tPos.x + j, m_tPos.y - (2 - i)))
				{
					//바닥에 닿은 후에 현재 도형 블럭의  한부분이라도 y좌표가
					// 0보다 작다면 종료한다.
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
			if (m_cShape[i][j] == '1') //블럭일때만 체크 
			{
				if (pStage->CheckBlock(m_tPos.x + j - 1, m_tPos.y - (3 - i)))
					return ;

			}
		}

	}
	--m_tPos.x;
}

void CShape::MoveRight()
{	// 가로가 몇 칸인지에 따라 달라짐
	if (m_tPos.x + m_iWidthCount == STAGE_WIDTH) return;

	class CStage* pStage = CStageManager::GenInst()->GetCurStage();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_cShape[i][j] == '1') //블럭일때만 체크 
			{
				if (pStage->CheckBlock(m_tPos.x + j + 1, m_tPos.y - (3 - i)))
					return;
			}
		}

	}
	++m_tPos.x;
}

bool CShape::Init()
{	// 왼쪽 제일 아래를 기준점으로 설정한다.
	m_tPivot.x = 0;
	m_tPivot.y = 3;
	return true;
}

void CShape::Rotation()
{
}

// 내려가고 있는 도형 출력

/* 4X4 칸에서 기준값은 X= 0, Y=3 일때이며 해당 값을 기준으로 도형 생성
   기준을 기반으로 콘솔창에 출력할 좌표 설정
   i=3일때, m_tPos.y가 4X4에서 바닥값을 갖게 하고, UPDATE될때마다 +1씩 커짐(화면상 아래로 내려감)
*/


void CShape::Render()
{
	class CStage* pStage = CStageManager::GenInst()->GetCurStage();

	//이전 위치의 도형 삭제 
	pStage->InitStage(STAGE_WIDTH, STAGE_HEIGHT,1);

		for (int i = 0; i < 4; ++i)
		{		
			int iYIndex = m_tPos.y - (3 - i);

			if (iYIndex < 0) continue; //세로화면을 넘어가는 경우 예외 처리

			for (int j = 0; j < 4; ++j)
			{	
				//가로 화면 영역을 넘어가는 경우 예외처리
				if (m_tPos.x + j >= STAGE_WIDTH)
					continue;

				// 도형 좌표에 해당하면 stage에 출력
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
	
	//next도형 칸 초기화
	pStage->InitStage(4, 4, 2);

	for (int i = 0; i < 4; ++i)
	{	
		//CCore::GenInst()->SetConsolePos(m_tPos.x, iYIndex);
		for (int j = 0; j < 4; ++j)
		{
			// 0인 경우가 도형이 존재하는 영역
			if (m_cShape[i][j] == '1') pStage->RenderNextShape(j, i);
		}
		//cout << endl;
	}

	
}
