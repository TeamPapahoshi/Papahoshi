//======================================================================
//	FixedStars
//	
//	概要＿：星クラスなど
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___FIXED_STARS_H___
#define ___FIXED_STARS_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"

//-----------------------------
//クラス定義
//-----------------------------

//******恒星********
class cFixedStar :public cBaseStar{

public:
	void Update();
	void Draw();

	~cFixedStar();
	cFixedStar();

	// 星の設定
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

	void SetCounAndUse(bool flag){}
private:
	cCollider		m_Collider;			// あたり判定
	cCircleOrbitMovement moveCircle;
	bool m_bSizeSwitch;

};


#endif	//!___FIXED_STARS_H___