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

#define RESPAWN_FREAM	(20)

//=======================================================================================
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
	m_pStarData = new cBlackHoleData[m_nMaxNum]();
	m_pRoot		= m_pStarData;							// �擪�A�h���X�ۑ�



	// ������
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		


		m_pStarData->m_sprite.SetVtxColorA(10);
		m_pStarData->rad = 0;

		// ���W�̌���
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// ���


	}




}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cBlackHole::~cBlackHole(){

	m_pStarData = m_pRoot;
	delete[]  m_pStarData;
	m_pStarData = NULL;

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cBlackHole::Update(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;


	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
		
	

		// �C�x���g���Ăяo����銴��
		if (m_pStarData->m_bCreateEvent){
			Create();
		}






	}

	// �f�o�b�O�L�[
	if (GetKeyboardTrigger(DIK_K)){
		m_pStarData = m_pRoot;	// �擪�ɖ߂�
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

			if (m_pStarData->m_bUse)
				continue;

			m_pStarData->m_bCreateEvent = true;
			break;
		}
	}



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
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++,m_pStarData++){

		if (!m_pStarData->m_bUse)
			continue;

			m_pStarData->m_sprite.Draw();
	}

	PrintDebugProc("K�L�[�Ő�����\n");
}


//=======================================================================================
//
//		����
//
//=======================================================================================
void cBlackHole::Create(){
	
	// �����C�x���g�̊J�n
	if(!m_pStarData->m_bCreateEnd){



		// �����ȊO�͓��������ɂȂ�͂�������R�s�؂ł����͂�
		//****** �����ɉ��o�Ƃ����������������Ă��� **********
		m_pStarData->m_bUse = true;




		// ��]�Ă��Ƃ�
		m_pStarData->rad += 0.01f;
		m_pStarData->m_sprite.SetRad(m_pStarData->m_sprite.GetRad() + m_pStarData->rad);

		//****************************************************



		// ���o����������琶���I���t���O�𗧂Ă�
		//m_pStarData->m_bCreateEnd = true;

		// ����͂�����x��]������I��
		if (m_pStarData->rad > 1.0f){
			m_pStarData->m_bCreateEnd = true;

		}

	}


	// �����I���t���O����������C�x���g�t���O���I�t�ɂ��ďI��
	if (m_pStarData->m_bCreateEnd){
		m_pStarData->m_bCreateEvent = false;
		return;
	}
}
