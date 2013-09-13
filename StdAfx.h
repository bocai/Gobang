// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A8A8352E_422A_4307_B27F_3B628B689D43__INCLUDED_)
#define AFX_STDAFX_H__A8A8352E_422A_4307_B27F_3B628B689D43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include  <afxsock.h> 

void SetWindowEllispeFrame(HWND hwnd, int nWidthEllipse, int nHeightEllipse);

#define WM_NOTIFY_GOBANG_TRAY (WM_USER + 10)

#define SCREEN_WIDTH    1000  //屏幕宽度
#define SCREEN_HEIGHT    700  // 屏幕高度
#define  N_BG           3   // 背景图数量
#define  CHESS_BOARD_SIZE 15  // 棋盘大小
#define  LINE_TOTAL    CHESS_BOARD_SIZE  // 棋盘画的线 
#define  LINE_DISTANCE   37    //线之间的（最小）距离

#define  NO_FORBIDDEN 0  //无禁手
#define  FORBIDDEN 1 //禁手

enum chessType{
	NOCHESS,
	BLACK,
	WHITE
};

// 游戏模式
enum GameMode {
	SINGLE_MODE, // 本地单机模式
	COMPUTER_MODE, // 人机模式
	ONLINE_MODE,      // 联机
	GAME_HALL		// 游戏大厅
};

enum MsgType {
	ONLINE,
	OFFLINE,  // 玩家上下线、、、
	START_GAME,  // 请求开始游戏
	PUT_CHESS, // 落子
	USR_INFO,   //交换用户的其他信息
	CHAT,       // 聊天
	UNDO_CHESS,   // 悔棋
	WIN_WIN,       // 请求和棋
	GIVE_UP,        //认输
	TIME_OUT,      //超时
	SYN_UPDATE,  // 同步棋盘信息
	STOP_GAME,  //停止游戏
	EXIT,    // 退出程序
	PLAYING   //正在进行游戏
};


typedef struct User				//玩家信息
{
	int usrId;
	char username[50];
	
}User;

typedef struct UsrOtherInfo {
	double historyScore;
	char characterSignature[80];  // 个性签名
}UsrOtherInfo;

typedef struct StartGame			
{
	bool      isAgree;
	bool      whoFirst;
	chessType chess_type;
	char nikeName[50];
	int headPortrait; //头像
	int countDownTime;
}StartGame;

typedef struct PlayChess {
	int chess_x, chess_y; // 落子的棋盘坐标
}PlayChess;

typedef struct 	UndoChess			//undo	悔棋
{
	int undo_nStep;  // 悔棋n步 ,在回复消息中为0表示不同意悔棋
}UndoChess;

typedef struct Error			//ERROR
{
	char conn_timeout;
	char unkown_error;
}Error;

union msgContent{  // 消息内容
	UsrOtherInfo usrOtherInfo;
	StartGame startGame;
	PlayChess playChess;
	UndoChess undoChess;
	char chatContent[512]; // 聊天消息内容
	bool  isWinWin; //和棋
	bool  isGiveUp;// 认输
	
};

typedef bool reqRespType;
#define  REQUEST_MSG  true
#define  RESPONSE_MSG false

typedef struct MsgStruct
{
	reqRespType  requestResponse;   // 请求 true、应答 false
	MsgType msg_type;
	
	User usrInfo;
	msgContent content;
	
}MsgStruct;


void SetWindowEllispeFrame(HWND hwnd, int nWidthEllipse, int nHeightEllipse);
void ShowCaption(HWND hWnd);

void HideCaption(HWND hWnd);
HBITMAP getBmpImg(CString &bmpPath);

#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A8A8352E_422A_4307_B27F_3B628B689D43__INCLUDED_)
