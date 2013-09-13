#if !defined(AFX_NETWORDSETING_H__1A463EF5_3EF5_486C_B019_F9CD0E9956B9__INCLUDED_)
#define AFX_NETWORDSETING_H__1A463EF5_3EF5_486C_B019_F9CD0E9956B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetwordSeting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetwordSeting dialog


class CNetwordSeting : public CDialog
{
// Construction
public:
	BOOL setIpByte(BYTE by0, BYTE by1, BYTE by2, BYTE by3);
	BOOL setPort(UINT port);
	UINT getPort();
	BOOL getIpAddr(BYTE &by0, BYTE &by1, BYTE &by2, BYTE &by3);
	CNetwordSeting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetwordSeting)
	enum { IDD = IDD_NETWORD_SETTING_DIALOG };
	CIPAddressCtrl	m_ipAddrCtrl;
	UINT	m_port;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetwordSeting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetwordSeting)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BYTE ipBytes[4];
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWORDSETING_H__1A463EF5_3EF5_486C_B019_F9CD0E9956B9__INCLUDED_)
