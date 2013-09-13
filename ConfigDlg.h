#if !defined(AFX_CONFIGDLG_H__BBB0B8B3_DB89_403D_965A_E69D97B054D4__INCLUDED_)
#define AFX_CONFIGDLG_H__BBB0B8B3_DB89_403D_965A_E69D97B054D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//
#include "bmpPicture.h"
#include "BtnST.h"
#include "StartUpAnimation.h"

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

// 设置菜单窗口
class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIG_DLG };
	CIPAddressCtrl	m_ipAddrCtrl;
	UINT	m_MyPort;
	UINT	m_hisPort;
	CString	m_nikeName;
	//}}AFX_DATA

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CbmpPicture bmpPic;

	CButtonST m_cancelBtn;

	CButtonST preDif, nextDif;// 难度
	CButtonST preChessCor, nextChessCor; // 棋子颜色
	CButtonST preHead, nextHead;
	CButtonST preTimeOut, nextTimeOut;

	CWinXPButtonST difBtn, chessColorBtn, headBtn, timeOutBtn, m_OkBtn;
	CFont m_font;
	StartUpAnimation *pParentDlg;
	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnOK();
	afx_msg void OnDifPreBtn();
	afx_msg void OnDifNextBtn();
	afx_msg void OnCorlorPreBtn();
	afx_msg void OnCorlorNextBtn();
	afx_msg void OnTimePreBtn();
	afx_msg void OnTimeNextBtn();
	afx_msg void OnHeadPreBtn();
	afx_msg void OnHeadNextBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__BBB0B8B3_DB89_403D_965A_E69D97B054D4__INCLUDED_)
