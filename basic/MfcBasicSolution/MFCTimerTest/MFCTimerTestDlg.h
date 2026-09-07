
// MFCTimerTestDlg.h: 헤더 파일
//

#pragma once


// CMFCTimerTestDlg 대화 상자
class CMFCTimerTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCTimerTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTIMERTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


#define TIMER_CLOCK 1

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_staticTime;
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnStop();
private:
	CFont m_fontTime;  // 시간표시 컨트롤 폰트 설정 변수
};
