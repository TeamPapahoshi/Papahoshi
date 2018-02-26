//======================================================================
//	Ryusei
//	
//	�T�v�Q�F��������
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
#include "Ryusei.h"
#include "rand.h"
#include "Input.h"
#include "MathEX.h"
#include <cmath>
#include "GameUI.h"
#include "sound.h"

//-----------------------------
//�}�N����`
//-----------------------------
#define STAR_SIZE				(160)
#define RESPAWN_FREAM			(200)
#define MAX_NORMAL_RYUSEI_NUM	(50)
#define MOVE_SPEED				(4.5f)


//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cRyusei::cRyusei(){

	// �����̏�����
	CRandam::InitRand();

	// �g�p�����i�[�t�@�C������ǂݍ��ނ��ǂ����ԕύX��������
	m_nMaxNum = MAX_NORMAL_RYUSEI_NUM;

	// ���I�C���X�^���X
	m_pStarData = new cRyuseiData[m_nMaxNum]();		//��������
	m_pRoot = m_pStarData;							// �擪�A�h���X�ۑ�


	// ������
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// �T�C�Y�̐ݒ�
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		
		// �e�N�X�`���̐ݒ�
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_CYAN_METEOR));
		m_pStarData->m_sprite.SetAnimationFlag(true);
		m_pStarData->m_sprite.SetTexPatternDevide(10, 1);
		m_pStarData->m_sprite.SetIntervalChangePattern(7);

		// �F
		m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));

		// ���Z����ON
		//m_pStarData->m_sprite.SetAddBlend(true);

		// ���W�̌���
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT + STAR_SIZE, GAME_SCREEN_RIGHT + 200);
		CreateRamdomPos.y = -(float)CRandam::RandamRenge(0, 800);
		//CreateRamdomPos = D3DXVECTOR2(SCREEN_CENTER);
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);


		//--- ����鏈���̂��߂̏��� ---
		m_pStarData->m_bStream = true;
		m_pStarData->m_StreamStartPos = CreateRamdomPos;																// ���������ʒu���X�^�[�g�ʒu�Ɏw��
		m_pStarData->m_StreamGoalPos  = D3DXVECTOR2(CreateRamdomPos.x - 250.0, CreateRamdomPos.y + SCREEN_HEIGHT);		// ��ʍ������S�[���Ɏw��
		m_pStarData->m_VecStreamMove  = m_pStarData->m_StreamGoalPos - m_pStarData->m_StreamStartPos;					// �X�^�[�g�ƃS�[�����痬�������̃x�N�g�������߂�
		m_pStarData->m_StremCos		  = (fabs(m_pStarData->m_StreamStartPos.x - m_pStarData->m_StreamGoalPos.x)			// �v�Z�p��cos�����߂�
										/ VectorSize(m_pStarData->m_VecStreamMove));
		m_pStarData->m_StreamRad	  = acosf(m_pStarData->m_StremCos);													// Cos����v�Z�p�̊p�x�����߂�
		m_pStarData->m_sprite.SetRad(D3DX_PI/2.0f - m_pStarData->m_StreamRad);										// �v�Z���ʂ���]�p�x���Z�b�g
		m_pStarData->m_MoveSpped      = MOVE_SPEED * UnitVector(m_pStarData->m_VecStreamMove);							// ���������̒P�ʃx�N�g�������߂đ������Z�b�g

	}
	m_bFever = false;
}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cRyusei::~cRyusei(){


	StopSound(SOUND_LABEL_SE_STREAM_METEOR);
	// �擪�ɖ߂�
	m_pStarData = m_pRoot;
	delete[] m_pStarData;
}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cRyusei::Update(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �X�V
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bUse)
			continue;

		// �����蔻��
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x, m_pStarData->m_sprite.GetPos().y+30), STAR_SIZE / 4.0f);

		// �ړ��̖ړI�ʒu����
		m_pStarData->m_Destination = m_pNetData->GetNetStart();
		// ������ړI�n�����̒P�ʃx�N�g�������߂�
		m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());

		// �A�j���[�V����
		m_pStarData->m_sprite.AnimationLoop();

		// ����鏈��
		if (m_pStarData->m_bStream){
			m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_MoveSpped);
		}


		// ��ʊO�ɏo����t���O�I�t
		if (m_pStarData->m_sprite.GetPosY() >= SCREEN_HEIGHT || m_pStarData->m_sprite.GetPosX() <= GAME_SCREEN_LEFT){
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


	

	// ���ׂĂ̗������g�p����Ȃ��Ȃ�������ʉ����~�߂�
	if (m_nCurrentNum==0 && !m_bFever){
		StopSound(SOUND_LABEL_SE_STREAM_METEOR);
	}



	// �C�x���g�̋N��
	// �f�o�b�O�L�[
	if (GetKeyboardTrigger(DIK_R)){
		m_pStarData = m_pRoot;	// �擪�ɖ߂�
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
			m_pStarData->m_bDestroyEvent = true;
		}
	}
	//if (GetKeyboardTrigger(DIK_K)){
	//	m_pStarData = m_pRoot;	// �擪�ɖ߂�
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (m_pStarData->m_bDraw)	// ��������
	//			continue;
	//		m_pStarData->m_bCreateEvent = true;
	//		break;
	//	}
	//}
	//// �f�o�b�O�L�[
	//if (GetKeyboardTrigger(DIK_D)){
	//	m_pStarData = m_pRoot;	// �擪�ɖ߂�
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (!m_pStarData->m_bUse)	// ��������
	//			continue;
	//		m_pStarData->m_bDestroyEvent = true;
	//		break;
	//	}
	//}

}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cRyusei::Draw(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �`��
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bDraw)
			continue;


		m_pStarData->m_sprite.Draw();
		//m_pStarData->m_Collision.Draw();

	}

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;



	// �f�o�b�O�v�����g
	PrintDebugProc("����������������������������\n");
	PrintDebugProc("���݂̐� %d/%d\n", m_nCurrentNum, m_nMaxNum);
	PrintDebugProc("R�L�[�Ń��Z�b�g\n");
	PrintDebugProc("���X�|�[���C���^�[�o���m�F %d/%d\n", m_pStarData->m_nRespawnFrame, RESPAWN_FREAM);
	PrintDebugProc("������������������������������\n");


}
//=======================================================================================
//
//		����
//
//=======================================================================================
void cRyusei::Create(){

	if (m_pStarData->m_bUse)
		return;

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
void cRyusei::Destroy(){

	if (!m_pStarData->m_bUse)
		return;

	// �����C�x���g�̊J�n
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);

		// �����ȊO�͓��������ɂȂ�͂�������R�s�؂ł����͂�
		//****** �����ɉ��o�Ƃ������������Ă��� **********
		//************************************************

		// ���o�����������I���t���O�𗧂Ă�->if(EffectEnd()){m_pStar->....}
		m_pStarData->m_bDestroyEnd = true;

	}

	// �����I���t���O���������烊�Z�b�g���ďI��
	if (m_pStarData->m_bDestroyEnd){


		// ���W�̌���
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT + STAR_SIZE, GAME_SCREEN_RIGHT + 200);
		CreateRamdomPos.y = -(float)CRandam::RandamRenge(0, 800);
		//CreateRamdomPos = D3DXVECTOR2(SCREEN_CENTER);
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);

		//--- ����鏈���̂��߂̏��� ---
		m_pStarData->m_bStream = true;
		m_pStarData->m_StreamStartPos = CreateRamdomPos;																// ���������ʒu���X�^�[�g�ʒu�Ɏw��
		m_pStarData->m_StreamGoalPos = D3DXVECTOR2(CreateRamdomPos.x - 250.0, CreateRamdomPos.y + SCREEN_HEIGHT);		// ��ʍ������S�[���Ɏw��
		m_pStarData->m_VecStreamMove = m_pStarData->m_StreamGoalPos - m_pStarData->m_StreamStartPos;					// �X�^�[�g�ƃS�[�����痬�������̃x�N�g�������߂�
		m_pStarData->m_StremCos = (fabs(m_pStarData->m_StreamStartPos.x - m_pStarData->m_StreamGoalPos.x)			// �v�Z�p��cos�����߂�
			/ VectorSize(m_pStarData->m_VecStreamMove));
		m_pStarData->m_StreamRad = acosf(m_pStarData->m_StremCos);													// Cos����v�Z�p�̊p�x�����߂�
		m_pStarData->m_sprite.SetRad(D3DX_PI / 2.0f - m_pStarData->m_StreamRad);										// �v�Z���ʂ���]�p�x���Z�b�g
		m_pStarData->m_MoveSpped = MOVE_SPEED * UnitVector(m_pStarData->m_VecStreamMove);							// ���������̒P�ʃx�N�g�������߂đ������Z�b�g

		// �ړ������̒P�ʃx�N�g�������߂�
		m_pStarData->m_MoveSpped = MOVE_SPEED * UnitVector(D3DXVECTOR2(CreateRamdomPos.x - 250.0f, CreateRamdomPos.y + SCREEN_HEIGHT) - CreateRamdomPos);


		// ������ړI�n�����̒P�ʃx�N�g�������߂�
		m_pStarData->m_Destination = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);
		m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());


		// �I����

		// �����C�x���g�J�n
		if (m_bFever)
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
void cRyusei::Respawn(){

	if (m_pStarData->m_bUse)
		return;

	if (!m_pStarData->m_bRespawnEnd){

		// �t���[�����Z�J�n
		m_pStarData->m_nRespawnFrame++;

		if (m_pStarData->m_nRespawnFrame > RESPAWN_FREAM){

			// ���W�̌���
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT + STAR_SIZE, GAME_SCREEN_RIGHT + 200);
			CreateRamdomPos.y = -(float)CRandam::RandamRenge(0, 800);
			//CreateRamdomPos = D3DXVECTOR2(SCREEN_CENTER);
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);

			//--- ����鏈���̂��߂̏��� ---
			m_pStarData->m_bStream = true;
			m_pStarData->m_StreamStartPos = CreateRamdomPos;																// ���������ʒu���X�^�[�g�ʒu�Ɏw��
			m_pStarData->m_StreamGoalPos = D3DXVECTOR2(CreateRamdomPos.x - 250.0, CreateRamdomPos.y + SCREEN_HEIGHT);		// ��ʍ������S�[���Ɏw��
			m_pStarData->m_VecStreamMove = m_pStarData->m_StreamGoalPos - m_pStarData->m_StreamStartPos;					// �X�^�[�g�ƃS�[�����痬�������̃x�N�g�������߂�
			m_pStarData->m_StremCos = (fabs(m_pStarData->m_StreamStartPos.x - m_pStarData->m_StreamGoalPos.x)			// �v�Z�p��cos�����߂�
				/ VectorSize(m_pStarData->m_VecStreamMove));
			m_pStarData->m_StreamRad = acosf(m_pStarData->m_StremCos);													// Cos����v�Z�p�̊p�x�����߂�
			m_pStarData->m_sprite.SetRad(D3DX_PI / 2.0f - m_pStarData->m_StreamRad);										// �v�Z���ʂ���]�p�x���Z�b�g
			m_pStarData->m_MoveSpped = MOVE_SPEED * UnitVector(m_pStarData->m_VecStreamMove);							// ���������̒P�ʃx�N�g�������߂đ������Z�b�g

			// �ړ������̒P�ʃx�N�g�������߂�
			m_pStarData->m_MoveSpped = MOVE_SPEED * UnitVector(D3DXVECTOR2(CreateRamdomPos.x - 250.0f, CreateRamdomPos.y + SCREEN_HEIGHT) - CreateRamdomPos);

			
			// ������ړI�n�����̒P�ʃx�N�g�������߂�
			m_pStarData->m_Destination = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);
			m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());

			m_pStarData->m_bRespawnEnd = true;
		}
	}

	// �����I���t���O���������烊�Z�b�g���ďI��
	if (m_pStarData->m_bRespawnEnd){

		// �����C�x���g�J�n
		if (m_bFever)
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
void cRyusei::SetNetData(cNet* data){
	m_pNetData = data;
}

//--- �ԂƓ����������̏��� ---
void cRyusei::OnCollidToNet(int num){

	// �擪���牽�Ԗڂ�
	m_pStarData = m_pRoot;
	m_pStarData += num;


	// Vector�m�F�p
	m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_VecStarToDest * 5);
}

//--- �Ԃ̒��ɗ���������Ƃ� ---
void cRyusei::OnCollidToNetArea(int num){

	// �擪���牽�Ԗڂ�
	m_pStarData = m_pRoot;
	m_pStarData += num;

	if (!m_pStarData->m_bUse)
		return;

	m_pStarData->m_bStream = false;
	
}