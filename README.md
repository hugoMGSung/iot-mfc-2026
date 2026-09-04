# IoT반 MFC 추가 학습

IoT반 MS MFC 학습 리포지토리

## MFC?

![](assets/20260901_094044_image.png)

Microsoft Foundation Class 의 약자. C++ 기반의 윈도우 프로그래밍 라이브러리 중 하나.

**GUI**를 디자인, 실행하는 앱을 만들기 위해서 MS에서 만든 기술

- Linux : Qt, GTK, wxWidgets ....
- Windows : Qt, Win32API, ...

리눅스와 윈도우가 OS 기반이 다르기때문에 초기에 표준화를 못함.

Win32 API 기반으로 GUI를 라이브러리화 -> Win32 API를 C++ 클래스로 감싸놓은 라이브러리

윈도우에서만 동작하는 GUI 라이브러리 프레임워크임.

현재는 리눅스에서 Wine 에뮬레이터로 Windows 기반 GUI도 실행 가능(PC카톡 윈도우 버전)

### MFC 단점 및 장점

#### 단점

- 너무 어렵다. 최소 6개월은 공부를 해야하는 문제
- 오래된 기술로 생각보다 최신 튜토리얼이 별로 없음
- 기업이 예전부터 사용하던 솔루션 기반이 변경하기 힘들어서 계속 사용

#### 장점

- C++ 자체가 어려운데 MFC를 사용하면 복잡한 Win32 API를 직접 다루지 않아도 구현이 가능
- 생산성 향상 : 기존 C/C++ 대비하여 생산성 높다는 의미. C#, Java등 OOP와는 비교하면 안됨
- C++ 실력이 많이 좋아짐

### MFC 학습 링크

