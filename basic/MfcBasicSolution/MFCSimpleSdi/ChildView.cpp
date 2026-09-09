
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCSimpleSdi.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


// ChildView에서만 마우스 위치, 이벤트처리하려면 여기 작성
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()

	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
	CString str = L"MFC ChildView CString";
	dc.TextOutW(100, 100, str);

	// GDI
	dc.MoveTo(100, 80); // 선이 시작할 위치로 이동
	dc.LineTo(330, 80); // 좌표까지 직선 그리기

	dc.Rectangle(100, 120, 300, 300);
	dc.Ellipse(100, 120, 300, 300);

	CPen pen;   // 펜 생성
	pen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));

	dc.SelectObject(&pen);  // 펜 선택

	dc.MoveTo(100, 340);
	dc.LineTo(330, 340);

	dc.Ellipse(
		m_ptClick.x - 30,
		m_ptClick.y - 30,
		m_ptClick.x + 30,
		m_ptClick.y + 30
	);  // 마우스 클릭시마다 원 변경

	CPen pen2;   // 펜 생성
	pen2.CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
	dc.SelectObject(&pen2);  // 펜 선택

	dc.Ellipse(
		m_ptCircle.x - 30,
		m_ptCircle.y - 30,
		m_ptCircle.x + 30,
		m_ptCircle.y + 30
	);

	dc.Rectangle(m_ptBox.x, m_ptBox.y, m_ptBox.x + 100, m_ptBox.y + 50);
}

/* afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point); */


void CChildView::OnLButtonDown(UINT nFlags, CPoint point) {
	CString str;
	str.Format(L"(%d, %d)", point.x, point.y);	
	// AfxMessageBox(str);

	m_ptClick = point;

	m_bDrag = true;

	Invalidate();  // 화면 다시그리기 요청 함수

	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point) {
	m_bDrag = false;
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point) {
	CString str;

	str.Format(L"x=%d, y=%d", point.x, point.y);
	GetParent()->SetWindowText(str); // 부모창(MainFrame)의 제목표시줄에 str를 할당

	if (m_bDrag) {
		m_ptCircle = point;

		Invalidate();  // 화면 업데이트
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point) {
	AfxMessageBox(L"Right Button Clicked");
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	//CString str;
	//str.Format(L"Key=%d", nChar);

	//AfxMessageBox(str);
	switch (nChar) {
	case VK_LEFT:
		m_ptBox.x -= 10;
		break;
	case VK_RIGHT:
		m_ptBox.x += 10;
		break;
	case VK_UP:
		m_ptBox.y -= 10;
		break;
	case VK_DOWN:
		m_ptBox.y += 10;
		break;
	}

	Invalidate();  // 화면 다시그리기 요청 함수

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//AfxMessageBox(L"Key Up");

	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//CString str;
	//str.Format(L"Key=%d", nChar);

	//AfxMessageBox(str);

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}
