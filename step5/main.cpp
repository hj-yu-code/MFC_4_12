#include <afxwin.h>
#include "resource.h"

class CMainFrame : public CFrameWnd {
public:
	DECLARE_DYNCREATE(CMainFrame); // RUNTIME_CLASS를 위한 선언

};

/*
Document/View
MVC
	Model (Document)
	View
	Controller (제어)

Document : Data 관리가 목적 (새문서, 열기, 저장)
View : 화면에 출력

*/


class CMyDoc : public CDocument {
public:
	DECLARE_DYNCREATE(CMyDoc);
	//새문서 기능 구현 함수 
	virtual BOOL OnNewDocument() override {
		return TRUE;
	}
	//파일에 읽기/쓰기를 담당하는 함수 
	virtual void Serialize(CArchive& ar) override {

	}
};

class CMyView : public CView {
public:
	DECLARE_DYNCREATE(CMyView);
	//화면 출력에 대한 함수
	virtual void OnDraw(CDC* pDC) override {

	}
};

// 메크로를 이용해 객체 생성에 관련된 함수 구현
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd);
IMPLEMENT_DYNCREATE(CMyDoc, CDocument);
IMPLEMENT_DYNCREATE(CMyView, CView);

class CMYApp : public CWinApp {
public:
	BOOL InitInstance() {
		/*CMainFrame* pMainFrame = new CMainFrame();
		pMainFrame->LoadFrame(IDR_MAIN_FRAME);

		pMainFrame->ShowWindow(SW_SHOW);
		m_pMainWnd = pMainFrame;*/

		// Doc/View 구조
		// Document/View 구조
		// - 단일 문서
		// - 다중 문서
		// 현재는 단일 문서만 진행함

		CSingleDocTemplate* pDocTemplate;
		pDocTemplate = new CSingleDocTemplate(IDR_MAIN_FRAME,
			RUNTIME_CLASS(CMyDoc), // CRutimeClass : Document 생성
			RUNTIME_CLASS(CMainFrame), // 알려주기
			RUNTIME_CLASS(CMyView)
			);

		if (pDocTemplate == nullptr) {
			return FALSE;
		}

		// Doc/View 구조 객체를 등록함
		AddDocTemplate(pDocTemplate);
		// Animal class에 추가하는 것과 유사한 것

		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		if (!ProcessShellCommand(cmdInfo)) { // 프로그램이 정상적인지 확인
			return FALSE;
		}

		m_pMainWnd->ShowWindow(SW_SHOW);
		m_pMainWnd->UpdateWindow();

		return TRUE;
	}
	int ExitInstance() {
		return 0;
	}
};

CMYApp theApp;