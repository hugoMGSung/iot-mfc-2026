#include <Windows.h>

// 윈도우 메시지를 처리하는 함수!!!!
// WndProc 함수 선언
LRESULT CALLBACK WndProc(		// LRESULT int64 타입의 포인터로 리턴
	HWND hwnd,					// 윈도우 핸들
	UINT message,				// 
	WPARAM wParam,				// 윈도우프로시저 첫번째 메시지 추가정보
	LPARAM lParam				// 두번째 메시지 추가정보
);

// console int main() 와 동일
int WINAPI WinMain(
	HINSTANCE hInstance,		// 현재 프로그램 객체 인스턴스(핸들)
	HINSTANCE hPrevInstance,	// 이전 핸들(예전 Win16 호환용) - 우리는 사용 안함
	LPSTR lpCmdLine,			// *char - 문자열 : 실행 명령줄
	int nCmdShow				// 윈도우 표시 방법
) {
	// 앞으로 이 형태로 윈도우를 만들겠다는 선언
	WNDCLASS wc = {};  // 윈도우 스타일을 지정하는 여러 속성이 담긴 구조체

	// 메시지가 발생하면 WndProc에서 처리하라는 뜻
	wc.lpfnWndProc = WndProc;	// 내가 만든 윈도우프로시저 콜백을 할당. 이거 써서 윈도우를 처리해
	wc.hInstance = hInstance;	// 현재 핸들 인스턴스 할당. 내 윈도우를 알려주는 기능
	wc.lpszClassName = L"MyWindowClass";  // 내 윈도우 클래스명 이 이름을 C++ 내에서 사용
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);  // 마우스 커서 모양 지정
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW); // 윈도우의 배경색 지정

	RegisterClass(&wc);    // 클래스 등록 MyWindowClass라는 이름으로 윈도우 클래스를 등록하라

	// 실제 윈도우 생성
	HWND hwnd = CreateWindow(
		L"MyWindowClass", 
		L"첫번째 윈도우",			// 제목 표시줄에 제목
		WS_OVERLAPPEDWINDOW,		// 윈도우 창 스타일 지정
		CW_USEDEFAULT,				// 윈도우 표시할 x좌표 
		CW_USEDEFAULT,				// 윈도우 표시할 y좌표
		800,						// 윈도우 width
		480,						// 윈도우 height
		NULL,						// 부모 핸들값
		NULL,						// 메뉴 핸들값
		hInstance,					// 현재 윈도우의 인스턴스핸들값
		NULL 						// 추가 메시지 파라미터
	);

	if (hwnd == NULL) {
		return 0;   // 프로그램 종료
	}

	ShowWindow(hwnd, nCmdShow);		// 윈도우 보이고
	UpdateWindow(hwnd);				// 업데이트. 화면 즉시 갱신. 변화한게 있으면 바로 표시

	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0)) {  // 메시지 계속 대기
		TranslateMessage(&msg);		// 메시지 변환
		DispatchMessage(&msg);		// WndProc() 함수로 전달
	}

	return (int)msg.wParam;         // 프로그램 종료 코드를 OS에 반환!
}

// 위에서 선언한 WndProc() 구현
LRESULT CALLBACK WndProc(
	HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (message) {
	case WM_DESTROY:   // 윈도우 종료 메시지가 넘어오면
		PostQuitMessage(0);   // GetMessage() 0으로 처리
		return 0;
	}

	return DefWindowProc(
		hwnd,
		message,
		wParam,
		lParam
	);
}