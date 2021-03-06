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
	cCollider	m_VacumeRange;		// 吸い込み範囲
	cCollider	m_DeleteRange;		// 削除範囲
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

	//---- 生成スタート ----
	void SetCreateStart(){
		m_pStarData = m_pRoot;
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
			m_pStarData->m_bCreateEvent = true;
		}
	}


	bool GetCapturedFlag(){
		return m_pStarData->m_bCaptured;
	}

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

#endif //!___BLACK_HOLE_H___