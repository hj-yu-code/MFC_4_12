#include <afxwin.h>
#include "resource.h"
// ��ü�� �����ϴ� ������ ����
// factory design pattern

class A : public CObject {
	// DECLARE_DYNAMIC(A); // ��Ȯ�� �����͸� ���ؼ� �Է��ؾ� ��
	// DECLARE_DYNAMIC : CObject::IsKindOf()�� ���� ����
	
	//DECLARE_DYNCREATE(A); // CObject::IsKindOf(), ��ü ������ �Ϲ�ȭ�� ���� : CRuntimeClass::CreateObject()
	
	DECLARE_SERIAL(A); // CObject::IsKindOf(), ��ü ������ �Ϲ�ȭ�� ���� : CRuntimeClass::CreateObject(), CObject::Serialize()
	// CObject::Serialize() : '����ҿ� �����ϰ�, �б� ��� ����' ȣ�� ����

private:
	int a;
	int b;
public:
	A() : a(100), b(100) {
		TRACE("A() ������ ȣ��\n");
	}
	~A() {
		TRACE("~A() �Ҹ��� ȣ��\n");
	}

	int add(int a, int b) {
		TRACE("A::add() ȣ�� = %d\n", (this->a + this->b + a + b));
		return this->a + this->b + a + b;
	}
	//// static Ŭ������ ���ؼ� ���� ����: factory
	//static A* CreateObject() {
	//	return new A;
	//}
};

class B : public CObject {
	DECLARE_DYNAMIC(B);
private:
	int b;
public:
	B() : b(200) {
		TRACE("B() ������ ȣ��\n");
	}
	~B() {
		TRACE("B() �Ҹ��� ȣ��\n");
	}
	int add(int a, int b) {
		return a + b;
	}
	int sub(int a, int b) {
		TRACE("B::sub() ȣ�� = %d\n", (this->b + (a - b)));
		return this->b + (a - b);
	}
};

/*
IMPLEMENT (����) : �ǹ̸� �ο��� ��ũ��
IMPLEMENT_DYNCREATE�� �ϰ� �Ǹ� 

A::CreateObject() {
	return new A;
}
�� �߰������� ������ ����
*/

// IMPLEMENT_DYNAMIC(A, CObject); // ��Ȯ�� �����͸� ���ؼ� �Է��ؾ� ��
// IMPLEMENT_DYNAMIC(B, CObject);
// IMPLEMENT_DYNAMIC : �θ� �ڽ� ������ ����� �����

// IMPLEMENT_DYNCREATE(A, CObject);
// �θ� �ڽ� ������ ����� �����, ���� ������ �Ϲ�ȭ�� ���� �Լ� ����

IMPLEMENT_SERIAL(A, CObject, 1)
// �θ� �ڽ� ������ ����� �����, ���� ������ �Ϲ�ȭ�� ���� �Լ� ����, �б� ���⿡ ���� ����� ���� �� ��� ����

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


		CObject* pObj = nullptr;
		// pObj = new A; // Ư��ȭ
		CRuntimeClass* pClass = RUNTIME_CLASS(A);
		// MFC���� factory �������� class ��ü ����
		pObj = pClass->CreateObject(); // �Ϲ�ȭ

		pClass = RUNTIME_CLASS(B);
		pObj = pClass->CreateObject(); // �Ϲ�ȭ




		// CObject* pObj = NULL; // C style
		// NULL : int type
		CObject* pObj = nullptr; // C++ style
		// nullptr : void type
		pObj = new A; // Ư��ȭ : A��� �����Ǿ� �ֱ� ����
		if (pObj->IsKindOf(RUNTIME_CLASS(A))) { // IsKindOf : object type �Ǻ�
			((A*)pObj)->add(10, 20);
		}
		else if (pObj->IsKindOf(RUNTIME_CLASS(B))) {
			((B*)pObj)->sub(10, 20);
		}
		else {
			TRACE("abababababab\n");
		}

		delete pObj;

		pObj = new B;
		if (pObj->IsKindOf(RUNTIME_CLASS(A))) {
			((A*)pObj)->add(10, 20);
		}
		else if (pObj->IsKindOf(RUNTIME_CLASS(B))) {
			((B*)pObj)->sub(10, 20);
		}
		else {
			TRACE("abababababab\n");
		}
		delete pObj;

		/*
		��ü ���� ���
		1. A obj;
			A obj(); // �ȵ�! �Լ��������� �ν�! �Լ���: obj / return type: A
			A obj{}; // ���� ��õ�ϴ� ���
		2. A* pObj = new A();
			A* pObj = new A;
			A* pObj = new A{}; // ���� ��õ�ϴ� ���

		RTTI -> RunTime Type Information

		CObject () : �ְ� ��� Ŭ����

		*/

		return TRUE;
	}
	int ExitInstance() {
		return 0;
	}
};

CMYApp theApp;