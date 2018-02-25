//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "Direct3D.h"
#include"xaudio2.h"

#define USE_SOUND

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,		// タイトル
	SOUND_LABEL_BGM_GAME,			//ゲーム中
	SOUND_LABEL_BGM_GAME_FEVER,		//フィーバータイム

	SOUND_LABEL_SE_NET_SHOOT,		//網投げ
	SOUND_LABEL_SE_NET_PULL,		//網引き
	SOUND_LABEL_SE_NET_GAGE,		//ゲージ
	SOUND_LABEL_MAX,
} SOUND_LABEL;


//----------------------------------------------------------
// 音量調節
// 1.0最大
// 0.0ミュート
//----------------------------------------------------------
#define TITLE_BGM_VOLUME	(1.0f)
#define GAME_BGM_VOLUME	(1.0f)
#define FEVER_BGM_VOLUME	(1.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
void SetVolume(float fVolume, SOUND_LABEL label);	//ボリューム調整

#endif
