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
#include <Windows.h>		//HRESULT他
#include "SceneManeger.h"	//BaseScene
#include "debugproc.h"		//printdebug

#include "Input.h"
#include "Enemy.h"
#include"Texture.h"

//-----------------------------
//マクロ定義
//-----------------------------
//----エネミー関連----
#define ENEMY_MOVE_SPEED	(D3DXVECTOR2(4.0f,4.0f))
#define ENEMY_DEFAULT_POS	(D3DXVECTOR2(500.0f,500.0f))

//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cEnemy::Init(){
	
	sprite.SetPos(ENEMY_DEFAULT_POS);
	sprite.SetTexPatternDevide(4, 4);
	sprite.SetCurrentAnimPattern(0);
	//sprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_JELLY));

	collider.SetCircleCollider(sprite.GetPos(), sprite.GetSizeX() / 2.0f);
	collider.SetType(cCollider::CollisionType::CIRCLE);
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cEnemy::Unit(){

}
//=======================================================================================
//
//		更新
//
//=======================================================================================
void cEnemy::Update(){
	collider.SetCircleCollider(sprite.GetPos(), sprite.GetSizeX() / 2.0f);
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cEnemy::Draw(){

	sprite.Draw();
	collider.Draw();

	//デバッグ
#ifdef _DEBUG
	PrintDebugProc("エネミー中心座標(%f,%f)\n", sprite.GetPosX(), sprite.GetPosY());
#endif
}