- [Microsoft Learn](https://learn.microsoft.com/ko-kr/cpp/mfc/class-library-overview?view=msvc-170)

## MFC 튜토리얼

### 순수 Win32 API로 윈도우 만들기

- 중요! Windows 32 bit에서 C++에 있는 여러 기능을 손쉽게 쓰도록 만들어놓은 API(Application Programming Interface)
- 최초에는 이를 통해서 윈도우를 직접 개발

#### Visual Studio 실행

![](assets/20260901_100429_image.png)

- Windows 데스크톱 마법사 로 시작

![](assets/20260901_100624_image.png)

- 프로젝트 이름 `Win32FirstApp` 으로 지정

![](assets/20260901_100739_image.png)

- 애플리케이션 종류
  - 콘솔 : 터미널에서 실행하는 CLI 앱
  - 데스크톱 : GUI로 실행하는 앱
  - 동적 연결 라이브러리(dll) : 다른 앱과 연결되는 라이브러리 또는 함수만 가지고 있는 패키지. 실행 후에 필요할 때 호출
  - 정적 라이브러리(lib) : dll과 거의 유사. 컴파일시에 포함되는 라이브러리

![](assets/20260901_101215_image.png)

- 데스크톱 애플리케이션 선택, 빈 프로젝트 체크 후 확인

![](assets/20260901_101313_image.png)

- 빈 프로젝트 생성

![](assets/20260901_101421_image.png)

- main.cpp 추가

#### 기본 Win32 코드 작성

![](assets/20260901_101637_image.png)

- `#include <windows.h>` 작성 후 저장 하면 위 외부 종속성 헤더파일들 추가됨. windows와 관련된 함수들을 마음대로 쓸 수 있다라는 의미

```cpp
// 윈도우 메시지를 처리하는 함수!!!!
LRESULT CALLBACK WndProc(     // LRESULT int64 타입의 포인터로 리턴
	HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
);

// 개념적
WndProc(
    현재창의 HWND,
    WM_DESTROY, // 윈도우창을 닫으라는 메시지
    추가정보,
    다른 추가정보
);
```

- LRESULT : int64 타입 LONG_PTR 포인터 크기를 의미. 32비트 OS든 64비트 OS든 기존 소스 그대로 사용하고자 만든 타입

  - Windows 메시지를 처리한 다음 Windows에게 돌려주는 결과값
- CALLBACK : 타입이 아니고 함수를 어떤 방식으로 호출할지 지정하는 매크로
- `HWND` : 윈도우 핸들. 식별번호와 참조값. 윈도우 내부 객체(포인터)를 직접 접근하면 위험함. 그래서 조금만 잘못하면 프로그램이 깨질 수 있기 때문에 핸들값으로 전달
- UINT : Unsigned Integer
- WPARAM : Word Parameter(윈도우 크기만큼의 Unsigned Integer), 메시지에 첫번째 추가 메시지 데이터.

  - 마우스 클릭시 위치값(x, y 좌표 등)
- LPARAM : Long Parameter(uint), 두번째 추가 메시지 데이터
- [소스코드 설명](./basic/MfcBasicSolution/Win32FirstApp/main.cpp)

![](assets/20260901_112026_image.png)

- 전체 작성 후 실행화면(MFC 근간)

#### 버튼 컨트롤 추가

- 소스코드

![](assets/20260901_114552_image.png)

- 버튼 및 클릭 메시지 추가 화면

![](assets/20260901_114822_image.png)

- 윈도우 스타일, 버튼 스타일 등 변경 화면

![](assets/20260901_120338_image.png)

- 텍스트 컨트롤 추가 화면

### MFC 프로젝트 생성

- Visual Studio 2026
  - 도구 > 도구 및 기능 가져오기...
- Visual Studio Installer 화면에서

![](assets/20260901_121015_image.png)

- 개별 구성 요소 추가

![](assets/20260901_121522_image.png)

- MFC 앱 선택

![](assets/20260901_121628_image.png)

- MFC 옵션 창 - 필요한 내용을 선택해야 함
  - 애플케이션 종류 - `단일 문서(SDI)`, `여러 문서(MDI)`, 대화상자 기반(Dialog) ...

![](assets/20260901_122128_image.png)

- 문서 템플릿 속성 - 기본 사용 권장

![](assets/20260901_122201_image.png)

- 사용자 인터페이스 기능 - 디자인 변경. 필요시 변경

![](assets/20260901_122225_image.png)

- 고급 기능 - 대체적으로 기본 사용

![](assets/20260901_122245_image.png)

- 생성된 클래스 - 이름 확인

![](assets/20260901_123129_image.png)

- MDI로 실행화면

### MFC 기초 학습

#### 기초 사상

순수 Win32 컨트롤 생성 함수

```cpp
HWND wnd = CreateWindow(...);
```

MFC 는 각 컨트롤을 C_ 로 미리 만들어 놓음

```cpp
CWnd
CDialog
CButton
CEdit
CStatic
```

#### 대화상자 기반 앱

![](assets/20260902_093938_image.png)

- 애플리케이션 종류 대화 상자 기반(Dialog based) 선택

![](assets/20260902_094412_image.png)

- 대화상자 기반으로 하면 대부분 옵션이 비활성화 됨

![](assets/20260902_094442_image.png)

- 시스템 메뉴, 정보 상자 도 체크 해제

![](assets/20260902_094734_image.png)

- 고급 기능도 전부 해제

![](assets/20260902_094838_image.png)

- 생성된 클래스 확인 후 마침

![](assets/20260902_095017_image.png)

- 스캐폴딩 진행 후

##### 프로젝트 구성

![](assets/20260902_100514_image.png)

- 프로그램 자체
  - MFCBasic.h
  - **MFCBasic.cpp** : 프로그램 시작점(EntryPoint)
- 화면(Dialog) UI
  - **MFCBasicDlg.h** : Dlalog 클래스 선언 헤더 파일
  - **MFCBasciDlg.cpp** : 화면 수정시 가장 많이 변경하는 파일
- 리소스 UI
  - **MFCBasic.rc** : 가장 중요한 리소스파일. 다이얼로그 UI, 메뉴, 아이콘, 툴바, 문자열 테이블, 버전, 비트맵...
  - MFCBasic.rc2 : 사용 안함, 백업과 유사
  - `Resource.h` : rc에 있는 리소스 ID를 정의
  - MFCBasic.ico : 기본 아이콘 MFC로고
- MFC 공통설정
  - pch.h
  - pch.cpp : Precompiled Header용 cpp. 수정 안함. VS가 사용하는 파일
  - framwork.h : 프로젝트 전체 사용하는 Windows 헤더 포함
  - targetver.h : 지원할 Windows 버전 지정

##### 디자인 화면

리소스 뷰(Ctrl + Shift + E) 전환 뒤, Dialog의 IDD_MFC... 클릭하면

![](assets/20260902_101142_image.png)

![](assets/20260902_101210_image.png)

- 디자인 확인 가능
- Dialog Based는 리소스에서 확인 가능하지만, SDI/MDI는 전체 화면을 확인할 메뉴/디자인뷰가 없음


| 방식         | 의미                  |     난이도 |
| ------------ | --------------------- | ---------: |
| Dialog Based | 일반 폼 형태          |         ★ |
| SDI          | 한 문서 중심 프로그램 |     ★★★ |
| MDI          | 여러 문서/창 관리     | ★★★★★ |

##### CWinApp 클래스

- MFCBasic.h 소스

```cpp

class CMFCBasicApp : public CWinApp
```

- CWinApp은 MFC가 제공하는 클래스이고 우리가 만든 CMFCBasicApp은 이를 상속한 자식 클래스

##### WinMain()이 없다! 대신 InitInstance() 가 중요!!

- MFC의 첫번째 핵심 요소! MFC에는 WinMain() 함수가 없음
- MFC가 대신 처리한다

```plaintext
# Win32 API

WinMin() 실행
     ↓
윈도우 실행
     ↓
메시지 루프
     ↓
WndProc() 
```

```plaintext
# MFC

MFC 내부 WinMain() 자동 실행
     ↓
CWinApp
     ↓
InitInstance() 
     ↓
Dialog 생성
```

- MFCBasic.cpp 소스

```cpp
// MFC 프로그램 시작시 실행되는 초기화 함수
BOOL CMFCBasicApp::InitInstance()
{
    CWinApp::InitInstance();   // 부모 객체도 초기화 한다
    ...
```

- WinMain() 에서 작성한 초기화 코드를 대부분 여기에 처리함

##### CDialogEx 클래스

- MFCBasicDlg.h 소스

```cpp
class CMFCBasicDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCBasicDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

```

- CWnd > CDialog > CDialogEx > CMFCBasicDlg

##### Win32 API와 가장 큰 차이

- Win32 API는 `HWND hwnd;` 라는 핸들을 중심으로 코딩
- MFC는 `CMFCBasicDlg dlg;` C++ 객체로 코딩. 실제 MFC 내부에 HWND 로 구성되어 있고, 이걸 MFC가 핸들링
- MFC CWnd는 Win32 API의 HWND를 C++ 클래스로 감싸 놓은 것일 뿐

#### MFC로 컨트롤 구성하기

##### 다이얼로그 리소스

![](assets/20260902_112549_image.png)

- 도구상자 오픈

![](assets/20260902_112937_image.png)

- 버튼 추가
- 속성에서
  - ID : IDC_BUTTON_OK
  - 캡션 : 확인
- 확인 버튼을 더블클릭

```cpp
void CMFCBasicDlg::OnBnClickedButtonOk()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    AfxMessageBox(L"헬로우 MFC!");
}

```

- TODO 영역을 작성하면 됨 -> C# WinForms, WPF와 동일

![](assets/20260902_113558_image.png)

- 실행결과

##### WM_COMMAND 가 없다

- MFC의 Message Map에서 처리해 줌
- MFCBasicDlg.cpp 소스
  - 버튼 추가하고 더블클릭해서 이벤트 함수가 생성되면 ON_BN_CLICKED... 자동 추가됨

```cpp
BEGIN_MESSAGE_MAP(CMFCBasicDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OK, &CMFCBasicDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()
```

##### 장점

```cpp
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
```

- 위와 쓴 코드를

```cpp
void CMFCBasicDlg::OnBnClickedButtonOk()
{
    AfxMessageBox(L"헬로우, MFC!!");
}
```

- C++ MFC로 위와 만큼 줄였다는 것이 장점
  - Win32 API -> WndProc + WM_MESSAGES + HWND
  - MFC -> CDialogEx + Message Map + CButton

#### Resource Editor

Visual Studio 가 제공하는 **GUI 디자이**너 기능. C# WinForms의 Form Designer와 같은 역할

기능은 동일하지만 C# WinForms보다 제약사항이 많고, 대부분 코딩으로 처리를 해야 함

리소스 뷰(Ctrl + Shift + E)

![](assets/20260903_093523_image.png)

- MDI의 경우에 생성되는 리소스 구조

![](assets/20260903_094731_image.png)

- STATIC, EDIT, BUTTON 세개로 구성
- MFC에서 추천하는 이름은 일반적으로 IDC_ Prefix 사용

##### ID가 가장 중요

ID로 코드에서 제어

##### 탭 오더

윈폼 탭으로 컨트롤 이동시 순서 지정

디자인 레이아웃 창에서 Ctrl + D

![](assets/20260903_095240_image.png)

- 번호를 클릭해서 변경

##### 로그인 화면 만들기

![](assets/20260903_102108_image.png)

- STATIC 2개, EDIT 2개, BUTTON 2개 구성
- 디자인 후 Resource.h 확인

```cpp
//{{NO_DEPENDENCIES}}
// Microsoft Visual C++에서 생성한 포함 파일입니다.
// MFCControls.rc에서 사용되고 있습니다.
//
#define IDC_BTN_LOGIN                   2
#define IDD_MFCCONTROLS_DIALOG          102
#define IDR_MAINFRAME                   128
#define IDC_EDIT_ID                     1000
#define IDC_STATIC_ID                   1002
#define IDC_STATIC_PW                   1003
#define IDC_EDIT_PW                     1004
#define IDC_BTN_CANCEL                  1005
```

##### 이벤트 처리

```cpp
	// 컨트롤에 있는 캡션을 변수 할당
	CString strID;
	GetDlgItemText(IDC_EDIT_ID, strID);

	CString strPW;
	GetDlgItemText(IDC_EDIT_PW, strPW);

	// 입력검증(Validation Check)
	if (strID.IsEmpty()) {
		AfxMessageBox(L"아이디를 입력하세요.");
		return;
	}

	if (strPW.IsEmpty()) {
		AfxMessageBox(L"패스워드를 입력하세요.");
		return;
	}

	//AfxMessageBox(strID);

	if (strID == L"admin" && strPW == L"p@ssw0rd!") {
		AfxMessageBox(L"관리자 로그인!");
	}
	else {
		AfxMessageBox(L"로그인 실패!!!");
	}

	//CString msg;
	//msg = strID + L"님 환영합니다!!";

	//AfxMessageBox(msg);
```

![](assets/20260903_103900_image.png)

- 관리자 로그인 처리
- 입력검증 ID, PW

![](assets/20260903_104448_image.png)

- 실행결과

#### DDX / DDV

```csharp
TxtName.Text // C# 방식
```

- C# 방식. 아주 간단

```cpp
UpdateData(TRUE);
```

- MFC 방식

##### 현재 예제 문제점

만약 컨트롤이 20개 있으면

```cpp
GetDlgItemText(IDC_..., var1);
GetDlgItemText(IDC_..., var2);
GetDlgItemText(IDC_..., var3);
GetDlgItemText(IDC_..., var4);
GetDlgItemText(IDC_..., var5);
GetDlgItemText(IDC_..., var6);
....
GetDlgItemText(IDC_..., var20);
```

이런 불편한 점을 개선한것이 DDX

- Dialog와 변수 사이의 데이터를 자동으로 교환하는 기능

##### 로그인 예제를 DDX로 변경

![](assets/20260903_111133_image.png)

- 다이얼로그 Context Menu > 변수 추가 선택

![](assets/20260903_111243_image.png)

- ID Edit 컨트롤 선택 상태에서 > Context Menu > 변수 추가

![](assets/20260903_111631_image.png)

- 아이디 컨트롤 내 값 담을 수 있는 변수 추가

```cpp
public:
	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnBnClickedBtnCancel();
	// 아이디 값 변수
	CString m_editID;
	// 패스워드 변수 값
	CString m_editPW;
};
```

- MFCControlsDlg.h에 위와 같이 추가 확인

```cpp
void CMFCControlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_editID);
	DDX_Text(pDX, IDC_EDIT_PW, m_editPW);
}

```

- MFCControlsDlg.cpp 에 DoDataExchange() 함수에 추가된 내용 확인
- OnBnClickedBtnLogin() 함수내 작성 내용 삭제

```cpp
UpdateData(TRUE);

AfxMessageBox(m_editID);
```

- GetDlgItemText() 가 컨트롤별로 수행할 필요가 없음
- UpdateData(TRUE) : 데이터 읽기
- UpdateData(FALSE) : 데이터 쓰기

여기까지가 DDX Value로 처리하는 방식임

##### DDX Control

변수값이 아닌 컨트롤 자체를 제어하고자 할때 사용

- 로그인을 성공하고 난뒤 아이디 입력창 비활성화
- 포커스 이동

과 같은 작업에 DDX Control 사용

- 다이얼로그 창 > Context Menu > 변수 선택
- 범주 컨트롤 선택, m_controlID, m_controlPW 추가
- 로그인 버튼, m_btnLogin 로 변수 추가

```cpp
	DDX_Control(pDX, IDC_EDIT_ID, m_controlID);
	DDX_Control(pDX, IDC_EDIT_PW, m_controlPW);
	DDX_Control(pDX, IDC_BTN_LOGIN, m_btnLogin);
```

- DoDataExchange() 함수에 추가된 로직 확인

![](assets/20260903_114634_image.png)

- SetWindowText() : 실행 후 로그인 버튼 클릭하면, IDC_EDIT_ID 컨트롤에 admin 텍스트 할당

![](assets/20260903_114847_image.png)

- GetWindowText() : 컨트롤의 텍스트를 변수에 할당, GetDlgItemText()와 동일

##### DDV

Dialog Data Validation. 컨트롤에 제대로 된 입력값이 들어갔는지 검증

```cpp
void CMFCControlsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
...
    // ID를 20자로 제한!
    DDV_MaxChars(pDX, m_editID, 20);
}
```

![](assets/20260903_121631_image.png)

- 아이디를 20자 이상 입력했을때 실행화면
- DDV 함수 종류 : DDV_MinMaxInt(), DDV_MinMaxUInt(), DDV_MinMaxDouble(),


#### 회원로그인 화면 만들기

![](assets/20260904_092958_image.png)

- Static 3 개 : IDC_STATIC_ID, IDC_STATIC_PW(사용X), IDC_STATIC_STATUS(소스코드 사용)
- Edit 2 개 : IDC_EDIT_ID, IDC_EDIT_PW
- CheckBox 1개 : IDC_CHK_AUTOLOGIN
- Radio Button 2개 : IDC_RDO_USER(첫번째 라디오버튼 그룹 속성을 True), IDC_RDO_ADMIN(그룹 속성 False)
- Button 2개 : IDC_BTN_LOGIN, IDC_BTN_CANCEL

##### DDX(Value) 설정

- 아이디, 패스워트 텍스트박스, 자동 로그인, 라디오 버튼 값 DDX 생성
  - IDC_EDIT_ID : CString m_strID
  - IDC_EDIT_PW : CString m_strPW
  - IDC_CHK_AUTOLOGIN : BOOL m_bAutoLogin
  - IDC_RDO_USER : int m_nUserType

##### DDX(Control) 설정

- 로그인 버튼, 아이디 에디트, 상태 스태틱 컨트롤 DDX 추가
  - IDC_EDIT_ID : CEdit m_editID
  - IDC_STATIC_STATUS : CStatic m_staticStatus
  - IDC_BTN_LOGIN : CButton m_btnLogin



#### MFC 학습 순서

1. [X]  Dialog Based MFC
2. [X]  CWinApp / CDialogEx 이해
3. [X]  Resource Editor
4. [X]  Button / Static / Edit / CheckBox / Radio Button 컨트롤 학습
5. [X]  컨트롤 사용 간단 프로젝트
6. [X]  Message Map 이해
7. [X]  이벤트 처리 방법 이해
8. [X]  컨트롤 값 읽기 / 쓰기
9. [X]  DDX / DDV
10. [ ]  Timer
11. [ ]  메뉴 / 파일 Dialog
12. [ ]  SDI(Single Document Interface)
13. [ ]  MDI(Multiple DI)
14. [ ]  GDI(Graphic Device Interface) : 원, 사각형 그래픽 그리기
15. [ ]  스레드...
16. [ ]  토이프로젝트 : 메모장(NotePad) 프로젝트
