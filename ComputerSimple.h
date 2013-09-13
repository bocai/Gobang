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
	int last; //0��Ǹû�ʤ��ʽʧЧ
	int z[5];//��¼�Ƿ�����,1Ϊ����,0Ϊ��
	int x[5];
	int y[5];
}WLIST;  

// ���˻���ս�����Ѷȵ��㷨
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

	/* ���㹲�ж����ֻ�ʤ��� */
	void install_game();
	
	void install_list();
	
	//���û�ʤ���,���Ի�ʤ���������Ӵ�����ΪʧЧ,�˻�ʤ���¼���Ӵ�
	void rest_win1(int x,int y);
	
	//�����������»�ʤ��,��¼���Ӵ�,�˻�ʤ���ΪʧЧ
	void rest_win2(int x,int y);
	
	//���ݻ�ʤ����÷ֱ�����
	void do_score();
	
	//��������
	BOOL Computer_play(chessType type, CPoint &point);
	
	//�������
	//	void People_play();
	//��ʼ��Ϸ
	void play_game(chessType type);

protected:
	// ���ӵ�ˮƽ����(��)�ϵ�����
	int HorizontalsimpleScore(int x, int y, chessType type) const;
	
	// ���ӵ㴹ֱ������(��)������
	int VerticalsimpleScore(int x, int y, chessType type) const;
	
	// ������б����Ʋ)�ϵ�����
	int getRightInclinesimpleScore(int x, int y, chessType type) const;
	// ������б����(��)�ϵ�����
	int getLeftInclinesimpleScore(int x, int y, chessType type) const;
	

private:
	int First;      //0����,1��	
	
	int	WIN_COUNT;			/* ��¼��ȡ��������� */
	WLIST  WinListP[572];      /* �˵Ļ�ʤ�����  */
	WLIST  WinListC[572];     /* ���ԵĻ�ʤ�����  */
};

#endif // !defined(AFX_COMPUTERSIMPLE_H__3985936E_5CE3_49A5_B749_7FDEEA2F13BD__INCLUDED_)
