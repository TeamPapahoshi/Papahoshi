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
	SOUND_LABEL_BGM_GAME,			//�Q�[����
	SOUND_LABEL_BGM_GAME_FEVER,		//�t�B�[�o�[�^�C��

	SOUND_LABEL_SE_NET_SHOOT,		//�ԓ���
	SOUND_LABEL_SE_NET_PULL,		//�Ԉ���
	SOUND_LABEL_SE_NET_GAGE,		//�Q�[�W
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
