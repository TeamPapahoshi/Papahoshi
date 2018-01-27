//======================================================================
//	BlackHole
//	
//	�T�v�Q�F�u���b�N�z�[��
//	����ҁF�����@��
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>
#include <math.h>
#include <fstream>
#include "debugproc.h"
#include "Common.h"
#include "Texture.h"
#include "rand.h"
#include "BlackHole.h"
#include "Input.h"

#define STAR_SIZE	(100)

#define VACUUM_RANGE	(200)
#define DELETE_RANGE	(20)

#define RESPAWN_FREAM	(200)

//****************************************************************************************************************
// �u���b�N�z�[��
//****************************************************************************************************************
//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cBlackHole::cBlackHole(){

	// �����̏�����
	CRandam::InitRand();

	// ���̍ő吔�@��Ƀt�@�C������Ǎ�������
	m_nMaxNum = MAX_BLACK_HOLE_NUM;
	m_nCurrentNum = 0;

	// ���I�m��
	m_pStarData = new tBlackHoleData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// ������
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_BLACK_HOLE));
		m_pStarData[nCuntStar].t_bRespawn = false;
		m_pStarData[nCuntStar].t_nRespawnFrame = 0;
		m_pStarData[nCuntStar].t_bUse = false;

		// �����蔻��
		m_pStarData[nCuntStar].t_VacuumCollider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_VacuumCollider.SetCircleCollider(m_pStarData->t_Sprite.GetPos(), VACUUM_RANGE);

		m_pStarData[nCuntStar].t_DeleteCollider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_DeleteCollider.SetCircleCollider(m_pStarData->t_Sprite.GetPos(), DELETE_RANGE);
	}

	//�@�t���[���J�E���g
	m_nRespawnFream = 0;

	// 
	m_bCapchared = false;


}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cBlackHole::~cBlackHole(){

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cBlackHole::Update(){

	
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){


		// �����蔻��
		m_pStarData[nCuntStar].t_VacuumCollider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_VacuumCollider.SetCircleCollider(m_pStarData[nCuntStar].t_Sprite.GetPos(), VACUUM_RANGE);

		m_pStarData[nCuntStar].t_DeleteCollider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_DeleteCollider.SetCircleCollider(m_pStarData[nCuntStar].t_Sprite.GetPos(), DELETE_RANGE);


		// �������t�F�[�h�C��
		if (m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() < 255){
			m_pStarData[nCuntStar].t_Sprite.SetVtxColorA(m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() + 0.5f);
		}

		// ���X�|�[���t���O���I���̎������J�n
		if (m_pStarData[nCuntStar].t_bRespawn){
			Create(nCuntStar);
		}
	}


	// �f�o�b�O�p
	if (GetKeyboardTrigger(DIK_C)){
		for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){
			if (m_pStarData[nCuntStar].t_bUse)
				continue;
			m_pStarData[nCuntStar].t_bRespawn = true;
			break;
		}
	}

}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cBlackHole::Draw(){
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		if (!m_pStarData[nCuntStar].t_bUse)
			continue;

		m_pStarData[nCuntStar].t_Sprite.Draw();
		m_pStarData[nCuntStar].t_VacuumCollider.Draw();
		m_pStarData[nCuntStar].t_DeleteCollider.Draw();
	}

	// �f�o�b�O�v�����g
	PrintDebugProc("***�u���b�N�z�[��***\n");
	PrintDebugProc("C:����\n");
	PrintDebugProc("������ %d\n", m_nCurrentNum);
	PrintDebugProc("****************\n");

}


//=======================================================================================
//
//		����
//
//=======================================================================================
void cBlackHole::Create(int num){

	// �t���[�����Z
	m_pStarData[num].t_nRespawnFrame++;

	if (m_pStarData[num].t_nRespawnFrame > RESPAWN_FREAM){

		// �g�p�ς݂̂�
		if (!m_pStarData[num].t_bUse){

			// ������������
			CountUp(num);

			// ���X�|�[���I���t���O�I�t
			m_pStarData[num].t_bRespawn = false;
			m_pStarData[num].t_nRespawnFrame = 0;

			// �����O�ŊJ�n
			m_pStarData[num].t_Sprite.SetVtxColorA(255);

			// �ʒu�̌���	
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
			CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
			m_pStarData[num].t_Sprite.SetPos(CreateRamdomPos);		// ���
		}
	}

}

//=======================================================================================
//
//		���̐ݒ�
//
//=======================================================================================
void cBlackHole::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

}
