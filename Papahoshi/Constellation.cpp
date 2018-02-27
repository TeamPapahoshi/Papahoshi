//======================================================================
//	���Q
//	
//	�T�v�Q�F
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
#include "Constellation.h"
#include "Input.h"
#include "GameUI.h"


//-----------------------------
// �}�N����`
//-----------------------------
#define CENTER_STAR_SIZE			(D3DXVECTOR2(150,150))
#define OTHER_STAR_SIZE				(D3DXVECTOR2(30,30))
#define MAX_CONSTELLATION_NUM		(10)
#define RESPAWN_FREAM				(10)

//	�����ʒu
#define CREATE_PATTERN		(2)
//#define CREATE_POS_01		(D3DXVECTOR2(GAME_SCREEN_LEFT+DEFAULT_STAR_SIZE/2.0f,100))
//#define CREATE_POS_02		(D3DXVECTOR2(GAME_SCREEN_RIGHT-DEFAULT_STAR_SIZE/2.0f,100))

#define CREATE_POS_01		(D3DXVECTOR2(SCREEN_CENTER))
#define CREATE_POS_02		(D3DXVECTOR2(SCREEN_CENTER))

//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cConstellation::cConstellation(){

	// �����̏�����
	CRandam::InitRand();

	// �g�p�����i�[�t�@�C������ǂݍ��ނ��ǂ����ԕύX��������
	m_nMaxNum = MAX_CONSTELLATION_NUM;

	// ���I�C���X�^���X
	m_pStarData = new cConstellationData[m_nMaxNum]();//��������
	m_pRoot = m_pStarData;							// �擪�A�h���X�ۑ�

	// ������
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// ��������
		m_pStarData->m_bDraw = true;
		SetCountAndUse(true);
		m_pStarData->m_bCreateEvent = true;

	
		D3DXVECTOR2 CreateCenterPos;

		//--- ���Q�̒��S�̐ݒ� ----
		if (nCountStarNum == 0){
	
			// ���W�̌���
			int RamdomNum = CRandam::RandamRenge(1, CREATE_PATTERN + 1);
			switch (RamdomNum)
			{
			case 1:
				CreateCenterPos = CREATE_POS_01;
				break;
			case CREATE_PATTERN:
				CreateCenterPos = CREATE_POS_02;
				break;
			default:
				break;
			}
			m_pStarData->m_sprite.SetPos(CreateCenterPos);

			// �T�C�Y�̐ݒ�
			m_pStarData->m_sprite.SetSize(CENTER_STAR_SIZE);

			// �e�N�X�`���̐ݒ�
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_PLANET03));

			// �A�j���[�V�����̐ݒ�
			m_pStarData->m_sprite.SetTexPatternDevide(10, 2);
			m_pStarData->m_sprite.SetIntervalChangePattern(7);
			m_pStarData->m_sprite.SetAnimationFlag(true);

			// �����蔻��
			m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
			// �����蔻��
			m_pStarData->m_Collision.SetCircleCollider(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x, m_pStarData->m_sprite.GetPos().y), CENTER_STAR_SIZE.x / 2.0f);

		}


		//--- ���Q�̎���̐��̐ݒ� ----
		else{

			// ���Q�̎���ɐ��𐶐�
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = (float)CRandam::RandamRenge(CreateCenterPos.x - 200, CreateCenterPos.x + 200);
			CreateRamdomPos.y = (float)CRandam::RandamRenge(CreateCenterPos.y - 200, CreateCenterPos.y + 200);
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);
			// ���̐F�̌���
			m_pStarData->m_nStarColorNum = CRandam::RandamRenge(0, 3);
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
			default:
				break;
			}
			// �A�j���[�V�����̐ݒ�
			m_pStarData->m_sprite.SetAnimationFlag(true);
		


			// �T�C�Y�̐ݒ�
			m_pStarData->m_sprite.SetSize(OTHER_STAR_SIZE);

			// �~�O���̐ݒ�
			m_pStarData->m_CircleMoveData.SetCenter(CreateCenterPos);	// �~�O���̒��S�𐯌Q��̒��S�ɃZ�b�g
			//m_pStarData->m_CircleMoveData.SetRadius(D3DXVECTOR2((float)CRandam::RandamRenge(100, 200), (float)CRandam::RandamRenge(100,200)));
			m_pStarData->m_CircleMoveData.SetRadius(D3DXVECTOR2(100, 100));
			m_pStarData->m_CircleMoveData.SetSpped(0.01f);
			m_pStarData->m_CircleMoveData.SetRad((float)CRandam::RandamRenge(0, 2*D3DX_PI ));

			// �����蔻��
			m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
			// �����蔻��
			m_pStarData->m_Collision.SetCircleCollider(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x, m_pStarData->m_sprite.GetPos().y), OTHER_STAR_SIZE.x / 2.0f);

		}
	}
}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cConstellation::~cConstellation(){

	m_pStarData = m_pRoot;
	delete[]  m_pStarData;
	m_pStarData = NULL;

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cConstellation::Update(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;


	// �X�V
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){


		// �g���ĂȂ��͔̂�΂�
		if (!m_pStarData->m_bUse)
			continue;


		//----- ���S�̂� ---------
		if (nCountStarNum == 0){

			// �����蔻��
			m_pStarData->m_Collision.SetCircleCollider(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x, m_pStarData->m_sprite.GetPos().y), CENTER_STAR_SIZE.x / 2.0f);
		}


		//---- ���S�ȊO ----------
		if (nCountStarNum != 0){

			// �~�O���̐ݒ�
			m_pStarData->m_sprite.SetPos(m_pStarData->m_CircleMoveData.GetMove());

			// �����蔻��
			m_pStarData->m_Collision.SetCircleCollider(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x, m_pStarData->m_sprite.GetPos().y) , OTHER_STAR_SIZE.x / 2.0f);
		}


		//-----  ���� ------------
		// �A�j���[�V�����̍X�V
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

		else if (m_pStarData->m_bDestroyEvent){
			Destroy();
		}
		if (m_pStarData->m_bRespawnEvent){
			Respawn();
		}
	}



	// �C�x���g�̋N��
	// �f�o�b�O�L�[
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
void cConstellation::Draw(){


	//---- 0�Ԗ�(���Q�̒��S����ԑO�ɕ`�悷�邽�߂̏���) --------------------------------------------
	// �擪+1
	m_pStarData = m_pRoot+1;

	// �`��
	for (int nCountStarNum = 1; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bDraw)
			continue;

		m_pStarData->m_sprite.Draw();
		m_pStarData->m_Collision.Draw();
	}

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	if (m_pStarData->m_bDraw){
		m_pStarData->m_sprite.Draw();
		m_pStarData->m_Collision.Draw();
	}
	
	//----------------------------------------------------------------------------------------------

	// �f�o�b�O�v�����g
	/*PrintDebugProc("���������T���v��������\n");
	PrintDebugProc("���݂̐� %d/%d\n", m_nCurrentNum, m_nMaxNum);
	PrintDebugProc("K�L�[�Ő���\n");
	PrintDebugProc("D�L�[�ō폜\n");
	PrintDebugProc("����������������������\n");*/
}


//=======================================================================================
//
//		����
//
//=======================================================================================
void cConstellation::Create(){

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
void cConstellation::Destroy(){

	// �����C�x���g�̊J�n
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);

		// �����ȊO�͓��������ɂȂ�͂�������R�s�؂ł����͂�
		//****** �����ɉ��o�Ƃ������������Ă��� **********






		//****************************************************


		// ���o�����������I���t���O�𗧂Ă�->if(EffectEnd()){m_pStar->....}
		//m_pStarData->m_bCreateEnd = true;

		// ����͂�����x��]������I��->if(EffectEnd()){m_pStar->....}

			m_pStarData->m_bDestroyEnd = true;
			//m_pStarData->m_bUse = false;

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
void cConstellation::Respawn(){


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