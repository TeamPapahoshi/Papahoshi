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
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void UnInit() = 0;
	virtual ~cBaseStar(){}


};


//----円軌道星----
class cCircleOrbitStar :public cBaseStar{

public:
	 void Init();
	 void Update();
	 void Draw();
	 void UnInit();

	 ~cCircleOrbitStar(){}
	 cCircleOrbitStar() :m_center(D3DXVECTOR2(100.0f, 100.0f)), m_radius(D3DXVECTOR2(50.0f,50.0f)), m_rad(D3DX_PI){}

	 // 星の設定
	 void SetcCircleOrbitStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

private:
	cSpriteParam	m_sprite;		// 描画用
	cCollider		m_collision;	// あたり判定	
	D3DXVECTOR2		m_center;		// 軌道の中心座標
	D3DXVECTOR2		m_radius;		// 半径
	float			m_rad;			// 角度
	int				m_second;		// 一周にかかる時間(秒)
};



#endif	//!___STAR_H___