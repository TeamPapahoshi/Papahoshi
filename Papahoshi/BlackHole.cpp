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
#include "GameUI.h"
#include "MathEX.h"

//-----------------------------
// �}�N����`
//-----------------------------
#define STAR_SIZE			(200)	// �T�C�Y
#define RESPAWN_FREAM		(100)	// ���X�|�[���̃C���^�[�o���t���[��
#define MAX_BLACK_HOLE_NUM	(1)		// �ő吔
#define VACUUM_RANGE		(200)	// �z�����ݔ͈�
#define DELETE_RANGE		(10)	// �폜�͈�

//===================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cBlackHole::cBlackHole(){

	// �����̏�����
	CRandam::InitRand();

	// �g�p�����i�[�t�@�C������ǂݍ��ނ��ǂ����ԕύX��������
	m_nMaxNum = MAX_BLACK_HOLE_NUM;

	// ���I�C���X�^���X
	m_pStarData = new cBlackHoleData[m_nMaxNum]();	//��������
	m_pRoot = m_pStarData;							// �擪�A�h���X�ۑ�

	// ������
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// ��������
		m_pStarData->m_bDraw = true;
		SetCountAndUse(true);

		// �T�C�Y�̕ύX
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));

		// �e�N�X�`���̐ݒ�
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_BLACK_HOLE));
		m_pStarData->m_sprite.SetTexPatternDevide(10, 6);
		m_pStarData->m_sprite.SetIntervalChangePattern(4);
		m_pStarData->m_sprite.SetAnimationFlag(true);
	
		// ���W�̌���
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT + m_pStarData->m_sprite.GetSizeX(), GAME_SCREEN_RIGHT - m_pStarData->m_sprite.GetSizeX());
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0 + m_pStarData->m_sprite.GetSizeY(), SCREEN_HEIGHT - m_pStarData->m_sprite.GetSizeY());
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);

		// �����蔻��
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f-30);

		// �z�����ݔ͈�
		m_pStarData->m_VacumeRange.SetType(cCollider::CIRCLE);
		m_pStarData->m_VacumeRange.SetCircleCollider(m_pStarData->m_sprite.GetPos(), VACUUM_RANGE);

		// �폜�͈�
		m_pStarData->m_DeleteRange.SetType(cCollider::CIRCLE);
		m_pStarData->m_DeleteRange.SetCircleCollider(m_pStarData->m_sprite.GetPos(), DELETE_RANGE);

	}
}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cBlackHole::~cBlackHole(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;
	delete[] m_pStarData;

}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cBlackHole::Update(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �X�V
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// �����蔻��
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f - 30);
		m_pStarData->m_VacumeRange.SetCircleCollider(m_pStarData->m_sprite.GetPos(), VACUUM_RANGE);
		m_pStarData->m_DeleteRange.SetCircleCollider(m_pStarData->m_sprite.GetPos(), DELETE_RANGE);
		m_pStarData->m_sprite.AnimationLoop();

		// �ړ��̖ړI�ʒu����
		m_pStarData->m_Destination = m_pNetData->GetNetStart();
		// ������ړI�n�����̒P�ʃx�N�g�������߂�
		m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());

		// �ړI�ʒu�ɂ���������C�x���g�J�n�x���Ō��߂�
		if (m_pStarData->m_sprite.GetPos().y >= m_pStarData->m_Destination.y)
		{
			m_pStarData->m_bDestroyEvent = true;
		}
	}

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �C�x���g�i�[
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// �C�x���g���Ăяo����銴��
		if (m_pStarData->m_bCreateEvent){
			Create();
		}
		if (m_pStarData->m_bDestroyEvent){
			Destroy();
		}
		if (m_pStarData->m_bRespawnEvent){
			Respawn();
		}

	}

	// �C�x���g�̋N��
	// �f�o�b�O�L�[
	if (GetKeyboardTrigger(DIK_B)){
		m_pStarData = m_pRoot;	// �擪�ɖ߂�
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

			if (m_pStarData->m_bDraw)	// ��������
				continue;

			m_pStarData->m_bCreateEvent = true;
			m_pStarData = m_pRoot;	// �擪�ɖ߂�
			break;
		}
	}
	// �f�o�b�O�L�[
	if (GetKeyboardTrigger(DIK_M)){
		m_pStarData = m_pRoot;	// �擪�ɖ߂�
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

			if (!m_pStarData->m_bUse)	// ��������
				continue;
			m_pStarData->m_bDestroyEvent = true;
			m_pStarData = m_pRoot;	// �擪�ɖ߂�
			break;
		}
	}
	//if (GetKeyboardTrigger(DIK_R)){
	//	m_pStarData = m_pRoot;	// �擪�ɖ߂�
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		m_pStarData->m_bDestroyEvent = true;
	//	}
	//}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cBlackHole::Draw(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �`��
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// �`��t���O���Ȃ����͔̂�΂�
		if (!m_pStarData->m_bDraw)
			continue;

		// ��
		m_pStarData->m_sprite.Draw();

		// �Q�[�����ŗL���Ȃ炠���蔻���`��
		if (m_pStarData->m_bUse){
			m_pStarData->m_Collision.Draw();
			//m_pStarData->m_VacumeRange.Draw();
			//m_pStarData->m_DeleteRange.Draw();
		}
	}

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �f�o�b�O�v�����g
	PrintDebugProc("���������u���b�N�z�[����������\n");
	PrintDebugProc("���݂̐� %d/%d\n", m_nCurrentNum, m_nMaxNum);
	PrintDebugProc("B�L�[�Ő���\n");
	PrintDebugProc("M�L�[�ō폜\n");
	PrintDebugProc("�폜�㎩�����X�|�[��\n");
	PrintDebugProc("���X�|�[���C���^�[�o���m�F %d/%d\n", m_pStarData->m_nRespawnFrame, RESPAWN_FREAM);
	PrintDebugProc("%d\n", m_pStarData->m_sprite.GetCurrentAnimPattern());
	PrintDebugProc("������������������������������\n");
}
//=======================================================================================
//
//		����
//
//=======================================================================================
void cBlackHole::Create(){

	// �����C�x���g�̊J�n
	if (!m_pStarData->m_bCreateEnd){

		// �����ȊO�͓��������ɂȂ�͂�������R�s�؂ł����͂�
		//****** �����ɉ��o�Ƃ����������������Ă��� **********
		//m_pStarData->m_bUse = true;->����ł��ł��邯�Ǎ���͐����������Ă�����������
		m_pStarData->m_bDraw = true;
		//****************************************************


		// ���o����������琶���I���t���O�𗧂Ă�->if(EffectEnd()){m_pStar->....}
		//m_pStarData->m_bCreateEnd = true;

		m_pStarData->m_bCreateEnd = true;
	}


	// �����I���t���O���������烊�Z�b�g���ďI��
	if (m_pStarData->m_bCreateEnd){

		//	���Z�b�g
		m_pStarData->m_bCreateEnd = false;

		// �t���O�I��
		SetCountAndUse(true);
		m_pStarData->m_bCreateEvent = false;
		return;
	}
}


