//======================================================================
//	Timer
//	
//	�T�v�Q�FTimer�̊Ǘ�
//	����ҁF�����@��
//	
//======================================================================
#include "Timer.h"
#include "Frame.h"
#include "debugproc.h"
#include "Input.h"
#include "Texture.h"

//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cTimer::cTimer(){


	//--- ���ۂɎ��Ԃ𑪂� ----
	timeBeginPeriod(1);	// �^�C�}�[����\��ݒ�(1ms�P�ʁj
	m_CurrentTime = 0;
	m_StartTime = timeGetTime();


	//--- �t���[�������玞�Ԃ����߂� ----
	m_nFrameRate = FRAME_RATE;
	m_nCountFrame = 0;
	m_nFrameTime = 0;
	m_fCountDownFrame = 0;
	m_fCountDownTime = 0;
	m_bCountDown = false;

	//---- �e�N�X�`�������� ----
	D3DXVECTOR2 pos, size;
	pos = D3DXVECTOR2(150.0f, 230.0f);
	size = D3DXVECTOR2(55.0f, 55.0f);
	for (int i = TIME_SEC_PLACE - 1; i >= 0; i--){
		m_aSecSprite[i].SetPos(D3DXVECTOR2(pos.x + (size.x * 0.8f) * i, pos.y));
		m_aSecSprite[i].SetSize(size);
	}

}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cTimer::~cTimer(){

}


//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cTimer::Update(){


	// �t���[���𐔂���
	m_nCountFrame++;


	// �J�E���g�_�E������
	if (m_bCountDown){

		m_fCountDownFrame++;

		if (m_fCountDownFrame*m_nFrameRate / 1000.0f >= 1.0f){	//1s��������J�E���g�_�E��

			m_fCountDownFrame = 0;
			m_fCountDownTime--;

		}

		if (m_fCountDownTime <= 0)
			m_bCountDown = false;
	}

	// �t���[���������ԂɊ��Z
	m_nFrameTime = m_nCountFrame*m_nFrameRate / 1000.0f;	// 


	// ���ۂ̎���
	m_CurrentTime = timeGetTime() - m_StartTime;

	PrintDebugProc("Time(timeGetTime) %f\n", m_CurrentTime / 1000.0f);
	PrintDebugProc("Time(frame) %f\n", m_nFrameTime);
	PrintDebugProc("CountDown %f\n", m_fCountDownTime);
	PrintDebugProc("S�L�[�ŃJ�E���g�_�E��\n", m_fCountDownTime);
}

//===================================================
//
// �`��֐�
//
//===================================================
void cTimer::Draw(){

	int work1, work2;
	work2 = (int)m_fCountDownTime;

	for (int i = TIME_SEC_PLACE - 1; i >= 0; i--)
	{
		//----- �X�R�A�̃X�v���C�g�����X�V -----
		work1 = work2 % 10;
		work2 = work2 / 10;
		m_aSecSprite[i].SetTexture(cTextureManeger::GetTextureGame((TEX_GAME)(TEX_GAME_0 + work1)));

		//----- �`�� -----
		m_aSecSprite[i].Draw();
	}

}