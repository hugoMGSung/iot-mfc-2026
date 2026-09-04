
// MFCControlsDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCControls.h"
#include "MFCControlsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCControlsDlg 대화 상자



CMFCControlsDlg::CMFCControlsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCONTROLS_DIALOG, pParent)
	, m_strID(_T(""))
	, m_strPW(_T(""))
	, m_bAutoLogin(FALSE)
	, m_nUserType(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCControlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPW);
	DDX_Check(pDX, IDC_CHK_AUTOLOGIN, m_bAutoLogin);
	DDX_Radio(pDX, IDC_RDO_USER, m_nUserType);

	DDX_Control(pDX, IDC_EDIT_ID, m_editID);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_staticStatus);
	DDX_Control(pDX, IDC_BTN_LOGIN, m_btnLogin);
}

BEGIN_MESSAGE_MAP(CMFCControlsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CMFCControlsDlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CMFCControlsDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CMFCControlsDlg 메시지 처리기

BOOL CMFCControlsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 코드로 닫기버튼 추가!
	ModifyStyle(
		0,
		WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX |
		WS_THICKFRAME |
		WS_SYSMENU
	);

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCControlsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCControlsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCControlsDlg::OnBnClickedBtnLogin()
{
	UpdateData(TRUE);

	if (m_strID.IsEmpty()) {
		AfxMessageBox(L"아이디를 입력하세요.");
		m_editID.SetFocus(); // 포커스 재지정
		return;
	}

	// 실제 DB와 연동 
	if (m_nUserType == 0) {
		// 사용자
		//AfxMessageBox(L"사용자 권한");
		if (m_strID == L"hugo" && m_strPW == "p@ssw0rd") {
			if (m_bAutoLogin) {
				AfxMessageBox(L"사용자(자동 로그인), " + m_strID + L" 로그인 성공!!!");
				m_staticStatus.SetWindowTextW(L"상태 : 로그인 성공");
			}
			else {
				AfxMessageBox(L"사용자(수동 로그인), " + m_strID + L" 로그인 성공!!!");
				m_staticStatus.SetWindowTextW(L"상태 : 로그인 성공");
			}
			return;
		}
		else {
			AfxMessageBox(L"사용자 로그인 실패!");
			m_staticStatus.SetWindowTextW(L"상태 : 로그인 실패");
			return;
		}
	}
	else {
		//AfxMessageBox(L"관리자 권한");

		if (m_strID == L"admin" && m_strPW == L"123456") {
			// 관리자 로그인 성공
			AfxMessageBox(L"관리자 로그인 성공!!!");
			return;
		}
		else {
			// 관리자 로그인 실패
			AfxMessageBox(L"관리자 로그인 실패!");
			return;
		}
	}	
}

void CMFCControlsDlg::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다
	CDialogEx::OnCancel();
}
