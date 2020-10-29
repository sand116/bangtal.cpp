#include "value.h"
#include "macro.h"
#include <bangtal>

using namespace bangtal;

class CStageManager
{
	//밖에서 생성자를 호출하지 못하도록 막음 
private:
	CStageManager();
	~CStageManager();

private:
	static CStageManager* m_pInst;

public:
	//static 메서드 함수 
	static CStageManager* GenInst() {
		// staic 객체 반환
		if (!m_pInst) m_pInst = new CStageManager;
		return m_pInst;
	}
	static void DestroyInst() {
		SAFE_DELETE(m_pInst);
	}
private:
		class CStage* m_pCurStage;// 지역변수 초기화 필수!
public :
	bool Init(const ScenePtr scene);
	bool Run(); 
	// cosnt 메서드 
	class CStage* GetCurStage() const;
};