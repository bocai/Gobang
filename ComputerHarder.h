// ComputerHarder.h: interface for the CComputerHarder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPUTERHARDER_H__521C57CD_497F_4307_A701_EE55151DB33B__INCLUDED_)
#define AFX_COMPUTERHARDER_H__521C57CD_497F_4307_A701_EE55151DB33B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "computerPlayer.h"

//���ֱ�
/*
#define  FIVE   100;//��5
#define  DOUBLE_ALIVE_FOUR   99;//˫��4
#define  ALIVE_FOUR_AND_DEAD_FOUR   98;//��4��4
#define  ALIVE_FOUR_AND_ALIVE_THREE   96;//��4��3
#define  ALIVE_FOUR_AND_DEAD_THREE   95;//��4��3
#define  ALIVE_FOUR_AND_ALIVE_TWO   94;//��4��2
#define  ALIVE_FOUR   93;//��4
#define  DOUBLE_DEAD_FOUR   92;//˫��4
#define  DEAD_FOUR_AND_ALIVE_THREE   91;//��4��3
#define  DEAD_FOUR_AND_ALIVE_TWO   90;//��4��2
#define  DOUBLE_ALIVE_THREE   80;//˫��3
#define  ALIVE_THREE_AND_DEAD_THREE   70;//��3��3
#define  ALIVE_THREE   60;//��3
#define  DEAD_FOUR   50;//��4
#define  DOUBLE_ALIVE_TWO   40;//˫��2
#define  DEAD_THREE   30;//��3
#define  ALIVE_TWO   20;//��2
#define  DEAD_TWO   10;//��2
#define  SINGLE   0;//����
*/


// �˻���ս���Ѷȴ�һ����㷨thinkPlayChess
class CComputerHarder :public CcomputerPlayer
{
public:
	BOOL thinkPlayChess(CPoint &point);
	CComputerHarder() {
		m_chessBoard = NULL;
	}
	CComputerHarder(chessType (*pChessBoard)[CHESS_BOARD_SIZE]);
	virtual ~CComputerHarder();

	//���㵱ǰλ�õĵ÷�
//	int getScore(int x, int y, chessType Type);

	//��ʼ����������  
//	void iniValue();
	// ��ù������ĵ�
	CPoint getBestPos();

	//�ĸ����������
	//����
	int HorizontalsimpleScore(int x, int y, chessType Type, BoardType type);

	//��
	int VerticalsimpleScore(int x, int y, chessType Type, BoardType type);

	//��б
	int getLeftInclinesimpleScore(int x, int y, chessType Type, BoardType type);

	//��б
	int getRightInclinesimpleScore(int x, int y, chessType Type, BoardType type);

private:
	BoardType m_type[4];

};

#endif // !defined(AFX_COMPUTERHARDER_H__521C57CD_497F_4307_A701_EE55151DB33B__INCLUDED_)
