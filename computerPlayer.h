// computerPlayer.h: interface for the CcomputerPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPUTERPLAYER_H__8648C24F_A342_403D_8DE3_B7B05DAA1D05__INCLUDED_)
#define AFX_COMPUTERPLAYER_H__8648C24F_A342_403D_8DE3_B7B05DAA1D05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GamePlayer.h"


// ���ͱ�(A��ʾĿ������,B��ʾ�������ӻ�߽�,?��ʾ�ո�)

#define FIVE_ALL  100000;//AAAAA ����

#define ALIVE_FOUR_ALL  50000;//?AAAA? ����

#define DEAD_FOUR_A  9000;//BAAAA? ����A
#define DEAD_FOUR_B  8000;//AAA?A ����B
#define DEAD_FOUR_C  7000;//AA?AA ����C

#define ALIVE_THREE_ALL_A  6000;//?AAA? ����A
#define ALIVE_THREE_ALL_B  5000;//?A?AA? ����B

#define DEAD_THREE_A  3000;//BAAA?? ����A
#define DEAD_THREE_B  4000;//BA?AA? ����B
#define DEAD_THREE_C  2500;//BAA?A ����C
#define DEAD_THREE_D  3500;//A?A?A ����D
#define DEAD_THREE_E  2000;//B?AAA?B ����E

#define ALIVE_TWO_A  1500;//??AA?? ���A
#define ALIVE_TWO_B  1300;//?A?A? ���B
#define ALIVE_TWO_C  1000;//?A??A? ���C

#define DEAD_TWO_A  700;//BAA??? �߶�A
#define DEAD_TWO_B  200;//BA?A?? �߶�B

enum BoardType
{
	DEAD,
		ALIVE,
		HALF_ALIVE
};

// û��ʵ�ֽӿڣ�ͬ���ǳ�����
class CcomputerPlayer :public CGamePlayer
{
public:
	
	BOOL BzeroComputerScoreTb();
	BOOL BzeroPeopleScoreTb();

	int	getScore(int x, int y, chessType Type);
	CcomputerPlayer();
	CcomputerPlayer(chessType (*pChessBoard)[CHESS_BOARD_SIZE]);
	virtual ~CcomputerPlayer();
// 	BOOL takeBack(int step = 1);
// 	BOOL thinkPlayChess(CPoint &point);

	virtual CPoint getBestPos() = 0;
protected:
	void iniValue();
	int	PeopleScore[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE];	/* ���ڴ��ÿ���ո�ĵ÷���� */
	int	ComputerScore[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE]; 
};

#endif // !defined(AFX_COMPUTERPLAYER_H__8648C24F_A342_403D_8DE3_B7B05DAA1D05__INCLUDED_)
