
// MFCThreadBasicDlg.h: 헤더 파일
//

#pragma once


// CMFCThreadBasicDlg 대화 상자
class CMFCThreadBasicDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCThreadBasicDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTHREADBASIC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnThread();

	afx_msg LRESULT OnProgressUpdate(WPARAM wParam, LPARAM lParam);

	// 멤버함수는 this 포인터 전달.
	// AfxBeginThread() 는 일반 함수 주소를 필요로 함
	// static으로 선언
	static UINT ThreadProc(LPVOID pParam);
	CProgressCtrl m_progress;
};
