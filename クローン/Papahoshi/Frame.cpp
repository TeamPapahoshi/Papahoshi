//======================================================================
//	Frame
//	
//	�T�v�Q�F�t���[���Ǘ��֘A
//	����ҁF�Ԉ�@�Y��
//	
//======================================================================

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "Frame.h"


//----- timeGetTime()�Ȃǁ@------------
#include <mmsystem.h>
#pragma comment( lib, "winmm.lib" )	// Windows�}���`���f�B�A���C�u����


#ifdef _FPS_MEASURE_
#include "DebugText.h"
#endif


//------------------------------
// �}�N����` 
//------------------------------
#define FRAME_RATE		(1000 / 60)		// �t���[�����[�g


//------------------------------
// �O���[�o���ϐ��錾 
//------------------------------
static DWORD g_dwExecLastTime;		//�O���s����
static DWORD g_dwCurrentTime = 0;	//������


//------------------------------
//FPS�v����
//------------------------------
#ifdef _FPS_MEASURE_

// �}�N����`
#define FPS_MEASURE_RATE	(500)			// FPS�v�����[�g

// �O���[�o���ϐ��錾 
static DWORD		g_dwFPSLastTime;		// FPS�O�v������
static DWORD		g_dwFPSFrameCount = 0;	// �t���[�����J�E���g
static int			g_nCurrentFPS = 0;		// ���݂�FPS

// �v���g�^�C�v�錾
HRESULT InitFPSMeasure(void);	//FPS�v��������
void	UnInitFPSMeasure(void);	//FPS�v���I������
void	MeasureFPS(void);		//FPS���v��
void	UpdateFPSText(void);	//FPS�\�����X�V

#endif





//=======================================================================================
//
//		�t���[���Ǘ�������
//
//	[�߂�l]	S_OK �F ����������		E_FAIL : ���������s
//
//=======================================================================================
HRESULT InitFrame(void){

	//------------------------------
	//������
	//------------------------------
	// �^�C�}�[����\��ݒ�(1ms�P�ʁj
	timeBeginPeriod(1);
	// �ŏI���s�����̏������i�������Ɂj
	g_dwExecLastTime = timeGetTime();


#ifdef _FPS_MEASURE_
	if (FAILED(InitFPSMeasure()))	//FPS�v��������
		return E_FAIL;
#endif



	return S_OK;
}


//=======================================================================================
//
//		�t���[���Ǘ��I������
//
//=======================================================================================
void UnInitFrame(void) {

	// ����\�����ɖ߂�
	timeEndPeriod(1);

#ifdef _FPS_MEASURE_
	UnInitFPSMeasure();	// FPS�v���I������
#endif

}


//=======================================================================================
//
//		�t���[���X�V�L���̊m�F
//
//	[�߂�l]	TRUE : �X�V����		FALSE�@�F�@�X�V�Ȃ�
//
//=======================================================================================
BOOL CheckFrameUpdate(void) {

	// ���������X�V
	g_dwCurrentTime = timeGetTime();


#ifdef _FPS_MEASURE_
	MeasureFPS();	// FPS���v��
#endif

	// �t���[���X�V�L��
	if (g_dwCurrentTime - g_dwExecLastTime >= FRAME_RATE) {
		g_dwExecLastTime = g_dwCurrentTime;

#ifdef _FPS_MEASURE_
		UpdateFPSText();
#endif

		return TRUE;
	}

	return FALSE;
}



//=======================================================================================
//
//		timeGetTime()
////
//=======================================================================================
DWORD Frame_timeGetTime(void){

	return timeGetTime();
}





//---------------------------------------------------------- FPS�v���� ----------------------------------------------------------
#ifdef _FPS_MEASURE_

//---------------------------------------------------------------------------------------
//
//		FPS�v��������
//
//	[�߂�l]	S_OK �F ����������		E_FAIL : ���������s
//
//---------------------------------------------------------------------------------------
HRESULT InitFPSMeasure(void){
	// FPS�J�E���g�������������ɐݒ�
	g_dwFPSLastTime = g_dwExecLastTime;
	// �J�E���g��0�N���A
	g_dwFPSFrameCount = 0;

	return S_OK;
}



//---------------------------------------------------------------------------------------
//
//		FPS�v���I������
//
//---------------------------------------------------------------------------------------
void	UnInitFPSMeasure(void){
}



//---------------------------------------------------------------------------------------
//
//		FPS���v��
//
//---------------------------------------------------------------------------------------
void	MeasureFPS(void){
	if (g_dwCurrentTime - g_dwFPSLastTime >= FPS_MEASURE_RATE)
	{

		// FPS�v��
		g_nCurrentFPS = (g_dwFPSFrameCount * 1000) / (g_dwCurrentTime - g_dwFPSLastTime);
		// FPS���肵��������ۑ�
		g_dwFPSLastTime = g_dwCurrentTime;
		// �J�E���g���N���A
		g_dwFPSFrameCount = 0;
	}
	if (g_dwCurrentTime - g_dwExecLastTime >= FRAME_RATE) {
		g_dwFPSFrameCount++;
	}
}



//=======================================================================================
//
//		FPS��`��
//
//=======================================================================================
void UpdateFPSText(void) {

	char aStr[256];
	wsprintf(aStr, "FPS %d\n", g_nCurrentFPS);
	DebugTextAdd(aStr);
}
#endif


