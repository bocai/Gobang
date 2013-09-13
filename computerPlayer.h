// computerPlayer.h: interface for the CcomputerPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPUTERPLAYER_H__8648C24F_A342_403D_8DE3_B7B05DAA1D05__INCLUDED_)
#define AFX_COMPUTERPLAYER_H__8648C24F_A342_403D_8DE3_B7B05DAA1D05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GamePlayer.h"


// 棋型表(A表示目标棋子,B表示对手棋子或边界,?表示空格)

#define FIVE_ALL  100000;//AAAAA 连五

#define ALIVE_FOUR_ALL  50000;//?AAAA? 活四

#define DEAD_FOUR_A  9000;//BAAAA? 冲四A
#define DEAD_FOUR_B  8000;//AAA?A 冲四B
#define DEAD_FOUR_C  7000;//AA?AA 冲四C

#define ALIVE_THREE_ALL_A  6000;//?AAA? 活三A
#define ALIVE_THREE_ALL_B  5000;//?A?AA? 活三B

#define DEAD_THREE_A  3000;//BAAA?? 眠三A
#define DEAD_THREE_B  4000;//BA?AA? 眠三B
#define DEAD_THREE_C  2500;//BAA?A 眠三C
#define DEAD_THREE_D  3500;//A?A?A 眠三D
#define DEAD_THREE_E  2000;//B?AAA?B 眠三E

#define ALIVE_TWO_A  1500;//??AA?? 活二A
#define ALIVE_TWO_B  1300;//?A?A? 活二B
#define ALIVE_TWO_C  1000;//?A??A? 活二C

#define DEAD_TWO_A  700;//BAA??? 眠二A
#define DEAD_TWO_B  200;//BA?A?? 眠二B

enum BoardType
{
	DEAD,
		ALIVE,
		HALF_ALIVE
};

// 没有实现接口，同样是抽象类
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
	int	PeopleScore[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE];	/* 用于存放每个空格的得分情况 */
	int	ComputerScore[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE]; 
};

#endif // !defined(AFX_COMPUTERPLAYER_H__8648C24F_A342_403D_8DE3_B7B05DAA1D05__INCLUDED_)
