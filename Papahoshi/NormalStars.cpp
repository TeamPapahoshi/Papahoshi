//======================================================================
//	NormalStar
//	
//	�T�v�Q�F���u������
//	����ҁF�����@��
//	
//======================================================================

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>
#include <math.h>
#include <fstream>
#include <cmath>

#include "debugproc.h"
#include "Common.h"
#include "Texture.h"
#include "NormalStars.h"
#include "rand.h"
#include "Input.h"
#include "MathEX.h"
#include "GameUI.h"
#include "Score.h"
#include "sound.h"

//-----------------------------
//�}�N����`
//----------------------------
#define STAR_SIZE			(25)		// �ŏ��T�C�Y
#define STAR_SIZE_MARGIN	(20)		// �T�C�Y�̕�
#define RESPAWN_FREAM		(200)
#define MAX_NORMAL_STAR_NUM	(150)

// ��������(�����Ɖ�ʂɎc���Ă��������)
#define LIFE_TIME			(2000)
#define LIFE_TIME_MARGIN	(500)

#define NORMAL_STAR_SCORE	(100)	

#define VACUMED_SPEED		(0.2f)

//����̃G�t�F�N�g�p
#define EFFECT_FRAME   (90)
#define EFFECT_SIZE    (40.0f)
#define EFFECT_RADIUS  (8.0f)

//�Q�[�W�Ɉړ�����Ƃ��̃G�t�F�N�g�p
#define EFFECT_BEZIERCURVE_FRAME (60)
#define EFFECT_BEZIERCURVE_SIZE (22.0f)

//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cNormalStar::cNormalStar(){

	// �����̏�����
	CRandam::InitRand();

	// �g�p�����i�[�t�@�C������ǂݍ��ނ��ǂ����ԕύX��������
	m_nMaxNum = MAX_NORMAL_STAR_NUM;

	// ���I�C���X�^���X
	m_pStarData = new cNormalStarData[m_nMaxNum]();	//��������
	m_pRoot = m_pStarData;							// �擪�A�h���X�ۑ�

	// ������
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// ��������
		m_pStarData->m_bDraw = true;
		SetCountAndUse(true);
		m_pStarData->m_nEffectSetTime = CRandam::RandamRenge(0, EFFECT_FRAME);

		// �e�N�X�`���̐ݒ�
		m_pStarData->m_sprite.SetAnimationFlag(true);
	

		Init();

	}
}
void cNormalStar::Init(){

	
	// �T�C�Y�̕ύX
	float size = (float)(CRandam::RandamRenge(STAR_SIZE, STAR_SIZE + STAR_SIZE_MARGIN));
	m_pStarData->m_sprite.SetSize(D3DXVECTOR2(size, size));

	// ���̐F�̌���
	m_pStarData->m_nStarColorNum = CRandam::RandamRenge(0, 4);
	switch (m_pStarData->m_nStarColorNum)
	{
	case 0:
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_YELLOW_STAR_ANIM));
		m_pStarData->m_sprite.SetTexPatternDevide(4, 2);
		m_pStarData->m_sprite.SetIntervalChangePattern(7);
		break;
	case 1:
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_GREEN_STAR_ANIM));
		m_pStarData->m_sprite.SetTexPatternDevide(11, 2);
		m_pStarData->m_sprite.SetIntervalChangePattern(7);
		break;
	case 2:
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_PINK_STAR_ANIM));
		m_pStarData->m_sprite.SetTexPatternDevide(11, 2);
		m_pStarData->m_sprite.SetIntervalChangePattern(7);
		break;
	case 3:
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_BLUE_STAR_ANIM));
		m_pStarData->m_sprite.SetTexPatternDevide(4, 2);
		m_pStarData->m_sprite.SetIntervalChangePattern(7);
		break;
	default:
		break;
	}

	// �������W�̌���
	D3DXVECTOR2 CreateRamdomPos;
	CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT, GAME_SCREEN_RIGHT);
	CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT - 100);
	//CreateRamdomPos = D3DXVECTOR2(SCREEN_CENTER);
	m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// ���

	// �����蔻��
	m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
	m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);

	// �������Ԃ̐ݒ�
	m_pStarData->m_nLifeTime = CRandam::RandamRenge(LIFE_TIME, LIFE_TIME + LIFE_TIME_MARGIN);
}


