//======================================================================
//	Star
//	
//	概要＿：星クラスなど
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___STAR_H___
#define ___STAR_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Sprite.h"
#include "Collision.h"



//-----------------------------
//クラス定義
//-----------------------------
//----継承用 星基本クラス----
class cBaseStar{
public:
	virtual void Update() = 0;	// 必須
	virtual void Draw() = 0;	// 必須
	virtual ~cBaseStar(){}		// デストラクタをオーバライドさせるため
};


//----継承用 円軌道星----
class cCircleOrbitStar :public cBaseStar{

public:



	 void Init(LPDIRECT3DTEXTURE9* pTex);	// 初期化 テクスチャのポインタを受け取って
	 void Update();				// 必須
	 void Draw();				// 必須
	 void Uninit();				// 終了

	 ~cCircleOrbitStar(){}		// デストラクタ
	 cCircleOrbitStar();		// コンストラクタ
private:
	cSpriteParam	m_sprite;		// 描画用
	cCollider		m_collision;	// あたり判定	
	D3DXVECTOR2		m_fMove;		// 移動量

};



#endif	//!___STAR_H___