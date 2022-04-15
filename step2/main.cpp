#include <afxwin.h>

// 프레임 윈도우 생성 방법
// CFrameWnd : 프레임 윈도우
// 윈도우 제목
// 메뉴 : resource(재사용가능한 자원)
// 아이콘 : resource
// 안쪽에 윈도우에 자식 윈도우를 생성하고 관리할 수 있는 책임이 있음
// 도구와 상태바를 생성해서 관리할 수 있음

/* 생성 방법 3가지
1. CWnd::Create() << 핵심
2. LoadFrame()
3. RuntimeClass를 사용하는 방법
*/

// 클래스 선언
// 클래스는 객체화 해야 사용 가능
class CMainFrame : public CFrameWnd {
public:

};

class CMYApp : public CWinApp {
public:
	virtual BOOL InitInstance() override {
		
		CMainFrame* pMainFrame = new CMainFrame();
		// 함수 끝날 때 소멸되지 않도록 heap에 저장

		pMainFrame->Create(NULL, NULL);

		// 화면에 윈도우 표시
		pMainFrame->ShowWindow(SW_SHOW);

		// 메인 윈도우를 설정
		m_pMainWnd = pMainFrame;

		return TRUE;
	}
	virtual int ExitInstance() override {
		return 0;
	}
};

CMYApp theAp;