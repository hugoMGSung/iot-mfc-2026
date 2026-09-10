
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCNotePad.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <vector>

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CMainFrame::OnFileSave)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 프레임의 클라이언트 영역을 차지하는 뷰를 만듭니다.
	if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("뷰 창을 만들지 못했습니다.\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 뷰 창으로 포커스를 이동합니다.
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 뷰에서 첫째 크랙이 해당 명령에 나타나도록 합니다.
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 그렇지 않으면 기본 처리합니다.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnFileOpen()
{
	CFileDialog dlg(
		TRUE,
		L"txt",
		NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		L"텍스트 파일 (*.txt)|*.txt||");

	if (dlg.DoModal() != IDOK)
		return;

	CString strPath;
	strPath = dlg.GetPathName();

	CFile file;

	if (!file.Open(strPath, CFile::modeRead)) {
		AfxMessageBox(L"파일을 열 수 없습니다.");
		return;
	}

	DWORD size = (DWORD)file.GetLength();
	std::vector<BYTE> buffer(size);
	file.Read(buffer.data(), size);

	file.Close();

	// UTF-8인지 EUC-KR인지 검사
	bool bUTF8 = false;
	int offset = 0;

	if (size >= 3 &&
		buffer[0] == 0xEF &&
		buffer[1] == 0xBB &&
		buffer[2] == 0xBF)
	{
		bUTF8 = true;
		offset = 3;
	}

	CString strText;

	if (bUTF8) {
		int len = MultiByteToWideChar(
			CP_UTF8,
			0,
			(LPCCH)(buffer.data() + offset),
			size - offset,
			NULL,
			0);

		MultiByteToWideChar(
			CP_UTF8,
			0,
			(LPCCH)(buffer.data() + offset),
			size - offset,
			strText.GetBuffer(len),
			len);

		strText.ReleaseBuffer(len);
	}
	else {
		int len = MultiByteToWideChar(
			CP_ACP,
			0,
			(LPCCH)buffer.data(),
			size,
			NULL,
			0);

		MultiByteToWideChar(
			CP_ACP,
			0,
			(LPCCH)buffer.data(),
			size,
			strText.GetBuffer(len),
			len);

		strText.ReleaseBuffer(len);
	}

	m_wndView.SetText(strText);  // ChildView에 추가한 함수 호출
}

void CMainFrame::OnFileSave()
{
	CFileDialog dlg(
		FALSE,   
		L"txt",
		L"NewFile.txt",    // 기본 이름
		OFN_OVERWRITEPROMPT,
		L"텍스트 파일 (*.txt)|*.txt||");

	if (dlg.DoModal() != IDOK)
		return;

	CString strPath = dlg.GetPathName();

	CString strText = m_wndView.GetText();

	CStringA utf8 = CW2A(strText, CP_UTF8);
	CFile file;

	if (!file.Open(strPath, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox(L"파일 저장 실패!");
		return;
	}

	// UTF-8 BOM
	BYTE bom[] = { 0xEF, 0xBB, 0xBF };
	file.Write(bom, sizeof(bom));

	file.Write(
		utf8.GetString(),
		utf8.GetLength());

	file.Close();

	AfxMessageBox(L"저장되었습니다.");
}
