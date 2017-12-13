//======================================================================
//	Title
//	
//	概要＿：タイトル
//	制作者：
//	
//======================================================================

//------------------------------
// インクルードファイル
//------------------------------
#include "SceneTitle.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"
#include "sound.h"


// このシーンで使うオブジェクト
#include "Player.h"
#include "Enemy.h"


//-----------------------------
// グローバル
//-----------------------------
// このシーンで使うオブジェクトのポインタを用意(ここでインスタンス化しない)
cPlayer* pPlayer;
cEnemy*	 pEnemy;


//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneTitle::cSceneTitle(){

	// 使うオブジェクトのインスタンス
	pPlayer = new cPlayer();
	pEnemy = new cEnemy();

	// テクスチャの読み込み
	LoadTextureFromFile();

	// プレイヤー
	pPlayer->Init(&m_pTex[PLAYER]);

	// エネミー
	pEnemy->Init(&m_pTex[ENEMY]);

	// 音源
	PlaySound(SOUND_LABEL_BGM000);	

}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cSceneTitle::~cSceneTitle(){

	StopSound(SOUND_LABEL_BGM000);
	pPlayer->Unit();
	pEnemy->Unit();

	// 動的インスタンスするならdeleteをUnitとは別にここに
	delete pPlayer;
	delete pEnemy;
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneTitle::Update(){

	pPlayer->Update();
	pEnemy->Update();

	// あたり判定
	if (cCollider::CheckCollisionCircleToCircle(pPlayer->GetCollider(), pEnemy->GetCollider())){
		pPlayer->OnColidToEnemy();	// エネミーに当たった時のプレイヤーの処理
		//enemy.OnColidToPlayer();	// プレイヤーに当たった時のエネミーーの処理
	}

	// スペースでシーンチェンジ
	if (GetKeyboardTrigger(DIK_SPACE)){
		cSceneManeger::ChangeScene(cSceneManeger::STAGE_SELECT);
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cSceneTitle::Draw(){

	pEnemy->Draw();
	pPlayer->Draw();
}


//=======================================================================================
//
//		このシーンで使うテクスチャの読込
//		ヘッダーのenumとこの関数のchar*配列に追加すればテクスチャがロードされます
//		※ヘッダーのenumとchar配列のファイル名の順番が一致するようにしてください
//		シーンが変わるとテクスチャも消えちゃうのでので同じオブジェクトを別シーンで呼ぶ
//		時はもう一度使うテクスチャを書いてください
//
//=======================================================================================
void cSceneTitle::LoadTextureFromFile(){

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// このシーンで使うテクスチャのファイル名
	char* pTexture[MAX_TEXTURE] = {			//※順番注意enumの順にファイル名を書いて
		{ TEXTURE_FILNAME_PLAYER },
		{ TEXTURE_FILNAME_ENEMY }
	};

	// ロード
	for (int i = 0; i < MAX_TEXTURE; i++){
		D3DXCreateTextureFromFile(pDevice, pTexture[i], &m_pTex[i]);
	}
}
