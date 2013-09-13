// GobangChess.h: interface for the GobangChess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GOBANGCHESS_H__9970C279_CE19_46CE_B482_80BA259152F3__INCLUDED_)
#define AFX_GOBANGCHESS_H__9970C279_CE19_46CE_B482_80BA259152F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

class GobangChess  
{
public:
	chessType (* getChessBoard())[CHESS_BOARD_SIZE];
	void reset();
	GobangChess();
	virtual ~GobangChess();
	
	BOOL cleanBoard(const chessType type);

	BOOL setBoardPos(const CPoint &point, const chessType type);
	BOOL getBoardPos(const CPoint &point, chessType &cType);
	
	BOOL setBoardPos(const int x, const int y, const chessType &cType);
	BOOL getBoardPos(const int x, const int y, chessType &cType);
	
	// ���ӵ�ˮƽ����(��)�ϵ���������(type���͵�)��
	int getHorizontalChessCount(int x, int y, chessType type, CPoint *point2);
	
	// ���ӵ㴹ֱ������(��)����������(type���͵�)��
	int getVerticalChessCount(int x, int y, chessType type, CPoint *point2);
	
	// ������б����(��)�ϵ���������(type���͵�)��
	int getLeftInclineChessCount(int x, int y, chessType type, CPoint *point2);
	
	// ������б����Ʋ)�ϵ���������(type���͵�)��
	int getRightInclineChessCount(int x, int y, chessType type, CPoint *point2);

private:
	chessType m_chessBoard[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE];

};

#endif // !defined(AFX_GOBANGCHESS_H__9970C279_CE19_46CE_B482_80BA259152F3__INCLUDED_)
