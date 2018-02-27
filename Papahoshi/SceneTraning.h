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
// �C���N���[�h��
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
// �N���X��`
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
	cNormalStar*				m_pNomalStar;		// ���u��
	cBlackHole*					m_pBlackHole;		// �u���b�N�z�[��
	cSpaceRock*					m_pSpaceRock;		// 覐�
	vector<cFixedStar*>			m_pFixedStar;		// �P��
	cRyusei*					m_pRyusei;			// ����
	cConstellation*				m_pConsellation;	// ���Q
	cGage*						m_pGage;			// �Q�[�W
	cGameUI*					m_pGameUI;
	cTimer*						m_pTimer;			// �^�C�}�[
	cSampleStar*				m_pSampleStar;
	cAnnounce*					m_pAnnounce;
	cPlaySupport*				m_pPlaySupport;

	bool m_bFever;				// �t�B�[�o�^�C�����ǂ���

	void CheckCollision();	//�����蔻������

	bool CheckCommand();
	int m_nLeverDirection[180];

	bool m_bSceneChange;
};

#endif