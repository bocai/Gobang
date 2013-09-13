#if !defined(AFX_STARTUPANIMATION_H__F006E574_6BB5_4A69_B43F_6D9E1725AE63__INCLUDED_)
#define AFX_STARTUPANIMATION_H__F006E574_6BB5_4A69_B43F_6D9E1725AE63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartUpAnimation.h : header file
//

#include "StdAfx.h"
#include "bmpPicture.h"
#include "BtnST.h"
#include "GobangDlg.h"
/////////////////////////////////////////////////////////////////////////////
// StartUpAnimation dialog
typedef struct ConfigIndex
{
	int difficulty;  // 游戏难度
	int chessColor;
	int timeOut;
	int headPortrait; // 头像

}ConfigIndex;

// 游戏模式选择窗口
class StartUpAnimation : public CDialog
{
// Construction
public:
	enum ForegroundWindow { //托盘双击再次弹出窗口时，用于区分上一次是哪个窗口
		MAIN_WINDOW,
		LOCAL_SINGLE,
		VS_COMPUTER,
		VS_ONLINE
	};
	
	void DeleteTray();
	void ToTray(ForegroundWindow fw);

	CGobangDlg * getGobangDlg();
	StartUpAnimation(CWnd* pParent = NULL);   // standard constructor
	virtual ~StartUpAnimation();

	// 分别指向本地人人对战，人机对战，网络对战的窗口
	CGobangDlg  *pPgobangDlg,*pCgobangDlg, *pNgobangDlg;
	CString nikeName;
	BYTE ipBytes[4];
	UINT myPort;
	UINT farPort;
 
	ConfigIndex configData;

// Dialog Data
	//{{AFX_DATA(StartUpAnimation)
	enum { IDD = IDD_START_ANIMATION_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StartUpAnimation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	CButtonST cancelBtn;  // 取消
	CButtonST minSizeBtn;
	CButtonST toTrayBtn;
	CButtonST m_singleBtn;
	CButtonST m_computerBtn;
	CButtonST m_networdBtn;
	CButtonST m_settingBtn;
	CButtonST m_exitBtn;
	CButtonST m_aboutBtn;
	CbmpPicture cpicBg;

	HCURSOR m_hCursor, m_selectBtnCur;


	CString singlePath, computerPath, networdPath, settingPath, exitPath;

	// Generated message map functions
	//{{AFX_MSG(StartUpAnimation)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnTrayIcon(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	virtual void OnCancel();
	afx_msg void OnSingleBtn();
	afx_msg void OnVsComputerBtn();
	afx_msg void OnVsNetwordBtn();
	afx_msg void OnExitBtn();
	afx_msg void OnMinsizeBtn();
	afx_msg void OnTotrayBtn();
	afx_msg void OnGameExit();
	afx_msg void OnAbout();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRuleHelp();
	afx_msg void OnSetBtn();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	NOTIFYICONDATA nid;

	ForegroundWindow lastForeground;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTUPANIMATION_H__F006E574_6BB5_4A69_B43F_6D9E1725AE63__INCLUDED_)