//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cNormalStar::~cNormalStar(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;
	delete[] m_pStarData;
}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cNormalStar::Update(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �X�V
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		//�G�t�F�N�g�\����
		if (m_pStarData->m_bEffectSetFlag)
		{
			//�G�t�F�N�g�\���t���[���̉��Z
			m_pStarData->m_nEffectFrame++;
			if (!m_pGageData->GetGagemax() && m_pStarData->m_nEffectFrame == EFFECT_BEZIERCURVE_FRAME)
			{
				m_pGageData->GageAdd();

				m_pStarData->m_bEffectSetFlag = false;
				m_pStarData->m_nEffectFrame = 0;
			}
		}

		// �g�p����Ă��Ȃ��͔̂�΂�
		if (!m_pStarData->m_bUse)
			continue;


		// �������Ԍ��炷
		m_pStarData->m_nLifeTime--;
		if (m_pStarData->m_nLifeTime<=0){
			m_pStarData->m_bDestroyEvent = true;
			m_pStarData->m_DeleteToLifeTime = true;
		}

		// �����蔻��
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);

		// �ړ��̖ړI�ʒu����
		m_pStarData->m_Destination = m_pNetData->GetNetStart();
		// ������ړI�n�����̒P�ʃx�N�g�������߂�
		m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());

		// �ړI�ʒu�ɂ���������C�x���g�J�n�x���Ō��߂�
		if (m_pStarData->m_sprite.GetPos().y >= m_pStarData->m_Destination.y )
		{
			m_pStarData->m_bDestroyEvent = true;
			m_pStarData->m_bAddScore = true;

			if (!m_pStarData->m_bEffectSetFlag)
			{
				// �G�t�F�N�g�̐ݒ�
				GetEffectManeger()->SetEffectBezierCurve(cTextureManeger::GetTextureGame(TEX_GAME_STAR_LIGHT),
					m_pStarData->m_sprite.GetPos(),
					D3DXVECTOR2(EFFECT_BEZIERCURVE_SIZE, EFFECT_BEZIERCURVE_SIZE),
					D3DXCOLOR(255, 255, 255, 255),
					EFFECT_BEZIERCURVE_FRAME,
					m_pStarData->m_sprite.GetPos(),
					m_pGageData->GetGageSprite().GetPos() + m_pGageData->GetGageSprite().GetSize() / 2);

				//�G�t�F�N�g�g�p�t���O��On��
				m_pStarData->m_bEffectSetFlag = true;
			}

		}

		// �A�j���[�V����
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

		if (m_pStarData->m_bDraw)
		{
			// �G�t�F�N�g�����t���[���̉��Z
			m_pStarData->m_nEffectSetTime--;

			//�t���[�������l�ɂȂ�����G�t�F�N�g�̐���
			if (m_pStarData->m_nEffectSetTime < 0)
			{
				GetEffectManeger()->SetEffectSparkle(cTextureManeger::GetTextureGame(TEX_GAME_EFFECT_SPARKLE),
					m_pStarData->m_sprite.GetPos(),
					D3DXVECTOR2(EFFECT_SIZE, EFFECT_SIZE),
					m_pStarData->m_sprite.GetVtxColor(),
					EFFECT_FRAME / 2,
					D3DXVECTOR2(EFFECT_RADIUS, EFFECT_RADIUS),
					EFFECT_SPARKLE_TEX_DIVIDE_X, EFFECT_SPARKLE_TEX_DIVIDE_Y);

				m_pStarData->m_nEffectSetTime = CRandam::RandamRenge(0, EFFECT_FRAME);
			}
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
void cNormalStar::Draw(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �`��
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bDraw)
			continue;

		m_pStarData->m_sprite.Draw();

		//if (m_pStarData->m_bUse)
		//	m_pStarData->m_Collision.Draw();
	}

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;


	// �f�o�b�O�v�����g
	PrintDebugProc("���������������u��������������\n");
	PrintDebugProc("���݂̐� %d/%d\n", m_nCurrentNum, m_nMaxNum);
	PrintDebugProc("R�L�[�Ń��Z�b�g\n");
	PrintDebugProc("���X�|�[���C���^�[�o���m�F %d/%d\n", m_pStarData->m_nRespawnFrame, RESPAWN_FREAM);
	PrintDebugProc("Anim %d\n", m_pStarData->m_sprite.GetCurrentAnimPattern());
	PrintDebugProc("������������������������������\n");


}
//=======================================================================================
//
//		����
//
//=======================================================================================
void cNormalStar::Create(){

	// �����C�x���g�̊J�n
	if (!m_pStarData->m_bCreateEnd){



		// �����ȊO�͓��������ɂȂ�͂�������R�s�؂ł����͂�
		//****** �����ɉ��o�Ƃ����������������Ă��� **********
		//m_pStarData->m_bUse = true;->����ł��ł��邯�Ǎ���͐����������Ă�����������
		m_pStarData->m_bDraw = true;

		if (m_pStarData->m_sprite.GetVtxColorA() <= 255){
			m_pStarData->m_sprite.SetVtxColorA(m_pStarData->m_sprite.GetVtxColorA() + 5.0f);
		}



		//****************************************************



		// ���o����������琶���I���t���O�𗧂Ă�->if(EffectEnd()){m_pStar->....}

		if (m_pStarData->m_sprite.GetVtxColorA() >= 255)
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
void cNormalStar::Destroy(){

	// �����C�x���g�̊J�n
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);

		// �����ȊO�͓��������ɂȂ�͂�������R�s�؂ł����͂�
		//****** �����ɉ��o�Ƃ������������Ă��� **********



		//****************************************************


		// ���o�����������I���t���O�𗧂Ă�->if(EffectEnd()){m_pStar->....}
		m_pStarData->m_bDestroyEnd = true;

	

	}

	// �����I���t���O���������烊�Z�b�g���ďI��
	if (m_pStarData->m_bDestroyEnd){

		// �X�R�A���Z
		if (m_pStarData->m_bAddScore){
			AddScore(NORMAL_STAR_SCORE);
			m_pStarData->m_bAddScore = false;
		}

		// �Ԃł̊l���ɂ���ď��ł�����
		if (m_pStarData->m_bCaptured && !m_pStarData->m_bHitBlackHoleDelete && !m_pStarData->m_bHitSpaceRock && !m_pStarData->m_DeleteToLifeTime){
			PlaySound(SOUND_LABEL_SE_STAR_GET);
			m_pStarData->m_bCaptured = false;
			m_pStarData->m_bHitBlackHoleDelete = false;
			m_pStarData->m_bHitSpaceRock = false;
			m_pStarData->m_DeleteToLifeTime = false;
		}


		// �u���b�N�z�[���ł̊l���ɂ���ď��ł�����
		if (!m_pStarData->m_bCaptured && m_pStarData->m_bHitBlackHoleDelete && !m_pStarData->m_bHitSpaceRock && !m_pStarData->m_DeleteToLifeTime){
			PlaySound(SOUND_LABEL_SE_VACUME_BLACK_HOLE);
			m_pStarData->m_bCaptured = false;
			m_pStarData->m_bHitBlackHoleDelete = false;
			m_pStarData->m_bHitSpaceRock = false;
			m_pStarData->m_DeleteToLifeTime = false;
		}

		//	���Z�b�g
		m_pStarData->m_bDestroyEnd = false;
		m_pStarData->m_bDraw = false;
		m_pStarData->m_bDestroyEvent = false;

		// �I�������瑦���X�|�[������
		m_pStarData->m_bRespawnEvent = true;

		return;
	}
}

////=======================================================================================
////
////		���X�|�[��
////
////=======================================================================================
void cNormalStar::Respawn(){

	
	if (!m_pStarData->m_bRespawnEnd){

		// �t���[�����Z�J�n
		m_pStarData->m_nRespawnFrame++;

		if (m_pStarData->m_nRespawnFrame > RESPAWN_FREAM){

			Init();

			// ���̐ݒ�
			m_pStarData->m_sprite.SetVtxColorA(0);


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
//--- �Ԃ̃f�[�^�擾 ---
void cNormalStar::SetNetData(cNet* data){
	m_pNetData = data;
}

//--- �ԂƓ����������̏��� ---
void cNormalStar::OnCollidToNet(int num){

	// �擪���牽�Ԗڂ�
	m_pStarData = m_pRoot;
	m_pStarData += num;

	// �l���t���O��ture
	if (!m_pStarData->m_bCaptured)
		m_pStarData->m_bCaptured = true;

	// Vector�m�F�p
	m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_VecStarToDest*5);
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
void cNormalStar::OnCollidToBlackHoleVacumeRange(int Normal, int Black){

	m_pStarData = m_pRoot;
	m_pStarData += Normal;

	// �U������
	if (m_pStarData->m_bVibration){

		m_pStarData->m_nVibrationFrame++;
		m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() + 0.25f);

		if (m_pStarData->m_nVibrationFrame > 5){
			m_pStarData->m_bVibration = false;
			m_pStarData->m_nVibrationFrame = 0;
		}	
	}

	else if (!m_pStarData->m_bVibration){

		m_pStarData->m_nVibrationFrame++;
		m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() - 0.25f);

		if (m_pStarData->m_nVibrationFrame > 5){
			m_pStarData->m_bVibration = true;
			m_pStarData->m_nVibrationFrame = 0;
		}
	}


	// �u���b�N�z�[���̒��S���擾
	D3DXVECTOR2 Center = m_pBlackHoleData->GetStarData()[Black].m_sprite.GetPos();

	// ������u���b�N�z�[�������ւ̒P�ʃx�N�g�������߂�
	D3DXVECTOR2 VecStarToBlack;
	VecStarToBlack = UnitVector(Center - m_pStarData->m_sprite.GetPos())*VACUMED_SPEED;

	// �ړ����f
	m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + VecStarToBlack);
	

}

//---- �u���b�N�z�[���̍폜�͈͂ɓ����������̏��� -----
void cNormalStar::OnCollidToBlackHoleDeleteRange(int Normal){

	m_pStarData = m_pRoot;
	m_pStarData += Normal;

	m_pStarData->m_bHitBlackHoleDelete = true;

	m_pStarData->m_bDestroyEvent = true;
	m_pStarData->m_bAddScore = false;
	
}


//=======================================================================================
//
//		覐΂Ƃ̏���
//
//=======================================================================================
void cNormalStar::OnCollidToSpaceRock(int num){

	m_pStarData = m_pRoot;
	m_pStarData += num;

	m_pStarData->m_bHitSpaceRock = true;


	m_pStarData->m_bDestroyEvent = true;
	m_pStarData->m_bAddScore = false;
}

//=======================================================================================
//
//		�Q�[�W�Ƃ̏���
//
//=======================================================================================
//---- �Q�[�W�̏����擾 -----
void cNormalStar::SetGageData(cGage* data)
{
	m_pGageData = data;
}