//=======================================================================================
//
//		�폜(�ꉞ�����)
//
//=======================================================================================
void cBlackHole::Destroy(){

	// �폜�C�x���g�̊J�n
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);

		// �����ȊO�͓��������ɂȂ�͂�������R�s�؂ł����͂�
		//********** �����ɉ��o�Ƃ������������Ă��� *************
		//*******************************************************

		// ���o�����������I���t���O�𗧂Ă�->if(EffectEnd()){m_pStar->....}
		m_pStarData->m_bDestroyEnd = true;

	}

	// �����I���t���O���������烊�Z�b�g���ďI��
	if (m_pStarData->m_bDestroyEnd){

		// �I�������瑦���X�|�[������
		m_pStarData->m_bRespawnEvent = true;


		//	���Z�b�g
		m_pStarData->m_bDestroyEnd = false;
		m_pStarData->m_bDraw = false;
		m_pStarData->m_bDestroyEvent = false;

		return;
	}
}

////=======================================================================================
////
////		���X�|�[��
////
////=======================================================================================
void cBlackHole::Respawn(){


	if (!m_pStarData->m_bRespawnEnd){

		// �t���[�����Z�J�n
		m_pStarData->m_nRespawnFrame++;

		if (m_pStarData->m_nRespawnFrame > RESPAWN_FREAM){

			// ���W�̌���
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT + m_pStarData->m_sprite.GetSizeX(), GAME_SCREEN_RIGHT - m_pStarData->m_sprite.GetSizeX());
			CreateRamdomPos.y = (float)CRandam::RandamRenge(0 + m_pStarData->m_sprite.GetSizeY(), SCREEN_HEIGHT - m_pStarData->m_sprite.GetSizeY());
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);

			m_pStarData->m_bRespawnEnd = true;
		}
	}

	// �����I���t���O���������烊�Z�b�g���ďI��
	if (m_pStarData->m_bRespawnEnd){

		// �����C�x���g�J�n
		m_pStarData->m_bCreateEvent = true;

		//	���Z�b�g
		m_pStarData->m_nRespawnFrame = 0;

		m_pStarData->m_bRespawnEnd = false;
		m_pStarData->m_bRespawnEvent = false;
		return;
	}
}

//=======================================================================================
//
//		�ԂƂ̏���
//
//=======================================================================================
//--- �Ԃ̃f�[�^�擾 ---
void cBlackHole::SetNetData(cNet* data){
	m_pNetData = data;
}

//--- �ԂƓ����������̏��� ---
void cBlackHole::OnCollidToNet(int num){

	// �擪���牽�Ԗڂ�
	m_pStarData = m_pRoot;
	m_pStarData += num;

	// Vector�m�F�p
	m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_VecStarToDest * 5);

}