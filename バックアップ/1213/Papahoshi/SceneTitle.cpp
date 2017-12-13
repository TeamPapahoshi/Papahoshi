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

	// �e�N�X�`���̓ǂݍ���
	LoadTextureFromFile();

	// �v���C���[
	pPlayer->Init(&m_pTex[PLAYER]);

	// �G�l�~�[
	pEnemy->Init(&m_pTex[ENEMY]);

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

	// �����蔻��
	if (cCollider::CheckCollisionCircleToCircle(pPlayer->GetCollider(), pEnemy->GetCollider())){
		pPlayer->OnColidToEnemy();	// �G�l�~�[�ɓ����������̃v���C���[�̏���
		//enemy.OnColidToPlayer();	// �v���C���[�ɓ����������̃G�l�~�[�[�̏���
	}

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

	pEnemy->Draw();
	pPlayer->Draw();
}


//=======================================================================================
//
//		���̃V�[���Ŏg���e�N�X�`���̓Ǎ�
//		�w�b�_�[��enum�Ƃ��̊֐���char*�z��ɒǉ�����΃e�N�X�`�������[�h����܂�
//		���w�b�_�[��enum��char�z��̃t�@�C�����̏��Ԃ���v����悤�ɂ��Ă�������
//		�V�[�����ς��ƃe�N�X�`�����������Ⴄ�̂ł̂œ����I�u�W�F�N�g��ʃV�[���ŌĂ�
//		���͂�����x�g���e�N�X�`���������Ă�������
//
//=======================================================================================
void cSceneTitle::LoadTextureFromFile(){

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���̃V�[���Ŏg���e�N�X�`���̃t�@�C����
	char* pTexture[MAX_TEXTURE] = {			//�����Ԓ���enum�̏��Ƀt�@�C������������
		{ TEXTURE_FILNAME_PLAYER },
		{ TEXTURE_FILNAME_ENEMY }
	};

	// ���[�h
	for (int i = 0; i < MAX_TEXTURE; i++){
		D3DXCreateTextureFromFile(pDevice, pTexture[i], &m_pTex[i]);
	}
}
