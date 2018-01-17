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
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_SE_DECIDE,		// ���艹
	SOUND_LABEL_SE_CANCEL,		// �L�����Z����
	SOUND_LABEL_SE_SELECT,		// �I����
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_LASER,		// ���[�U�[���ˉ�
	SOUND_LABEL_SE_LOCKON,		// ���b�N�I����
	SOUND_LABEL_SE_HIT,			// �q�b�g��
	SOUND_LABEL_SE_GUARD,		// �K�[�h��
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_JUMP,		// �W�����v��
	SOUND_LABEL_MAX,

} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
