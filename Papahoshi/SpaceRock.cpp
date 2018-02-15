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
#include "GameUI.h"

#define STAR_SIZE			(100)
#define VACUUM_RANGE		(200)
#define DELETE_RANGE		(10)
#define RESPAWN_FREAM		(20)
#define MAX_SPACE_ROCK_NUM	(1)


//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cSpaceRock::cSpaceRock(){

	// �����̏�����
	CRandam::InitRand();

	// �g�p�����i�[�t�@�C������ǂݍ��ނ��ǂ����ԕύX��������
	m_nMaxNum = MAX_SPACE_ROCK_NUM;

	// ���I�C���X�^���X
	m_pStarData = new cSpaceRockData[m_nMaxNum]();	//��������
	m_pRoot = m_pStarData;							// �擪�A�h���X�ۑ�

	// ������
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// ��������
		m_pStarData->m_bDraw = true;
		SetCountAndUse(true);

		// �T�C�Y�̕ύX
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));

		// �e�N�X�`���̐ݒ�
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_SPACE_ROCK));

		// ���W�̌���
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT + m_pStarData->m_sprite.GetSizeX(), GAME_SCREEN_RIGHT - m_pStarData->m_sprite.GetSizeX());
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0 + m_pStarData->m_sprite.GetSizeY(), SCREEN_HEIGHT - m_pStarData->m_sprite.GetSizeY());
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);

		// �����蔻��
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);
	}
}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cSpaceRock::~cSpaceRock(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;
	delete[] m_pStarData;

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSpaceRock::Update(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �X�V
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
		// �����蔻��
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);
		m_pStarData->m_sprite.AnimationLoop();
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
		m_pStarData = m_pRoot;			// �擪�ɖ߂�
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

			if (m_pStarData->m_bDraw)	// ��������
				continue;

			m_pStarData->m_bCreateEvent = true;
			m_pStarData = m_pRoot;		// �擪�ɖ߂�
			break;
		}
	}
	// �f�o�b�O�L�[
	if (GetKeyboardTrigger(DIK_M)){
		m_pStarData = m_pRoot;			// �擪�ɖ߂�
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

			if (!m_pStarData->m_bUse)	// ��������
				continue;
			m_pStarData->m_bDestroyEvent = true;
			m_pStarData = m_pRoot;		// �擪�ɖ߂�
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
//		����
//
//=======================================================================================
void cSpaceRock::Create(){

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
//		�폜(�ꉞ�����)
//
//=======================================================================================
void cSpaceRock::Destroy(){

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


//=======================================================================================
//
//		���X�|�[��
//
//=======================================================================================
void cSpaceRock::Respawn(){

	

}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cSpaceRock::Draw(){

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
	//	m_pStarData->m_Collision.Draw();
		}
	}

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �f�o�b�O�v�����g
	PrintDebugProc("��������覐΄�������\n");
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
//		�ԂƂ̏���
//
//=======================================================================================
//--- �ԂƓ����������̏��� ---
void cSpaceRock::OnCollidToNet(int count){

	

}