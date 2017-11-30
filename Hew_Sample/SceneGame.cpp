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


//-----------------------------
// �O���[�o��
//-----------------------------
// �C���X�^���X�p�|�C���^
cBaseStar* pCircleOrbitStar;


//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneGame::cSceneGame(){


	// �e�N�X�`���̓ǂݍ���
	LoadTextureFromFile();

	// �C���X�^���X
	pCircleOrbitStar = new cCircleOrbitStar();

	pCircleOrbitStar->Init(&m_pTex[STAR]);

}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
cSceneGame::~cSceneGame(){

	pCircleOrbitStar->UnInit();

	// �f���[��
	delete pCircleOrbitStar;
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneGame::Update(){

	pCircleOrbitStar->Update();


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

	pCircleOrbitStar->Draw();
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