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

//-----------------------------
// �}�N����`
//-----------------------------
#define STAR_SIZE			(100)
#define RESPAWN_FREAM		(200)
#define MAX_SPACE_ROCK_NUM	(1)
#define DESTROY_STAR		(5)
#define EXPLOSION_FRAME		(100)		// ��������


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

		// �e�N�X�`���̐ݒ�
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_SPACE_ROCK));

		// ���W�̌���
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT + m_pStarData->m_sprite.GetSizeX(), GAME_SCREEN_RIGHT - m_pStarData->m_sprite.GetSizeX());
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0 + m_pStarData->m_sprite.GetSizeY(), SCREEN_HEIGHT - m_pStarData->m_sprite.GetSizeY());
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);

		// �T�C�Y�̕ύX
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));

		// �����蔻��
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);

		// �j�󐔂�ݒ�
		m_pStarData->m_nDestroyStarNum = DESTROY_STAR;

		// �����p
		m_pStarData->m_ExplosionAnim.SetPos(m_pStarData->m_sprite.GetPos());	// 
		m_pStarData->m_ExplosionAnim.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_EXPLOSION));
		m_pStarData->m_ExplosionAnim.SetAnimationFlag(true);
		m_pStarData->m_ExplosionAnim.SetTexPatternDevide(8, 1);
		m_pStarData->m_ExplosionAnim.SetIntervalChangePattern(5);
		m_pStarData->m_ExplosionFrame = EXPLOSION_FRAME;				// ��������
		m_pStarData->m_bExplosion = false;								// �J�n�p�t���O
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

		// �j�󐔂ɂ���ĐF��ς���
		switch (m_pStarData->m_nDestroyStarNum){

		case 5:
			m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));
			break;
		case 4:
			m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 200, 200, 255));
			break;
		case 3:
			m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 155, 155, 255));
			break;
		case 2:
			m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 55, 55, 255));
			break;
		case 1:
			m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 0, 0, 255));
			break;
		}

		// �j��J�E���g���[���ɂȂ�Ɣ���
		if (m_pStarData->m_nDestroyStarNum <= 0){

			m_pStarData->m_nDestroyStarNum = DESTROY_STAR;
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


	if (GetKeyboardTrigger(DIK_2)){
		m_pStarData = m_pRoot;			// �擪�ɖ߂�
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
			if (!m_pStarData->m_bUse)	// ��������
			continue;
			m_pStarData->m_nDestroyStarNum--;
			m_pStarData = m_pRoot;		// �擪�ɖ߂�
			break;
		}
	}
	// �C�x���g�̋N��
	// �f�o�b�O�L�[
	//if (GetKeyboardTrigger(DIK_B)){
	//	m_pStarData = m_pRoot;			// �擪�ɖ߂�
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (m_pStarData->m_bDraw)	// ��������
	//			continue;
	//		m_pStarData->m_bCreateEvent = true;
	//		m_pStarData = m_pRoot;		// �擪�ɖ߂�
	//		break;
	//	}
	//}
	//// �f�o�b�O�L�[
	//if (GetKeyboardTrigger(DIK_M)){
	//	m_pStarData = m_pRoot;			// �擪�ɖ߂�
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (!m_pStarData->m_bUse)	// ��������
	//			continue;
	//		m_pStarData->m_bDestroyEvent = true;
	//		m_pStarData = m_pRoot;		// �擪�ɖ߂�
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
void cSpaceRock::Draw(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �`��
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){


		if (m_pStarData->m_bExplosion)
			m_pStarData->m_ExplosionAnim.Draw();

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
	PrintDebugProc("2�L�[�Ŕj�󐔍X�V");
	PrintDebugProc("�j�� %d/%d\n", m_pStarData->m_nDestroyStarNum, DESTROY_STAR);
	PrintDebugProc("�������� %d/%d\n", m_pStarData->m_ExplosionFrame, EXPLOSION_FRAME);
	PrintDebugProc("���X�|�[���C���^�[�o�� %d/%d\n", m_pStarData->m_nRespawnFrame, RESPAWN_FREAM);
	PrintDebugProc("������������������������������\n");

}

//=======================================================================================
//
//		����
//
//=======================================================================================
void cSpaceRock::Create(){

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
void cSpaceRock::Destroy(){

	// �폜�C�x���g�̊J�n
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);
		m_pStarData->m_bDraw = false;

		
		//****** �����ɉ��o�Ƃ������������Ă��� *************

		// �����t���[���̍X�V
		m_pStarData->m_ExplosionFrame--;

		// �t���O�I��
		m_pStarData->m_bExplosion = true;

		// �A�j���[�V����
		m_pStarData->m_ExplosionAnim.AnimationLoop();

		//****************************************************

		// ���o�����������I���t���O�𗧂Ă�->if(EffectEnd()){m_pStar->....}
		if (m_pStarData->m_ExplosionFrame <= 0)
			m_pStarData->m_bDestroyEnd = true;

	}

	// �����I���t���O���������烊�Z�b�g���ďI��
	if (m_pStarData->m_bDestroyEnd){

		m_pStarData->m_ExplosionFrame = EXPLOSION_FRAME;				// ��������
		m_pStarData->m_bExplosion = false;								// �J�n�p�t���O

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

	if (!m_pStarData->m_bRespawnEnd){

		// �t���[�����Z�J�n
		m_pStarData->m_nRespawnFrame++;

		if (m_pStarData->m_nRespawnFrame > RESPAWN_FREAM){

			
			m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));// �T�C�Y�̕ύX

			m_pStarData->m_Collision.SetType(cCollider::CIRCLE);// �����蔻��
			m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);
		
			m_pStarData->m_nDestroyStarNum = DESTROY_STAR;						// �j�󐔂�ݒ�

			m_pStarData->m_ExplosionFrame = EXPLOSION_FRAME;				// ��������
			m_pStarData->m_bExplosion = false;								// �J�n�p�t���O

			// ���X�|�[�������I��
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
//--- �ԂƓ����������̏��� ---
void cSpaceRock::OnCollidToNet(int count){

	

}

//=======================================================================================
//
//		���u���Ƃ̏���
//
//=======================================================================================
void cSpaceRock::SetNormalStarData(cNormalStar* data){
	m_pNormalStarData = data;
}


void cSpaceRock::OnCollidToNormalStar(int num){

	// �擪���牽�Ԗڂ�
	m_pStarData = m_pRoot;
	m_pStarData += num;

	m_pStarData->m_nDestroyStarNum--;

	//m_pStarData->m_bDestroyEvent = true;




}