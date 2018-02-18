//======================================================================
//	Scenegame
//	
//	�T�v�Q�F�Q�[�����C��(��)
//	����ҁF
//	
//======================================================================

#ifndef ___SCENE_GAME_H___
#define ___SCENE_GAME_H___

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include <d3d9.h>
#include "SceneManeger.h"
#include "Common.h"

// �X�e�[�W
#include "StageManager.h"

// ���̃X�e�[�W�Ŏg���I�u�W�F�N�g
#include "BG.h"

// ��
#include "Net.h"
#include "Net_Type2.h"

// ��
#include "SampleStar.h"
#include "NormalStars.h"
#include "FixedStars.h"
#include "Ryusei.h"
#include "Gage.h"

#include "BlackHole.h"
#include "SpaceRock.h"

#include "GameUI.h"

#include "Announce.h"
#include "Timer.h"


// �Ăяo�����̐�
#define STAR_NUM		(5)	//��
#define FIXED_STAR_NUM	(1)	//��


//------------------------------
// �񋓑̒�`
//------------------------------
// �Q�[���̏��
enum eGameState{
	GAME_STATE_SET,		// 3,2,1 Start
	GAME_STATE_MAIN,	// ���C��
	GAME_STATE_END,		// TimeUp
};

//------------------------------
// �N���X��`
//------------------------------
//----�V�[���Q�[��-----
class cSceneGame :public cBaseScene{

public:
	//---- �v���g�^�C�v�錾 ----
	void Draw();	//�`��
	void Update();	//�X�V
	cSceneGame();	//�R���X�g���N�^
	~cSceneGame();	//�f�X�g���N�^

private:
	// ���̃V�[���ŃC���X�^���X������̂̃|�C���^
	cBG*						m_pBG;
	cNet*						m_pNet;
	cNormalStar*				m_pNomalStar;		// ���u��
	cBlackHole*					m_pBlackHole;		// �u���b�N�z�[��
	cSpaceRock*					m_pSpaceRock;		// 覐�
	vector<cFixedStar*>			m_pFixedStar;		// �P��
	cRyusei*					m_pRyusei;			// ����
	cGage*						m_pGage;			// �Q�[�W
	cGameUI*					m_pGameUI;
	cTimer*						m_pTimer;			// �^�C�}�[
	cSampleStar*				m_pSampleStar;
	cAnnounce*					m_pAnnounce;


	// �Q�[���̏��
	eGameState					m_eGameState;
	void SetUpdate();
	void MainUpdate();
	void EndUpdate();

	// �Q�[�����C���p
	bool m_bFever;				// �t�B�[�o�^�C�����ǂ���





	void CheckCollision();	//�����蔻������
};



#endif //!___SCENE_TITLE_H___