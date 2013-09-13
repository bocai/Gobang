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
class CGameManager;  //����

#define  TAKE_BACK_TOTAL_COUNT   7
// �ӿ�
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
// ����
	virtual BOOL thinkPlayChess(CPoint &)= 0;  //
	//���ͷ����������ж�
	int forbid(int x,int y);
	CGamePlayer();
	CGamePlayer(CString name, chessType type, CGameManager *pManager);
	virtual ~CGamePlayer();	
protected:
	CString playerName;
	chessType myChessType; // �Լ�����������
	chessType  opponentChessType; // ���ֵ���������
	CGameManager *pGameManager;
	chessType (*m_chessBoard)[CHESS_BOARD_SIZE]; //����
	int takeBackCount;
	int suggestCount;
	stack <CPoint> recordStack;  // ��¼�Ѿ��߹�������

private:
	int tieCount; // ƽ��
	int victoryCount; // ʤ������
	int defeatCount; // ʧ�ܴ���

	UINT port;
	CString ipString;

//�ؼ����ж�
int keyforbidden(int x,int y,int same,int direction);

};

#endif // !defined(AFX_GAMEPLAYER_H__8D06BC10_608B_4366_99F3_85D8F95666FC__INCLUDED_)
