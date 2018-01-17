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
#include "Net.h"
#include "Net_Type2.h"

// �X�e�[�W
#include "StageManager.h"

// ���̃X�e�[�W�Ŏg���I�u�W�F�N�g
#include "BG.h"
#include "NormalStars.h"
#include "FixedStars.h"


// �Ăяo�����̐�
#define STAR_NUM		(5)	//��
#define FIXED_STAR_NUM	(1)	//��

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
	cBG*				m_pBG;
	cNet *pNet;

	vector<cNormalStar*>		m_pNomalStar;		// ���u��
	vector<cFixedStar*>			m_pFixedStar;		// �P��
	
	cStageManager*				m_pStageManager;	// �X�e�[�W�}�l�[�W���[
};

#endif //!___SCENE_TITLE_H___