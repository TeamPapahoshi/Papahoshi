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

private:
	cCollider		m_Collider;			// あたり判定
	int				m_nVacuumStar;		// 吸い込む星の数
	D3DXVECTOR2		move;				// 移動量
};
#endif //!___BLACK_HOLE_H___