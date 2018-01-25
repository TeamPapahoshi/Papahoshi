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

	// ��
	pNet = new cNet();

	// ���u��
	m_pNomalStar = new cNormalStar();


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

	m_pNomalStar->Draw();

	m_pStageManager->Draw();
	pNet->Draw();	//����
}


//============================================
//
// �����蔻����擾
//
//============================================
void cSceneGame::CheckCollision(){

	cCollider c, t;
	c.SetType(cCollider::CollisionType::CIRCLE);
	t.SetType(cCollider::CollisionType::TRIANGLE);
	c.SetCircleCollider(D3DXVECTOR2(200.0f, 200.0f), 10.0f);
	t.SetTriangleCollider(D3DXVECTOR2(200, 100), D3DXVECTOR2(300, 300), D3DXVECTOR2(100, 300));

	if (cCollider::CheckCollisionCircleToTriangle(c, t)){
		int i = 0;
	}

	// �Ԃƃ��u���̂����蔻��
	for (int i = 0; i < MAX_NORMAL_STAR; i++){

		for (int j = 0; j < 2; j++){
			if (cCollider::CheckCollisionCircleToTriangle(m_pNomalStar->GetStarData()[i].t_Collider, pNet->GetCollider()[j])){

				m_pNomalStar->OnCollidToNet(i);

			}
		}
	}


}