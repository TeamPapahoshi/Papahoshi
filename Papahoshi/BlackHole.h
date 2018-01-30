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
// マクロ定義
//-----------------------------
#define MAX_BLACK_HOLE_NUM	(100)



//-----------------------------
//クラス定義
//-----------------------------

class cBlackHoleData :public cBaseStarData{

public:
	// 追加分だけ
	cCollider		m_VacuumCollider;				// 吸い込み範囲
	cCollider		m_DeleteCollider;


	float rad;			// テスト用演出確認

	
};

class cBlackHole :public cBaseStar{		//使わないかもだけど一応継承して

public:
	void Update();
	void Draw();
	~cBlackHole();
	cBlackHole();


	// Getter
	cBlackHoleData* GetStarData(){
		return m_pStarData;
	}

	void Create();

private:
	cBlackHoleData* m_pStarData;	// ブラックホールの必要データ
	cBlackHoleData*	m_pRoot;		// 先頭アドレス格納用

};
#endif //!___BLACK_HOLE_H___