//======================================================================
//	Frame
//	
//	概要＿：フレーム管理関連
//	制作者：花井　雄矢
//	
//======================================================================

//------------------------------
// インクルードファイル
//------------------------------
#include "Frame.h"


//----- timeGetTime()など　------------
#include <mmsystem.h>
#pragma comment( lib, "winmm.lib" )	// Windowsマルチメディアライブラリ


#ifdef _FPS_MEASURE_
#include "DebugText.h"
#endif


//------------------------------
// マクロ定義 
//------------------------------
#define FRAME_RATE		(1000 / 60)		// フレームレート


//------------------------------
// グローバル変数宣言 
//------------------------------
static DWORD g_dwExecLastTime;		//前実行時刻
static DWORD g_dwCurrentTime = 0;	//現時刻


//------------------------------
//FPS計測時
//------------------------------
#ifdef _FPS_MEASURE_

// マクロ定義
#define FPS_MEASURE_RATE	(500)			// FPS計測レート

// グローバル変数宣言 
static DWORD		g_dwFPSLastTime;		// FPS前計測時刻
static DWORD		g_dwFPSFrameCount = 0;	// フレーム数カウント
static int			g_nCurrentFPS = 0;		// 現在のFPS

// プロトタイプ宣言
HRESULT InitFPSMeasure(void);	//FPS計測初期化
void	UnInitFPSMeasure(void);	//FPS計測終了処理
void	MeasureFPS(void);		//FPSを計測
void	UpdateFPSText(void);	//FPS表示を更新

#endif





//=======================================================================================
//
//		フレーム管理初期化
//
//	[戻り値]	S_OK ： 初期化成功		E_FAIL : 初期化失敗
//
//=======================================================================================
HRESULT InitFrame(void){

	//------------------------------
	//初期化
	//------------------------------
	// タイマー分解能を設定(1ms単位）
	timeBeginPeriod(1);
	// 最終実行時刻の初期化（現時刻に）
	g_dwExecLastTime = timeGetTime();


#ifdef _FPS_MEASURE_
	if (FAILED(InitFPSMeasure()))	//FPS計測初期化
		return E_FAIL;
#endif



	return S_OK;
}


//=======================================================================================
//
//		フレーム管理終了処理
//
//=======================================================================================
void UnInitFrame(void) {

	// 分解能を元に戻す
	timeEndPeriod(1);

#ifdef _FPS_MEASURE_
	UnInitFPSMeasure();	// FPS計測終了処理
#endif

}


//=======================================================================================
//
//		フレーム更新有無の確認
//
//	[戻り値]	TRUE : 更新あり		FALSE　：　更新なし
//
//=======================================================================================
BOOL CheckFrameUpdate(void) {

	// 現時刻を更新
	g_dwCurrentTime = timeGetTime();


#ifdef _FPS_MEASURE_
	MeasureFPS();	// FPSを計測
#endif

	// フレーム更新有り
	if (g_dwCurrentTime - g_dwExecLastTime >= FRAME_RATE) {
		g_dwExecLastTime = g_dwCurrentTime;

#ifdef _FPS_MEASURE_
		UpdateFPSText();
#endif

		return TRUE;
	}

	return FALSE;
}



//=======================================================================================
//
//		timeGetTime()
////
//=======================================================================================
DWORD Frame_timeGetTime(void){

	return timeGetTime();
}





//---------------------------------------------------------- FPS計測時 ----------------------------------------------------------
#ifdef _FPS_MEASURE_

//---------------------------------------------------------------------------------------
//
//		FPS計測初期化
//
//	[戻り値]	S_OK ： 初期化成功		E_FAIL : 初期化失敗
//
//---------------------------------------------------------------------------------------
HRESULT InitFPSMeasure(void){
	// FPSカウント時刻を現時刻に設定
	g_dwFPSLastTime = g_dwExecLastTime;
	// カウントを0クリア
	g_dwFPSFrameCount = 0;

	return S_OK;
}



//---------------------------------------------------------------------------------------
//
//		FPS計測終了処理
//
//---------------------------------------------------------------------------------------
void	UnInitFPSMeasure(void){
}



//---------------------------------------------------------------------------------------
//
//		FPSを計測
//
//---------------------------------------------------------------------------------------
void	MeasureFPS(void){
	if (g_dwCurrentTime - g_dwFPSLastTime >= FPS_MEASURE_RATE)
	{

		// FPS計測
		g_nCurrentFPS = (g_dwFPSFrameCount * 1000) / (g_dwCurrentTime - g_dwFPSLastTime);
		// FPS測定した時刻を保存
		g_dwFPSLastTime = g_dwCurrentTime;
		// カウントをクリア
		g_dwFPSFrameCount = 0;
	}
	if (g_dwCurrentTime - g_dwExecLastTime >= FRAME_RATE) {
		g_dwFPSFrameCount++;
	}
}



//=======================================================================================
//
//		FPSを描画
//
//=======================================================================================
void UpdateFPSText(void) {

	char aStr[256];
	wsprintf(aStr, "FPS %d\n", g_nCurrentFPS);
	DebugTextAdd(aStr);
}
#endif


