// GamePlayer.cpp: implementation of the CGamePlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gobang.h"
#include "GamePlayer.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGamePlayer::CGamePlayer()
{
	initData();
}

CGamePlayer::~CGamePlayer()
{

}

void CGamePlayer::setPlayer(CString name, chessType type)
{
	playerName = name;
	myChessType = type;

}

CString & CGamePlayer::getPlayerName()
{
	return playerName;
}


BOOL CGamePlayer::setGameManager(CGameManager *pManager)
{
	pGameManager = pManager;
	return TRUE;
}

CGameManager * CGamePlayer::getGameManager()
{
	return pGameManager;
}

BOOL CGamePlayer::takeBack(int nStep, vector <CPoint> *vecPoint=NULL)
{
	if (nStep <= 0 || NULL == m_chessBoard)
	{
		return FALSE;
	}
	
	for ( int i = nStep; i > 0 && !recordStack.empty(); i--)
	{
		CPoint point = recordStack.top();
		recordStack.pop();

		if (vecPoint != NULL)
		{
			vecPoint->push_back(point);
		}
		takeBackCount++;
	}

	return TRUE;
}

//����
BOOL CGamePlayer::giveUp()
{

	return TRUE;
}

void CGamePlayer::initData()
{
	pGameManager = NULL;
	suggestCount = takeBackCount = 0;
	victoryCount = defeatCount = tieCount = 0;
}

CGamePlayer::CGamePlayer(CString name, chessType type, CGameManager *pManager)
{
	initData();
	setPlayer(name, type);
	setGameManager(pManager);
}

int CGamePlayer::getTakeBackCount()
{
	return takeBackCount;
}

chessType CGamePlayer::getOppenentChess()
{
	return opponentChessType;
}

BOOL CGamePlayer::pushRecord(CPoint point)
{
	recordStack.push(point);
	
	return TRUE;
}

BOOL CGamePlayer::setMyChessType(chessType cType)
{
	myChessType = cType;

	return TRUE;
}

BOOL CGamePlayer::setOpponentChessType(chessType cType)
{
	opponentChessType = cType;

	return TRUE;
}

chessType CGamePlayer::getMyChessType()
{
	return myChessType;
}

BOOL CGamePlayer::setIpString(CString ipstr)
{
	ipString = ipstr;
	return TRUE;
}

CString & CGamePlayer::getIpString()
{

	return ipString;
}

BOOL CGamePlayer::setPort(UINT nPort)
{
	port = nPort;
	return TRUE;
}

UINT CGamePlayer::getPort()
{
	return port;
}

int CGamePlayer::getTieCount()
{
	return tieCount;
}
int CGamePlayer::getDefeatCount()
{
	return defeatCount;
}
int CGamePlayer::getVictoryCount()
{
	return victoryCount;
}

BOOL CGamePlayer::setTieCount(int tieCount)
{
	 this->tieCount = tieCount;
	 return TRUE;
}

BOOL CGamePlayer::setDdefeatCount(int defeatCount)
{
	this->defeatCount = defeatCount;
	return TRUE;
}

BOOL CGamePlayer::setVictoryCount(int victoryCount)
{
	this->victoryCount = victoryCount;
	return TRUE;
}

BOOL CGamePlayer::cleanRecordStack()
{
	takeBackCount = 0;
	
	while (!recordStack.empty())
	{
		recordStack.pop();		
	}
	return TRUE;
}

