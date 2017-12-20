//======================================================================
//	BlackHole
//	
//	概要＿：ブラックホール
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___BLACK_HOLE_H___
#define ___BLACK_HOLE_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"

#include <vector>
#include <fstream>

//struct SetNormalStar{
//	D3DXVECTOR2 center;
//	D3DXVECTOR2 radius;
//	D3DXVECTOR2 size;
//	float		speed;
//};



//-----------------------------
//クラス定義
//-----------------------------
//******ブラックホール********
class cBlackHole :public cBaseStar{

public:
	void Update();
	void Draw();

	~cBlackHole();
	cBlackHole();

	// 星の設定
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

	// ファイルで読み込んだデータをセット
	//void SetStarFromFile(int loop);

	// 恒星との距離によってみえるか見えないかを変える処理
	//void StarVisibility(float distance);

	// 計算用の位置を取得
	D3DXVECTOR2 GetPos(){
		return m_sprite.GetPos();
	}

private:
	cCircleOrbitMovement moveCircle;	// 円軌道するために必要


};
#endif	//!___BLACK_HOLE_H___