// #include <iostream>
// using namespace std;
#include <afxwin.h>
// mfc에서 사용하는 헤더 파일

// 콘솔 응용프로그램의 진입점 : main
//int main(int argc, char** argv) {
//	return 0;
//}

// 윈도우 응용프로그램 -> C style
//BOOL WinMain(...) {
//	return 0;
//}

// 윈도우 응용 프로그램 클래스로 사용하는 경우
//CWinApp : 응용프로그램을 담당하는 클래스
class CMyApp : public CWinApp {
public:
	virtual BOOL InitInstance() override{ // 진입점 : 시작함수
		// CWinApp에 virtual 함수로 정의 되어 있음
		// cout << "hello world" << endl;
		// cout : 콘솔 출력 장치 -> 윈도우에서는 쓸수가 없음

		TRACE("hello world\n"); // TRACE : 디버깅으로 실행될 때만 동작
		TRACE("InitInstance() 호출됨\n");
		// 실행 : F5 -> 디버깅 : 출력으로 나타남
		// 실행 : ctrl + F5 -> 디버깅 하지 않고 시작

		// 문자
		// char : 1byte
		// wchar_t : 2byte

		char p1[] = "Hello World";
		wchar_t p2[] = L"Hello World";
		// MFC는 기존과 다른게 2가지 문자 타입을 가짐

//#ifdef _UNICODE
//	#define TCHAR wchar_t
//	#define _T(str) L(str)
//#else
//	#define TCHAR char
//	#define _T(str) str
//#endif // _UNICODE
	// 내부적으로 구성되어 있음

		//TCHAR p[] = _T("Hello World");
		// _UNICODE 일때 : wchar_t* p1 = L"Hello World";
		// 일반적일 때 : char* p1 = "Hello World";
		// 
		// unicode 설정 : 속성 - 고급 - 문자 집합 - 유니코드 문자 집합 사용
		// 그외 설정 : 속성 - 고급 - 문자 집합 - 설정 안 함 / 멀티바이트 문자 집합 사용

		// 문자열
		//char* str;
		//char str[]; //-> LPSTR
		// L : long(아무의미없음) / P : pointer / STR : string
		// near pointer (64K) -> 현재는 사라짐
		// long pointer (64K 이상)
		
		// const char* // -> LPCSTR
		// L : long(아무의미없음) / P : pointer / C : const / STR : string

		//wchar_t* wtsl;
		//wchar_t wstr2[]; // -> LPWSTR
		// L : long(아무의미없음) / P : pointer / W : wide / STR : string

		// LPCTSTR : const char*, const wchar_t*
		// LPTSTR : char*, wchar_t*

		/*long LONG
		short SHORD
		unsigned short WORD
		unsigned int DWORD;*/

		//AfxMessageBox(L"hello world"); // unicode
		//AfxMessageBox("hello world");  // ansi code
		AfxMessageBox(_T("hello world")); // MFC 함수 (Win32API로 짜져있음)

		::MessageBox(NULL, _T("hello world"), _T("step2"), MB_OK); // Win32API 버전 template
		// 부모 윈도우가 없으므로 첫번째 인자에 NULL 작성
		// 
		//::MessageBoxW(); // Win32API 버전 -> unicode
		//::MessageBoxA(); // Win32API 버전 -> ansi code
		// unicode와 ansi code가 따로 구현되어 있음


		return TRUE; // 응용 프로그램이 자동으로 종료됨


	}
	virtual int ExitInstance() override { // 종료시점
		// CWinApp에 virtual 함수로 정의 되어 있음
		TRACE("ExitInstance() 호출됨\n");

		return 0;
	}
};
CMyApp theApp; // 전역 객체 생성

/*
별도의 설정 필요
프로젝트 - 속성
 - 구성 : 모든 구성, 플랫폼 : 모든 플랫폼
 - 고급 - MFC 사용 - 공유 DLL에서 MFC 사용
 - 링커 - 시스템 - 하위 시스템 - 창(/SUBSYSTEM:WINDOWS) // 진입점을 WinMain으로 수정
*/