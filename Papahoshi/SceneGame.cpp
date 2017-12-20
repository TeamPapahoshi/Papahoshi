//======================================================================
//	Scenegame
//	
//	�T�v�Q�F�V�[���Q�[��(��)
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
#include <fstream>
#include <vector>



//------------------------------
// �}�N����`
//------------------------------
#define FIXED_STAR_NUM	(1)


//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneGame::cSceneGame(){

	// �X�e�[�W�}�l�[�W��
	m_pStageManager = new cStageManager();
	cStageManager::ChangeStage(cStageManager::STAGE_01);


	pNet = new cNet();
	m_pNomalStar.resize(STAGE_01_STAR_NUM);
	m_pFixedStar.resize(FIXED_STAR_NUM);


	// ���u��
	for (int i = 0; i < STAGE_01_STAR_NUM; i++) m_pNomalStar[i] = new cNormalStar();


	// �t�@�C������ǂݍ��񂾃f�[�^���Z�b�g����
	for (int i = 0; i < STAGE_01_STAR_NUM; i++){
		m_pNomalStar[i]->SetStarFromFile(i);
	}

	// �P��
	for (int i = 0; i < FIXED_STAR_NUM; i++)	m_pFixedStar[i] = new cFixedStar();
	//m_pFixedStar[0]->Set()




	// �w�i
	m_pBG = new cBG();
	m_pBG->SetBG(cBG::GAME_SKY);
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
cSceneGame::~cSceneGame(){

	// �f���[�g
	delete m_pBG;

	for (int i = 0; i < STAGE_01_STAR_NUM; i++)	delete m_pNomalStar[i];
	for (int i = 0; i < FIXED_STAR_NUM; i++)	delete m_pFixedStar[i];
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneGame::Update(){

	// �X�V
	m_pStageManager->Update();


	// �X�V
	pNet->Update();	//����
	m_pBG->Update();	// �w�i

	for (int i = 0; i < STAGE_01_STAR_NUM; i++)	m_pNomalStar[i]->Update();
	for (int i = 0; i < FIXED_STAR_NUM; i++)	m_pFixedStar[i]->Update();

	// �P���ƃ��u���̋������v�Z
	for (int i = 0; i < STAGE_01_STAR_NUM; i++){
		float Distance = CalculateDistanceAtoB(m_pNomalStar[i]->GetPos(), m_pFixedStar[0]->GetPos());
		m_pNomalStar[i]->StarVisibility(Distance);
	}



	// �V�[���X�V
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


	m_pStageManager->Draw();

	m_pBG->Draw();	// �w�i

	for (int i = 0; i < STAGE_01_STAR_NUM; i++)	m_pNomalStar[i]->Draw();
	for (int i = 0; i < FIXED_STAR_NUM; i++)	m_pFixedStar[i]->Draw();
	pNet->Draw();	//����
}
