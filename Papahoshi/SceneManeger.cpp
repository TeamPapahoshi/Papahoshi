//======================================================================
//	SceneManeger
//	
//	概要＿：シーン管理
//	制作者：加藤 遼
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <stdio.h>
#include <iostream>

#include "SceneManeger.h"
#include "debugproc.h"
#include "Texture.h"

// 各シーン
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneTraning.h"

//-----------------------------
//グローバル
//-----------------------------
cBaseScene* cSceneManeger::m_pScene = NULL;							//現在のシーンの初期化
cSceneManeger::SCENE cSceneManeger::m_nCurrentSceneNum = TITLE;		//現在のシーン番号の初期化
cTransition* pTransition = NULL;									//トランジション

// textureのインスタンス
cTextureManeger* tex = new cTextureManeger();

//=======================================================================================
//
//	シーンチェンジ関数
//	ここにシーンをついかすればいいよ
//	
//	引数
//	scene インスタンス化したいシーン
//=======================================================================================
void cSceneManeger::ChangeScene(SCENE scene){


	if (m_pScene != NULL){
		delete m_pScene;				// シーンの解放
		GetEffectManeger()->Uninit();	// エフェクトの終了処理
	}

	//現在のシーン番号の更新
	SetSceneNum(scene);
	switch (scene){
	case TITLE:
		tex->LoadTexture(TITLE);			// テクスチャのロード
		m_pScene = new cSceneTitle();		// 動的インスタンス&初期化
		break;;
	case GAME:
		tex->LoadTexture(GAME);				// テクスチャのロード
		m_pScene = new cSceneGame();		// 動的インスタンス&初期化
		break;
	case RESULT:
		tex->LoadTexture(RESULT);
		m_pScene = new cSceneResult();		// 動的インスタンス&初期化
		break;
	case TRANING:
		tex->LoadTexture(GAME);				// テクスチャのロード
		m_pScene = new cSceneTraning();
	default:
		break;
	}


}


//=======================================================================================
//
//	トランジション付きのシーンチェンジ関数
//	画面切り替え効果付きで呼び出すときに
//	
//	引数
//	scene インスタンス化したいシーン
//  transition セットするトランジション番号
//=======================================================================================
void cSceneManeger::ChangeSceneSetTransition(SCENE scene, cTransition::TRANSITION_TYPE transition){

	switch (transition)
	{
	case cTransition::TRANSITION_FADE:
		pTransition = new cTransitonFade();
		pTransition->SetTransition(scene);
		break;
	case cTransition::TRANSITION_DICE_SCALE_CHANGE:
		pTransition = new cTransitonDiceScaleChange();
		pTransition->SetTransition(scene);
		break;
	case cTransition::TRANSITION_ONCE_ROTATION:
		pTransition = new cTransitonOnceRotation();
		pTransition->SetTransition(scene);
		break;
	case cTransition::TRANSITION_TILE_CREATE_RANDOM:
		pTransition = new cTransitionTileCreateRandom();
		pTransition->SetTransition(scene);
		break;
	default:
		break;
	}

}

//=======================================================================================
//
//	
//	終了(一応)
//	
//	
//=======================================================================================
void cSceneManeger::Uninit() {

	if (m_pScene != NULL){
		delete m_pScene;	//Uninit
		m_pScene = NULL;
		delete tex;
		tex = NULL;
	}


}

//=======================================================================================
//
//	
//	更新
//	
//	
//=======================================================================================
void cSceneManeger::Update(){


	if (m_pScene == NULL){
		//なんかメッセージボックス出したほうがいいかな？
	}

	else
		m_pScene->Update();	//現在のシーンの更新関数を呼び出す

	//トランジションがある場合は実行
	if (pTransition){
		pTransition->Update();
		if (pTransition->FinishCall()){
			delete pTransition;
			pTransition = NULL;
		}
	}

	
}

//=======================================================================================
//
//	
//	描画
//	
//	
//=======================================================================================
void cSceneManeger::Draw(){


//デバッグ用
#ifdef _DEBUG
	PrintDebugProc("━━━━シーン━━━━\n");
	PrintDebugProc("spaceでシーン切り替え\n");
	PrintDebugProc("シーン番号:%d\n", m_nCurrentSceneNum);
	PrintDebugProc("━━━━━━━━━━━\n");
#endif

	if (m_pScene == NULL){
		//なんかメッセージボックス出したほうがいいかな？
	}

	else
		m_pScene->Draw();	//現在のシーンの描画関数を呼び出す

	//トランジションがある場合は実行
	if (pTransition)
		pTransition->Draw();
}

//=======================================================================================
//
//	現在のシーン番号を設定
//
//=======================================================================================
void cSceneManeger::SetSceneNum(SCENE secene){
	m_nCurrentSceneNum = secene;
}

//=======================================================================================
//
//	現在のシーン番号を受け取り
//
//=======================================================================================
cSceneManeger::SCENE cSceneManeger::GetSceneNum(void){
	return m_nCurrentSceneNum;
}