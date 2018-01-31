//======================================================================
//	Title
//	
//	�T�v�Q�F�^�C�g��(��)
//	����ҁF
//	
//======================================================================

#ifndef ___SCENE_TITLE_H___
#define ___SCENE_TITLE_H___

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "SceneManeger.h"
#include <d3d9.h>

//------ �g�p����I�u�W�F�N�g -------
#include "TitleRogo.h"
#include "TitleWave.h"
#include "TitleShip.h"
#include "Meteor.h"
#include "BG.h"

//------------------------------
// �}�N����`
//------------------------------
#define CIRCLE_ORBIT_STAR_NUM (2)

//------------------------------
// �N���X��`
//------------------------------
//----�V�[���^�C�g��-----
class cSceneTitle :public cBaseScene{

public:
	void Draw();	//�`��
	void Update();	//�X�V
	cSceneTitle();	//�R���X�g���N�^
	~cSceneTitle();	//�f�X�g���N�^

private:
	cTitleRogo* m_pTitleRogo;
	cTitleWave* m_pTitleWave;
	cTitleShip* m_pTitleShip;
	cMeteor*	m_pMeteor;
	cBG*		m_pBG;
	//cCircleOrbitStar*	pCircleOrbitStar[CIRCLE_ORBIT_STAR_NUM];

	bool		bSceneChangeFlag;
	bool		m_bChange;	//�V�[���`�F���W���Ă񂾂�false
};
#endif //!___SCENE_TITLE_H___