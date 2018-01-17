//======================================================================
//	SceneStageSelect
//	
//	�T�v�Q�F�X�e�[�W�I�����
//	����ҁF���� ����
//	
//======================================================================

#ifndef ___SCENE_STAGESELECT_H___
#define ___SCENE_STAGESELECT_H___

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include <d3d9.h>
#include "SceneManeger.h"
#include "StageSelect.h"
#include "TitleWave.h"
#include "TitleShip.h"
#include "Meteor.h"
#include "StageSelect.h"

//------------------------------
// �N���X��`
//------------------------------
//----�V�[���Q�[��-----
class cSceneStageSelect :public cBaseScene{

private:

	cStageSelect* pStageSelect;
	cTitleWave* pTitleWave;
	cTitleShip* pTitleShip;
	cMeteor*	pMeteor;

public:
	void Draw();	//�`��
	void Update();	//�X�V
	cSceneStageSelect();	//�R���X�g���N�^
	~cSceneStageSelect();	//�f�X�g���N�^

	cStageSelect* GetStage(void);	//�X�e�[�W���̎擾�p(�b��)


};
#endif //!___SCENE_STAGESELECT_H___