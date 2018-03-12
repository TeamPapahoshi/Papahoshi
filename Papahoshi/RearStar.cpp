//======================================================================
//	RearStar
//	
//	�T�v�Q�F���A��
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
#include "RearStar.h"
#include "Input.h"
#include "GameUI.h"
#include "MathEX.h"
#include "Score.h"
#include "sound.h"



//-----------------------------
// �}�N����`
//-----------------------------
#define STAR_SIZE			(150)	// �T�C�Y
#define RESPAWN_FREAM		(1000)	// ���X�|�[���̃C���^�[�o���t���[��
#define MAX_BLACK_HOLE_NUM	(1)		// �ő吔
#define REAR_STAR_SCORE		(1000)

//	�����ʒu
#define CREATE_PATTERN		(4)
#define CREATE_POS_01		(D3DXVECTOR2(GAME_SCREEN_RIGHT-STAR_SIZE/2.0f,GAME_SCREEN_UNDER-100))
#define CREATE_POS_02		(D3DXVECTOR2(GAME_SCREEN_LEFT+STAR_SIZE/2.0f,GAME_SCREEN_UNDER-100))
#define CREATE_POS_03		(CREATE_POS_01)
#define CREATE_POS_04		(CREATE_POS_01)



//===================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cRearStar::cRearStar(){

	// �����̏�����
	CRandam::InitRand();

	// �g�p�����i�[�t�@�C������ǂݍ��ނ��ǂ����ԕύX��������
	m_nMaxNum = MAX_BLACK_HOLE_NUM;

	// ���I�C���X�^���X
	m_pStarData = new cRearStarData[m_nMaxNum]();	//��������
	m_pRoot = m_pStarData;							// �擪�A�h���X�ۑ�

	// ������
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		//m_pStarData->m_bCreateEvent = true;


		// �^�C�v�̌���
		int Type = CRandam::RandamRenge(0, REAR_TYPE_MAX);
		switch (Type)
		{
		case PANET_01:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_PLANET01));
			m_pStarData->m_sprite.SetTexPatternDevide(10, 2);
			m_pStarData->m_sprite.SetIntervalChangePattern(7);
			m_pStarData->m_sprite.SetAnimationFlag(true);
			break;
		case PANET_02:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_PLANET02));
			m_pStarData->m_sprite.SetTexPatternDevide(10, 2);
			m_pStarData->m_sprite.SetIntervalChangePattern(7);
			m_pStarData->m_sprite.SetAnimationFlag(true);
			break;
		case PANET_03:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_PLANET03));
			m_pStarData->m_sprite.SetTexPatternDevide(10, 2);
			m_pStarData->m_sprite.SetIntervalChangePattern(7);
			m_pStarData->m_sprite.SetAnimationFlag(true);
			break;
		case SUN:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_SUN));
			m_pStarData->m_sprite.SetTexPatternDevide(5,4);
			m_pStarData->m_sprite.SetIntervalChangePattern(7);
			m_pStarData->m_sprite.SetAnimationFlag(true);
			break;
		default:
			break;
		}


		// ���W�̌���
		D3DXVECTOR2 CreateRamdomPos;
		int RamdomNum = CRandam::RandamRenge(1, CREATE_PATTERN + 1);
		switch (RamdomNum)
		{
		case 1:
			CreateRamdomPos = CREATE_POS_01;
			break;
		case 2:
			CreateRamdomPos = CREATE_POS_02;
			break;
		case 3:
			CreateRamdomPos = CREATE_POS_03;
			break;
		case 4:
			CreateRamdomPos = CREATE_POS_04;
			break;
		default:
			break;
		}
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);

		// �����蔻��
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f - 30);


		m_pStarData->m_bCaptured = false;

		// �T�C�Y�̕ύX
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(0, 0));

	}
}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cRearStar::~cRearStar(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;
	delete[] m_pStarData;
	m_pStarData = NULL;
	m_pRoot = NULL;
}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cRearStar::Update(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �X�V
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// �g�p����Ă��Ȃ��͔̂�΂�
		if (!m_pStarData->m_bUse)
			continue;

		// �����蔻��
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f - 30);
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

			//---- �t�B�[�o���łȂ��Ƃ��͌����������Đ��� -----
			//if (!m_bFever && m_nCurrentNum < LIMIT_METEOR_NOT_FEVER){
			//	Create();
			//}
			//if (!m_bFever && m_nCurrentNum >= LIMIT_METEOR_NOT_FEVER){
			//	m_pStarData->m_bCreateEvent = false;
			//}

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
	//if (GetKeyboardTrigger(DIK_B)){
	//	m_pStarData = m_pRoot;	// �擪�ɖ߂�
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (m_pStarData->m_bDraw)	// ��������
	//			continue;
	//		m_pStarData->m_bCreateEvent = true;
	//		m_pStarData = m_pRoot;	// �擪�ɖ߂�
	//		break;
	//	}
	//}
	//// �f�o�b�O�L�[
	//if (GetKeyboardTrigger(DIK_M)){
	//	m_pStarData = m_pRoot;	// �擪�ɖ߂�
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (!m_pStarData->m_bUse)	// ��������
	//			continue;
	//		m_pStarData->m_bDestroyEvent = true;
	//		m_pStarData = m_pRoot;	// �擪�ɖ߂�
	//		break;
	//	}
	//}
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
void cRearStar::Draw(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �`��
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// �`��t���O���Ȃ����͔̂�΂�
		if (!m_pStarData->m_bDraw)
			continue;

		// ��
		m_pStarData->m_sprite.Draw();

	}

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �f�o�b�O�v�����g
	PrintDebugProc("���������u���b�N�z�[����������\n");
	PrintDebugProc("���݂̐� %d/%d\n", m_nCurrentNum, m_nMaxNum);
	//PrintDebugProc("B�L�[�Ő���\n");
	//PrintDebugProc("M�L�[�ō폜\n");
	PrintDebugProc("���X�|�[���C���^�[�o���m�F %d/%d\n", m_pStarData->m_nRespawnFrame, RESPAWN_FREAM);
	PrintDebugProc("%d\n", m_pStarData->m_sprite.GetCurrentAnimPattern());
	PrintDebugProc("������������������������������\n");
}
//=======================================================================================
//
//		����
//
//=======================================================================================
void cRearStar::Create(){

	// �����C�x���g�̊J�n
	if (!m_pStarData->m_bCreateEnd){


		// �����ȊO�͓��������ɂȂ�͂�������R�s�؂ł����͂�
		//****** �����ɉ��o�Ƃ����������������Ă��� **********
		//m_pStarData->m_bUse = true;->����ł��ł��邯�Ǎ���͐����������Ă�����������
		m_pStarData->m_bDraw = true;

		//// �����グ�Ă���
		//if (m_pStarData->m_sprite.GetVtxColorA()+5.0f <= 255){
		//	m_pStarData->m_sprite.SetVtxColorA(m_pStarData->m_sprite.GetVtxColorA() + 5.0f);
		//}
		//else{
		//	m_pStarData->m_sprite.SetVtxColorA(255);
		//}


		// �T�C�Y��i�X�傫��
		if (m_pStarData->m_sprite.GetSize().x + 3.0f <= STAR_SIZE){
			m_pStarData->m_sprite.SetSizeX(m_pStarData->m_sprite.GetSize().x + 3.0f);
			m_pStarData->m_sprite.SetSizeY(m_pStarData->m_sprite.GetSize().y + 3.0f);
		}
		else{
			m_pStarData->m_sprite.SetSizeX(STAR_SIZE);
			m_pStarData->m_sprite.SetSizeY(STAR_SIZE);
		}



		//****************************************************



		// ���o����������琶���I���t���O�𗧂Ă�->if(EffectEnd()){m_pStar->....}

		//if (m_pStarData->m_sprite.GetVtxColorA() >= 255)
		//	m_pStarData->m_bCreateEnd = true;


		if (m_pStarData->m_sprite.GetSize().x >= STAR_SIZE)
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
void cRearStar::Destroy(){

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


		// �ԂŃL���b�`����Ă�����X�R�A���Z
		if (m_pStarData->m_bCaptured){
			AddScore(REAR_STAR_SCORE);
			PlaySound(SOUND_LABEL_SE_REAR_STAR_GET);
		}

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
void cRearStar::Respawn(){


	if (!m_pStarData->m_bRespawnEnd){

		// �t���[�����Z�J�n
		m_pStarData->m_nRespawnFrame++;

		if (m_pStarData->m_nRespawnFrame > RESPAWN_FREAM){

			// ���̐ݒ�
			//m_pStarData->m_sprite.SetVtxColorA(0);

			// �T�C�Y�̕ύX
			m_pStarData->m_sprite.SetSize(D3DXVECTOR2(0, 0));

			// �����̏�����
			CRandam::InitRand();


			// �^�C�v�̌���
			int Type = CRandam::RandamRenge(0, REAR_TYPE_MAX);
			switch (Type)
			{
			case PANET_01:
				m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_PLANET01));
				m_pStarData->m_sprite.SetTexPatternDevide(10, 2);
				m_pStarData->m_sprite.SetIntervalChangePattern(7);
				m_pStarData->m_sprite.SetAnimationFlag(true);
				break;
			case PANET_02:
				m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_PLANET02));
				m_pStarData->m_sprite.SetTexPatternDevide(10, 2);
				m_pStarData->m_sprite.SetIntervalChangePattern(7);
				m_pStarData->m_sprite.SetAnimationFlag(true);
				break;
			case PANET_03:
				m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_PLANET03));
				m_pStarData->m_sprite.SetTexPatternDevide(10, 2);
				m_pStarData->m_sprite.SetIntervalChangePattern(7);
				m_pStarData->m_sprite.SetAnimationFlag(true);
				break;
			case SUN:
				m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_SUN));
				m_pStarData->m_sprite.SetTexPatternDevide(5, 4);
				m_pStarData->m_sprite.SetIntervalChangePattern(7);
				m_pStarData->m_sprite.SetAnimationFlag(true);
				break;
			default:
				break;
			}

			// ���W�̌���
			D3DXVECTOR2 CreateRamdomPos;
			int RamdomNum = CRandam::RandamRenge(1, CREATE_PATTERN + 1);
			switch (RamdomNum)
			{
			case 1:
				CreateRamdomPos = CREATE_POS_01;
				break;
			case 2:
				CreateRamdomPos = CREATE_POS_02;
				break;
			case 3:
				CreateRamdomPos = CREATE_POS_03;
				break;
			case 4:
				CreateRamdomPos = CREATE_POS_04;
				break;
			default:
				break;
			}
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);
			m_pStarData->m_bCaptured = false;


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
void cRearStar::SetNetData(cNet* data){
	m_pNetData = data;
}

//--- �ԂƓ����������̏��� ---
void cRearStar::OnCollidToNet(int num){

	// �擪���牽�Ԗڂ�
	m_pStarData = m_pRoot;
	m_pStarData += num;

	// Vector�m�F�p
	m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_VecStarToDest * 5);

	m_pStarData->m_bCaptured = true;

}