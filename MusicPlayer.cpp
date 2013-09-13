// MusicPlayer.cpp: implementation of the CMusicPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gobang.h"
#include "MusicPlayer.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMusicPlayer::CMusicPlayer()
{

}

CMusicPlayer::~CMusicPlayer()
{

}

//≤•∑≈±≥æ∞“Ù¿÷
void CMusicPlayer::PlayMusicRepeat(BOOL m_StartPlay)
{		
		if (m_StartPlay)
		{
			CString path;
			path.Format("play %s repeat", m_mp3Path);
			mciSendString(path, NULL, 0, NULL);
		} 
		else
		{
			CString path;
			path.Format("close %s", m_mp3Path);
			mciSendString(path, NULL, 0, NULL);
		}
}

void CMusicPlayer::PlayMusicNoRepeat(BOOL m_StartPlay)
{		
	if (m_StartPlay)
	{
		CString path;
		path.Format("play %s", m_mp3Path);
		mciSendString(path, NULL, 0, NULL);
	} 
	else
	{
		CString path;
		path.Format("close %s", m_mp3Path);
		mciSendString(path, NULL, 0, NULL);
	}
}

void CMusicPlayer::SetMusicFilePath(CString &backpath)
{
	m_mp3Path = backpath;
}

CString CMusicPlayer::GetMusicFilePath()
{
	return m_mp3Path;
}

