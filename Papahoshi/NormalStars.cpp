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

//-----------------------------
//�}�N����`
//-----------------------------
#define STAR_SIZE	(20)

#define RESPAWN_FREAM (100)

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

	// ���I�m��
	m_pStarData = new tNormalStarData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// ������
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(100, 100));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR));
		m_pStarData[nCuntStar].t_bUse = false;
		
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

	// ������
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){
		
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
		if (m_pStarData[nCuntStar].t_bUse)
			m_pStarData[nCuntStar].t_Sprite.Draw();
	}


	// �f�o�b�O�v�����g
	PrintDebugProc("***NormalStar***\n");
	PrintDebugProc("R:Reset\n");
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
