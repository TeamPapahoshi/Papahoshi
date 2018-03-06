//======================================================================
//	SampleStar
//	
//	�T�v�Q�F�R�s�[�p���@�@���̂܂܃R�s�[���Ďg����w�b�_�[�ƈꏏ��
//	����ҁF�����@��				�g�݂Ȃ���������
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
#include "SampleStar.h"
#include "Input.h"


//-----------------------------
// �}�N����`
//-----------------------------
#define DEFAULT_STAR_SIZE			(100)
#define MAX_SAMPLE_STAR_NUM			(50)

//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cSampleStar::cSampleStar(){

	// �����̏�����
	CRandam::InitRand();

	// �g�p�����i�[�t�@�C������ǂݍ��ނ��ǂ����ԕύX��������
	m_nMaxNum = MAX_SAMPLE_STAR_NUM;

	// ���I�C���X�^���X
	m_pStarData = new cSampleStarData[m_nMaxNum]();//��������
	m_pRoot = m_pStarData;							// �擪�A�h���X�ۑ�



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
cSampleStar::~cSampleStar(){

	m_pStarData = m_pRoot;
	delete[]  m_pStarData;
	m_pStarData = NULL;

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSampleStar::Update(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �C�x���g�i�[���[�v�H
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// �C�x���g���Ăяo����銴��
		if (m_pStarData->m_bCreateEvent){
			Create();
		}

		else if (m_pStarData->m_bDestroyEvent){
			Destroy();
		}
	}



	//// �f�o�b�O�L�[
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
void cSampleStar::Draw(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �`��
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bDraw)
			continue;

		m_pStarData->m_sprite.Draw();
	}


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
void cSampleStar::Create(){

	// �����C�x���g�̊J�n
	if (!m_pStarData->m_bCreateEnd){



		// �����ȊO�͓��������ɂȂ�͂�������R�s�؂ł����͂�
		//****** �����ɉ��o�Ƃ����������������Ă��� **********
		//m_pStarData->m_bUse = true;->����ł��ł��邯�Ǎ���͐����������Ă�����������
		m_pStarData->m_bDraw = true;

	




		// ��]�Ă��Ƃ�
		m_pStarData->rad += 0.01f;
		m_pStarData->m_sprite.SetRad(m_pStarData->m_sprite.GetRad() + m_pStarData->rad);

		//****************************************************



		// ���o����������琶���I���t���O�𗧂Ă�->if(EffectEnd()){m_pStar->....}
		//m_pStarData->m_bCreateEnd = true;

		// ����͂�����x��]������I��->if(EffectEnd()){m_pStar->....}
		if (m_pStarData->rad > 1.0f){
			m_pStarData->m_bCreateEnd = true;

		}

	}


	// �����I���t���O���������烊�Z�b�g���ďI��
	if (m_pStarData->m_bCreateEnd){

		//	���Z�b�g
		m_pStarData->m_bCreateEnd = false;
		m_pStarData->rad = 0;					// �����Ƃ��j�b�g�ƃA�����j�b�g�ɂ����̂���Ƃ�������

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
void cSampleStar::Destroy(){

	// �����C�x���g�̊J�n
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);

		// �����ȊO�͓��������ɂȂ�͂�������R�s�؂ł����͂�
		//****** �����ɉ��o�Ƃ������������Ă��� **********
	




		// ��]�Ă��Ƃ�
		m_pStarData->rad += 0.01f;
		m_pStarData->m_sprite.SetRad(m_pStarData->m_sprite.GetRad() + m_pStarData->rad);

		//****************************************************


		// ���o�����������I���t���O�𗧂Ă�->if(EffectEnd()){m_pStar->....}
		//m_pStarData->m_bCreateEnd = true;

		// ����͂�����x��]������I��->if(EffectEnd()){m_pStar->....}
		if (m_pStarData->rad > 1.0f){
			m_pStarData->m_bDestroyEnd = true;
			//m_pStarData->m_bUse = false;
			

		}

	}

	// �����I���t���O���������烊�Z�b�g���ďI��
	if (m_pStarData->m_bDestroyEnd){

		//	���Z�b�g
		m_pStarData->m_bDestroyEnd = false;
		m_pStarData->rad = 0;
		m_pStarData->m_bDraw = false;
		m_pStarData->m_bDestroyEvent = false;
		return;
	}
}