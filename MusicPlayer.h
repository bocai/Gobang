// MusicPlayer.h: interface for the CMusicPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSICPLAYER_H__55F317FC_D4F5_4CB0_BD62_77E234248478__INCLUDED_)
#define AFX_MUSICPLAYER_H__55F317FC_D4F5_4CB0_BD62_77E234248478__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 播放音乐（声音）
class CMusicPlayer  
{
public:
	void PlayMusicRepeat(BOOL m_StartPlay); // 参数TRUE表示开始播放，FALAE表示停止
	
	void PlayMusicNoRepeat(BOOL m_StartPlay);
	void SetMusicFilePath(CString &backpath);

	CString GetMusicFilePath();

	CMusicPlayer();
	virtual ~CMusicPlayer();

private:
	CString m_mp3Path;
	BOOL isPlaying;
};

#endif // !defined(AFX_MUSICPLAYER_H__55F317FC_D4F5_4CB0_BD62_77E234248478__INCLUDED_)
