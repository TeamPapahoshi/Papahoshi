//======================================================================
//	SpaceRock
//	
//	概要＿：隕石
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___SPACE_ROCK_H___
#define ___SPACE_ROCK_H___

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
#define MAX_SPACE_ROCK_NUM	(1)



//-----------------------------
// 構造体定義
//-----------------------------
// ブラックホールのデータ
typedef struct _tSpaceRockData{

	cSpriteParam			t_Sprite;				// 描画用
	cCollider				t_Collider;				// あたり判定
	cCircleOrbitMovement	t_MoveCircle;			// 円軌道用判定
	bool					t_bUse;					// 使用フラグ

}tSpaceRockData;

//-----------------------------
//クラス定義
//-----------------------------
class cSpaceRock :public cBaseStar{

public:
	void Update();
	void Draw();
	~cSpaceRock();
	cSpaceRock();

	// Getter
	tSpaceRockData* GetStarData(){
		return m_pStarData;
	}

	// 星の設定
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

private:
	tSpaceRockData*	m_pStarData;
};
#endif //!___SPACE_ROCK_H___