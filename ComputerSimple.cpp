// ComputerSimple.cpp: implementation of the CComputerSimple class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gobang.h"
#include "ComputerSimple.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComputerSimple::CComputerSimple()
{

}

CComputerSimple::~CComputerSimple()
{

}
CPoint CComputerSimple::getBestPos()
{
// 	CPoint point;
// 	return 	Computer_play(myChessType, point);



	iniValue();
	CPoint point;
	point.x = -1;
	point.y = -1;
	
	int maxComputer = 0, maxPlayer = 0, i, j;
	int x1, x2, y1, y2, pointx, pointy;
	
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		for (j = 0; j < CHESS_BOARD_SIZE; j++)
		{
			if (m_chessBoard[i][j] == NOCHESS)//ģ������
			{
				ComputerScore[i][j] = getScore(i, j, myChessType);//ΪPC���
				PeopleScore[i][j] = getScore(i, j, opponentChessType);//Ϊ��Ҵ��
				
				if (ComputerScore[i][j] > maxComputer)
				{
					maxComputer = ComputerScore[i][j];
				}
				
				//ѡ��PeopleScore�����ֵ
				if (PeopleScore[i][j] > maxPlayer)
				{
					maxPlayer = PeopleScore[i][j];
					
				}		
			}
		}
	}
	
	
    for (i = 0; i < CHESS_BOARD_SIZE; i++)
    {
		for (j = 0; j < CHESS_BOARD_SIZE; j++)
        {
			if (ComputerScore[i][j] == maxComputer)
			{
				if ((rand()%((10)-(0))+(0)%2) == 0)
				{ 
					maxComputer = ComputerScore[i][j];
					x1 = i;
                    y1 = j;
				}
            }
			
			if (PeopleScore[i][j] == maxPlayer)
			{
				if ((rand()%((10)-(0))+(0)%2) == 1)
				{
					maxPlayer = PeopleScore[i][j];
					x2 = i;
					y2 = j;
				}
			}
		}
	}
	
	
	if(maxComputer>=maxPlayer)
	{
		pointx=x1;
		pointy=y1;
	}
	else if(maxComputer<maxPlayer)
	{
		pointx=x2;
		pointy=y2;
	}
	
	point.x = pointx;
	point.y = pointy;
	
	return point;
}



BOOL CComputerSimple::simpleComputerPlay(CPoint *point)
{
//	CcomputerPlayer::BzeroComputerScoreTb();
	
	return TRUE;
}

BOOL CComputerSimple::simpleComputerPlay(CPoint &point)
{
	
	return TRUE;
}

BOOL CComputerSimple::thinkPlayChess(CPoint &point)
{

	if ( NULL == m_chessBoard)
	{
		return FALSE;
	}

// 	
// 	point.x = p.x;
// 	point.y = p.y;

	return TRUE;
	
}

/* ���㹲�ж����ֻ�ʤ��� */
void CComputerSimple::install_game()
{
    int i, k=0;
    for (i = 1; i <= (CHESS_BOARD_SIZE - 4 ); i++)
    {
		k=k+i;
    } 
	for(i = (CHESS_BOARD_SIZE - 4) - 1; i>0; i--)
	{	
		k=k+i;
	}
	WIN_COUNT = (CHESS_BOARD_SIZE - 4) * CHESS_BOARD_SIZE *2+k*2;
}

void CComputerSimple::install_list()
{
    int i, j, k, m;	
    /* ��ʼ����ʤ����� */
    for (k = 0;k < WIN_COUNT; k++)
    {	
		WinListP[k].last = 1;
		WinListC[k].last = 1;
		for(m = 0;m < 5; m++)
		{
			WinListP[k].z[m] = 0;
			WinListC[k].z[m] = 0;
		}
	}
	//�����ʤ���	
	k=0;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		for (j = 0; j < (CHESS_BOARD_SIZE - 4); j++)
		{	
			for(m = 0; m < 5; m++)
			{
				WinListP[k].x[m] = j;
				WinListP[k].y[m] = i + m;
				WinListC[k].x[m] = j;
				WinListC[k].y[m] = i + m;
			}
			k++;
		}
	}
	//�����ʤ���
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		for (j = 0; j < (CHESS_BOARD_SIZE - 4); j++)
		{	
			for(m = 0; m < 5; m++)
			{
				WinListP[k].x[m] = i + m;
				WinListP[k].y[m] = j ;	
				WinListC[k].x[m] = i + m;
				WinListC[k].y[m] = j ;
			}
			k++;
		}
	}
	//��б��ʤ���
	for (i = 0; i < (CHESS_BOARD_SIZE - 4); i++)
	{
		for	(j = 0; j < (CHESS_BOARD_SIZE- 4); j++)
		{
			for (m = 0; m < 5; m++)
			{
				WinListP[k].x[m] = i + m;
				WinListP[k].y[m] = j + m;
				WinListC[k].x[m] = i + m;
				WinListC[k].y[m] = j + m;
			}
			k++;
		}
	}
	//��б��ʤ���
	for (i = 0; i < (CHESS_BOARD_SIZE - 4); i++)
	{
		for (j = (CHESS_BOARD_SIZE - 1); j > 3; j--)
		{
			for (m = 0; m < 5; m++)
			{
				WinListP[k].x[m] = i + m;
				WinListP[k].y[m] = j - m;
				WinListC[k].x[m] = i + m;
				WinListC[k].y[m] = j - m;
			}
			k++;
		}
	}
}

