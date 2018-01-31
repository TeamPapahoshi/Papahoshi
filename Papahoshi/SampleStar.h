//======================================================================
//	SampleStar
//	
//	概要＿：コピー用星
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___SAMPLE_STAR_H___
#define ___SAMPLE_STAR_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"


//-----------------------------
//クラス定義
//-----------------------------
//------- 構造体みたいに使う ---------
class cSampleStarData :public cBaseStarData{
public:
	// この星だけ(例)
	cCollider		m_VacuumCollider;				// 吸い込み範囲
	cCollider		m_DeleteCollider;
	float rad;										// テスト用演出確認
};

//--- シーンでインスタンス方  --------
class cSampleStar :public cBaseStar{		

public:
	void Update();
	void Draw();
	~cSampleStar();
	cSampleStar();

	void Create();		// 生成
	void Destroy();		// 削除

private:
	cSampleStarData* m_pStarData;	// 必要データ
	cSampleStarData*	m_pRoot;	// 先頭アドレス格納用

//Set&Get
public:

	cSampleStarData* GetStarData(){
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
#endif //!___BLACK_HOLE_H___