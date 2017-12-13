//======================================================================
//	Player
//	
//	概要＿：プレイヤー(仮)
//	制作者：
//	
//======================================================================
#ifndef ___PLAYER_H___
#define ___PLAYER_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Sprite.h"
#include "Collision.h"


//-----------------------------
//クラス定義
//-----------------------------
class cPlayer{

public:
	cPlayer(){}		// コンストラクタ
	~cPlayer(){}	// デストラクタ

	// ここは何かから継承させてもいいかもオーバライド
	void Init(LPDIRECT3DTEXTURE9* pTex);	// 初期化 テクスチャのポインタを受け取って
	void Unit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

	// エネミーと当たった時の処理
	void OnColidToEnemy();

	// プレイヤーのあたり判定の取得
	cCollider GetCollider(){
		return collider;
	}

private:
	// プレイヤーに必要なもの
	cSpriteParam	sprite;			// スプライトのステータス
	cCollider		collider;		// あたり判定
};
#endif	//!___PLAYER_H___



