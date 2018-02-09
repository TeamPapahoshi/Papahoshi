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

	void Start(){
		m_TimerStart = true;
		m_StartTime = timeGetTime();
	}

	void Init(){


	}
	void UnInit(){

	}

	void StartCountDown(int Time){

		// 時間をフレーム数に換算
		//m_fCountDownFrame = Time*1000.0f / m_nFrameRate;

		m_fCountDownTime = Time;

	

	}

	void Update();

private:

	// 直接時間をはかる方法
	DWORD	m_CurrentTime;	// 現在時間
	DWORD	m_StartTime;	// 開始時間
	bool	m_TimerStart;

	// フレーム数から時間に換算
	float		m_nFrameRate;		// このゲームのフレームレート
	float		m_nCountFrame;		// フレームを数える
	float		m_nFrameTime;		// 時間に換算
	float		m_fCountDownFrame;	// カウントダウン用フレーム
	float		m_fCountDownTime;	// カウントダウン用時間



};


#endif //!___TIMER_H___