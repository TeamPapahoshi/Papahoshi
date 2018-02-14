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
#include "Input.h"
#include "Texture.h"

//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cTimer::cTimer(){


	//--- 実際に時間を測る ----
	timeBeginPeriod(1);	// タイマー分解能を設定(1ms単位）
	m_CurrentTime = 0;
	m_StartTime = timeGetTime();


	//--- フレーム数から時間を求める ----
	m_nFrameRate = FRAME_RATE;
	m_nCountFrame = 0;
	m_nFrameTime = 0;
	m_fCountDownFrame = 0;
	m_fCountDownTime = 0;
	m_bCountDown = false;

	//---- テクスチャ初期化 ----
	D3DXVECTOR2 pos, size;
	pos = D3DXVECTOR2(150.0f, 230.0f);
	size = D3DXVECTOR2(55.0f, 55.0f);
	for (int i = TIME_SEC_PLACE - 1; i >= 0; i--){
		m_aSecSprite[i].SetPos(D3DXVECTOR2(pos.x + (size.x * 0.8f) * i, pos.y));
		m_aSecSprite[i].SetSize(size);
	}

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


	// カウントダウン処理
	if (m_bCountDown){

		m_fCountDownFrame++;

		if (m_fCountDownFrame*m_nFrameRate / 1000.0f >= 1.0f){	//1s立ったらカウントダウン

			m_fCountDownFrame = 0;
			m_fCountDownTime--;

		}

		if (m_fCountDownTime <= 0)
			m_bCountDown = false;
	}

	// フレーム数を時間に換算
	m_nFrameTime = m_nCountFrame*m_nFrameRate / 1000.0f;	// 


	// 実際の時間
	m_CurrentTime = timeGetTime() - m_StartTime;

	PrintDebugProc("Time(timeGetTime) %f\n", m_CurrentTime / 1000.0f);
	PrintDebugProc("Time(frame) %f\n", m_nFrameTime);
	PrintDebugProc("CountDown %f\n", m_fCountDownTime);
	PrintDebugProc("Sキーでカウントダウン\n", m_fCountDownTime);
}

//===================================================
//
// 描画関数
//
//===================================================
void cTimer::Draw(){

	int work1, work2;
	work2 = (int)m_fCountDownTime;

	for (int i = TIME_SEC_PLACE - 1; i >= 0; i--)
	{
		//----- スコアのスプライト情報を更新 -----
		work1 = work2 % 10;
		work2 = work2 / 10;
		m_aSecSprite[i].SetTexture(cTextureManeger::GetTextureGame((TEX_GAME)(TEX_GAME_0 + work1)));

		//----- 描画 -----
		m_aSecSprite[i].Draw();
	}

}