#if !defined(AFX_STARTUP_H__36B8C5B8_6137_4CC5_B326_C3E2BECE6FE7__INCLUDED_)
#define AFX_STARTUP_H__36B8C5B8_6137_4CC5_B326_C3E2BECE6FE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartUp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartUp dialog
// 程序加载前的动画
class CStartUp : public CDialog
{
// Construction
public:
	CStartUp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStartUp)
	enum { IDD = IDD_GAME_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartUp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int mvWait;
	// Generated message map functions
	//{{AFX_MSG(CStartUp)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTUP_H__36B8C5B8_6137_4CC5_B326_C3E2BECE6FE7__INCLUDED_)
