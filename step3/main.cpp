#include <afxwin.h>
#include "resource.h"
// 리소스 파일을 사용하기 위한 헤더

/*
resource (재사용 가능한 자원)
1. 윈도우 제목
2. 메뉴
3. 아이콘

위 3가지를 사용하여 윈도우 생성하는 방법
LoadFrame() 사용하여 FrameWnd 생성
*/
class CMainFrame : public CFrameWnd {

};

class CMYApp : public CWinApp {
public:
	BOOL InitInstance() {
		CMainFrame* pMainFrame = new CMainFrame();
		// pMainFrame->Create(NULL, NULL);
		pMainFrame->LoadFrame(IDR_MAIN_FRAME);

		pMainFrame->ShowWindow(SW_SHOW);
		m_pMainWnd = pMainFrame;


		return TRUE;
	}
	int ExitInstance() {
		return 0;
	}
};

CMYApp theApp;