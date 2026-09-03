
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
	, m_editID(_T(""))
	, m_editPW(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCControlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_editID);
	DDX_Text(pDX, IDC_EDIT_PW, m_editPW);

	DDX_Control(pDX, IDC_EDIT_ID, m_controlID);
	DDX_Control(pDX, IDC_EDIT_PW, m_controlPW);
	DDX_Control(pDX, IDC_BTN_LOGIN, m_btnLogin);

	// ID를 20자로 제한!
	DDV_MaxChars(pDX, m_editID, 20);
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
	UpdateData(TRUE); // DDX! GetDlgItemText() 함수 호출 대체

	//// 입력검증(Validation Check)
	if (m_editID.IsEmpty()) {
		AfxMessageBox(L"아이디를 입력하세요.");
		return;
	}

	if (m_editPW.IsEmpty()) {
		AfxMessageBox(L"패스워드를 입력하세요.");
		return;
	}

	//AfxMessageBox(strID);

	if (m_editID == L"admin" && m_editPW == L"p@ssw0rd!") {
		AfxMessageBox(L"관리자 로그인!");
	}
	else {
		AfxMessageBox(L"로그인 실패!!!");
	}
}

void CMFCControlsDlg::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
