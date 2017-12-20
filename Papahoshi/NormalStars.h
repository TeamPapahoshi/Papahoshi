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

#include <vector>
#include <fstream>

struct SetNormalStar{
	D3DXVECTOR2 center;
	D3DXVECTOR2 radius;
	D3DXVECTOR2 size;
	float		speed;
};

// マクロ定義
#define STAGE_01_STAR_NUM	(5)



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

	// ファイルで読み込んだデータをセット
	void SetStarFromFile(int loop);

	// 恒星との距離によってみえるか見えないかを変える処理
	void StarVisibility(float distance);

	// 計算用の位置を取得
	D3DXVECTOR2 GetPos(){
		return m_sprite.GetPos();
	}

	// 仮
	enum STAFGE_NUM{
		STAGE_01,
		STAGE_MAX,
	};


private:
	cCircleOrbitMovement moveCircle;	// 円軌道するために必要
	vector<SetNormalStar> a_Data;
	STAFGE_NUM stageNum = STAGE_01; //仮

};
#endif	//!___NORMAL_STARS_H___