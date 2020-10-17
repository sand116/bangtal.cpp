#include "value.h"
#include "macro.h"
#include <bangtal>

using namespace bangtal;

class CStageManager
{
private:
	CStageManager();
	~CStageManager();

private:
	static CStageManager* m_pInst;

public:
	static CStageManager* GenInst() {
		// staic ��ü ��ȯ
		if (!m_pInst) m_pInst = new CStageManager;
		return m_pInst;
	}
	static void DestroyInst() {
		SAFE_DELETE(m_pInst);
	}
private:
		class CStage* m_pCurStage;// �������� �ʱ�ȭ �ʼ�!
public :
	bool Init(const ScenePtr scene);
	bool Run(); 
	class CStage* GetCurStage() const;
};