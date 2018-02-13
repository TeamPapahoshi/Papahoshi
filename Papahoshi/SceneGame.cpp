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
	m_pNet = new cNet();

	// �u���b�N�z�[��
	m_pBlackHole = new cBlackHole();
	m_pBlackHole->SetNetData(m_pNet);

	// 覐�
	m_pSpaceRock = new cSpaceRock();

	// �T���v��
	m_pSampleStar = new cSampleStar();

	// ����
	m_pRyusei = new cRyusei();

	// �Q�[�W
	m_pGage = new cGage();
	m_pGage->Init();

	// ���u��
	m_pNomalStar = new cNormalStar();
	m_pNomalStar->SetBlackHoleData(m_pBlackHole);
	m_pNomalStar->SetNetData(m_pNet);
	m_pNomalStar->SetGageData(m_pGage);

	// UI
	m_pGameUI = new cGameUI();

	// �^�C�}�[
	m_pTimer = new cTimer();

	// �w�i
	m_pBG = new cBG();
	m_pBG->SetBG(cBG::GAME_SKY);


	// �Q�[���̏��
	m_eGameState = GAME_STATE_SET;
	m_bFever = false;

	//�A�i�E���X�̃Z�b�g
	m_pAnnounce = new cAnnounce(cAnnounce::eAnnounceType::Start);
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
	delete m_pNet;
	delete m_pGameUI;
	delete m_pTimer;
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneGame::Update(){

	// �Q�[���̏�Ԃŕ���
	switch (m_eGameState)
	{
	case GAME_STATE_SET:
		SetUpdate();
		break;
	case GAME_STATE_MAIN:		// �������֐��ɂ��Ă���������
		MainUpdate();
		break;
	case GAME_STATE_END:
		EndUpdate();
		break;
	default:
		break;
	}

	// �����ׂĂ̏�ԂōX�V��

	// �V�[���X�V
	if (GetKeyboardTrigger(DIK_G)){
		m_eGameState = GAME_STATE_MAIN;
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


	// �Q�[���̏�Ԃŕ���(������K�v�Ȃ�����)
	switch (m_eGameState)
	{
	case GAME_STATE_SET:
		PrintDebugProc("�����Q�[���̏�Ԅ���\n");
		PrintDebugProc("SET\n");
		PrintDebugProc("G�L�[�Ń��C����\n");
		PrintDebugProc("��������������������\n");
		break;
	case GAME_STATE_MAIN:
		PrintDebugProc("�����Q�[���̏�Ԅ���\n");
		PrintDebugProc("MAIN\n");
		m_bFever ? PrintDebugProc("Fever\n") : PrintDebugProc("Normal\n");
		PrintDebugProc("G�L�[�Ń��C����\n");
		PrintDebugProc("F�L�[��FEVER or NORMAL\n");
		PrintDebugProc("��������������������\n");
		break;
	case GAME_STATE_END:
		PrintDebugProc("�����Q�[���̏�Ԅ���\n");
		PrintDebugProc("END\n");
		PrintDebugProc("G�L�[�Ń��C����\n");
		PrintDebugProc("��������������������\n");
		break;
	default:
		break;
	}

	m_pBG->Draw();				// �w�i
	m_pBlackHole->Draw();
	m_pSampleStar->Draw();
	//m_pSpaceRock->Draw();
	m_pNomalStar->Draw();
	m_pRyusei->Draw();
	m_pNet->Draw();

	m_pGameUI->Draw();
	m_pGage->Draw();
	if (m_pAnnounce)
		m_pAnnounce->Draw();
}


//============================================
//
// SET
//
//============================================
void cSceneGame::SetUpdate(){

	m_pAnnounce->Update();

	//�A�i�E���X�I���Ŏ���
	if (m_pAnnounce->CallFin()){
		delete m_pAnnounce;
		m_pAnnounce = NULL;
		m_eGameState = GAME_STATE_MAIN;
	}

}

//============================================
//
// MAIN
//
//============================================
void cSceneGame::MainUpdate(){

	m_pNet->Update();			//����
	m_pBG->Update();			// �w�i
	m_pGage->Update();			// �Q�[�W
	m_pNomalStar->Update();
	m_pBlackHole->Update();
	m_pSpaceRock->Update();
	m_pSampleStar->Update();
	m_pGameUI->Update();
	m_pTimer->Update();
	CheckCollision();			//�����蔻��

	// �t�B�[�o�^�C���̎�
	if (m_bFever){
		//���̃t���OOn�ɂ�����A�i�E���X���Ă�
		m_pRyusei->Update();
	}

	//�Q�[���I���ŃA�i�E���X���Ă�
	/*
	if(){
		m_pAnnounce = new cAnnounce(cAnnounce::eAnnounceType::Finish);
	}
	*/

	if (GetKeyboardTrigger(DIK_F)){
		m_bFever ? m_bFever = false : m_bFever = true;
	}
	
}

//============================================
//
// END
//
//============================================
void cSceneGame::EndUpdate(){

	//�A�i�E���X�I���Ŏ���
	if (m_pAnnounce->CallFin())
		int i = 0;
		//�肴���

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

			  if (m_pNet->GetPullFlug()){
				  if (CheckCollisionCircleToLine(m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos, 
					  m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetLeft(), m_pNet->GetNetRight())){

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

			  if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, m_pBlackHole->GetStarData()[nCountBlackHole].m_VacumeRange)){
				  m_pNomalStar->OnCollidToBlackHole(nCountStar, nCountBlackHole);

				  }
			  }
	  }
}