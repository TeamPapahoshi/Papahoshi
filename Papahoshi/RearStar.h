//======================================================================
//	RearStar
//	
//	概要＿：レア星
//	制作者：加藤　遼
//	
//======================================================================
#ifndef ___REAR_STAR_H___
#define ___REAR_STAR_H___

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
// 列挙体定義
//-----------------------------
enum eRearStarType{
	PANET_01,
	PANET_02,
	PANET_03,
	SUN,
	REAR_TYPE_MAX
};
//-----------------------------
// クラス定義
//-----------------------------
class cRearStarData :public cBaseStarData{
public:
	cCollider		m_VacumeRange;		// 吸い込み範囲
	cCollider		m_DeleteRange;		// 削除範囲

	eRearStarType	m_eType;			// 種類
};


class cRearStar :public cBaseStar{

public:
	void Update();
	void Draw();
	~cRearStar();
	cRearStar();

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
	cRearStarData* m_pStarData;	// 必要データ
	cRearStarData*	m_pRoot;	// 先頭アドレス格納用
	cNet*			m_pNetData;

	//Set&Get
public:

	// Getter
	cRearStarData* GetStarData(){
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