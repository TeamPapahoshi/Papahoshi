//======================================================================
//	Timer
//	
//	概要＿：Timerの管理
//	制作者：加藤　遼
//	
//======================================================================
#include "Timer.h"
#include "Frame.h"
#include "debugproc.h"

//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cTimer::cTimer(){


	// タイマー分解能を設定(1ms単位）
	timeBeginPeriod(1);

	m_CurrentTime = 0;
	m_StartTime = timeGetTime();
	m_TimerStart = true;

	m_nFrameRate = FRAME_RATE;
	m_nCountFrame = 0;
	m_nFrameTime = 0;

	m_fCountDownFrame = 0;




}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cTimer::~cTimer(){

}


//=======================================================================================
//
//		更新
//
//=======================================================================================
void cTimer::Update(){

	// フレームを数える
	m_nCountFrame++;
	m_fCountDownFrame++;


	if (m_fCountDownFrame*m_nFrameRate / 1000.0f >= 1.0f){	//1s立ったらカウントダウン

		m_fCountDownFrame = 0;
		m_fCountDownTime--;

	}

	// フレーム数を時間に換算
	m_nFrameTime = m_nCountFrame*m_nFrameRate / 1000.0f;	// /s





	if (m_StartTime)
		m_CurrentTime = timeGetTime() - m_StartTime;

	PrintDebugProc("Time(timeGetTime) %f\n", m_CurrentTime / 1000.0f);
	PrintDebugProc("Time(frame) %f\n", m_nFrameTime);
	PrintDebugProc("CountDown %f\n", m_fCountDownTime);
}
