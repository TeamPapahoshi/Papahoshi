//======================================================================
//	星群
//	
//	概要＿：
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___CONSTELLATION_H___
#define ___CONSTELLATION_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"
#include "NormalStars.h"

//-----------------------------
// 列挙体定義
//-----------------------------
enum eConsellationType
{
	TYPE_01,
	TYPE_MAX,
};


//-----------------------------
//クラス定義
//-----------------------------
//------- 構造体みたいに使う ---------
class cConstellationData :public cBaseStarData{		// 星群れ全体
public:
	int m_nStarColorNum;
	cCircleOrbitMovement m_CircleMoveData;			// 円軌道に必要なデータ
	
};

//--- シーンでインスタンス方  --------
class cConstellation :public cBaseStar{

public:
	void Update();
	void Draw();
	~cConstellation();
	cConstellation();

	void Create();		// 生成
	void Destroy();		// 削除
	void Respawn();		// リスポーン

private:
	cConstellationData* m_pStarData;	// 必要データ
	cConstellationData*	m_pRoot;	// 先頭アドレス格納用


	eConsellationType	m_eType;


	//Set&Get
public:

	cConstellationData* GetStarData(){
		return m_pStarData;
	}

	// 生成とかでフラグを操作するときはこの関数を使って
	//※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※
	void SetCountAndUse(bool flag){
		if (flag){
			if (!m_pStarData->m_bUse){
				m_pStarData->m_bUse = true;
				m_nCurrentNum++;
			}
		}
		else{
			if (m_pStarData->m_bUse){
				m_pStarData->m_bUse = false;
				m_nCurrentNum--;
			}
		}
	}
	//※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※
};
#endif //!___CONSTELLATION_H___