//���û�ʤ���,���Ի�ʤ���������Ӵ�����ΪʧЧ,�˻�ʤ���¼���Ӵ�
void CComputerSimple::rest_win1(int x,int y)
{
	int i, j;
	for (i = 0;i < WIN_COUNT; i++)
	{
		for(j = 0;j < 5; j++)
		{
			if(WinListC[i].x[j] == x&&WinListC[i].y[j] == y)
			{
				WinListC[i].last = 0;
				WinListP[i].z[j] = 1;
				break;
			}
		}
    }
}
//�����������»�ʤ��,��¼���Ӵ�,�˻�ʤ���ΪʧЧ
void CComputerSimple::rest_win2(int x,int y)
{
	int i, j;
	for (i = 0;i < WIN_COUNT; i++)
	{
		for(j = 0;j < 5; j++)
		{
			if(WinListP[i].x[j] == x&&WinListP[i].y[j] == y)
			{
				WinListP[i].last = 0;
				WinListC[i].z[j] = 1;
				break;
			}
		}
    }
}

//���ݻ�ʤ����÷ֱ�����
void CComputerSimple::do_score()
{
	int i, j, k, m;
	//��ʼ��
	for (i = 0; i < CHESS_BOARD_SIZE ; i++)
	{
		for (j = 0; j < CHESS_BOARD_SIZE; j++)
		{
			PeopleScore[i][j] = 0;                /* ��ʼ���ˣ��������ֱ�    */
			ComputerScore[i][j] = 0;
			
			if (m_chessBoard[i][j] == NOCHESS)        /* Ϊ�ո�                */
			{
				for (k = 0; k < WIN_COUNT; k++)
				{
					if (WinListC[k].last == 1)    /* ���������ո�����    */
					{
						for (m = 0; m < 5; m++)
						{
							if (WinListC[k].x[m] == i && WinListC[k].y[m] == j)
							{
								ComputerScore[i][j]++;
							}
						}
					}   
					if (WinListP[k].last == 1)    /* �˷����ո�����    */
					{
						for (m = 0; m < 5; m++)
						{
							if (WinListP[k].x[m] == i && WinListP[k].y[m] == j)
							{
								PeopleScore[i][j]++;
							}
						}
					}
				}
			}
		}
	}
}

