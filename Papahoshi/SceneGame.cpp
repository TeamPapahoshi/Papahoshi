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

//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneGame::cSceneGame(){

	// ��
	pNet = new cNet();

	// �u���b�N�z�[��
	m_pBlackHole = new cBlackHole();
	m_pBlackHole->SetNetData(pNet);

	// 覐�
	m_pSpaceRock = new cSpaceRock();

	// �T���v��
	m_pSampleStar = new cSampleStar();

	// ����
	m_pRyusei = new cRyusei();

	// ���u��
	m_pNomalStar = new cNormalStar();
	m_pNomalStar->SetBlackHoleData(m_pBlackHole);
	m_pNomalStar->SetNetData(pNet);

	// �Q�[�W
	m_pGage = new cGage();
	m_pGage->Init();

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
	delete m_pSpaceRock;
	delete m_pRyusei;
	delete m_pGage;
	delete m_pBlackHole;
	delete m_pSampleStar;
	delete pNet;
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneGame::Update(){

	// �X�V
	pNet->Update();		//����
	m_pBG->Update();	// �w�i
	m_pGage->Update();	// �Q�[�W
	m_pNomalStar->Update();
	m_pBlackHole->Update();
	m_pSpaceRock->Update();
	m_pSampleStar->Update();
	m_pRyusei->Update();

	
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

	m_pBG->Draw();				// �w�i
	m_pBlackHole->Draw();
	m_pSampleStar->Draw();
	//m_pSpaceRock->Draw();
	m_pNomalStar->Draw();
	pNet->Draw();				//����
	m_pGage->Draw();

	m_pRyusei->Draw();

	for (int nCountBlackHole = 0; nCountBlackHole < m_pBlackHole->GetMaxNum(); nCountBlackHole++){


		PrintDebugProc("�g�p�t���Oaaaaa %d\n", m_pBlackHole->GetStarData()[0].m_bUse);
	}
}


//============================================
//
// �����蔻����擾
//
//============================================
void cSceneGame::CheckCollision(){

	  //---�Ԃƃ��u���̔���type2---
	  for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		  if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			  continue;

		  for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			  if (pNet->GetPullFlug()){
				  if (CheckCollisionCircleToLine(m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos, m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, pNet->GetNetLeft(), pNet->GetNetRight())){

					  m_pNomalStar->OnCollidToNet(nCountStar);
					  //m_pNomalStar->GetStarData()[nCountStar].m_bUse = false;
				  }
			  }
		  }
	  }

	  //���u���ƃu���b�N�z�[���̋z�����݂̔���
	  for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		  if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			  continue;

		  for (int nCountBlackHole = 0; nCountBlackHole < m_pBlackHole->GetMaxNum(); nCountBlackHole++){

			  if (!m_pBlackHole->GetStarData()[nCountBlackHole].m_bUse)
				  continue;

			  if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, m_pBlackHole->GetStarData()[nCountBlackHole].m_Collision)){
				  m_pNomalStar->OnCollidToBlackHole(nCountStar, nCountBlackHole);

				  }
			  }
	  }


}