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
#include "Net_Type2.h"


//-----------------------------
// 構造体定義
//-----------------------------
//-----------------------------
// クラス定義
//-----------------------------
class cSpaceRockData :public cBaseStarData{
public:

};


//-----------------------------
//クラス定義
//-----------------------------
class cSpaceRock :public cBaseStar{

public:
	void Update();
	void Draw();
	~cSpaceRock();
	cSpaceRock();

	//--- 網との処理 ---
	void SetNetData(cNet* data);
	void OnCollidToNet(int num);

	void Create();		// 生成
	void Destroy();		// 削除
	void Respawn();		// リスポーン

private:
	cSpaceRockData* m_pStarData;	// 必要データ
	cSpaceRockData*	m_pRoot;	// 先頭アドレス格納用
	cNet*			m_pNetData;

	//Set&Get
public:

	// Getter
	cSpaceRockData* GetStarData(){
		return m_pRoot;
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
#endif //!___SPACE_ROCK_H___