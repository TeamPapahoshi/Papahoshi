//======================================================================
//	NormalStars
//	
//	概要＿：星クラスなど
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___NORMAL_STARS_H___
#define ___NORMAL_STARS_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"

//-----------------------------
//クラス定義
//-----------------------------
//******モブ星********
class cNormalStar :public cBaseStar{

public:
	void Update();
	void Draw();

	~cNormalStar();
	cNormalStar();

	// 星の設定
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

	// 恒星との距離によってみえるか見えないかを変える処理
	void StarVisibility(float distance);

	// 計算用の位置を取得
	D3DXVECTOR2 GetPos(){
		return m_sprite.GetPos();
	}

private:
	cCircleOrbitMovement moveCircle;	// 円軌道するために必要

};

#endif	//!___NORMAL_STARS_H___