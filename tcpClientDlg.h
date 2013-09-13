#if !defined(AFX_TCPCLIENTDLG_H__17E8FCA6_44EA_48A0_A6C7_2726DF40492E__INCLUDED_)
#define AFX_TCPCLIENTDLG_H__17E8FCA6_44EA_48A0_A6C7_2726DF40492E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tcpClientDlg.h : header file
//
#include "TcpMessager.h"

/////////////////////////////////////////////////////////////////////////////
// CtcpClientDlg dialog

// tcp连接的客户端（测试用)
class CtcpClientDlg : public CDialog
{
// Construction
public:
	BOOL appenStrToEdit(CString str);
	CtcpClientDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CtcpClientDlg)
	enum { IDD = IDD_DLG_CLIENT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CtcpClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEdit m_cedIp;
	CEdit m_cedPort;
	CEdit m_ShowMsg;
	CString msgStr;

	CTcpMessager tcpMsger;
	// Generated message map functions
	//{{AFX_MSG(CtcpClientDlg)
	afx_msg void OnConSvr();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCPCLIENTDLG_H__17E8FCA6_44EA_48A0_A6C7_2726DF40492E__INCLUDED_)
