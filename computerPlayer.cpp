// computerPlayer.cpp: implementation of the CcomputerPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gobang.h"
#include "computerPlayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CcomputerPlayer::CcomputerPlayer()
{
	m_chessBoard = NULL;
}
CcomputerPlayer::CcomputerPlayer(chessType (*pChessBoard)[CHESS_BOARD_SIZE])
{
	m_chessBoard = pChessBoard;
// 	CString cstr;
// 	cstr.Format("%p", m_chessBoard);
// 	AfxMessageBox(cstr);
}

CcomputerPlayer::~CcomputerPlayer()
{
	 
}


BOOL CcomputerPlayer::BzeroPeopleScoreTb()
{
	memset(PeopleScore, 0, sizeof(PeopleScore));
	
	return TRUE;
}

BOOL CcomputerPlayer::BzeroComputerScoreTb()
{
	memset(ComputerScore, 0, sizeof(ComputerScore));
	return TRUE;
}

// CPoint CcomputerPlayer::getBestPos()
// {
// 	CPoint point;
// 	return point;
// }

//��ʼ����������  
void CcomputerPlayer::iniValue()
{
	// 	for (int i = 0; i < CHESS_BOARD_SIZE; i++)
	// 	{
	// 		for (int j = 0; j < CHESS_BOARD_SIZE; j++)
	// 		{
	// 			ComputerScore[i][j] = 0;
	// 			PeopleScore[i][j] = 0;
	// 		}
	// 	}
	//	memset(ComputerScore, 0,sizeof(ComputerScore));

		BzeroComputerScoreTb();
		BzeroPeopleScoreTb();
}

