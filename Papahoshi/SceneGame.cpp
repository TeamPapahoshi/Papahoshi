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


cCollider g_col[3];
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

	// 覐�
	m_pSpaceRock = new cSpaceRock();



	// 覐�
	m_pSampleStar = new cSampleStar();

	// ���u��
	m_pNomalStar = new cNormalStar();
	m_pNomalStar->SetBlackHoleData(m_pBlackHole);
	m_pNomalStar->SetNetData(pNet);

	// �Q�[�W
	m_pGage = new cGage();
	m_pGage->Init();
	g_col[0].SetType(cCollider::CIRCLE);
	g_col[1].SetType(cCollider::CIRCLE);
	g_col[2].SetType(cCollider::CIRCLE);
	g_col[0].SetCircleCollider(D3DXVECTOR2(300, 200), 10);
	g_col[1].SetCircleCollider(D3DXVECTOR2(500, 200), 10);
	g_col[2].SetCircleCollider(D3DXVECTOR2(SCREEN_CENTER), 30);
	
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
	delete m_pGage;
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
	pNet->Update();		//����
	m_pBG->Update();	// �w�i
	m_pGage->Update();	// �Q�[�W

	m_pNomalStar->Update();
	m_pBlackHole->Update();
	m_pSpaceRock->Update();
	m_pSampleStar->Update();

	if (GetKeyboardPress(DIK_RIGHT)){
		g_col[0].SetCircleCollider(D3DXVECTOR2(g_col[0].GetCollider().CirclePos.x + 1.0f, g_col[0].GetCollider().CirclePos.y),10);
		g_col[1].SetCircleCollider(D3DXVECTOR2(g_col[1].GetCollider().CirclePos.x + 1.0f, g_col[1].GetCollider().CirclePos.y), 10);
	}
	if (GetKeyboardPress(DIK_LEFT)){
		g_col[0].SetCircleCollider(D3DXVECTOR2(g_col[0].GetCollider().CirclePos.x - 1.0f, g_col[0].GetCollider().CirclePos.y), 10);
		g_col[1].SetCircleCollider(D3DXVECTOR2(g_col[1].GetCollider().CirclePos.x - 1.0f, g_col[1].GetCollider().CirclePos.y), 10);
	}
	if (GetKeyboardPress(DIK_UP)){
		g_col[0].SetCircleCollider(D3DXVECTOR2(g_col[0].GetCollider().CirclePos.x, g_col[0].GetCollider().CirclePos.y - 1.0f), 10);
		g_col[1].SetCircleCollider(D3DXVECTOR2(g_col[1].GetCollider().CirclePos.x, g_col[1].GetCollider().CirclePos.y - 1.0f), 10);
	}
	if (GetKeyboardPress(DIK_DOWN)){
		g_col[0].SetCircleCollider(D3DXVECTOR2(g_col[0].GetCollider().CirclePos.x, g_col[0].GetCollider().CirclePos.y + 1.0f), 10);
		g_col[1].SetCircleCollider(D3DXVECTOR2(g_col[1].GetCollider().CirclePos.x, g_col[1].GetCollider().CirclePos.y + 1.0f), 10);
	}


	if (CheckCollisionCircleToLine(g_col[2].GetCollider().CirclePos, 30, g_col[0].GetCollider().CirclePos, g_col[1].GetCollider().CirclePos))
	{	
		PrintDebugProc("aaa\n");
	
	}
	
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

			 
	g_col[0].Draw();
	g_col[1].Draw();
	g_col[2].Draw();
	
	m_pBlackHole->Draw();
	m_pSampleStar->Draw();
	//m_pSpaceRock->Draw();

	m_pNomalStar->Draw();

	
	pNet->Draw();	//����

	m_pGage->Draw();
}


//============================================
//
// �����蔻����擾
//
//============================================
void cSceneGame::CheckCollision(){

	//---�Ԃƃ��u���̔���---
	  for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		  if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			  continue;

		  for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			if( cCollider::CheckCollisionCircleToTriangle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, pNet->GetCollider()[nCountNet])){

				m_pNomalStar->OnCollidToNet(nCountStar);

			  }
		  }
	  }

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



}