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
#include "Sprite.h"

#include <vector>
#include <fstream>

struct SetNormalStar{
	D3DXVECTOR2 center;
	D3DXVECTOR2 radius;
	D3DXVECTOR2 size;
	float		speed;
};

//-----------------------------
// マクロ定義
//-----------------------------
#define STAGE_01_STAR_NUM	(5)
#define MAX_NORMAL_STAR		(50)


//-----------------------------
// 構造体定義
//-----------------------------
// モブ星のデータ
typedef struct _tNormalStarData{

	cSpriteParam			t_Sprite;		// 描画用
	cCollider				t_Collider;		// あたり判定
	cCircleOrbitMovement	t_MoveCircle;	// 円軌道用
	bool					t_bUse;			// 使用フラグ
	
}tNormalStarData;

//-----------------------------
// クラス定義
//-----------------------------
//******モブ星********
class cNormalStar :public cBaseStar{

public:
	void Update();
	void Draw();

	~cNormalStar();
	cNormalStar();

	// 星のランダム生成
	void CreateRamdom();


	// 星のリスポーン
	void Respawn();


	// 星の設定
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

private:
	tNormalStarData*	m_pStarData;
	int					m_nMaxNum;


	// フラグ
	bool	m_bCapchared;	// 確保完了

	// フレーム関連
	int m_nRespawnFream;	// リスポーン


};
#endif	//!___NORMAL_STARS_H___