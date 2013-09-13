#if !defined(AFX_GOBANGABOUTDLG_H__E99D2B9D_9BDD_4691_B5B0_0ACCF7F54B46__INCLUDED_)
#define AFX_GOBANGABOUTDLG_H__E99D2B9D_9BDD_4691_B5B0_0ACCF7F54B46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GobangAboutDlg.h : header file
//
#include "StdAfx.h"
#include "BtnST.h"
#include "bmpPicture.h"

/////////////////////////////////////////////////////////////////////////////
// CGobangAboutDlg dialog

class CGobangAboutDlg : public CDialog
{
// Construction
public:	
	enum ShowImg {
		ABOUT_IMG,
		HELP_IMG
	};
	BOOL setBkImg(ShowImg img=ABOUT_IMG);

	CGobangAboutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGobangAboutDlg();
// Dialog Data
	//{{AFX_DATA(CGobangAboutDlg)
	enum { IDD = IDD_DLG_ABOUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGobangAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CbmpPicture bmpPic;
	CButtonST m_okBtn;
	CButtonST m_quitBtn;
	ShowImg bkImg;
	// Generated message map functions
	//{{AFX_MSG(CGobangAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnQuitAbout();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOBANGABOUTDLG_H__E99D2B9D_9BDD_4691_B5B0_0ACCF7F54B46__INCLUDED_)
