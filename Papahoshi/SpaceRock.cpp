//======================================================================
//	SpaceRock
//	
//	�T�v�Q�F覐�
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
#include "SpaceRock.h"
#include "Input.h"

#define STAR_SIZE	(100)

#define VACUUM_RANGE	(200)
#define DELETE_RANGE	(20)

#define RESPAWN_FREAM	(20)

//****************************************************************************************************************
// �u���b�N�z�[��
//****************************************************************************************************************
//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cSpaceRock::cSpaceRock(){

	// �����̏�����
	CRandam::InitRand();

	// ���̍ő吔�@��Ƀt�@�C������Ǎ�������
	m_nMaxNum = MAX_SPACE_ROCK_NUM;
	m_nCurrentNum = 0;

	// ���I�m��
	m_pStarData = new tSpaceRockData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// ������
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(100, 100));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_SPACE_ROCK));
		m_pStarData[nCuntStar].t_bUse = false;
		m_pStarData[nCuntStar].t_bRespawn = false;
		m_pStarData[nCuntStar].t_nRespawnFrame = 0;

		// �����蔻��
		m_pStarData[nCuntStar].t_Collider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData[nCuntStar].t_Sprite.GetPos(), STAR_SIZE / 2.0f);
	}



}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cSpaceRock::~cSpaceRock(){

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSpaceRock::Update(){

	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){


		// �����蔻��
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData[nCuntStar].t_Sprite.GetPos(), STAR_SIZE / 2.0f);

		// �������t�F�[�h�C��
		if (m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() < 255){
			m_pStarData[nCuntStar].t_Sprite.SetVtxColorA(m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() + 0.5f);
		}

		// ���X�|�[���t���O���I���̎������J�n
		if (m_pStarData[nCuntStar].t_bRespawn){
			Respawn(nCuntStar);
		}
	}


	// �f�o�b�O�p
	if (GetKeyboardTrigger(DIK_V)){
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
//		���X�|�[��
//
//=======================================================================================
void cSpaceRock::Respawn(int num){

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
//		�`��
//
//=======================================================================================
void cSpaceRock::Draw(){
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){


		if (!m_pStarData[nCuntStar].t_bUse)
			continue;


		m_pStarData[nCuntStar].t_Sprite.Draw();
		m_pStarData[nCuntStar].t_Collider.Draw();

	}

	// �f�o�b�O�v�����g
	PrintDebugProc("***覐�***\n");
	PrintDebugProc("V:����\n");
	PrintDebugProc("������ %d\n", m_nCurrentNum);
	PrintDebugProc("****************\n");
}

//=======================================================================================
//
//		���̐ݒ�
//
//=======================================================================================
void cSpaceRock::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

}


//=======================================================================================
//
//		�ԂƂ̏���
//
//=======================================================================================
//--- �ԂƓ����������̏��� ---
void cSpaceRock::OnCollidToNet(int count){

	CountDown(count);
	m_pStarData[count].t_bRespawn = true;	// ���X�|�[���J�n

}