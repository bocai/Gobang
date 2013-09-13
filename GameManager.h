// GameManager.h: interface for the CGameManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEMANAGER_H__2E1CCC9B_A884_45A3_BFEE_E2822DB652FB__INCLUDED_)
#define AFX_GAMEMANAGER_H__2E1CCC9B_A884_45A3_BFEE_E2822DB652FB__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stack>
using namespace std;
#include "GobangChess.h"
#include "GamePlayer.h"
#include "StdAfx.h"	// Added by ClassView

class CGameManager  
{
public:	
	int getWinnerChessCount();
	CPoint getSuggestPoint(chessType selfChess, chessType rivalChess);
	CPoint * getWin2points();
	BOOL setWinner(CGamePlayer *player);
	CPoint getOneEmptyPosByRand();
	CGamePlayer * getWinner();
	BOOL cleanRecord();
	BOOL setWhoFirst(chessType cType);
	chessType getWhoFirst();
	vector   <CPoint> *getVecRecord();
	BOOL takeBack(CGamePlayer *pToTackBack, CGamePlayer *pPlayer, int nStep);
	chessType (* getChessBoard(CGamePlayer *pGameplayer)) [CHESS_BOARD_SIZE];

	BOOL setGameMode(GameMode mode);
	GameMode getGameMode();

	BOOL setBoardPos(const CPoint &point, const chessType type);
	BOOL getBoardPos(const CPoint &point, chessType &cType);
	
	BOOL setBoardPos(const int x, const int y, const chessType &cType);
	BOOL getBoardPos(const int x, const int y, chessType &cType);
	//判断胜负
	BOOL judgeVictory(int chess_x, int chess_y, chessType cType);
	
	BOOL setGamePlayer(CGamePlayer *blackPlayer, CGamePlayer *whitePlayer);
	BOOL isGameStart();	

	BOOL startGame(chessType m_turn);
	BOOL stopGame();

	chessType whoIsRuning() const;
	
	BOOL setWhoIsRun(chessType turn);
	GobangChess *getGobangChess();

	CGameManager();
	virtual ~CGameManager();
	

protected:
	CGamePlayer *pBlackPlayer;
	CGamePlayer *pWhitePlayer;
	CGamePlayer *pWinnerPlayer;

	CGamePlayer *pSuggest;  // 用于提示(建议)走棋
	GameMode gameMode;
	BOOL isStart;
	chessType whoFirst;
	chessType  m_turn;
	GobangChess gobangChess;  // 棋盘
	vector <CPoint> VecChessRecord;
	CPoint win2point[2]; // 胜利时形成连线的两个端点
	int winnerChessCount; // 胜利时连起来的棋子计数

};

#endif // !defined(AFX_GAMEMANAGER_H__2E1CCC9B_A884_45A3_BFEE_E2822DB652FB__INCLUDED_)
