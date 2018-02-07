//======================================================================
//	GameMain
//	
//	概要＿：Init, UnInit, Update, Draw
//	制作者：花井　雄矢
//	
//======================================================================

//------------------------------
// インクルードファイル
//------------------------------
#include "GameMain.h"
#include "Direct3D.h"	//Direct3D
#include "Frame.h"		//フレーム管理
#include "Sprite.h"		//スプライト管理
#include "Input.h"		//入力装置管理
#include "SceneManeger.h"
#include "sound.h"

//デバッグ
#ifdef _DEBUG
#include"debugproc.h"
#endif

//-----------------------------
// グローバル
//-----------------------------
#ifdef _DEBUG
bool g_bDispDebug = true;	//デバッグON/OFF
#endif

cEffectManeger g_CEffectManeger;	//エフェクト管理用クラス

//=======================================================================================
//
//		初期化
//
//=======================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindowed){

	//Direct3Dの初期化
	if (FAILED(InitDirect3D(hInstance, hWnd, bWindowed)))
		return E_FAIL;

#ifdef _DEBUG
	if (FAILED(InitDebugProc()))
		return E_FAIL;
#endif	// _DEBUG

	//フレーム管理の初期化
	if (FAILED(InitFrame()))
		return E_FAIL;

	//スプライト管理の初期化
	if (FAILED(CreateBufferSprite()))
		return E_FAIL;

	//エフェクトの初期化
	g_CEffectManeger.Init();

	//乱数の初期化
	CRandam::InitRand();

	//入力装置管理の初期化
	if (FAILED(InitInput(hInstance, hWnd)))
		return E_FAIL;

	//サウンドの初期化
	if (FAILED(InitSound(hWnd)))
		return E_FAIL;

	//最初のシーンの設定
	cSceneManeger::ChangeScene(cSceneManeger::GAME);	//デバッグ用にステージセレクト画面から開始
	

	//初期化完了
	return S_OK;
}

//=======================================================================================
//
//		終了処理
//
//=======================================================================================
void UnInit(void){


#ifdef _DEBUG
	//デバッグ表示用テキストの終了処理
	UninitDebugProc();
#endif	//_DEBUG

	// フレーム管理の終了処理
	UnInitFrame();

	// スプライト管理の終了処理
	ReleaseBufferSprite();

	//エフェクトの初期化
	g_CEffectManeger.Uninit();

	//乱数の初期化
	CRandam::InitRand();

	// 入力装置管理の終了処理
	UnInitInput();

	// サウンドの終了処理
	UninitSound();

	//Direct3Dの終了処理
	UnInitDirect3D();

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void Update(void){

	//入力装置情報の更新
	UpdateInput();

	//エフェクトの初期化
	g_CEffectManeger.Update();

	//現在のシーンの更新
	cSceneManeger::Update();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1))
	{// デバッグ表示ON/OFF
		g_bDispDebug = g_bDispDebug ? false : true;
	}
	//デバッグ表示用テキストの更新
	UpdateDebugProc();
#endif	//_DEBUG

}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void Draw(void){

	//----------------------------
	// ローカル変数宣言
	//----------------------------
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// Direct3Dデバイス

	//----------------------------
	// 描画準備
	//----------------------------
	//バックバッファとZバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 0, 255, 0), 1.0f, 0);

	//----------------------------
	// 描画
	//----------------------------
	// 描画開始
	if (SUCCEEDED(pDevice->BeginScene())){

		//現在のシーンの描画
		cSceneManeger::Draw();

		//エフェクトの初期化
		g_CEffectManeger.Draw();

#ifdef _DEBUG
		//デバッグ表示用テキストの描画
		if (g_bDispDebug)
			DrawDebugProc();
#endif	//_DEBUG

		pDevice->EndScene(); 
	}	// 描画終了
	
	//----------------------------
	// 描画内容を画面に反映
	//----------------------------
	//バックバッファとフロントバッファの入れ替え
	pDevice->Present(NULL, NULL, NULL, NULL);

}

//==================================================================
//
//	エフェクト情報引き渡し関数
//
//==================================================================
cEffectManeger* GetEffectManeger(void)
{
	return &g_CEffectManeger;
}



