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

//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cTimer::cTimer(){


	// �^�C�}�[����\��ݒ�(1ms�P�ʁj
	timeBeginPeriod(1);

	m_CurrentTime = 0;
	m_StartTime = timeGetTime();
	m_TimerStart = true;

	m_nFrameRate = FRAME_RATE;
	m_nCountFrame = 0;
	m_nFrameTime = 0;

	m_fCountDownFrame = 0;




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
	m_fCountDownFrame++;


	if (m_fCountDownFrame*m_nFrameRate / 1000.0f >= 1.0f){	//1s��������J�E���g�_�E��

		m_fCountDownFrame = 0;
		m_fCountDownTime--;

	}

	// �t���[���������ԂɊ��Z
	m_nFrameTime = m_nCountFrame*m_nFrameRate / 1000.0f;	// /s





	if (m_StartTime)
		m_CurrentTime = timeGetTime() - m_StartTime;

	PrintDebugProc("Time(timeGetTime) %f\n", m_CurrentTime / 1000.0f);
	PrintDebugProc("Time(frame) %f\n", m_nFrameTime);
	PrintDebugProc("CountDown %f\n", m_fCountDownTime);
}
