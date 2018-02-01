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
#include <math.h>

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
	D3DXVECTOR2 TriangleVertexPos[3];					//三角形の各頂点(時計回りに設定)

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
		QUAD,	// 四角
		TRIANGLE,	//三角形
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

	// 三角形のコライダーのセット
	void SetTriangleCollider(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 pos3){
		m_tColBody.TriangleVertexPos[0] = pos1;
		m_tColBody.TriangleVertexPos[1] = pos2;
		m_tColBody.TriangleVertexPos[2] = pos3;
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

	//円と三角の当たり判定
	static bool CheckCollisionCircleToTriangle(cCollider circle, cCollider triangle);

	// 描画
	void Draw();	

	//数学的な関数だけど
	static float	VectorDotProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2);	//ベクトルの内積
	static float	VectorCrossProduct(D3DXVECTOR2 v1, D3DXVECTOR2 v2);	//ベクトルの外積
	static float	VectorSize(D3DXVECTOR2 v);	//ベクトルの大きさ
	
private:
	tCollisionBody	m_tColBody;	// あたり判定の要素
	cSpriteParam	sprite;		// スプライトパラメーター
	CollisionType	m_type;		// あたり判定の種類


};

// 計算関数

// 二点間の距離を求める
float CalculateDistanceAtoB(D3DXVECTOR2 posA, D3DXVECTOR2 posB); 
bool CheckCollisionCircleToLine(D3DXVECTOR2 circle, float Cradius, D3DXVECTOR2 leftpos, D3DXVECTOR2 rightpos);





#endif	//!___COLLISION_H___