//======================================================================
//	Player
//	
//	概要＿：プレイヤー処理(仮)
//	制作者：
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include "SceneManeger.h"	//BaseScene
#include "debugproc.h"		//printdebug
#include "d3dx9.h"			//D3DXVECTOR2他

#include "Input.h"
#include "Player.h"
#include "Texture.h"


//-----------------------------
//マクロ定義
//-----------------------------
//----プレイヤー関連----
#define PLAYER_DEFAULT_POS	(D3DXVECTOR2(100.0f,100.0f))
#define PLAYER_MOVE_SPEED	(4.0f)


//-----------------------------
//グローバル
//-----------------------------
bool g_hit = false;	//仮

//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cPlayer::Init(){ //pTex

	// ここで初期化しないとそれぞれのクラスのコンストラクタの値で初期化される

	// Sprite
	sprite.SetPos(PLAYER_DEFAULT_POS);										// 座標セット
	sprite.SetTexPatternDevide(4, 4);										// テクスチャの分割数のセット
	sprite.SetCurrentAnimPattern(0);										// テクスチャの現在のパターン番号セット
	sprite.SetTexture(cTextureManager::GetTextureTitle(TEX_TITLE_JELLY));	// テクスチャのセット

	// Collider
	collider.SetType(cCollider::CollisionType::CIRCLE);						// 使用するあたり判定を指定
	collider.SetCircleCollider(sprite.GetPos(), sprite.GetSizeX() / 2.0f);	// あたり判定の座標セット(Updateのしわすれ注意)
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cPlayer::Unit(){
	// StopSoundとかメモリの解放とか
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cPlayer::Update(){
	
	//移動
	if (GetKeyboardPress(DIK_RIGHT)){
		sprite.SetPosX(sprite.GetPosX() + PLAYER_MOVE_SPEED);
	}
	else if (GetKeyboardPress(DIK_LEFT)){
		sprite.SetPosX(sprite.GetPosX() - PLAYER_MOVE_SPEED);
	}
	else if (GetKeyboardPress(DIK_UP)){
		sprite.SetPosY(sprite.GetPosY() - PLAYER_MOVE_SPEED);
	}
	else if (GetKeyboardPress(DIK_DOWN)){
		sprite.SetPosY(sprite.GetPosY() + PLAYER_MOVE_SPEED);
	}

	// あたり判定の位置の更新
	collider.SetCircleCollider(sprite.GetPos(), sprite.GetSizeX() / 2.0f);

	// アニメーション
	// sprite.SetCurrentAnimPattern(sprite.GetCurrentAnimPattern() + 1);
	

	g_hit = false;

}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cPlayer::Draw(){

	//描画
	sprite.Draw();
	collider.Draw();

//デバッグ
#ifdef _DEBUG
	PrintDebugProc("プレイヤー中心座標(%f,%f)\n", sprite.GetPosX(), sprite.GetPosY());
	PrintDebugProc("当たった:%d\n", g_hit);
#endif
}

//=======================================================================================
//
//		プレイヤーがエネミーと衝突したときのプレイヤーの処理
//
//=======================================================================================
void cPlayer::OnColidToEnemy(){
	g_hit = true;
}