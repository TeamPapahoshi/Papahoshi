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
#include "Net_Type2.h"
#include "BlackHole.h"

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
	cCollider				t_Collider;		// あたり
	cCircleOrbitMovement	t_MoveCircle;	// 円軌道用判定
	bool					t_bUse;			// 使用フラグ
	D3DXVECTOR2				t_Move;
	
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

	//--- 網との処理 ---
	void OnCollidToNet(int count);
	void SetNetData();

	//--- ブラックホールとの処理 ---
	void OnCollidToBlackHole(int Normal,int Black);
	void OnCollidToDelete(int Normal);
	void SetBlackHoleData(cBlackHole*);


	//--- 星のランダム生成 ---
	void CreateRamdom();

	//--- 星のリスポーン ---
	void Respawn();


	//--- 星の設定 ---
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);


	// Getter
	tNormalStarData* GetStarData(){
		return m_pStarData;
	}

private:
	cNet*				m_pNetData;
	tNormalStarData*	m_pStarData;
	cBlackHole*			m_pBlackHoleData;

	

};
#endif	//!___NORMAL_STARS_H___