//======================================================================
//	Scenegame
//	
//	�T�v�Q�F�Q�[�����C��(��)
//	����ҁF
//	
//======================================================================

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "SceneGame.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"

// �I�u�W�F�N�g
#include "Star.h"


//------------------------------
// �}�N����`
//------------------------------
#define TEXTURE_FILNAME_ENEMY ("Image/Character/KingJelly.jpg")
//#define TEXTURE_FILNAME_PLAYER ("Image/Character/Jelly.png")

#define STAR_NUM	(4)	//��

//-----------------------------
// �O���[�o��
//-----------------------------
// �C���X�^���X�p�|�C���^
cCircleOrbitStar* pStar[STAR_NUM];


//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneGame::cSceneGame(){


	// �e�N�X�`���̓ǂݍ���
	LoadTextureFromFile();

	// �C���X�^���X
	for (int i = 0; i < STAR_NUM; i++){
		pStar[i] = new cCircleOrbitStar();
	}

	// ������
	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->Init(&m_pTex[STAR]);
	}

	// ���l�̃Z�b�g
	pStar[1]->SetcCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(100, 200), D3DXVECTOR2(20.0f, 20.0f), 5);
	pStar[2]->SetcCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(0,0), D3DXVECTOR2(20.0f, 20.0f), 5);
	pStar[3]->SetcCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(100,100), D3DXVECTOR2(20.0f, 20.0f), 5);

}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
cSceneGame::~cSceneGame(){

	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->UnInit();
	}
	// �f���[��
	
	for (int i = 0; i < STAR_NUM; i++){
		delete pStar[i];
	}
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneGame::Update(){

	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->Update();
	}

	if (GetKeyboardTrigger(DIK_SPACE)){
		cSceneManeger::ChangeScene(cSceneManeger::TITLE);
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cSceneGame::Draw(){

	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->Draw();
	}
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
void cSceneGame::LoadTextureFromFile(){

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	 // ���̃V�[���Ŏg���e�N�X�`���̃t�@�C����
	char* pTexture[MAX_TEXTURE] = {			//�����Ԓ���enum�̏��Ƀt�@�C������������
		{ TEXTURE_FILNAME_ENEMY }
	};

	// ���[�h
	for (int i = 0; i < MAX_TEXTURE; i++){
		D3DXCreateTextureFromFile(pDevice, pTexture[i], &m_pTex[i]);
	}
}