// GamePlayer.h: interface for the CGamePlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEPLAYER_H__8D06BC10_608B_4366_99F3_85D8F95666FC__INCLUDED_)
#define AFX_GAMEPLAYER_H__8D06BC10_608B_4366_99F3_85D8F95666FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stack>
#include <vector>
#include "StdAfx.h"	// Added by ClassView
using namespace std;
//#include "GameManager.h"
class CGameManager;  //声明

#define  TAKE_BACK_TOTAL_COUNT   7
// 接口
class CGamePlayer  
{
public:	
	virtual BOOL loadPlayerInfoFromFile(CString &fileName);
	int getSuggestCount();
	BOOL suggestAdd(int i);
	BOOL setPlayerName(CString &naem);
	BOOL cleanRecordStack();
	UINT getPort();
	BOOL setPort(UINT port);
	CString & getIpString();
	BOOL setIpString(CString ipstr);
	chessType getMyChessType();
	BOOL setOpponentChessType(chessType cType);
	BOOL setMyChessType(chessType cType);
	BOOL pushRecord(CPoint point);
	chessType getOppenentChess();
	int getTakeBackCount();

	int	getTieCount();
	
	int getDefeatCount();
	
	int getVictoryCount();
	
	BOOL setTieCount(int tieCount);
	
	BOOL setDdefeatCount(int defeatCount);
	
	BOOL setVictoryCount(int victoryCount);

	virtual void initData();
	virtual BOOL giveUp();
	virtual BOOL takeBack(int nStep, vector <CPoint> *vecPoint);
	virtual CGameManager *getGameManager();
	virtual BOOL setGameManager(CGameManager *pManager);

	virtual CString & getPlayerName();
	virtual void setPlayer(CString name, chessType type);
// 悔棋
	virtual BOOL thinkPlayChess(CPoint &)= 0;  //
	//棋型分析，禁手判断
	int forbid(int x,int y);
	CGamePlayer();
	CGamePlayer(CString name, chessType type, CGameManager *pManager);
	virtual ~CGamePlayer();	
protected:
	CString playerName;
	chessType myChessType; // 自己的棋子类型
	chessType  opponentChessType; // 对手的棋子类型
	CGameManager *pGameManager;
	chessType (*m_chessBoard)[CHESS_BOARD_SIZE]; //棋盘
	int takeBackCount;
	int suggestCount;
	stack <CPoint> recordStack;  // 记录已经走过的棋子

private:
	int tieCount; // 平局
	int victoryCount; // 胜利次数
	int defeatCount; // 失败次数

	UINT port;
	CString ipString;

//关键点判断
int keyforbidden(int x,int y,int same,int direction);

};

#endif // !defined(AFX_GAMEPLAYER_H__8D06BC10_608B_4366_99F3_85D8F95666FC__INCLUDED_)
