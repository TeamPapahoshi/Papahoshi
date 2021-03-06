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
#include "Gage.h"
#include <vector>
#include <fstream>
#include "Score.h"
#include "GameMain.h"	// エフェクトクラス取得用

//-----------------------------
// クラス定義
//-----------------------------
class cNormalStarData :public cBaseStarData{
public:
	bool	m_bVibration = true;
	int		m_nVibrationFrame = 0;
	int		m_nEffectFrame = 0;
	int		m_nStarColorNum = 0;
	bool	m_bAddScore = false;
	int		m_nLifeTime = 0;

	// ブラックホール
	bool	m_bHitBlackHoleDelete=false;

	// 正存時間で消滅
	bool	m_DeleteToLifeTime=false;

	// 隕石
	bool	m_bHitSpaceRock = false;




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
	void OnCollidToBlackHoleVacumeRange(int Normal,int Black);
	void OnCollidToBlackHoleDeleteRange(int Normal,int Black);

	//--- 隕石との処理との処理 ---
	void SetSpaceRockData(cBlackHole* data);
	void OnCollidToSpaceRock(int num);
	
	//--- ゲージとの処理 ---
	void SetGageData(cGage* data);
	
	void Create();		// 生成
	void Destroy();		// 削除
	void Respawn();		// リスポーン

private:
	cNormalStarData*	m_pStarData;		// 必要データ
	cNormalStarData*	m_pRoot;			// 先頭アドレス格納用
	cBlackHole*			m_pBlackHoleData;	// ブラックホールのデータを格納
	cNet*				m_pNetData;			// 網のデータ格納
	cGage*				m_pGageData;		// ゲージのデータ格納
	bool	m_bSound = false;
	int		m_nSoundLimit = 0;

	// リスポーンするときに初期化するもの
	void Init();
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