#include <afxwin.h>
#include "resource.h"
// 객체를 생성하는 디자인 패턴
// factory design pattern

class A : public CObject {
	// DECLARE_DYNAMIC(A); // 정확한 데이터를 위해서 입력해야 함
	// DECLARE_DYNAMIC : CObject::IsKindOf()을 위한 선언
	
	//DECLARE_DYNCREATE(A); // CObject::IsKindOf(), 객체 생성의 일반화를 제공 : CRuntimeClass::CreateObject()
	
	DECLARE_SERIAL(A); // CObject::IsKindOf(), 객체 생성의 일반화를 제공 : CRuntimeClass::CreateObject(), CObject::Serialize()
	// CObject::Serialize() : '저장소에 저장하고, 읽기 기능 제공' 호출 가능

private:
	int a;
	int b;
public:
	A() : a(100), b(100) {
		TRACE("A() 생성자 호출\n");
	}
	~A() {
		TRACE("~A() 소멸자 호출\n");
	}

	int add(int a, int b) {
		TRACE("A::add() 호출 = %d\n", (this->a + this->b + a + b));
		return this->a + this->b + a + b;
	}
	//// static 클래스를 통해서 제작 가능: factory
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
		TRACE("B() 생성자 호출\n");
	}
	~B() {
		TRACE("B() 소멸자 호출\n");
	}
	int add(int a, int b) {
		return a + b;
	}
	int sub(int a, int b) {
		TRACE("B::sub() 호출 = %d\n", (this->b + (a - b)));
		return this->b + (a - b);
	}
};

/*
IMPLEMENT (구현) : 의미를 부여한 메크로
IMPLEMENT_DYNCREATE를 하게 되면 

A::CreateObject() {
	return new A;
}
가 추가적으로 생생된 것임
*/

// IMPLEMENT_DYNAMIC(A, CObject); // 정확한 데이터를 위해서 입력해야 함
// IMPLEMENT_DYNAMIC(B, CObject);
// IMPLEMENT_DYNAMIC : 부모 자식 관계의 연결고리 만들기

// IMPLEMENT_DYNCREATE(A, CObject);
// 부모 자식 관계의 연결고리 만들기, 개게 생성의 일반화에 대한 함수 제공

IMPLEMENT_SERIAL(A, CObject, 1)
// 부모 자식 관계의 연결고리 만들기, 개게 생성의 일반화에 대한 함수 제공, 읽기 쓰기에 대한 기능을 제공 및 사용 가능

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
		// pObj = new A; // 특별화
		CRuntimeClass* pClass = RUNTIME_CLASS(A);
		// MFC에서 factory 형식으로 class 객체 생성
		pObj = pClass->CreateObject(); // 일반화

		pClass = RUNTIME_CLASS(B);
		pObj = pClass->CreateObject(); // 일반화




		// CObject* pObj = NULL; // C style
		// NULL : int type
		CObject* pObj = nullptr; // C++ style
		// nullptr : void type
		pObj = new A; // 특별화 : A라고 고정되어 있기 때문
		if (pObj->IsKindOf(RUNTIME_CLASS(A))) { // IsKindOf : object type 판별
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
		객체 생성 방법
		1. A obj;
			A obj(); // 안됨! 함수선언으로 인식! 함수명: obj / return type: A
			A obj{}; // 요즘 추천하는 방식
		2. A* pObj = new A();
			A* pObj = new A;
			A* pObj = new A{}; // 요즘 추천하는 방식

		RTTI -> RunTime Type Information

		CObject () : 최고 기반 클래스

		*/

		return TRUE;
	}
	int ExitInstance() {
		return 0;
	}
};

CMYApp theApp;