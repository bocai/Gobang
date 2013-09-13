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

#define SCREEN_WIDTH    1000  //��Ļ���
#define SCREEN_HEIGHT    700  // ��Ļ�߶�
#define  N_BG           3   // ����ͼ����
#define  CHESS_BOARD_SIZE 15  // ���̴�С
#define  LINE_TOTAL    CHESS_BOARD_SIZE  // ���̻����� 
#define  LINE_DISTANCE   37    //��֮��ģ���С������

#define  NO_FORBIDDEN 0  //�޽���
#define  FORBIDDEN 1 //����

enum chessType{
	NOCHESS,
	BLACK,
	WHITE
};

// ��Ϸģʽ
enum GameMode {
	SINGLE_MODE, // ���ص���ģʽ
	COMPUTER_MODE, // �˻�ģʽ
	ONLINE_MODE,      // ����
	GAME_HALL		// ��Ϸ����
};

enum MsgType {
	ONLINE,
	OFFLINE,  // ��������ߡ�����
	START_GAME,  // ����ʼ��Ϸ
	PUT_CHESS, // ����
	USR_INFO,   //�����û���������Ϣ
	CHAT,       // ����
	UNDO_CHESS,   // ����
	WIN_WIN,       // �������
	GIVE_UP,        //����
	TIME_OUT,      //��ʱ
	SYN_UPDATE,  // ͬ��������Ϣ
	STOP_GAME,  //ֹͣ��Ϸ
	EXIT,    // �˳�����
	PLAYING   //���ڽ�����Ϸ
};


typedef struct User				//�����Ϣ
{
	int usrId;
	char username[50];
	
}User;

typedef struct UsrOtherInfo {
	double historyScore;
	char characterSignature[80];  // ����ǩ��
}UsrOtherInfo;

typedef struct StartGame			
{
	bool      isAgree;
	bool      whoFirst;
	chessType chess_type;
	char nikeName[50];
	int headPortrait; //ͷ��
	int countDownTime;
}StartGame;

typedef struct PlayChess {
	int chess_x, chess_y; // ���ӵ���������
}PlayChess;

typedef struct 	UndoChess			//undo	����
{
	int undo_nStep;  // ����n�� ,�ڻظ���Ϣ��Ϊ0��ʾ��ͬ�����
}UndoChess;

typedef struct Error			//ERROR
{
	char conn_timeout;
	char unkown_error;
}Error;

union msgContent{  // ��Ϣ����
	UsrOtherInfo usrOtherInfo;
	StartGame startGame;
	PlayChess playChess;
	UndoChess undoChess;
	char chatContent[512]; // ������Ϣ����
	bool  isWinWin; //����
	bool  isGiveUp;// ����
	
};

typedef bool reqRespType;
#define  REQUEST_MSG  true
#define  RESPONSE_MSG false

typedef struct MsgStruct
{
	reqRespType  requestResponse;   // ���� true��Ӧ�� false
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
