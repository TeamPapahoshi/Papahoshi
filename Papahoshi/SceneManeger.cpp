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
#include<stdio.h>
#include<iostream>

#include"SceneManeger.h"
#include"debugproc.h"
#include"Texture.h"

// 各シーン
#include"SceneTitle.h"
#include"SceneStageSelect.h"
#include"SceneGame.h"
//#include"SceneResult.h"

//-----------------------------
//グローバル
//-----------------------------
cBaseScene* cSceneManeger::m_pScene = NULL;							//現在のシーンの初期化
cSceneManeger::SCENE cSceneManeger::m_nCurrentSceneNum = TITLE;		//現在のシーン番号の初期化

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
		delete m_pScene;	// シーンの解放
	}

	//現在のシーン番号の更新
	SetSceneNum(scene);

	switch (scene){
	case TITLE:
		tex->LoadTexture(TITLE);			// テクスチャのロード
		m_pScene = new cSceneTitle();		// 動的インスタンス&初期化
		break;
	case STAGE_SELECT:
		tex->LoadTexture(STAGE_SELECT);		// テクスチャのロード
		m_pScene = new cSceneStageSelect();
		break;
	case GAME:
		tex->LoadTexture(GAME);				// テクスチャのロード
		m_pScene = new cSceneGame();		// 動的インスタンス&初期化
		break;
	//case RESULT:
	//	m_pScene = new cResultScene();		// 動的インスタンス&初期化
	//	break;
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

	PrintDebugProc("spaceでシーン切り替え\n");
}

//=======================================================================================
//
//	
//	描画
//	
//	
//=======================================================================================
void cSceneManeger::Draw(){

	if (m_pScene == NULL){
		//なんかメッセージボックス出したほうがいいかな？
	}

	else
		m_pScene->Draw();	//現在のシーンの描画関数を呼び出す

//デバッグ用
#ifdef _DEBUG
	PrintDebugProc("シーン番号:%d\n",m_nCurrentSceneNum);
#endif

}

//=======================================================================================
//
//	現在のシーン番号を設定
//
//=======================================================================================
void cSceneManeger::SetSceneNum(SCENE secene){
	m_nCurrentSceneNum = secene;
}