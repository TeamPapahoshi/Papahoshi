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
#include "Sprite.h"

//-------------------------------
// �萔��`
//-------------------------------
#define TIME_SEC_PLACE	(2)	//�b�̈ʂ̐�
#define LIMIT_TIME		(60)

class cTimer{

public:
	cTimer();
	~cTimer();

	void Init(){
	}
	void UnInit(){

	}

	// �J�E���g�_�E���J�n
	void StartCountDown(float Time){
		m_fCountDownTime = Time;
		m_bCountDown = true;
	}
	void ResetCountDown(float Time){
		m_fCountDownTime;
		m_bCountDown = false;
	}

	float GetTime(){
		return m_fCountDownTime;
	}

	void Draw();


	void Update();

private:

	// ���ڎ��Ԃ��͂�����@
	DWORD	m_CurrentTime;	// ���ݎ���
	DWORD	m_StartTime;	// �J�n����

	// �t���[�������玞�ԂɊ��Z
	float		m_nFrameRate;		// ���̃Q�[���̃t���[�����[�g
	float		m_nCountFrame;		// �t���[���𐔂���
	float		m_nFrameTime;		// ���ԂɊ��Z

	bool		m_bCountDown;		// �J�E���g�_�E���J�n�t���O
	float		m_fCountDownFrame;	// �J�E���g�_�E���p�t���[��
	float		m_fCountDownTime;	// �J�E���g�_�E���p����

	//�`��p�X�v���C�g
	cSpriteParam	m_aSecSprite[TIME_SEC_PLACE];

};


#endif //!___TIMER_H___