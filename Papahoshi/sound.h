//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "Direct3D.h"
#include"xaudio2.h"

#define USE_SOUND

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,		// �^�C�g��
	SOUND_LABEL_BGM_GAME,			// �Q�[����
	SOUND_LABEL_BGM_GAME_FEVER,		// �t�B�[�o�[�^�C��

	SOUND_LABEL_SE_NET_SHOOT,		// �ԓ���
	SOUND_LABEL_SE_NET_PULL,		// �Ԉ���
	SOUND_LABEL_SE_NET_GAGE,		// �Q�[�W

	SOUND_LABEL_SE_STAR_GET,		// ���擾
	SOUND_LABEL_SE_STREAM_METEOR,	// ����闬��
	SOUND_LABEL_SE_SPACE_ROCK_BOMB,	// 覐Δ���
	SOUND_LABEL_SE_VACUME_BLACK_HOLE,	// �u���b�N�z�[���z�����݂���

<<<<<<< HEAD
	SOUND_LABEL_SE_TITLE_SHIP,	// �D�J
	SOUND_LABEL_GINGLE_RESULT_MIN,	// ���U���g�W���O��(臒l�ȉ�)
	SOUND_LABEL_GINGLE_RESULT_MAX,	// ���U���g�W���O��(臒l�ȏ�)
	SOUND_LABEL_SE_RESULT_COUNTUP,	// ���U���g�J�E���g�A�b�v��
	SOUND_LABEL_SE_RESULT_MOVE_STAR,// ���U���g��������
=======

	SOUND_LABEL_SE_TITLE_SHIP,	// �D�J
	SOUND_LABEL_GINGLE_RESULT_MIN,	// ���U���g�W���O��(臒l�ȉ�)
	SOUND_LABEL_GINGLE_RESULT_MAX,	// ���U���g�W���O��(臒l�ȏ�)
>>>>>>> cd4e7a85e4f51a22bb84fbae3c4849fb832b50a4

	SOUND_LABEL_VOICE_3,	//�A�i�E���X�u3�v
	SOUND_LABEL_VOICE_2,	//�A�i�E���X�u2�v
	SOUND_LABEL_VOICE_1,	//�A�i�E���X�u1�v
	SOUND_LABEL_VOICE_START,	//�A�i�E���X�uSTART�v
<<<<<<< HEAD
=======

>>>>>>> cd4e7a85e4f51a22bb84fbae3c4849fb832b50a4
	SOUND_LABEL_MAX,
} SOUND_LABEL;


//----------------------------------------------------------
// ���ʒ���
// 1.0�ő�
// 0.0�~���[�g
//----------------------------------------------------------
#define TITLE_BGM_VOLUME	(1.0f)
#define GAME_BGM_VOLUME	(1.0f)
#define FEVER_BGM_VOLUME	(1.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
void SetVolume(float fVolume, SOUND_LABEL label);	//�{�����[������

#endif
