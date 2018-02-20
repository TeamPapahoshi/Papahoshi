//======================================================================
//	Ryusei.h
//	
//	概要＿：流星
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___RYUSEI_H___
#define ___RYUSEI_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "BaseStar.h"
#include "Sprite.h"
#include "RyuseiLine.h"
#include "Net_Type2.h"

#define MAX_LINE_EFFECT	(1)

//-----------------------------
// クラス定義
//-----------------------------
class cRyuseiData :public cBaseStarData{
public:

	D3DXVECTOR2		cp1, cp2, cp3, cp4;	// ベジェ曲線計算用
	float			time=0;
	cSpriteParam	m_Core;				//　核
	cRyuseiLine		m_Line;


	D3DXVECTOR2		m_VecMove;			// 移動方向のベクトル

};

class cRyusei :public cBaseStar{

public:
	void Update();
	void Draw();
	~cRyusei();
	cRyusei();


	//--- 網との処理 ---
	void SetNetData(cNet* data);
	void OnCollidToNet(int num);

	void Create();		// 生成
	void Destroy();		// 削除
	void Respawn();		// リスポーン

private:
	cRyuseiData*	m_pStarData;		// 必要データ
	cRyuseiData*	m_pRoot;			// 先頭アドレス格納用
	cRyuseiLine*	m_pLine;
	cNet*			m_pNetData;			// 網のデータ格納




	//Set&Get
public:

	// Getter
	cRyuseiData* GetStarData(){
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
#endif	//!___RYUSEI_H___