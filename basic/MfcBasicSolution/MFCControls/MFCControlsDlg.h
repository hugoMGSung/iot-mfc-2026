
// MFCControlsDlg.h: 헤더 파일
//

#pragma once


// CMFCControlsDlg 대화 상자
class CMFCControlsDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCControlsDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCONTROLS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	// DDX Value
	CString m_strID;
	CString m_strPW;
	BOOL m_bAutoLogin;
	int m_nUserType;

	// DDX Control
	CEdit m_editID;
	CStatic m_staticStatus;
	CButton m_btnLogin;
};
