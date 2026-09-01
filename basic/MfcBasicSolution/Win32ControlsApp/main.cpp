#include <Windows.h>

LRESULT CALLBACK WndProc(
	HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
);

int WINAPI WinMain(
	HINSTANCE hInstance,		
	HINSTANCE hPrevInstance,	
	LPSTR lpCmdLine,			
	int nCmdShow				
) {
	WNDCLASS wc = {};
	
	wc.lpfnWndProc = WndProc;	
	wc.hInstance = hInstance;	
	wc.lpszClassName = L"MyWindowClass";  
	wc.hCursor = LoadCursor(NULL, IDC_HAND);  
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 20); 

	RegisterClass(&wc);    
	
	HWND hwnd = CreateWindow(
		L"MyWindowClass",
		L"두번째 윈도우",			
		WS_OVERLAPPEDWINDOW,		
		CW_USEDEFAULT,				
		CW_USEDEFAULT,				
		800,						
		480,						
		NULL,						
		NULL,						
		hInstance,					
		NULL 						
	);

	if (hwnd == NULL) {
		return 0;   
	}

	ShowWindow(hwnd, nCmdShow);		
	UpdateWindow(hwnd);				

	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0)) {  
		TranslateMessage(&msg);		
		DispatchMessage(&msg);		
	}

	return (int)msg.wParam;         
}

LRESULT CALLBACK WndProc(
	HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (message) {
	case WM_CREATE:  // 윈도우가 생성되면

		// 1. 버튼도 CreateWindow() 함수 사용 - 버튼도 사실 하나의 Window임
		CreateWindow(
			L"BUTTON",
			L"확인",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			240,
			150,
			100,
			40,
			hwnd,
			(HMENU)1001,
			NULL,
			NULL
		);

		// 2. 텍스트 추가
		CreateWindow(
			L"STATIC",
			L"Hello, Win32API!",
			WS_CHILD | WS_VISIBLE,
			210,
			80,
			200,
			30,
			hwnd,
			NULL,
			NULL,
			NULL
		);
		return 0;

	case WM_COMMAND:
		if (LOWORD(wParam) == 1001) {
			MessageBox(
				hwnd,
				L"버튼을 클릭했습니다.",
				L"알림",
				MB_OKCANCEL
			);
		}
		return 0;

	case WM_DESTROY:   
		PostQuitMessage(0);   
		return 0;
	}

	return DefWindowProc(
		hwnd,
		message,
		wParam,
		lParam
	);
}