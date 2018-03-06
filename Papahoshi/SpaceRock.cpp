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
#include "MathEX.h"
#include "sound.h"

//-----------------------------
// �}�N����`
//-----------------------------
//---- 覐� ----
#define CREATE_PATTERN		(2)
#define CREATE_POS_01		(D3DXVECTOR2(GAME_SCREEN_LEFT+500,200))
//#define CREATE_POS_01		(D3DXVECTOR2(GAME_SCREEN_LEFT+150,350))
//#define CREATE_POS_02		(D3DXVECTOR2(GAME_SCREEN_RIGHT-150,350)
#define CREATE_POS_02		(D3DXVECTOR2(GAME_SCREEN_LEFT+500,200))
#define STAR_SIZE			(150)
#define RESPAWN_FREAM		(500)
#define MAX_SPACE_ROCK_NUM	(1)
#define DESTROY_STAR		(20)

//---- �����֘A -----
#define EXPLOSION_FRAME		(40)		// ��������
#define EXPLOSION_SIZE		(250)

//---- �������� -------
#define LIFE_TIME			(600)


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

		// �e�N�X�`���̐ݒ�
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_SPACE_ROCK));
		m_pStarData->m_sprite.SetAnimationFlag(true);
		m_pStarData->m_sprite.SetTexPatternDevide(5, 4);
		m_pStarData->m_sprite.SetIntervalChangePattern(7);

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
		default:
			break;
		}
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);

		// �T�C�Y�̕ύX
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));

		// �����蔻��
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f-20.0f);

		// �j�󐔂�ݒ�
		m_pStarData->m_nDestroyStarNum = DESTROY_STAR;

		// �����p
		m_pStarData->m_ExplosionAnim.SetPos(m_pStarData->m_sprite.GetPos());	// 
		m_pStarData->m_ExplosionAnim.SetSize(D3DXVECTOR2(EXPLOSION_SIZE, EXPLOSION_SIZE));
		m_pStarData->m_ExplosionAnim.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_EXPLOSION));
		m_pStarData->m_ExplosionAnim.SetAddBlend(true);
		m_pStarData->m_ExplosionAnim.SetAnimationFlag(true);
		m_pStarData->m_ExplosionAnim.SetCurrentAnimPattern(0);
		m_pStarData->m_ExplosionAnim.SetTexPatternDevide(8, 2);
		m_pStarData->m_ExplosionAnim.SetIntervalChangePattern(3);
		m_pStarData->m_ExplosionFrame = EXPLOSION_FRAME;				// ��������
		m_pStarData->m_bExplosion = false;								// �J�n�p�t���O

		// �������Ԃ̎w��
		m_pStarData->m_nLifeTime = LIFE_TIME;

		// ���̐ݒ�
		m_pStarData->m_sprite.SetVtxColorA(0);

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


		if (!m_pStarData->m_bUse)
			continue;

		// �����蔻��
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f - 20.0f);

		// �A�j���[�V�����X�V
		m_pStarData->m_sprite.AnimationLoop();

		// �ԂƂ̏����p
		m_pStarData->m_Destination = m_pNetData->GetNetStart();	// �ړ��̖ړI�ʒu����
		m_pStarData->m_Destination.y = m_pNetData->GetNetStart().y - 100.0f;	// �ړ��̖ړI�ʒu����
		m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());// ������ړI�n�����̒P�ʃx�N�g�������߂�

		// �����̈ʒu
		m_pStarData->m_ExplosionAnim.SetPos(m_pStarData->m_sprite.GetPos());


		//---- �����J�E���g�ɂ���ĐF��ς��� -----
		float ratio = (float)m_pStarData->m_nLifeTime / (float)LIFE_TIME;
		m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 255 * ratio, 255 * ratio, 255));
		// �c��1�Ő^���Ԃ�
		if (m_pStarData->m_nLifeTime <= 200){
			m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 0, 0, 255));

			// �U������
			if (m_pStarData->m_bVibration){

				m_pStarData->m_nVibrationFrame++;
				m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() + 0.4f);

				if (m_pStarData->m_nVibrationFrame > 3){
					m_pStarData->m_bVibration = false;
					m_pStarData->m_nVibrationFrame = 0;
				}
			}

			else if (!m_pStarData->m_bVibration){

				m_pStarData->m_nVibrationFrame++;
				m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() - 0.4f);

				if (m_pStarData->m_nVibrationFrame > 3){
					m_pStarData->m_bVibration = true;
					m_pStarData->m_nVibrationFrame = 0;
				}
			}
		}

		// �ړI�ʒu�ɂ���������C�x���g�J�n�x���Ō��߂�
		if (m_pStarData->m_sprite.GetPos().y >= m_pStarData->m_Destination.y)
		{
			m_pStarData->m_bDestroyEvent = true;
		}

		//--- �������Ԃ����炷 ---
		m_pStarData->m_nLifeTime--;
		if (m_pStarData->m_nLifeTime <= 0){
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


	//if (GetKeyboardTrigger(DIK_2)){
	//	m_pStarData = m_pRoot;			// �擪�ɖ߂�
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (!m_pStarData->m_bUse)	// ��������
	//		continue;
	//		m_pStarData->m_nDestroyStarNum--;
	//		m_pStarData = m_pRoot;		// �擪�ɖ߂�
	//		break;
	//	}
	//}
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
			//m_pStarData->m_Collision.Draw();
		}
	}

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �f�o�b�O�v�����g
	PrintDebugProc("��������覐΄�������\n");
	PrintDebugProc("���݂̐� %d/%d\n", m_nCurrentNum, m_nMaxNum);
	//PrintDebugProc("2�L�[�Ŕj�󐔍X�V");
	//PrintDebugProc("�j�� %d/%d\n", m_pStarData->m_nDestroyStarNum, DESTROY_STAR);
	//PrintDebugProc("�������� %d/%d\n", m_pStarData->m_ExplosionFrame, EXPLOSION_FRAME);
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


		// �����グ�Ă���
		if (m_pStarData->m_sprite.GetVtxColorA()+5.0f <= 255){
			m_pStarData->m_sprite.SetVtxColorA(m_pStarData->m_sprite.GetVtxColorA() + 5.0f);
		}
		else{
			m_pStarData->m_sprite.SetVtxColorA(255);
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
void cSpaceRock::Destroy(){

	// �폜�C�x���g�̊J�n
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);
		m_pStarData->m_bDraw = false;

		
		//****** �����ɉ��o�Ƃ������������Ă��� *************

		// �����t���[���̍X�V
		m_pStarData->m_ExplosionFrame--;


		// SE�Đ�
		if (!m_pStarData->m_bExplosion)
		PlaySound(SOUND_LABEL_SE_SPACE_ROCK_BOMB);

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


		if (m_pStarData->m_bCaptured){
			m_pGageData->GageChange(-50);
		}


		// ���̐ݒ�
		m_pStarData->m_sprite.SetVtxColorA(0);

		// ���W�̌���
		D3DXVECTOR2 CreateRamdomPos;
		int RamdomNum = CRandam::RandamRenge(1, CREATE_PATTERN + 1);
		switch (RamdomNum)
		{
		case 1:
			CreateRamdomPos = CREATE_POS_01;
			break;
		case CREATE_PATTERN:
			CreateRamdomPos = CREATE_POS_02;
			break;
		default:
			break;
		}
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);

		m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));
		m_pStarData->m_nDestroyStarNum = DESTROY_STAR;					// �j�󐔂�ݒ�
		m_pStarData->m_ExplosionAnim.SetCurrentAnimPattern(0);
		m_pStarData->m_ExplosionFrame = EXPLOSION_FRAME;				// ��������
		m_pStarData->m_bExplosion = false;								// �J�n�p�t���O
		m_pStarData->m_bCaptured = false;
		m_pStarData->m_nLifeTime = LIFE_TIME;							// �������Ԃ̎w��


		// �I�������瑦���X�|�[������
		m_pStarData->m_bRespawnEvent = true;

		// �t���O�I��
		m_pStarData->m_bExplosion = false;

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

			// ���̐ݒ�
			m_pStarData->m_sprite.SetVtxColorA(0);

			// ���W�̌���
			D3DXVECTOR2 CreateRamdomPos;
			int RamdomNum = CRandam::RandamRenge(1, CREATE_PATTERN + 1);
			switch (RamdomNum)
			{
			case 1:
				CreateRamdomPos = CREATE_POS_01;
				break;
			case CREATE_PATTERN:
				CreateRamdomPos = CREATE_POS_02;
				break;
			default:
				break;
			}
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);

			m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));
			m_pStarData->m_nDestroyStarNum = DESTROY_STAR;					// �j�󐔂�ݒ�
			m_pStarData->m_ExplosionAnim.SetCurrentAnimPattern(0);
			m_pStarData->m_ExplosionFrame = EXPLOSION_FRAME;				// ��������
			m_pStarData->m_bExplosion = false;								// �J�n�p�t���O
			m_pStarData->m_bCaptured = false;
			m_pStarData->m_nLifeTime = LIFE_TIME;							// �������Ԃ̎w��

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
void cSpaceRock::SetNetData(cNet* data){
	m_pNetData = data;
}

void cSpaceRock::OnCollidToNet(int count){


	// �擪���牽�Ԗڂ�
	m_pStarData = m_pRoot;
	m_pStarData += count;

	m_pStarData->m_bCaptured = true;


	// Vector�m�F�p
	m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_VecStarToDest * 5);

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

//=======================================================================================
//
//		�Q�[�W�Ƃ̏���
//
//=======================================================================================
//---- �Q�[�W�̏����擾 -----
void cSpaceRock::SetGageData(cGage* data)
{
	m_pGageData = data;
}