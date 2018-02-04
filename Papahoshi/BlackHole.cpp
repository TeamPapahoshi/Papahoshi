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


//-----------------------------
// �}�N����`
//-----------------------------
#define STAR_SIZE	(100)

#define VACUUM_RANGE	(200)
#define DELETE_RANGE	(20)

#define RESPAWN_FREAM	(100)
#define MAX_BLACK_HOLE_NUM	(1)

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

		// ���W�̌���
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// ���

		// �����蔻��
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);

	

		// �z�����ݔ͈�
	/*	m_pStarData->m_VacumeRange.SetType(cCollider::CIRCLE);
		m_pStarData->m_VacumeRange.SetCircleCollider(m_pStarData->m_sprite.GetPos(), VACUUM_RANGE);*/

		//// �ړ��̖ړI�ʒu����
		//m_pStarData->m_PurposPos = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);
		//// �ړI�n�܂ł̋����𑪒�
		//m_pStarData->m_PurPosDist.x = fabs(m_pStarData->m_PurposPos.x - m_pStarData->m_sprite.GetPos().x);
		//m_pStarData->m_PurPosDist.y = fabs(m_pStarData->m_PurposPos.y - m_pStarData->m_sprite.GetPos().y);
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

	// �C�x���g�i�[���[�v�H
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
		// �����蔻��
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);
	}


	//// �C�x���g�̋N��
	// �f�o�b�O�L�[
	////if (GetKeyboardTrigger(DIK_B)){
	////	m_pStarData = m_pRoot;	// �擪�ɖ߂�
	////	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

	////		if (m_pStarData->m_bDraw)	// ��������
	////			continue;

	////		m_pStarData->m_bCreateEvent = true;
	////		m_pStarData = m_pRoot;	// �擪�ɖ߂�
	////		break;
	////	}
	////}
	//// �f�o�b�O�L�[
	////if (GetKeyboardTrigger(DIK_M)){
	////	m_pStarData = m_pRoot;	// �擪�ɖ߂�
	////	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

	////		if (!m_pStarData->m_bUse)	// ��������
	////			continue;
	////		m_pStarData->m_bDestroyEvent = true;
	////		m_pStarData = m_pRoot;	// �擪�ɖ߂�
	////		break;
	////	}
	////}
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

		if (!m_pStarData->m_bDraw)
			continue;

		m_pStarData->m_sprite.Draw();

		if (m_pStarData->m_bUse)
			m_pStarData->m_Collision.Draw();
	}

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �f�o�b�O�v�����g
	PrintDebugProc("���������u���b�N�z�[����������\n");
	PrintDebugProc("���݂̐� %d/%d\n", m_nCurrentNum, m_nMaxNum);
	PrintDebugProc("�g�p�t���O %d\n", m_pStarData->m_bUse);
	PrintDebugProc("�`��t���O %d\n", m_pStarData->m_bDraw);
	PrintDebugProc("B�L�[�Ő���\n");
	PrintDebugProc("M�L�[�ō폜\n");
	PrintDebugProc("�폜�㎩�����X�|�[��\n");
	PrintDebugProc("���X�|�[���C���^�[�o���m�F %d/%d\n", m_pStarData->m_nRespawnFrame, RESPAWN_FREAM);
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
		//****** �����ɉ��o�Ƃ������������Ă��� *************
		//****************************************************


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
			CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
			CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// ���


			//// �ړ��̖ړI�ʒu����
			//m_pStarData->m_PurposPos = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);
			//// �ړI�n�܂ł̋����𑪒�
			//m_pStarData->m_PurPosDist.x = fabs(m_pStarData->m_PurposPos.x - m_pStarData->m_sprite.GetPos().x);
			//m_pStarData->m_PurPosDist.y = fabs(m_pStarData->m_PurposPos.y - m_pStarData->m_sprite.GetPos().y);

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


	// �Ԃ������Ă���Ƃ��݈̂ړ�����
	if (m_pNetData->GetPullFlug()){

		// �ړ�����������
		float DistGoalX = m_pStarData->m_PurPosDist.x / 3.0f;	// �O��ɕ����Ĉړ�����
		float DistGoalY = m_pStarData->m_PurPosDist.y / 3.0f;


		// ��������ړ��ʂ��Z�o(�t���[�����Ŋ���)
		m_pStarData->m_Move.x = DistGoalX / 50.0f;
		m_pStarData->m_Move.y = DistGoalY / 45.0f;



		// �ړ��ʂ𔽉f
	/*	if (m_pStarData->m_sprite.GetPosX() >= m_pStarData->m_PurposPos.x){
			m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() - m_pStarData->m_Move.x);
		}
		else if ((m_pStarData->m_sprite.GetPosX() <= m_pStarData->m_PurposPos.x)){
			m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() + m_pStarData->m_Move.x);
		}
		if ((m_pStarData->m_sprite.GetPosY() <= m_pStarData->m_PurposPos.y)){
			m_pStarData->m_sprite.SetPosY(m_pStarData->m_sprite.GetPosY() + m_pStarData->m_Move.y);
		}
		else if ((m_pStarData->m_sprite.GetPosY() >= m_pStarData->m_PurposPos.y)){
			m_pStarData->m_sprite.SetPosY(m_pStarData->m_sprite.GetPosY() + m_pStarData->m_Move.y);
		}*/
	}

}