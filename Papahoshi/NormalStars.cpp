//======================================================================
//	Star
//	
//	�T�v�Q�F������
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
#include "NormalStars.h"
#include "rand.h"
#include "Input.h"
#include <cmath>

//-----------------------------
//�}�N����`
//-----------------------------
#define STAR_SIZE	(20)

#define RESPAWN_FREAM (400)

//****************************************************************************************************************
// ���ʂ̐�
//****************************************************************************************************************
//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cNormalStar::cNormalStar(){

	// �����̏�����
	CRandam::InitRand();

	// ���̍ő吔�@��Ƀt�@�C������Ǎ�������
	m_nMaxNum = MAX_NORMAL_STAR;
	m_nCurrentNum = MAX_NORMAL_STAR;

	// ���I�m��
	m_pStarData = new tNormalStarData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// ������
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(100, 100));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR));
		m_pStarData[nCuntStar].t_bUse = false;	

		// �����蔻��
		m_pStarData[nCuntStar].t_Collider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData->t_Sprite.GetPos(), STAR_SIZE / 2.0f);
	}

	//�@�t���[���J�E���g
	m_nRespawnFream = 0;

	// 
	m_bCapchared = false;

	// ����
	CreateRamdom();


}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cNormalStar::~cNormalStar(){

	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

	


	}

}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cNormalStar::Update(){

	


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){


		// �����蔻��
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData[nCuntStar].t_Sprite.GetPos(), STAR_SIZE / 2.0f);


		// ������
		if (m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() < 255){

			m_pStarData[nCuntStar].t_Sprite.SetVtxColorA(m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() + 0.5f);

		}
	}


	// ���X�|�[������
	if (m_bCapchared){
		Respawn();
	}

	// �f�o�b�O�p
	if (GetKeyboardTrigger(DIK_R)){
		for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){
			m_pStarData[nCuntStar].t_bUse = false;
			m_bCapchared = true;
			m_nCurrentNum = 0;
		}
	}

}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cNormalStar::Draw(){

	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){
		if (m_pStarData[nCuntStar].t_bUse){
			m_pStarData[nCuntStar].t_Sprite.Draw();
		//	m_pStarData[nCuntStar].t_Collider.Draw();

		}

	}


	// �f�o�b�O�v�����g
	PrintDebugProc("***NormalStar***\n");
	PrintDebugProc("R:Reset\n");
	PrintDebugProc("CurrentNum %d\n", m_nCurrentNum);
	PrintDebugProc("RespawnFrame %d\n", m_nRespawnFream);
	PrintDebugProc("****************\n");

}

//=======================================================================================
//
//		���̐ݒ�
//
//=======================================================================================
void cNormalStar::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){






	}
}

//=======================================================================================
//
//		���̃����_������
//
//=======================================================================================
void cNormalStar::CreateRamdom(){

	
	// �Ƃ肠������ʂ͈̔͂ɏo��
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){


		// �g�p�ς݂͔�΂�
		if (m_pStarData[nCuntStar].t_bUse)
			continue;

		// �t���O�𗧂Ă�
		m_pStarData[nCuntStar].t_bUse = true;


		// �ʒu�̌���
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = CRandam::RandamRenge(0, SCREEN_WIDTH);
		CreateRamdomPos.y = CRandam::RandamRenge(0, SCREEN_HEIGHT);
		m_pStarData[nCuntStar].t_Sprite.SetPos(CreateRamdomPos);		// ���

	}

}

//=======================================================================================
//
//		���̃��X�|�[��
//
//=======================================================================================
void cNormalStar::Respawn(){

	// �t���[�����Z�J�n(��)
	m_nRespawnFream++;

	if (m_nRespawnFream > RESPAWN_FREAM){

		// �J�E���g���Z�b�g
		m_nRespawnFream = 0;

		// �t���O���Z�b�g
		m_bCapchared = false;

		// �Ƃ肠������ʂ͈̔͂ɏo��
		for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){


			// �g�p�ς݂͔�΂�
			if (m_pStarData[nCuntStar].t_bUse)
				continue;

			// �t���O�𗧂Ă�
			m_pStarData[nCuntStar].t_bUse = true;
			m_nCurrentNum++;

			// �����O�ŊJ�n
			m_pStarData[nCuntStar].t_Sprite.SetVtxColorA(0);

			// �ʒu�̌���
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = CRandam::RandamRenge(0, SCREEN_WIDTH);
			CreateRamdomPos.y = CRandam::RandamRenge(0, SCREEN_HEIGHT);
			m_pStarData[nCuntStar].t_Sprite.SetPos(CreateRamdomPos);		// ���

		}
	}
}


//=======================================================================================
//
//		�ԂƂ̏���
//
//=======================================================================================
void cNormalStar::OnCollidToNet(int count){


	// ��
	if (m_pStarData[count].t_bUse){
		m_pStarData[count].t_bUse = false;
		m_nCurrentNum--;
	}



	m_bCapchared = true;

}

void cNormalStar::SetBlackHoleData(cBlackHole* data){
	m_pBlackHoleData = data;
}

void cNormalStar::OnCollidToBlackHole(int Normal, int Black){

	// �u���b�N�z�[���̒��S���擾
	D3DXVECTOR2 Center = m_pBlackHoleData->GetStarData()[Black].t_Sprite.GetPos();

	// �u���b�N�z�[���Ɛ��Ƃ̋��������߂�
	D3DXVECTOR2 Distance;
	Distance.x = sqrt((m_pStarData[Normal].t_Sprite.GetPosX() - Center.x)*(m_pStarData[Normal].t_Sprite.GetPosX() - Center.x));
	Distance.y = sqrt((m_pStarData[Normal].t_Sprite.GetPosY() - Center.y)*(m_pStarData[Normal].t_Sprite.GetPosY() - Center.y));

	// ��������ړ��ʂ��Z�o
	m_pStarData[Normal].t_Move.x = Distance.x / 500.0f;
	m_pStarData[Normal].t_Move.y = Distance.y / 500.0f;

	// �ړ��ʂ𔽉f
	if (m_pStarData[Normal].t_Sprite.GetPosX() > Center.x){
		m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() - m_pStarData[Normal].t_Move.x);
	}
	if (m_pStarData[Normal].t_Sprite.GetPosX() < Center.x){
		m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() + m_pStarData[Normal].t_Move.x);
	}

	if (m_pStarData[Normal].t_Sprite.GetPosY() > Center.y){
		m_pStarData[Normal].t_Sprite.SetPosY(m_pStarData[Normal].t_Sprite.GetPosY() - m_pStarData[Normal].t_Move.y);
	}
	if (m_pStarData[Normal].t_Sprite.GetPosY() < Center.y){
		m_pStarData[Normal].t_Sprite.SetPosY(m_pStarData[Normal].t_Sprite.GetPosY() + m_pStarData[Normal].t_Move.y);
	}

}

void cNormalStar::OnCollidToDelete(int Normal){

	// 
	m_pStarData[Normal].t_bUse = false;
	m_nCurrentNum--;
}