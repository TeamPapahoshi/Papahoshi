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
#define MAX_BLACK_HOLE_NUM	(1)



//-----------------------------
// 構造体定義
//-----------------------------
// ブラックホールのデータ
typedef struct _tBlackHoleData{

	cSpriteParam			t_Sprite;				// 描画用
	cCollider				t_VacuumCollider;		// 吸い込み範囲
	cCollider				t_DeleteCollider;		// 消滅範囲
	cCircleOrbitMovement	t_MoveCircle;			// 円軌道用判定
	bool					t_bUse;					// 使用フラグ

}tBlackHoleData;

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

	// Getter
	tBlackHoleData* GetStarData(){
		return m_pStarData;
	}

	// 星の設定
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

private:
	tBlackHoleData*	m_pStarData;
};
#endif //!___BLACK_HOLE_H___