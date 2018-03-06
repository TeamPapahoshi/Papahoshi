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
#include "Net_Type2.h"
#include "sound.h"

#define MAX_LINE_EFFECT	(1)





//-----------------------------
// クラス定義
//-----------------------------
class cRyuseiData :public cBaseStarData{
public:

	// 流れる処理用
	bool			m_bStream=true;		// 流れるどうか
	D3DXVECTOR2		m_StreamStartPos;	// 流れるスタート位置
	D3DXVECTOR2		m_StreamGoalPos;	// 流れるゴール位置
	D3DXVECTOR2		m_VecStreamMove;	// 流れる方向のベクトル
	float			m_StremCos;			// 計算用
	float			m_StreamRad;		// 計算用
	D3DXVECTOR2		m_MoveSpped;		// 流れるスピードベクトル

	cSpriteParam	m_MeteorLight;		// 光の表現



	//


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
	void OnCollidToNetArea(int num);
	void SetStream(bool a ,int num){
		m_pStarData = m_pRoot;
		m_pStarData += num;

		m_pStarData->m_bStream = a;
	}

	void Create();		// 生成
	void Destroy();		// 削除
	void Respawn();		// リスポーン

	void SetFeverStar(){

		// 流星音
		PlaySound(SOUND_LABEL_SE_STREAM_METEOR);

		m_bFever = true;

		m_pStarData = m_pRoot;

		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

			if (m_pStarData->m_bUse)
				continue;

			m_pStarData->m_bCreateEvent = true;
		}
		
	}

	void SetFeverEnd(){
		m_bFever = false;
	}


private:
	cRyuseiData*	m_pStarData;		// 必要データ
	cRyuseiData*	m_pRoot;			// 先頭アドレス格納用
	cNet*			m_pNetData;			// 網のデータ格納

	bool			m_bFever;



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