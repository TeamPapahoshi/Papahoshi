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

	//----------------
	// �C���X�^���X
	//----------------
	for (int i = 0; i < STAR_NUM; i++)			pStar[i] = new cCircleOrbitStar();	// �~�O����
	for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i] = new cFixedStar();	// �P��
	m_pBG = new cBG();	// �w�i
	pNet = new cNet();

	//----------------
	// ������
	//----------------
	for (int i = 0; i < STAR_NUM; i++)	pStar[i]->Init();
	for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i]->Init();	// �P��
	m_pBG->Init();
	m_gamePhase = GAME_PHASE::PHASE_POST;

	//----------------
	// �Z�b�g
	//----------------
	// ��
	pStar[0]->SetCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(30.0f, 30.0f), 0);
	pStar[1]->SetCircleOrbitStar(D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 0);
	pStar[2]->SetCircleOrbitStar(D3DXVECTOR2(600.0f, 200.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 0);
	pStar[3]->SetCircleOrbitStar(D3DXVECTOR2(150.0f, 300.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 0);
	pStar[4]->SetCircleOrbitStar(D3DXVECTOR2(800, 400), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 0);

	// �P��
	pFixedStar[0]->SetFixedStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 10);

	// �w�i
	m_pBG->SetBG(cBG::GAME_SKY);
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
cSceneGame::~cSceneGame(){

	// �I��
	for (int i = 0; i < STAR_NUM; i++)			pStar[i]->UnInit();			// �~�O����
	for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i]->UnInit();	// �P��
	m_pBG->UnInit();	// �w�i

	// �f���[�g
	delete m_pBG;
	for (int i = 0; i < STAR_NUM; i++)			delete pStar[i];
	for (int i = 0; i < FIXED_STAR_NUM; i++)	delete pFixedStar[i];

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneGame::Update(){

	// �X�V
	pNet->Update();	//����
	for (int i = 0; i < STAR_NUM; i++)			pStar[i]->Update();			// �~�O���̐�
	for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i]->Update();	// �P��
	m_pBG->Update();	// �w�i


	// �����邩�����Ȃ����̔���
	for (int i = 0; i < STAR_NUM; i++){
			pStar[i]->StarVisibility(CalculateDistanceAtoB(pStar[i]->GetPos(), pFixedStar[0]->GetPos()));
	}

	// �V�[���X�V
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

	m_pBG->Draw();	// �w�i
	for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i]->Draw();	// �P��
	for (int i = 0; i < STAR_NUM; i++)			pStar[i]->Draw();		// �~�O����
	pNet->Draw();	//����

}


//========================================================================================
//
//  �Q�[���t�F�C�Y�󂯓n��
//
//  �߂�l�@GAME_PHASE
//
//========================================================================================
cSceneGame::GAME_PHASE cSceneGame::GetGamePhase(){
	return m_gamePhase;
}