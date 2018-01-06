//======================================================================
//	Title
//	
//	�T�v�Q�F�^�C�g��
//	����ҁF
//	
//======================================================================

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "SceneTitle.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"
#include "sound.h"

// ���̃V�[���Ŏg���I�u�W�F�N�g


//-----------------------------
// �O���[�o��
//-----------------------------
// ���̃V�[���Ŏg���I�u�W�F�N�g�̃|�C���^��p��(�����ŃC���X�^���X�����Ȃ�)


//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneTitle::cSceneTitle(){

	// �g���I�u�W�F�N�g�̃C���X�^���X
	pTitleRogo = new cTitleRogo;	//�^�C�g�����S
	pTitleWave = new cTitleWave;	//�g
	pTitleShip = new cTitleShip;	//�D
	pMeteor    = new cMeteor;
	for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++)	pCircleOrbitStar[i] = new cCircleOrbitStar();	// �~�O����

	//����������
	pTitleRogo->Init();
	pTitleWave->Init();
	pTitleShip->Init();
	pMeteor   ->Init();
	for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++)
	{
		pCircleOrbitStar[i]->Init();
		if (!i)
			pCircleOrbitStar[i]->SetCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 100),
													D3DXVECTOR2(350.0f, 180.0f),
													D3DXVECTOR2(40.0f, 40.0f),
													5);
		else
			pCircleOrbitStar[i]->SetCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 100),
													D3DXVECTOR2(350.0f, 180.0f),
													D3DXVECTOR2(40.0f, 40.0f),
													10);
	}

	// ����
	//PlaySound(SOUND_LABEL_BGM000);	

}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
cSceneTitle::~cSceneTitle(){
	
	//�I������
	pTitleRogo->UnInit();
	pTitleWave->UnInit();
	pTitleShip->UnInit();
	pMeteor   ->UnInit();
	for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++) pCircleOrbitStar[i]->UnInit();

	//StopSound(SOUND_LABEL_BGM000);

	// ���I�C���X�^���X����Ȃ�delete��Unit�Ƃ͕ʂɂ�����
	delete pTitleRogo;
	pTitleRogo = NULL;
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneTitle::Update(){
	//�X�V����
	pTitleRogo->Update();
	pTitleWave->Update();
	pTitleShip->Update();
	pMeteor   ->Update();
	for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++) pCircleOrbitStar[i]->Update();

	// �X�y�[�X�ŃV�[���`�F���W
	if (GetKeyboardTrigger(DIK_SPACE)){
		cSceneManeger::ChangeScene(cSceneManeger::STAGE_SELECT);
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cSceneTitle::Draw(){
	//�`�揈��
	pTitleRogo->Draw();
	pTitleWave->Draw();
	pTitleShip->Draw();
	pMeteor   ->Draw();
	for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++) pCircleOrbitStar[i]->Draw();
}



