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



};


#endif //!___TIMER_H___