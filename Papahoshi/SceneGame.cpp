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
#include "BaseStar.h"

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

	// ��
	pNet = new cNet();

	// �u���b�N�z�[��
	m_pBlackHole = new cBlackHole();

	// 覐�
	m_pSpaceRock = new cSpaceRock();



	// 覐�
	m_pSampleStar = new cSampleStar();

	// ���u��
	m_pNomalStar = new cNormalStar();
	m_pNomalStar->SetBlackHoleData(m_pBlackHole);

	


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
	delete m_pNomalStar;
	delete m_pBlackHole;
	delete m_pSampleStar;
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
	pNet->Update();		//����
	m_pBG->Update();	// �w�i

	m_pNomalStar->Update();
	m_pBlackHole->Update();
	m_pSpaceRock->Update();
	m_pSampleStar->Update();



	
	
	//�����蔻��
	CheckCollision();

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

	m_pBG->Draw();	// �w�i

	//
	m_pBlackHole->Draw();
	m_pSampleStar->Draw();
	//m_pSpaceRock->Draw();

	m_pNomalStar->Draw();


	
	pNet->Draw();	//����
}


//============================================
//
// �����蔻����擾
//
//============================================
void cSceneGame::CheckCollision(){

	cCollider c,t;
	c.SetType(cCollider::CollisionType::CIRCLE);
	c.SetCircleCollider(D3DXVECTOR2(700.0f, 580.0f), 10.0f);

	t = pNet->GetCollider()[1];
	if (cCollider::CheckCollisionCircleToTriangle(c, t)){
		int i = 0;
	}

	// �Ԃƃ��u���̂����蔻��
	//for (int nCountStar = 0; nCountStar < MAX_NORMAL_STAR; nCountStar++){

	//	if (!m_pNomalStar->GetStarData()[nCountStar].t_bUse)
	//		continue;

	//	for (int nCountNet = 0; nCountNet < 2; nCountNet++){
	//		if (cCollider::CheckCollisionCircleToTriangle(m_pNomalStar->GetStarData()[nCountStar].t_Collider, pNet->GetCollider()[nCountNet])){

	//			m_pNomalStar->OnCollidToNet(nCountStar);

	//		}
	//	}
	//}

	 
	// �Ԃ�覐΂̂����蔻��
	for (int nCountStar = 0; nCountStar <MAX_SPACE_ROCK_NUM; nCountStar++){

		if (!m_pSpaceRock->GetStarData()[nCountStar].t_bUse)
			continue;

		for (int nCountNet = 0; nCountNet < 2; nCountNet++){
			if (cCollider::CheckCollisionCircleToTriangle(m_pSpaceRock->GetStarData()[nCountStar].t_Collider, pNet->GetCollider()[nCountNet])){

				m_pSpaceRock->OnCollidToNet(nCountStar);

			}
		}
	}


	// �Ԃƃu���b�N�z�[���̂����蔻��
	//for (int nCountStar = 0; nCountStar <MAX_BLACK_HOLE_NUM; nCountStar++){

	//	if (!m_pBlackHole->GetStarData()[nCountStar].t_bUse)
	//		continue;

	//	for (int nCountNet = 0; nCountNet < 2; nCountNet++){
	//		if (cCollider::CheckCollisionCircleToTriangle(m_pBlackHole->GetStarData()[nCountStar].t_Collider, pNet->GetCollider()[nCountNet])){



	//		}
	//	}
	//}

	//// ���u���ƃu���b�N�z�[���̋z�����ݔ͈͂Ƃ̂����蔻��
	//for (int Normal = 0; Normal < MAX_NORMAL_STAR; Normal++){

	//	if (!m_pNomalStar->GetStarData()[Normal].t_bUse)
	//		continue;

	//	for (int Black = 0; Black < MAX_BLACK_HOLE_NUM; Black++){

	//		if (!m_pBlackHole->GetStarData()[Black].t_bUse)
	//			continue;


	//		if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[Normal].t_Collider,
	//			m_pBlackHole->GetStarData()[Black].t_VacuumCollider)){

	//			m_pNomalStar->OnCollidToBlackHole(Normal, Black);

	//		}
	//	}
	//}
	//// ���u���ƃu���b�N�z�[���̍폜�͈͂Ƃ̂����蔻��
	//for (int Normal = 0; Normal < MAX_NORMAL_STAR; Normal++){

	//	if (!m_pNomalStar->GetStarData()[Normal].t_bUse)
	//		continue;

	//	for (int Black = 0; Black < MAX_BLACK_HOLE_NUM; Black++){

	//		if (!m_pBlackHole->GetStarData()[Black].t_bUse)
	//		continue;


	//		if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[Normal].t_Collider,
	//			m_pBlackHole->GetStarData()[Black].t_DeleteCollider)){

	//			m_pNomalStar->OnCollidToDelete(Normal);

	//		}
	//	}
	//}





}