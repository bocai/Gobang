// ComputerSimple.h: interface for the CComputerSimple class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPUTERSIMPLE_H__3985936E_5CE3_49A5_B749_7FDEEA2F13BD__INCLUDED_)
#define AFX_COMPUTERSIMPLE_H__3985936E_5CE3_49A5_B749_7FDEEA2F13BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GamePlayer.h"
#include "computerPlayer.h"
typedef struct  
{
	int last; //0标记该获胜方式失效
	int z[5];//记录是否落子,1为落子,0为空
	int x[5];
	int y[5];
}WLIST;  

// （人机对战）简单难度的算法
class CComputerSimple :public CcomputerPlayer
{
	//overide
public:
	BOOL thinkPlayChess(CPoint &point);
public:
	CComputerSimple();
	virtual ~CComputerSimple();

	CPoint CComputerSimple::getBestPos();

	BOOL simpleComputerPlay(CPoint *point);
	BOOL simpleComputerPlay(CPoint &point);

	/* 计算共有多少种获胜情况 */
	void install_game();
	
	void install_list();
	
	//重置获胜情况,电脑获胜表发现人落子处即标为失效,人获胜表记录落子处
	void rest_win1(int x,int y);
	
	//电脑下棋后更新获胜表,记录落子处,人获胜表标为失效
	void rest_win2(int x,int y);
	
	//根据获胜表给得分表评分
	void do_score();
	
	//电脑下棋
	BOOL Computer_play(chessType type, CPoint &point);
	
	//玩家下子
	//	void People_play();
	//开始游戏
	void play_game(chessType type);

protected:
	// 落子点水平方向(横)上的评分
	int HorizontalsimpleScore(int x, int y, chessType type) const;
	
	// 落子点垂直方向上(竖)的评分
	int VerticalsimpleScore(int x, int y, chessType type) const;
	
	// 向右倾斜方向（撇)上的评分
	int getRightInclinesimpleScore(int x, int y, chessType type) const;
	// 向左倾斜方向(捺)上的评分
	int getLeftInclinesimpleScore(int x, int y, chessType type) const;
	

private:
	int First;      //0电脑,1人	
	
	int	WIN_COUNT;			/* 记录获取的情况总数 */
	WLIST  WinListP[572];      /* 人的获胜情况表  */
	WLIST  WinListC[572];     /* 电脑的获胜情况表  */
};

#endif // !defined(AFX_COMPUTERSIMPLE_H__3985936E_5CE3_49A5_B749_7FDEEA2F13BD__INCLUDED_)
