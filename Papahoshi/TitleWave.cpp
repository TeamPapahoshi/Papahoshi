//======================================================================
//	TitleWave.cpp
//	
//	�T�v�Q�F�^�C�g���I�u�W�F�N�g�E�g
//	����ҁF���� ����
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>		//HRESULT��

#include "debugproc.h"		//printdebug
#include "TitleWave.h"
#include "Texture.h"


//-----------------------------
//�}�N����`
//-----------------------------
#define WAVE_POS_X (-WAVE_SIZE_X / 2 - 10)
#define WAVE_POS_Y (SCREEN_HEIGHT - WAVE_SIZE_Y / 2)

#define WAVE_MOVE_X (1.0f)

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------

//-----------------------------
//�O���[�o��
//-----------------------------


//=======================================================================================
//
//		�C���N�������g
//
//=======================================================================================
cTitleWave::cTitleWave(){

}

//=======================================================================================
//
//		�f�N�������g
//
//=======================================================================================
cTitleWave::~cTitleWave(){

}

//=======================================================================================
//
//		������
//
//=======================================================================================
void cTitleWave::Init(){
	//�|�C���^�̐ݒ�
	cSpriteParam* pTitleWave = m_TitleWave;

	//����������
	for (int TitleWaveloop = 0; TitleWaveloop < MAX_WAVE; TitleWaveloop++, pTitleWave++)
	{
		pTitleWave->SetPos(D3DXVECTOR2(WAVE_POS_X + WAVE_SIZE_X * TitleWaveloop, WAVE_POS_Y));
		pTitleWave->SetSize(D3DXVECTOR2(WAVE_SIZE_X, WAVE_SIZE_Y));
		pTitleWave->SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_WAVE));
		pTitleWave->SetMoveX(WAVE_MOVE_X);
	}
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cTitleWave::UnInit(){

	//�|�C���^�̐ݒ�
	cSpriteParam* pTitleWave = m_TitleWave;
}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cTitleWave::Update(){

	//�|�C���^�̐ݒ�
	cSpriteParam* pTitleWave = m_TitleWave;

	//�X�V����
	for (int TitleWaveloop = 0; TitleWaveloop < MAX_WAVE; TitleWaveloop++, pTitleWave++)
	{
		//���W�̍X�V
		pTitleWave->SetPosX(pTitleWave->GetPosX() + pTitleWave->GetMoveX());

		//��ʉE�ɏo���ꍇ
		if (pTitleWave->GetPosX() > SCREEN_WIDTH - WAVE_POS_X)
		{
			//��ʍ��ɍĐݒu
			pTitleWave->SetPosX(WAVE_POS_X);
		}
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cTitleWave::Draw(){

	//�|�C���^�̐ݒ�
	cSpriteParam* pTitleWave = m_TitleWave;

	//�`�揈��
	for (int TitleWaveloop = 0; TitleWaveloop < MAX_WAVE; TitleWaveloop++, pTitleWave++)
	{
		pTitleWave->Draw();
	}
}