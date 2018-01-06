//======================================================================
//	SceneStageSelect
//	
//	�T�v�Q�F�X�e�[�W�I��(��)
//	����ҁF���� ����
//	
//======================================================================

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "SceneStageSelect.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"

// �I�u�W�F�N�g

//------------------------------
// �}�N����`
//------------------------------
#define TEXTURE_FILNAME_STAGE (NULL)

//-----------------------------
// �O���[�o��
//-----------------------------

//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneStageSelect::cSceneStageSelect(){

	//�g�p����I�u�W�F�N�g�̓��I�m��
	pStageSelect = new cStageSelect();
	/*
	pTitleWave = new cTitleWave;	//�g
	pTitleShip = new cTitleShip;	//�D
	pMeteor = new cMeteor;
	*/

	pStageSelect->Init();		//�X�e�[�W�Z���N�g�p�I�u�W�F�N�g�̏�����

}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
cSceneStageSelect::~cSceneStageSelect()
{
	pStageSelect->Uninit();		//�X�e�[�W�Z���N�g�p�I�u�W�F�N�g�̏I������

	delete pStageSelect;		//���I�m�ۂ����I�u�W�F�N�g�̉��
	pStageSelect = NULL;

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneStageSelect::Update()
{
	//�X�V����
	/*
	pTitleWave->Update();
	pTitleShip->Update();
	pMeteor->Update();
	*/
	pStageSelect->Update();

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		cSceneManeger::ChangeScene(cSceneManeger::GAME);
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cSceneStageSelect::Draw()
{
	pStageSelect->Draw();
}

//=======================================================================================
//
//		�X�e�[�W���̈����n���֐�
//
//=======================================================================================
cStageSelect* cSceneStageSelect::GetStage(void)
{
	return pStageSelect;
}