//���ͷ����������ж�
int CGamePlayer::forbid(int x,int y)
{
	int same[8]; //��¼��(x,y)��������������
    int none[8]; //��¼same������������λ��
	int same1[8];//��¼none����������������
	int none1[8];//��¼same1������������λ��
	int same2[8];//��¼none1����������������
	for(int i=0;i<8;i++)
	{
		same[i]=none[i]=same1[i]=none1[i]=same2[i]=0;
	}
	m_chessBoard[x][y]=BLACK;//������(x,y)��������

	//�˷�����������
	int m,n;
	//����
	for(n=y-1;n>=0&&m_chessBoard[x][n]==BLACK; n--,same[0]++);
	for(;n>=0&&m_chessBoard[x][n]==NOCHESS; n--,none[0]++);
	for(;n>=0&&m_chessBoard[x][n]==BLACK;n--,same1[0]++);
	for(;n>=0&&m_chessBoard[x][n]==NOCHESS;n--,none1[0]++);
	for(;n>=0&&m_chessBoard[x][n]==BLACK;n--,same2[0]++);
	//������
	for(m=x+1,n=y-1;m<CHESS_BOARD_SIZE&&n>=0&&m_chessBoard[m][n]==BLACK;m++,n--,same[1]++);
	for(;m<CHESS_BOARD_SIZE&&n>=0&&m_chessBoard[m][n]==NOCHESS;m++,n--,none[1]++);
	for(;m<CHESS_BOARD_SIZE&&n>=0&&m_chessBoard[m][n]==BLACK;m++,n--,same1[1]++);
	for(;m<CHESS_BOARD_SIZE&&n>=0&&m_chessBoard[m][n]==NOCHESS;m++,n--,none[1]++);
	for(;m<CHESS_BOARD_SIZE&&n>=0&&m_chessBoard[m][n]==BLACK;m++,n--,same2[1]++);
	//����
	for(m=x+1;m<CHESS_BOARD_SIZE&&m_chessBoard[m][y]==BLACK;m++,same[2]++);
	for(;m<CHESS_BOARD_SIZE&&m_chessBoard[m][y]==NOCHESS;m++,none[2]++);
	for(;m<CHESS_BOARD_SIZE&&m_chessBoard[m][y]==BLACK;m++,same1[2]++);
	for(;m<CHESS_BOARD_SIZE&&m_chessBoard[m][y]==NOCHESS;m++,none1[2]++);
	for(;m<CHESS_BOARD_SIZE&&m_chessBoard[m][y]==BLACK;m++,same2[2]++);
	//������
    for(m=x+1,n=y+1;m<CHESS_BOARD_SIZE&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==BLACK;
		m++,n++,same[3]++);
	for(;m<CHESS_BOARD_SIZE&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==NOCHESS;m++,n++,none[3]++);
	for(;m<CHESS_BOARD_SIZE&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==BLACK;m++,n++,same1[3]++);
	for(;m<CHESS_BOARD_SIZE&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==NOCHESS;m++,n++,none1[3]++);
	for(;m<CHESS_BOARD_SIZE&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==BLACK;m++,n++,same2[3]++);
	//����
	for(n=y+1;n<CHESS_BOARD_SIZE&&m_chessBoard[x][n]==BLACK;n++,same[4]++);
	for(;n<CHESS_BOARD_SIZE&&m_chessBoard[x][n]==NOCHESS;n++,none[4]++);
	for(;n<CHESS_BOARD_SIZE&&m_chessBoard[x][n]==BLACK;n++,same1[4]++);
	for(;n<CHESS_BOARD_SIZE&&m_chessBoard[x][n]==NOCHESS;n++,none1[4]++);
	for(;n<CHESS_BOARD_SIZE&&m_chessBoard[x][n]==BLACK;n++,same2[4]++);
	//������
	for(m=x-1,n=y+1;m>=0&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==BLACK;m--,n++,same[5]++);
	for(;m>=0&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==NOCHESS;m--,n++,none[5]++);
	for(;m>=0&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==BLACK;m--,n++,same1[5]++);
	for(;m>=0&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==NOCHESS;m--,n++,none1[5]++);
	for(;m>=0&&n<CHESS_BOARD_SIZE&&m_chessBoard[m][n]==BLACK;m--,n++,same2[5]++);
	//����
	for(m=x-1;m>=0&&m_chessBoard[m][y]==BLACK;m--,same[6]++);
	for(;n>=0&&m_chessBoard[m][y]==NOCHESS;n--,none[6]++);
	for(;n>=0&&m_chessBoard[m][y]==BLACK;n--,none[6]++);
	for(;n>=0&&m_chessBoard[m][y]==NOCHESS;n--,none[6]++);
	for(;n>=0&&m_chessBoard[m][y]==BLACK;n--,none[6]++);
	//������
	for(m=x-1,n=y-1;m>=0&&n>=0&&m_chessBoard[m][n]==BLACK;m--,n--,same[7]++);
	for(;m>=0&&n>=0&&m_chessBoard[m][n]==NOCHESS;m--,n--,none[7]++);
	for(;m>=0&&n>=0&&m_chessBoard[m][n]==BLACK;m--,n--,same1[7]++);
	for(;m>=0&&n>=0&&m_chessBoard[m][n]==NOCHESS;m--,n--,none1[7]++);
	for(;m>=0&&n>=0&&m_chessBoard[m][n]==BLACK;m--,n--,same2[7]++);
	//��ԭ����
	m_chessBoard[x][y]=NOCHESS;
    //�Ƿ�����
	for(i=0;i<4;i++)
	{
		if(same[i]+same[i+4]==4)
			return NO_FORBIDDEN;
	}
	int three=0,four=0;//����������ͳ����
	for(i=0;i<4;i++)
	{
// 		if(same[i]+same[i+4]>=5) //��������
// 			return FORBIDDEN;
// 		else 
		if(same[i]+same[i]==3) //��������
		{
			bool isfour=false;
			if(none[i]>0)
			{
				if(keyforbidden(x,y,same[i],i)==NO_FORBIDDEN)
					isfour=true;
			}
			if(none[i+4]>0)
			{
				if(keyforbidden(x,y,same[i+4],i+4)==NO_FORBIDDEN)
					isfour=true;
			}
			if(isfour)
				four++;
		}
		else if(same[i]+same[i+4]==2)//��������
		{
			if(none[i]==1&&same[i]==1)
			{
				if(keyforbidden(x,y,same[i],i)==NO_FORBIDDEN)
					four++;
			}
			if(none[i+4]==1&&same[i+4]==1)
			{
				if(keyforbidden(x,y,same[i+4],i+4)==NO_FORBIDDEN)
					four++;
			}
			bool isthree=false;
			if((none[i]>2||none[i]==2&&same1[i]==0)&&(none[i+4]>1||none[i+4]==1&&same1[i+4]==0))
			{	
				if(keyforbidden(x,y,same[i],i)==NO_FORBIDDEN)
					isthree=true;
			}
			if((none[i+4]>2||none[i+4]==2&&same1[i+4]==0)&&(none[i]>1||none[i]==1&&same1[i]==0))
			{	
				if(keyforbidden(x,y,same[i+4],i+4)==NO_FORBIDDEN)
					isthree=true;
			}
			if(isthree)
				three++;
		}
		else if(same[i]+same[i+4]==1)//��������
		{
			if(none[i]==1&&same1[i]==2)
			{
				if(keyforbidden(x,y,same[i],i)==NO_FORBIDDEN)
					four++;
			}	
			if(none[i+4]==1&&same1[i+4]==2)
			{
				if(keyforbidden(x,y,same[i+4],i+4)==NO_FORBIDDEN)
					four++;
			}
			if(none[i]==1&&same1[i]==1&&(none1[i]>1
				||none1[i]==1&&same2[i]==0)&&(none[i+4]>1||none[i+4]==1&&same1[i+4]==0))
			{	
				if(keyforbidden(x,y,same[i],i)==NO_FORBIDDEN)
					three++;
			}
			if(none[i+4]==1&&same1[i+4]==1&&(none1[i+4]>1
				||none1[i+4]==1&&same2[i+4]==0)&&(none[i]>1||none[i]==1&&same1[i]==0))
			{	
				if(keyforbidden(x,y,same[i+4],i+4)==NO_FORBIDDEN)
					three++;
			}
		}
		else if(same[i]+same[i+4]==0)//����һ��
		{
			if(none[i]==1&&same1[i]==3)
			{
				if(keyforbidden(x,y,same[i],i)==NO_FORBIDDEN)
					four++;
			}
			if(none[i+4]==1&&same1[i+4]==3)
			{
				if(keyforbidden(x,y,same[i+4],i+4)==NO_FORBIDDEN)
					four++;
			}
			if(none[i]==1&&same1[i]==2&&(none1[i]>1
				||none1[i]==1&&same2[i]==0)&&(none[i+4]>1||none[i+4]==1&&same1[i+4]==0))
			{	
				if(keyforbidden(x,y,same[i],i)==NO_FORBIDDEN)
					three++;
			}
			if(none[i+4]==1&&same1[i+4]==2&&(none1[i+4]>1
				||none1[i+4]==1&&same2[i+4]==0)&&(none[i]>1||none[i]==1&&same1[i]==0))
			{	
				if(keyforbidden(x,y,same[i+4],i+4)==NO_FORBIDDEN)
					three++;
			}
		}
	}
	//�ܽ����
	if(four>1||three>1)
		return FORBIDDEN;
	else
		return NO_FORBIDDEN;
}

