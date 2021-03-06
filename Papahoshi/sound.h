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
	SOUND_LABEL_BGM_GAME,			// ゲーム中
	SOUND_LABEL_BGM_GAME_FEVER,		// フィーバータイム

	SOUND_LABEL_BGM_RESULT_MIN,
	SOUND_LABEL_BGM_RESULT_MAX,

	SOUND_LABEL_SE_NET_SHOOT,		// 網投げ
	SOUND_LABEL_SE_NET_SET,			// 網設置
	SOUND_LABEL_SE_NET_PULL,		// 網引き
	SOUND_LABEL_SE_NET_GAGE,		// ゲージ

	SOUND_LABEL_SE_STAR_GET,			// 星取得
	SOUND_LABEL_SE_STREAM_METEOR,		// 流れる流星
	SOUND_LABEL_SE_SPACE_ROCK_BOMB,		// 隕石爆発
	SOUND_LABEL_SE_VACUME_BLACK_HOLE,	// ブラックホール吸い込みおん
	SOUND_LABEL_SE_REAR_STAR_GET,		// レア星獲得音

	SOUND_LABEL_SE_TITLE_SHIP,	// 汽笛
	SOUND_LABEL_SE_TITLE_STAR,	//タイトル流星
	SOUND_LABEL_SE_GAME_GAGEADD,	//ゲージ増加
	SOUND_LABEL_SE_GAME_GAGESUB,	//ゲージ減少
	SOUND_LABEL_GINGLE_RESULT_MIN,	// リザルトジングル(閾値以下)
	SOUND_LABEL_GINGLE_RESULT_MAX,	// リザルトジングル(閾値以上)
	SOUND_LABEL_SE_RESULT_COUNTUP,	// リザルトカウントアップ音
	SOUND_LABEL_SE_RESULT_COUNTUPEND,	// リザルトカウントアップ終了音
	SOUND_LABEL_SE_RESULT_MOVE_STAR,// リザルト星生成音

	SOUND_LABEL_VOICE_3,	//アナウンス「3」
	SOUND_LABEL_VOICE_2,	//アナウンス「2」
	SOUND_LABEL_VOICE_1,	//アナウンス「1」
	SOUND_LABEL_VOICE_START,	//アナウンス「START」
	SOUND_LABEL_SE_GAME_WHISTLE,		//終了時ホイッスル
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
#define RESULT_BGM_VOLUME   (1.0f)

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
