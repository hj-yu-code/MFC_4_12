#include <afxwin.h>
#include "resource.h"

class CMainFrame : public CFrameWnd {
public:
	DECLARE_DYNCREATE(CMainFrame); // RUNTIME_CLASS�� ���� ����

};

/*
Document/View
MVC
	Model (Document)
	View
	Controller (����)

Document : Data ������ ���� (������, ����, ����)
View : ȭ�鿡 ���

*/


class CMyDoc : public CDocument {
public:
	DECLARE_DYNCREATE(CMyDoc);
	//������ ��� ���� �Լ� 
	virtual BOOL OnNewDocument() override {
		return TRUE;
	}
	//���Ͽ� �б�/���⸦ ����ϴ� �Լ� 
	virtual void Serialize(CArchive& ar) override {

	}
};

class CMyView : public CView {
public:
	DECLARE_DYNCREATE(CMyView);
	//ȭ�� ��¿� ���� �Լ�
	virtual void OnDraw(CDC* pDC) override {

	}
};

// ��ũ�θ� �̿��� ��ü ������ ���õ� �Լ� ����
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

		// Doc/View ����
		// Document/View ����
		// - ���� ����
		// - ���� ����
		// ����� ���� ������ ������

		CSingleDocTemplate* pDocTemplate;
		pDocTemplate = new CSingleDocTemplate(IDR_MAIN_FRAME,
			RUNTIME_CLASS(CMyDoc), // CRutimeClass : Document ����
			RUNTIME_CLASS(CMainFrame), // �˷��ֱ�
			RUNTIME_CLASS(CMyView)
			);

		if (pDocTemplate == nullptr) {
			return FALSE;
		}

		// Doc/View ���� ��ü�� �����
		AddDocTemplate(pDocTemplate);
		// Animal class�� �߰��ϴ� �Ͱ� ������ ��

		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		if (!ProcessShellCommand(cmdInfo)) { // ���α׷��� ���������� Ȯ��
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