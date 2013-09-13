// ComputerHarder.h: interface for the CComputerHarder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPUTERHARDER_H__521C57CD_497F_4307_A701_EE55151DB33B__INCLUDED_)
#define AFX_COMPUTERHARDER_H__521C57CD_497F_4307_A701_EE55151DB33B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "computerPlayer.h"

//估分表
/*
#define  FIVE   100;//成5
#define  DOUBLE_ALIVE_FOUR   99;//双活4
#define  ALIVE_FOUR_AND_DEAD_FOUR   98;//活4死4
#define  ALIVE_FOUR_AND_ALIVE_THREE   96;//活4活3
#define  ALIVE_FOUR_AND_DEAD_THREE   95;//活4死3
#define  ALIVE_FOUR_AND_ALIVE_TWO   94;//活4活2
#define  ALIVE_FOUR   93;//活4
#define  DOUBLE_DEAD_FOUR   92;//双死4
#define  DEAD_FOUR_AND_ALIVE_THREE   91;//死4活3
#define  DEAD_FOUR_AND_ALIVE_TWO   90;//死4活2
#define  DOUBLE_ALIVE_THREE   80;//双活3
#define  ALIVE_THREE_AND_DEAD_THREE   70;//活3死3
#define  ALIVE_THREE   60;//活3
#define  DEAD_FOUR   50;//死4
#define  DOUBLE_ALIVE_TWO   40;//双活2
#define  DEAD_THREE   30;//死3
#define  ALIVE_TWO   20;//活2
#define  DEAD_TWO   10;//死2
#define  SINGLE   0;//单个
*/


// 人机对战，难度大一点的算法thinkPlayChess
class CComputerHarder :public CcomputerPlayer
{
public:
	BOOL thinkPlayChess(CPoint &point);
	CComputerHarder() {
		m_chessBoard = NULL;
	}
	CComputerHarder(chessType (*pChessBoard)[CHESS_BOARD_SIZE]);
	virtual ~CComputerHarder();

	//计算当前位置的得分
//	int getScore(int x, int y, chessType Type);

	//初始化估分数组  
//	void iniValue();
	// 获得估分最大的点
	CPoint getBestPos();

	//四个方向的搜索
	//横向
	int HorizontalsimpleScore(int x, int y, chessType Type, BoardType type);

	//竖
	int VerticalsimpleScore(int x, int y, chessType Type, BoardType type);

	//左斜
	int getLeftInclinesimpleScore(int x, int y, chessType Type, BoardType type);

	//右斜
	int getRightInclinesimpleScore(int x, int y, chessType Type, BoardType type);

private:
	BoardType m_type[4];

};

#endif // !defined(AFX_COMPUTERHARDER_H__521C57CD_497F_4307_A701_EE55151DB33B__INCLUDED_)