//�ؼ����ж�
int CGamePlayer::keyforbidden(int x,int y,int same,int direction)
{
	int i,j;
    same++;
	if(direction>=4)
		same=-same;
	switch(direction%4)
	{
		case 0:
			i=x;
			j=y-same;
			break;
		case 1:
			i=x+same;
			j=y-same;
			break;
		case 2:
			i=x+same;
			j=y;
			break;
		default:
			i=x+same;
			j=y+same;
			break;
	}
	//ģ������
	m_chessBoard[x][y]=BLACK;
	m_chessBoard[i][j]=BLACK;
	int result=forbid(x,y);
    //��ԭ
	m_chessBoard[x][y]=NOCHESS;
	m_chessBoard[i][j]=NOCHESS;

	return result;
}

BOOL CGamePlayer::setPlayerName(CString &name)
{
	playerName = name;

	return TRUE;
}
// ��ʾ������1, �������С��0������ 0
BOOL CGamePlayer::suggestAdd(int i)
{
	if (i < 0)
	{
		suggestCount = 0;
	}
	else {
		suggestCount += i;
	}
	
	return TRUE;
}

int CGamePlayer::getSuggestCount()
{
	return suggestCount;
}

BOOL CGamePlayer::loadPlayerInfoFromFile(CString &fileName)
{
	return TRUE;
}
