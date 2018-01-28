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
#define MAX_BLACK_HOLE_NUM	(5)



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
	int						t_nRespawnFrame;		// リスポーンフレーム
	bool					t_bRespawn;				// リスポーンフラグ

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


	//--- 星のフラグオン & カウントアップ ----
	void CountUp(int num){

		if (!m_pStarData[num].t_bUse){
			m_pStarData[num].t_bUse = true;
			m_nCurrentNum++;
		}

	}
	//--- 星のフラグオフ & カウントダウン ----
	void CountDown(int num){

		if (m_pStarData[num].t_bUse){
			m_pStarData[num].t_bUse = false;
			m_nCurrentNum--;
		}
	}

	// Getter
	tBlackHoleData* GetStarData(){
		return m_pStarData;
	}

	void Create(int num);

	// 星の設定
	void Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

private:
	tBlackHoleData*	m_pStarData;
};
#endif //!___BLACK_HOLE_H___