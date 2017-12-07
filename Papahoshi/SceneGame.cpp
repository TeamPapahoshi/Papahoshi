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

#define STAR_NUM	(1)	//��

//-----------------------------
// �O���[�o��
//-----------------------------
// �C���X�^���X�p�|�C���^
cCircleOrbitStar* pStar[STAR_NUM];	// ��base�ł͂Ȃ�


//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneGame::cSceneGame(){

	// �C���X�^���X
	for (int i = 0; i < STAR_NUM; i++){
		pStar[i] = new cCircleOrbitStar();
	}

	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->Init();
	}

	pStar[0]->SetcCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(20.0f, 20.0f), 3);

	

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

