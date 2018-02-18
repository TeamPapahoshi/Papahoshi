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

//-----------------------------
//�}�N����`
//-----------------------------
#define STAR_SIZE				(30)
#define RESPAWN_FREAM			(200)
#define MAX_NORMAL_RYUSEI_NUM	(50)
#define MOVE_SPEED				(2.5f)


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

		// ��������
		m_pStarData->m_bDraw = true;
		SetCountAndUse(true);

		// �T�C�Y�̕ύX
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		

		// �e�N�X�`���̐ݒ�
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_YELLOW_STAR_ANIM));
		m_pStarData->m_sprite.SetTexPatternDevide(11, 2);

		// �F
		m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));

		// ���Z����ON
		m_pStarData->m_sprite.SetAddBlend(true);

		// ���W�̌���
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT + STAR_SIZE, GAME_SCREEN_RIGHT + 200);
		CreateRamdomPos.y = -(float)CRandam::RandamRenge(0, 800);
		//CreateRamdomPos = D3DXVECTOR2(SCREEN_CENTER);
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);

		// ���������̒P�ʃx�N�g�������߂đ����̕␳
		m_pStarData->m_VecMove = MOVE_SPEED * UnitVector(D3DXVECTOR2(CreateRamdomPos.x - 250.0, CreateRamdomPos.y + SCREEN_HEIGHT) - CreateRamdomPos);

		// �ړ��̖ړI�ʒu����
		m_pStarData->m_Destination = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 100);
		// ������ړI�n�����̒P�ʃx�N�g�������߂�
		m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());


		// CORE
		m_pStarData->m_Core.SetPos(m_pStarData->m_sprite.GetPos());
		m_pStarData->m_Core.SetAddBlend(true);
		m_pStarData->m_Core.SetSize(D3DXVECTOR2(STAR_SIZE + 50, STAR_SIZE + 50));// �T�C�Y�̕ύX
		m_pStarData->m_Core.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR_LIGHT));// �e�N�X�`���̐ݒ�
		m_pStarData->m_Core.SetVtxColor(D3DXCOLOR((float)CRandam::RandamRenge(0, 255), (float)CRandam::RandamRenge(0, 255),
													(float)CRandam::RandamRenge(0, 255), 155));		// �F
		m_pStarData->m_Core.SetVtxColor(D3DXCOLOR(255,255,0,155));		// �F
	}
}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cRyusei::~cRyusei(){

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

		// �����蔻��
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);


		m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_VecMove);
		m_pStarData->m_sprite.SetRad(m_pStarData->m_sprite.GetRad() - 0.01f);

		// �O�Ղ̍X�V
		m_pStarData->m_Line.Update(m_pStarData->m_sprite.GetPos(), m_pStarData->m_Core.GetVtxColor());

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

		m_pStarData->m_Line.Draw();
		m_pStarData->m_Core.Draw();
		m_pStarData->m_sprite.Draw();

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
void cRyusei::Respawn(){


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

			// �ړ������̒P�ʃx�N�g�������߂�
			m_pStarData->m_VecMove = MOVE_SPEED * UnitVector(D3DXVECTOR2(CreateRamdomPos.x - 250.0, CreateRamdomPos.y + SCREEN_HEIGHT) - CreateRamdomPos);

			
			// ������ړI�n�����̒P�ʃx�N�g�������߂�
			m_pStarData->m_Destination = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);
			m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());

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
