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



//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneGame::cSceneGame(){

	// �C���X�^���X
	for (int i = 0; i < STAR_NUM; i++)
		pStar[i] = new cCircleOrbitStar();

	m_pBG = new cBG();

	// ������
	for (int i = 0; i < STAR_NUM; i++)
		pStar[i]->Init();
	pStar[0]->SetcCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(20.0f, 20.0f), 3);

	
	m_pBG->Init();
	m_pBG->SetBG(cBG::GAME_MAIN);

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

	m_pBG->UnInit();

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

	m_pBG->Update();
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cSceneGame::Draw(){

	m_pBG->Draw();

	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->Draw();
	}

	
}

