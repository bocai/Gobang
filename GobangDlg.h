// GobangDlg.h : header file
//

#if !defined(AFX_GOBANGDLG_H__AD8A7160_A776_4A45_80B6_92A5560E3333__INCLUDED_)
#define AFX_GOBANGDLG_H__AD8A7160_A776_4A45_80B6_92A5560E3333__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "GobangChess.h"
#include "GameManager.h"
#include "bmpPicture.h"	// Added by ClassView
#include "BtnST.h"
#include "WinXPButtonST.h"
#include "UdpMessager.h"
#include "computerPlayer.h"
#include "MusicPlayer.h"

#include "ComputerHarder.h"
//class CComputerHarder;
/////////////////////////////////////////////////////////////////////////////
// CGobangDlg dialog
// 下棋的主窗口
class CGobangDlg : public CDialog
{
// Construction
public:
	BOOL transparentTextOut(CDC &dc, RECT &rect, COLORREF color, CString &str);
	BOOL switchShowChess(chessType turn);
	BOOL dealwithPutChessMsg(MsgStruct *pMsg);
	BOOL DrawNumber(CDC &dc, RECT &rect,  COLORREF textColor, int num);
	BOOL setGameMode(GameMode mode);
	
	BOOL handleStartGameMsg(MsgStruct *pMsgstruct, int bufLen, CString &ipStr, UINT port);
	BOOL saveUiPathToFile(CString &path_ini);
	BOOL playInNetword(UINT nFlag, CPoint point);
	BOOL handleNetMsg(MsgStruct *pMsgStruct, int bufLen, CString &ipStr, UINT port);
	BOOL setUIwidgetPathFromFile(CString filepath);
	virtual BOOL setUIwidgetPos();
	BOOL setBtnsImg();
	
	void ToTray();
	void strTextOut(CDC &dc, int sx, int sy, CFont &font, CString &str);
	BOOL initGame(GameMode mode);
	BOOL playInSingle(UINT nFlags, CPoint point);
	BOOL playWithComputer(UINT nFlags, CPoint point);
	BOOL CustomBackground();

	
	virtual void DrawTable(CDC &dc);
	CGobangDlg(CWnd* pParent = NULL);	// standard constructor
	

			

// Dialog Data
	//{{AFX_DATA(CGobangDlg)
	enum { IDD = IDD_GOBANG_DIALOG };
	CButtonST	m_btnCancel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGobangDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL setHoverBtnSound();
	BOOL showWinner(CDC &dc);
	void initChessSwitchBmp(chessType selectType);

//	CPoint currentChess;

	CGamePlayer *pWhitePlayer; // 只用于new 初始化和析构函数delete
	CGamePlayer *pBlackPlayer;
	CGameManager *pGameManager;
	CGamePlayer *pSelf, *pOpponent; //自己和对手（是pWhitePlayer或pBlackPlayer)
	CcomputerPlayer *pCmpSelf, *pCmpOpponent; // 对方

	BOOL doCountDown();
	CPoint randPutChess(chessType turn);
	void DrawOneChess(CDC &dc, chessType cType, int x, int y);
	void DrawChesses(CDC &dc);

	CUdpMessager *pUdpMsger;

	NOTIFYICONDATA nid; // 系统托盘
	HICON m_hIcon;

	CFont m_font, m_numFont;
	HCURSOR m_hCurNormal; //正常时鼠标句柄 
	HCURSOR m_hCurError;  // 点击出错时
	CString m_curPathNormal; //光标的路径，初始化
	CString m_curPathError;  // 点击错误时的鼠标
	
	HCURSOR m_handCur, m_putChess;
	bool    hadSetCur;
	
	CBitmap m_hBitmap;
	COLORREF lineColor; //棋盘格子的线
	COLORREF maskColor; // 掩码贴图的透明色
	COLORREF chessNumColor;  // 棋子上显示序号的颜色
	int timeCount;  // 
	RECT boardTabRect;

