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

//-----------------------------
// クラス定義
//-----------------------------
class cNormalStarData :public cBaseStarData{
public:


};

class cNormalStar :public cBaseStar{

public:
	void Update();
	void Draw();
	~cNormalStar();
	cNormalStar();

	//--- 網との処理 ---
	void SetNetData(cNet* data);
	void OnCollidToNet(int num);
	
	//--- ブラックホールとの処理 ---
	void SetBlackHoleData(cBlackHole* data);
	void OnCollidToBlackHole(int Normal,int Black);
	void OnCollidToDelete(int Normal);
	
	void Create();		// 生成
	void Destroy();		// 削除
	void Respawn();		// リスポーン

private:
	cNormalStarData*	m_pStarData;		// 必要データ
	cNormalStarData*	m_pRoot;			// 先頭アドレス格納用
	cBlackHole*			m_pBlackHoleData;	// ブラックホールのデータを格納
	cNet*				m_pNetData;			// 網のデータ格納


	//Set&Get
public:

	// Getter
	cNormalStarData* GetStarData(){
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
#endif	//!___NORMAL_STARS_H___