//======================================================================
//	Timer
//	
//	概要＿：タイマーの管理
//	制作者：加藤 遼
//	
//======================================================================
#ifndef ___TIMER_H___
#define ___TIMER_H___

#include <Windows.h>
#include "Common.h"
#include "debugproc.h"
#include  "Frame.h"
#include "Sprite.h"

//-------------------------------
// 定数定義
//-------------------------------
#define TIME_SEC_PLACE	(2)	//秒の位の数
#define LIMIT_TIME		(60)

class cTimer{

public:
	cTimer();
	~cTimer();

	void Init(){
	}
	void UnInit(){

	}

	// カウントダウン開始
	void StartCountDown(float Time){
		m_fCountDownTime = Time;
		m_bCountDown = true;
	}
	void ResetCountDown(float Time){
		m_fCountDownTime;
		m_bCountDown = false;
	}

	float GetTime(){
		return m_fCountDownTime;
	}

	void Draw();


	void Update();

private:

	// 直接時間をはかる方法
	DWORD	m_CurrentTime;	// 現在時間
	DWORD	m_StartTime;	// 開始時間

	// フレーム数から時間に換算
	float		m_nFrameRate;		// このゲームのフレームレート
	float		m_nCountFrame;		// フレームを数える
	float		m_nFrameTime;		// 時間に換算

	bool		m_bCountDown;		// カウントダウン開始フラグ
	float		m_fCountDownFrame;	// カウントダウン用フレーム
	float		m_fCountDownTime;	// カウントダウン用時間

	//描画用スプライト
	cSpriteParam	m_aSecSprite[TIME_SEC_PLACE];

};


#endif //!___TIMER_H___