//��������
BOOL CComputerSimple::Computer_play(chessType type, CPoint &point)
{
	 //��,����
	int i, j;
	int score_c=0,score_p=0;
    int people_x, people_y, computer_x, computer_y,computer_x1, computer_y1;
	people_x = people_y = computer_x = computer_y = computer_x1 = computer_y1 = -1;
	/* �����㷨 */
    for (i = 0; i < WIN_COUNT; i++)
    {
		if (WinListC[i].last == 1 )			//����
		{
			for (j = 0; j < 5; j++)
			{
				if (WinListC[i].z[j] == 0)
				{
					ComputerScore[WinListC[i].x[j]][WinListC[i].y[j]] += 1;
					PeopleScore[WinListC[i].x[j]][WinListC[i].y[j]] -= 1;
				}
			}
		}
		if (WinListP[i].last == 1 )			//��
		{
			for (j = 0; j < 5; j++)
			{
				if (WinListP[i].z[j] == 0)
				{
					PeopleScore[WinListP[i].x[j]][WinListP[i].y[j]] += 1; 
					ComputerScore[WinListC[i].x[j]][WinListC[i].y[j]] -= 1;
				}
			}
		}
	}
	/* ��ǿ�㷨����ֹ3��4����ʱ���Բ���ʶ�� */
    for (i = 0; i < WIN_COUNT; i++)
    {
		int computer_count=0;
		if (WinListC[i].last == 1)		//���Ե�����
		{	
			for(j = 0; j < 5; j++)
			{
				if(WinListC[i].z[j] == 1)
					computer_count++;
			}
			switch(computer_count)
			{
			case 3:                 //3���ӵ÷ֱ��λ��20��
				for(j = 0;j < 5; j++)
				{
					if(WinListC[i].z[j] == 0)
						ComputerScore[WinListC[i].x[j]][WinListC[i].y[j]] += 20;			
				}
				break;
			case 4:                //4���ӵ÷ֱ��λ��30��
				for(j = 0;j < 5; j++)
				{
					if(WinListC[i].z[j] == 0)
						ComputerScore[WinListC[i].x[j]][WinListC[i].y[j]] += 30;	
				}
				break;
			}
		}
		int people_count=0;
		if (WinListC[i].last == 0)		//�˵�����,�ӷֶ�,ʹ�����ط���
		{
			for(j = 0; j < 5; j++)
			{
				if(WinListP[i].z[j] == 1)
					people_count++;
			}
			switch(people_count)
			{
			case 3:                 //3���ӵ÷ֱ��λ��25��
				for(j = 0;j < 5; j++)
				{
					if(WinListP[i].z[j] == 0)
					PeopleScore[WinListP[i].x[j]][WinListP[i].y[j]] += 25;		
				}
				break;
			case 4:                //4���ӵ÷ֱ��λ��35��
				for(j = 0;j < 5; j++)
				{
					if(WinListP[i].z[j] == 0)
						PeopleScore[WinListP[i].x[j]][WinListP[i].y[j]] += 35;	
				}
				break;
			}
		}
	}
	
	//�Ƚϵ÷�
	for(i = 0;i < CHESS_BOARD_SIZE; i++)     
	{
		for(j = 0;j < CHESS_BOARD_SIZE; j++)
		{
			if((ComputerScore[i][j]+PeopleScore[i][j]) > score_c&&m_chessBoard[i][j] == NOCHESS)     //����
			{
				score_c=ComputerScore[i][j]+PeopleScore[i][j];
				computer_x=i;
				computer_y=j;
			}
		}
	}

// 	if(score_c > score_p)     //�Ƚϵ÷ֱ�,����
// 	{
// 		computer_x=computer_x1;
// 		computer_y=computer_y1;
// 		m_chessBoard[computer_x][computer_y] = type;
// 	}
// 	else
// 	{
// 		computer_x=people_x;
// 		computer_y=people_y;
// 		m_chessBoard[computer_x][computer_y] = type;
// 	}
	if (computer_x < 0 || computer_y < 0)
	{
		return FALSE;
	}

	point.x = computer_x;
	point.y = computer_y;
	return TRUE;
}
	
	//�������
	// void CComputerSimple::People_play()
	// {
	// 
	// }

	//��ʼ��Ϸ
// 	void CComputerSimple::play_game(chessType type)
// 	{
// 		int play_x,play_y;
// 		chessType typePeople ,typeComputer;   //��,����
// 	
// 		if(First == 0)       //������,�������������
// 		{
// 			play_x=play_y=7;
// 			m_chessBoard[play_x][play_y]=typeComputer;
// 			rest_win2(play_x,play_y);     //����
// 			//��ʾ����
// 			First=1;
// 		}
// 		if (First == 1)      //��
// 		{
// 			//������������
// 			m_chessBoard[play_x][play_y]=typePeople;
// 			rest_win1(play_x,play_y);     //����
// 			//��ʾ����
// 			First=0;
// 		}
// 		while(1)
// 		{
// 			if(First == 0)
// 			{
// 				Computer_play(type);
// 				//��ʾ����
// 				First=1;
// 			}
// 			if(First == 1)
// 			{
// 				People_play();
// 				//��ʾ����
// 				First=0;
// 			}
// 		}
// 		
// 	}

// ����
// BOOL CComputerSimple::takeBack(int step)
// {
// 
// 	return FALSE; // ���Բ��ܻ���
// }






// ���ӵ�ˮƽ����(��)�ϵ�����
int CComputerSimple::HorizontalsimpleScore(int x, int y, chessType type) const
{
	int score = 0;

	return score;

}

// ���ӵ㴹ֱ������(��)������
int CComputerSimple::VerticalsimpleScore(int x, int y, chessType type) const
{
	int score = 0;
	
	return score;

}

// ������б����(��)�ϵ�����
int CComputerSimple::getLeftInclinesimpleScore(int x, int y, chessType type) const
{
	int score = 0;
	
	return score;

}

// ������б����Ʋ)�ϵ�����
int CComputerSimple::getRightInclinesimpleScore(int x, int y, chessType type) const
{
	int score = 0;
	
	return score;

}