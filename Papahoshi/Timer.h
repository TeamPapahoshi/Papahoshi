//======================================================================
//	Timer
//	
//	�T�v�Q�F�^�C�}�[�̊Ǘ�
//	����ҁF���� ��
//	
//======================================================================
#ifndef ___TIMER_H___
#define ___TIMER_H___

#include <Windows.h>
#include "Common.h"
#include "debugproc.h"
#include  "Frame.h"


class cTimer{

public:
	cTimer();
	~cTimer();

	void Start(){
		m_TimerStart = true;
		m_StartTime = timeGetTime();
	}

	void Init(){


	}
	void UnInit(){

	}

	void StartCountDown(int Time){

		// ���Ԃ��t���[�����Ɋ��Z
		//m_fCountDownFrame = Time*1000.0f / m_nFrameRate;

		m_fCountDownTime = Time;

	

	}

	void Update();

private:

	// ���ڎ��Ԃ��͂�����@
	DWORD	m_CurrentTime;	// ���ݎ���
	DWORD	m_StartTime;	// �J�n����
	bool	m_TimerStart;

	// �t���[�������玞�ԂɊ��Z
	float		m_nFrameRate;		// ���̃Q�[���̃t���[�����[�g
	float		m_nCountFrame;		// �t���[���𐔂���
	float		m_nFrameTime;		// ���ԂɊ��Z
	float		m_fCountDownFrame;	// �J�E���g�_�E���p�t���[��
	float		m_fCountDownTime;	// �J�E���g�_�E���p����



};


#endif //!___TIMER_H___