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
#include "Player.h"
#include "Enemy.h"


//-----------------------------
// �O���[�o��
//-----------------------------
// ���̃V�[���Ŏg���I�u�W�F�N�g�̃|�C���^��p��(�����ŃC���X�^���X�����Ȃ�)
cPlayer* pPlayer;
cEnemy*	 pEnemy;


//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneTitle::cSceneTitle(){

	// �g���I�u�W�F�N�g�̃C���X�^���X
	pPlayer = new cPlayer();
	pEnemy = new cEnemy();
	pNet = new cNet();

	// �v���C���[
	pPlayer->Init();

	// �G�l�~�[
	pEnemy->Init();

	// ����
	PlaySound(SOUND_LABEL_BGM000);	

}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
cSceneTitle::~cSceneTitle(){

	StopSound(SOUND_LABEL_BGM000);
	pPlayer->Unit();
	pEnemy->Unit();

	// ���I�C���X�^���X����Ȃ�delete��Unit�Ƃ͕ʂɂ�����
	delete pPlayer;
	delete pEnemy;
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneTitle::Update(){

	pPlayer->Update();
	pEnemy->Update();
	pNet->Update();

	// �����蔻��
	if (cCollider::CheckCollisionCircleToCircle(pPlayer->GetCollider(), pEnemy->GetCollider())){
		pPlayer->OnColidToEnemy();	// �G�l�~�[�ɓ����������̃v���C���[�̏���
		//enemy.OnColidToPlayer();	// �v���C���[�ɓ����������̃G�l�~�[�[�̏���
	}

	// �X�y�[�X�ŃV�[���`�F���W
	if (GetKeyboardTrigger(DIK_SPACE)){
		cSceneManeger::ChangeScene(cSceneManeger::GAME);
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cSceneTitle::Draw(){

	pEnemy->Draw();
	pPlayer->Draw();
	pNet->Draw();
}



