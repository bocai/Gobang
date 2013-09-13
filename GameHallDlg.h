#if !defined(AFX_GAMEHALLDLG_H__02362608_DBAB_4AB6_B2D1_69C22D27BC90__INCLUDED_)
#define AFX_GAMEHALLDLG_H__02362608_DBAB_4AB6_B2D1_69C22D27BC90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameHallDlg.h : header file


/////////////////////////////////////////////////////////////////////////////
// CGameHallDlg dialog

class CGameHallDlg : public CDialog
{
// Construction
public:
	CGameHallDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGameHallDlg)
	enum { IDD = IDD_GAME_HALL_DLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameHallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CTabCtrl m_tabRooms;
	// Generated message map functions
	//{{AFX_MSG(CGameHallDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEHALLDLG_H__02362608_DBAB_4AB6_B2D1_69C22D27BC90__INCLUDED_)