	CMusicPlayer soundPlayer, chessVoice; // 音乐播放
	CMusicPlayer soundStart;
	BOOL bgroundChg;
	// Generated message map functions
	//{{AFX_MSG(CGobangDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBtnTest();
	virtual void OnCancel();
	afx_msg void OnMinsizeBtn();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTakebackBtn();
	afx_msg void OnBtnTotray();
	afx_msg void OnGameExit();
	afx_msg void OnAbout();
	afx_msg void OnHeqiBtn();
	afx_msg void OnGiveupBtn();
	afx_msg void OnSettingBtn();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSkinchgBtn();
	afx_msg void OnStartBtn();
	afx_msg void OnDestroy();
	afx_msg void OnSuggestBtn();
	afx_msg void OnMusic1();
	afx_msg void OnMusic2();
	afx_msg void OnMusic3();
	afx_msg void OnStopMusic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
private:
	// UI path
	CString  m_backgroundImgPath;
	CString  cancelBmpPathIn, cancelBmpPathOut;
	CString  minSizeBmpPathIn, minSizeBmpPathOut;
	CString  startBtnBmpPathIn, startBtnBmpPathOut;
	CString  takeBackBmpPathIn, takeBackBmpPathOut;
	CString  sendMsgBmpPath;
	CString  heqiBmpPathIn, heqiBmpPathOut;
	CString  giveUpBmpPathIn, giveUpBmpPathOut;
	CString  suggestBmpPathIn, suggestBmpPathOut;
	CString  backHomeBmpPathIn, backHomeBmpPathOut;
	CString  settingBmpPathIn, settingBmpPathOut;
	
	CString showBlackPath, showWhitePath;
	CString  blackChessBmpPath;
	CString  whiteChessBmpPath;
	CString  skinBmpPath;   //皮肤

	CString  selfHeadPath, rivalHeadPath;
	CString  m_logoPath, m_chatBgPath;
	CString  playerInfo1BmpPath, playerInfo2BmpPath, countDownPath, tableBgPath;
	// 各个部件的矩形位置
	RECT logoRect, chatBgRect, playerInfoRect1, playerInfoRect2, countDownRect, tableBgRect;
//	BOOL isStart;
	// 贴图
	CbmpPicture bmpPicture, logoPic, msgPic, playerInfo1Bmp, playerInfo2Bmp, countDownBgBmp, tableBgBmp;
	
	GameMode gameMode;
	int LinesNo;
	int n_pixel;  // 相距像素
	int borderWidth;  // 棋盘(0,0）点与客户区原点的边界
	int borderHeight;
//	COLORREF  m_bPenColor, m_wPenColor;  // 棋子颜色
 	int    m_chessRadius;  //棋子半径
	RECT  chessRect;
	CPen ChessBlackPen, ChessWhitePen; 

	CbmpPicture cpicBlackChess, cpicWhiteChess;
	chessType selectChess; // 用户选择的棋子（黑、白)

	CButtonST  m_btnStart;
	CButtonST  m_btnMinSize;
	CButtonST  m_btnTakeBack;
	CButtonST  m_btnToTray;
	CButtonST  m_btnSendMsg;
	CButtonST  m_btnHeQi;
	CButtonST  m_btnGiveUp;
	CButtonST  m_btnSuggest;
	CButtonST  m_btnBackHome;
	CButtonST  m_btnSetting;
	CButtonST  m_btnSkin;
	CButtonST  m_musicBtn;
	
	CWinXPButtonST m_rivalChess, m_myChess; // 显示当前该谁下棋了
	CButtonST m_rivalHeadBtn, m_selfHeadBtn;
	CButtonST m_showSelfIp, m_showRivalIp;

	CButtonST m_countDownBtn;//倒计时
	CEdit m_SendMsg;
	CEdit m_ShowMsg;
	CString msgStr;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOBANGDLG_H__AD8A7160_A776_4A45_80B6_92A5560E3333__INCLUDED_)
