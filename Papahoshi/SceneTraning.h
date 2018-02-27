//===========================================
//
// Papahoshi  SceneTraning.h
//
// Mei Goto.
//
//===========================================

#ifndef __SCENE_TRANING_H__
#define __SCENE_TRANING_H__

//-----------------------------
// インクルード部
//-----------------------------
#include "SceneManeger.h"
#include "Common.h"
#include "PlaySupport.h"
#include "StageManager.h"
#include "BG.h"
#include "Net_Type2.h"
#include "SampleStar.h"
#include "NormalStars.h"
#include "FixedStars.h"
#include "Ryusei.h"
#include "Constellation.h"
#include "Gage.h"
#include "BlackHole.h"
#include "SpaceRock.h"
#include "GameUI.h"
#include "Announce.h"
#include "Timer.h"

//-----------------------------
// クラス定義
//-----------------------------
class cSceneTraning : public cBaseScene{

public:
	cSceneTraning();
	~cSceneTraning();
	void Update();
	void Draw();

private:
	cBG*						m_pBG;
	cNet*						m_pNet;
	cNormalStar*				m_pNomalStar;		// モブ星
	cBlackHole*					m_pBlackHole;		// ブラックホール
	cSpaceRock*					m_pSpaceRock;		// 隕石
	vector<cFixedStar*>			m_pFixedStar;		// 恒星
	cRyusei*					m_pRyusei;			// 流星
	cConstellation*				m_pConsellation;	// 星群
	cGage*						m_pGage;			// ゲージ
	cGameUI*					m_pGameUI;
	cTimer*						m_pTimer;			// タイマー
	cSampleStar*				m_pSampleStar;
	cAnnounce*					m_pAnnounce;
	cPlaySupport*				m_pPlaySupport;

	bool m_bFever;				// フィーバタイムかどうか

	void CheckCollision();	//当たり判定を取る

	bool CheckCommand();
	int m_nLeverDirection[180];

	bool m_bSceneChange;
};

#endif