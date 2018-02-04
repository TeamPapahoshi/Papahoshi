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
#include "Net_Type2.h"
#include <vector>
#include <fstream>

//-----------------------------
// クラス定義
//-----------------------------
class cBlackHoleData :public cBaseStarData{
public:
};


class cBlackHole :public cBaseStar{

public:
	void Update();
	void Draw();
	~cBlackHole();
	cBlackHole();

	//--- 網との処理 ---
	void SetNetData(cNet* data);
	void OnCollidToNet(int num);

	void Create();		// 生成
	void Destroy();		// 削除
	void Respawn();		// リスポーン

private:
	cBlackHoleData* m_pStarData;	// 必要データ
	cBlackHoleData*	m_pRoot;	// 先頭アドレス格納用
	cNet*			m_pNetData;

	//Set&Get
public:

	// Getter
	cBlackHoleData* GetStarData(){
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