//��ǰλ�����
int CcomputerPlayer::getScore(int x, int y, chessType Type)
{
	int same[8]; //��¼��(x,y)��������������
	int none[8]; //��¼same������������λ��
	int same1[8];//��¼none����������������
	int none1[8];//��¼same1������������λ��
	int same2[8];//��¼none1����������������
	for(int i = 0; i < 8; i++)
	{
		same[i] = none[i] = same1[i] = none1[i] = same2[i] = 0;
	}
	m_chessBoard[x][y] = Type;//������(x,y)��������
	//�˷�����������
	int m,n;
	//����
	for(n=y-1;n>=0&&m_chessBoard[x][n]==Type; n--,same[0]++);
	for(;n>=0&&m_chessBoard[x][n]==NOCHESS; n--,none[0]++);
	for(;n>=0&&m_chessBoard[x][n]==Type;n--,same1[0]++);
	for(;n>=0&&m_chessBoard[x][n]==NOCHESS;n--,none1[0]++);
	for(;n>=0&&m_chessBoard[x][n]==Type;n--,same2[0]++);
	//������
	for(m=x+1,n=y-1;m<CHESS_BOARD_SIZE&&n>=0&&m_chessBoard[m][n]==Type;m++,n--,same[1]++);
	for(;m<CHESS_BOARD_SIZE&&n>=0&&m_chessBoard[m][n]==NOCHESS;m++,n--,none[1]++);
	for(;m<CHESS_BOARD_SIZE&&n>=0&&m_chessBoard[m][n]==Type;m++,n--,same1[1]++);
	for(;m<CHESS_BOARD_SIZE&&n>=0&&m_chessBoard[m][n]==NOCHESS;m++,n--,none[1]++);
	for(;m<CHESS_BOARD_SIZE&&n>=0&&m_chessBoard[m][n]==Type;m++,n--,same2[1]++);
	//����
	for(m=x+1;m<CHESS_BOARD_SIZE&&m_chessBoard[m][y]==Type;m++,same[2]++);
	for(;m<CHESS_BOARD_SIZE&&m_chessBoard[m][y]==NOCHESS;m++,none[2]++);
	for(;m<CHESS_BOARD_SIZE&&m_chessBoard[m][y]==Type;m++,same1[2]++);
	for(;m<CHESS_BOARD_SIZE&&m_chessBoard[m][y]==NOCHESS;m++,none1[2]++);
	for(;m<CHESS_BOARD_SIZE&&m_chessBoard[m][y]==Type;m++,same2[2]++);
	//������
   	for(m=x+1,n=y+1;m<CHESS_BOARD_SIZE&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==Type;
	m++,n++,same[3]++);
	for(;m<CHESS_BOARD_SIZE&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==NOCHESS;m++,n++,none[3]++);
	for(;m<CHESS_BOARD_SIZE&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==Type;m++,n++,same1[3]++);
	for(;m<CHESS_BOARD_SIZE&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==NOCHESS;m++,n++,none1[3]++);
	for(;m<CHESS_BOARD_SIZE&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==Type;m++,n++,same2[3]++);
	//����
	for(n=y+1;n<CHESS_BOARD_SIZE&&m_chessBoard[x][n]==Type;n++,same[4]++);
	for(;n<CHESS_BOARD_SIZE&&m_chessBoard[x][n]==NOCHESS;n++,none[4]++);
	for(;n<CHESS_BOARD_SIZE&&m_chessBoard[x][n]==Type;n++,same1[4]++);
	for(;n<CHESS_BOARD_SIZE&&m_chessBoard[x][n]==NOCHESS;n++,none1[4]++);
	for(;n<CHESS_BOARD_SIZE&&m_chessBoard[x][n]==Type;n++,same2[4]++);
	//������
	for(m=x-1,n=y+1;m>=0&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==Type;m--,n++,same[5]++);
	for(;m>=0&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==NOCHESS;m--,n++,none[5]++);
	for(;m>=0&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==Type;m--,n++,same1[5]++);
	for(;m>=0&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==NOCHESS;m--,n++,none1[5]++);
	for(;m>=0&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==Type;m--,n++,same2[5]++);
	//����
	for(m=x-1;m>=0&&m_chessBoard[m][y]==Type;m--,same[6]++);
	for(;n>=0&&m_chessBoard[m][y]==NOCHESS;n--,none[6]++);
	for(;n>=0&&m_chessBoard[m][y]==Type;n--,none[6]++);
	for(;n>=0&&m_chessBoard[m][y]==NOCHESS;n--,none[6]++);
	for(;n>=0&&m_chessBoard[m][y]==Type;n--,none[6]++);
	//������
	for(m=x-1,n=y-1;m>=0&&n>=0&&m_chessBoard[m][n]==Type;m--,n--,same[7]++);
	for(;m>=0&&n>=0&&m_chessBoard[m][n]==NOCHESS;m--,n--,none[7]++);
	for(;m>=0&&n>=0&&m_chessBoard[m][n]==Type;m--,n--,same1[7]++);
	for(;m>=0&&n>=0&&m_chessBoard[m][n]==NOCHESS;m--,n--,none1[7]++);
	for(;m>=0&&n>=0&&m_chessBoard[m][n]==Type;m--,n--,same2[7]++);
	//��ԭ����
	m_chessBoard[x][y] = NOCHESS;
    //����
	for(i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==4)
			return FIVE_ALL;
	}
	//���� ?AAAA?
	for (i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==3 && none[i]>0 && none[i+4]>0)
			return ALIVE_FOUR_ALL;
	}
	//����A BAAAA?
	for(i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==3)
		{
			if ((none[i]==0 && none[i+4]!=0)||(none[i]>0 && none[i+4]==0))
			{
				return DEAD_FOUR_A;
			}
		}
	}
	//����B AAA?A
	for(i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==2)
		{
			for(int j=0;j<8;j++)
			{
				if(none[j]==1&&same1[j]==1)
					return DEAD_FOUR_B;
			}
		}
		if(same[i]+same[i+4]==0)
		{
			for(int j=0;j<8;j++)
			{
				if(none[j]==1&&same1[j]==3)
					return DEAD_FOUR_B;
			}
		}
	}
	//����C AA?AA
	for(i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==1)
		{
			for(int j=0;j<8;j++)
			{
				if(none[j]==1&&same1[j]==2)
					return DEAD_FOUR_B;
			}
		}
	}
	//����A ?AAA?
	for(i=0;i<4;i++)
	{	
		if(same[i]+same[i+4]==2&&none[i]>0&&none[i+1]>0)
			return ALIVE_THREE_ALL_A;
	}
	//����B ?A?AA?
	for(i=0;i<4;i++)
	{	
		if(same[i]+same[i+4]==0)
		{
			if(none[i]==1&&same1[i]==2&&none1[i]!=0&&none[i+4]>0)
				return ALIVE_THREE_ALL_B;
		}
		if(same[i]+same[i+4]==1)
		{
			if(none[i]!=0&&none[i+4]==1&&same1[i+4]==1&&none1[i+4]>0)
				return ALIVE_THREE_ALL_B;
		}
	}
	//����A BAAA??
	for(i=0;i<4;i++)
	{

		if(same[i]+same[i+4]==2)
		{
			if((none[i]==0&&none[i+4]>1)||(none[i+4]==0&&none[i]>1))
				return DEAD_THREE_A;
		}
	}
	//����B BA?AA?
	for(i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==0)
		{
			if(none[i]==1&&same1[i]==2&&none1[i]!=0&&none[i+4]==0)
				return DEAD_THREE_B;
		}
		if(same[i]+same[i+4]==1)
		{
			if(none[i]!=0&&none[i+4]==1&&same1[i+4]==1&&none1[i+4]==0)
				return DEAD_THREE_B;
		}
	}
	//����C BAA?A?
	for(i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==1)
		{
			if(none[i]==1&&same1[i]==1&&none1[i]!=0&&none[i+4]==0)
				return DEAD_THREE_C;
		}
		if(same[i]+same[i+4]==0)
		{
			if(none[i]!=0&&none[i+4]==1&&same1[i+4]==2&&none1[i+4]==0)
				return DEAD_THREE_C;
		}
	}
	//����D A?A?A
	for(i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==0)
		{
			if(none[i]==1&&same1[i]==1&&none1[i]==1&&same2[i]==1)
				return DEAD_THREE_D;
			if(none[i]!=0&&same1[i+4]==1&&none1[i+4]==1&&same2[i+4]==1)
				return DEAD_THREE_D;
			if(none[i]==1&&same1[i]==1&&none1[i+4]==1&&same1[i+4]==1)
				return DEAD_THREE_D;
		}
	}
	//����E B?AAA?B
	for(i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==2&&none[i]==1&&none[i+1]==1&&same1[i]==0&&same1[i+1]==0)
			return DEAD_THREE_E;
	}
	//���A ??AA??
	for(i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==1&&none[i]>1&&none[i+4]>1)
			return ALIVE_TWO_A;
	}
	//���B ?A?A?
	for(i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==0)
		{
			if((none[i]==1&&none[i+4]>0&&same1[i]==1&&none1[i]>0)
				||(none[i]>0&&none[i+4]==1&&same1[i+4]==1&&none1[i+4]>0))
				return ALIVE_TWO_B;
		}
	}
	//���C ?A??A?
	for(i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==0)
		{
			if(none[i]==2&&none[i+4]>0&&same1[i]==1&&none1[i]>0)
				return ALIVE_TWO_C;
			if(none[i]>0&&none[i+4]==2&&same1[i+4]==1&&none1[i+4]>0)
				return ALIVE_TWO_C;
		}
	}
	//�߶�A BAA???
	for(i=4;i<4;i++)
	{
		if(same[i]+same[i+4]==1)
		{
			if((none[i]>3&&none[i+4]==0)||(none[i]==0&&none[i+4]>3))
				return DEAD_TWO_A;
		}
	}
	//�߶�B BA?A??
	for(i=4;i<4;i++)
	{
		if(same[i]+same[i+4]==0)
		{
			if(none[i]==1&&same[i]==1&&none1[i]>1&&none[i+4]==0)
				return DEAD_TWO_B;
		}
	}

	return 0;
}