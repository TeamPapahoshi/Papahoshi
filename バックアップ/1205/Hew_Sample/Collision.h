//======================================================================
//	Collision.h
//	
//	概要＿：Collision
//	制作者：加藤　遼
//	
//======================================================================

#ifndef ___COLLISION_H___
#define ___COLLISION_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Common.h"
#include <Windows.h>
#include "Sprite.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define TEXTURE_FILENAME_CIRCLE_COLLIDER	("Image/Collision/Circle/Circle.png")	// 円のコライダー
#define TEXTURE_FILENAME_CIRCLE_QUAD		("Image/Collision/Quad/Quad.png")		// 四角のコライダー


//-----------------------------
//構造体定義
//-----------------------------
//----あたり判定の要素(サイズ　位置　半径)をまとめた----
typedef struct _tCollisionBody{

	D3DXVECTOR2	QuadPos = D3DXVECTOR2(0.0f, 0.0f);		//四角の中心座標
	D3DXVECTOR2	QuadSize = D3DXVECTOR2(0.0f, 0.0f);		//四角のサイズ
	D3DXVECTOR2	CirclePos = D3DXVECTOR2(0.0f, 0.0f);	//円の中心座標
	float	fRadius = 0.0f;								//円の半径

}tCollisionBody;

//-----------------------------
//クラス定義
//-----------------------------
// コライダークラス(あたり判定をもつクラスのprivateにもたせて使うplayerみてください)
class cCollider{

public:

	// あたり判定の種類
	enum CollisionType{
		CIRCLE,	// 円
		QUAD	// 四角
	};

	cCollider();	// コンストラクタ
	~cCollider(){}	// デストラクタ

	
	// 円のコライダーのセット
	void SetCircleCollider(D3DXVECTOR2 pos ,float radius){
		m_tColBody.CirclePos = pos;
		m_tColBody.fRadius = radius;
	}
	
	// 四角のコライダーのセット
	void SetQuadCollider(D3DXVECTOR2 pos, D3DXVECTOR2 size){
		m_tColBody.QuadPos = pos;
		m_tColBody.QuadSize = size;
	}

	// 使用するあたり判定のセット
	void SetType(CollisionType type){
		m_type = type;
	}

	// コライダーの取得
	tCollisionBody GetCollider(){
		return m_tColBody;
	}

	// 円と円のあたり判定
	static bool CheckCollisionCircleToCircle(cCollider obj1, cCollider obj2);	

	// 描画
	void Draw();	
	
private:
	tCollisionBody	m_tColBody;	// あたり判定の要素
	cSpriteParam	sprite;		// スプライトパラメーター
	CollisionType	m_type;		// あたり判定の種類

};
#endif	//!___COLLISION_H___