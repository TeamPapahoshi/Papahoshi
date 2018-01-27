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

#define RESPAWN_FREAM (200)


// �g�ݕ��~�X�������Ȃ�����ai

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
	m_nCurrentNum = 0;

	// ���I�m��
	m_pStarData = new tNormalStarData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// ������
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(100, 100));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR));
		m_pStarData[nCuntStar].t_bUse = false;	
		m_pStarData[nCuntStar].t_bRespawn = false;
		m_pStarData[nCuntStar].t_nRespawnFrame = 0;
		m_pStarData[nCuntStar].t_nVibrationFrame = 0;
		m_pStarData[nCuntStar].t_bVibration = true;
		//m_pStarData[nCuntStar].t_Vibration.x = 0;

		// �����蔻��
		m_pStarData[nCuntStar].t_Collider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData->t_Sprite.GetPos(), STAR_SIZE / 2.0f);
	}

	// ����
	CreateRamdom();
}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cNormalStar::~cNormalStar(){

	delete[] m_pStarData;
}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cNormalStar::Update(){

	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// �����蔻��̈ʒu�X�V
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData[nCuntStar].t_Sprite.GetPos(), STAR_SIZE / 2.0f);

		// �������t�F�[�h�C��
		if (m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() < 255){
			m_pStarData[nCuntStar].t_Sprite.SetVtxColorA(m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() + 0.5f);
		}

		// ���X�|�[������ ���X�|�[���t���O���I���ɂȂ�����t���[�����Z�J�n���āB�B�B
		if (m_pStarData[nCuntStar].t_bRespawn){
			Respawn(nCuntStar);
		}

	}

	// �f�o�b�O�p
	if (GetKeyboardTrigger(DIK_R)){	// ���Z�b�g�����X�|�[���m�F
		for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){
			m_pStarData[nCuntStar].t_bUse = false;
			m_pStarData[nCuntStar].t_bRespawn = true;
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
	PrintDebugProc("***���u��***\n");
	PrintDebugProc("R:���Z�b�g\n");
	PrintDebugProc("������ %d\n", m_nCurrentNum);
	PrintDebugProc("���Z�b�g���̂ݕ������� %d\n", m_pStarData[0].t_nRespawnFrame);	
	PrintDebugProc("****************\n");

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
		CountUp(nCuntStar);


		// �ʒu�̌���
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
		m_pStarData[nCuntStar].t_Sprite.SetPos(CreateRamdomPos);		// ���

	}
}

//=======================================================================================
//
//		���̃��X�|�[��
//
//=======================================================================================
void cNormalStar::Respawn(int num){

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
			m_pStarData[num].t_Sprite.SetVtxColorA(0);

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
//		�ԂƂ̏���
//
//=======================================================================================
//--- �ԂƓ����������̏��� ---
void cNormalStar::OnCollidToNet(int count){

	CountDown(count);
	m_pStarData[count].t_bRespawn = true;	// ���X�|�[���J�n

}

//=======================================================================================
//
//		�u���b�N�z�[���Ƃ̏���
//
//=======================================================================================
//---- �u���b�N�z�[���̏����擾 -----
void cNormalStar::SetBlackHoleData(cBlackHole* data){
	m_pBlackHoleData = data;
}

//---- �u���b�N�z�[���z�����ݔ͈͂ɓ����������̏��� -----
void cNormalStar::OnCollidToBlackHole(int Normal, int Black){

	// �U������
	if (m_pStarData[Normal].t_bVibration){

		m_pStarData[Normal].t_nVibrationFrame++;
		m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() + 0.15f);

		if (m_pStarData[Normal].t_nVibrationFrame > 5){
			m_pStarData[Normal].t_bVibration = false;
			m_pStarData[Normal].t_nVibrationFrame = 0;
		}	
	}

	else if (!m_pStarData[Normal].t_bVibration){
		m_pStarData[Normal].t_nVibrationFrame++;
		m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() - 0.15f);
		if (m_pStarData[Normal].t_nVibrationFrame > 5){
			m_pStarData[Normal].t_bVibration = true;
			m_pStarData[Normal].t_nVibrationFrame = 0;
		}
	}


	// �u���b�N�z�[���̒��S���擾
	D3DXVECTOR2 Center = m_pBlackHoleData->GetStarData()[Black].t_Sprite.GetPos();

	// �u���b�N�z�[���Ɛ��Ƃ̋��������߂�
	D3DXVECTOR2 Distance;
	Distance.x = sqrt((m_pStarData[Normal].t_Sprite.GetPosX() - Center.x)*(m_pStarData[Normal].t_Sprite.GetPosX() - Center.x));
	Distance.y = sqrt((m_pStarData[Normal].t_Sprite.GetPosY() - Center.y)*(m_pStarData[Normal].t_Sprite.GetPosY() - Center.y));

	// ��������ړ��ʂ��Z�o
	m_pStarData[Normal].t_Move.x = Distance.x / 800.0f;
	m_pStarData[Normal].t_Move.y = Distance.y / 800.0f;

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

//---- �u���b�N�z�[���̍폜�͈͂ɓ����������̏��� -----
void cNormalStar::OnCollidToDelete(int Normal){

	CountDown(Normal);
	m_pStarData[Normal].t_bRespawn = true;
}