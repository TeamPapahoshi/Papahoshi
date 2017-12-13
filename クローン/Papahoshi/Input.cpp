//======================================================================
//	Input
//	
//	�T�v�Q�F���͑��u�֘A�̏���
//	����ҁF�Ԉ�@�Y��
//	
//======================================================================

//------------------------------
//�C���N���[�h�t�@�C��
//------------------------------
#include "Input.h"
#include "Direct3D.h"	//Direct3d�f�o�C�X

// DirectInput8
#pragma comment (lib, "dinput8.lib")


//------------------------------
//�}�N����`
//------------------------------
#define NUM_KEY_MAX			(256)	// �L�[�{�[�h�L�[�̍ő吔

#define MAX_CONTROLER		(1)		//�@�Q�[���p�b�h�ő吔
#define MAX_BUTTON			(32)	//�@�Q�[���p�b�h�{�^���ő吔

#define LIMIT_COUNT_REPEAT	(20)	// ���s�[�g�J�E���g���~�b�^�[


//------------------------------
//�O���[�o���ϐ��錾
//------------------------------
LPDIRECTINPUT8			g_pDInput = NULL;					// DirectInput

LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// ���̓f�o�C�X�i�L�[�{�[�h�j
BYTE					g_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̃v���X���
BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[���
BYTE					g_aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g���
BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X���
int						g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�񐔃J�E���^


LPDIRECTINPUTDEVICE8	g_pDIDevJoyPad[MAX_CONTROLER];			// ���̓f�o�C�X�i�Q�[���p�b�h�j]
static int				g_nNumJoyPadCount = 0;					// ���������Q�[���p�b�h�̐�
DIJOYSTATE				g_aJoyPadState[MAX_CONTROLER];			// �Q�[���p�b�h�̃v���X���
DIJOYSTATE				g_aJoyPadStateTrigger[MAX_CONTROLER];	// �Q�[���p�b�h�̃g���K�[���
DIJOYSTATE				g_aJoyPadStateRepeat[MAX_CONTROLER];	// �Q�[���p�b�h�̃��s�[�g���
DIJOYSTATE				g_aJoyPadStateRelease[MAX_CONTROLER];	// �Q�[���p�b�h�̃����[�X���
int						g_aJoyPadStateRepeatCnt[MAX_CONTROLER];	// �Q�[���p�b�h�̃��s�[�g�񐔃J�E���^


//------------------------------
//�v���g�^�C�v�錾
//------------------------------
// �L�[�{�[�h�̏�����
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
// �L�[�{�[�h�̏I������
void	UnInitKeyboard(void);
// �L�[�{�[�h�̍X�V
void	UpdateKeyboard(void);

// �Q�[���p�b�h�̏�����
HRESULT InitJoyPad(HINSTANCE hInstance, HWND hWnd);
// �Q�[���p�b�h�̏I������
void	UnInitJoyPad(void);
// �Q�[���p�b�h�̍X�V
void	UpdateJoyPad(void);

BOOL CALLBACK EnumJoyPadCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);



//=======================================================================================
//
//		���͑��u������
//
//	[�߂�l]	S_OK �F ����������		E_FAIL : ���������s
//
//=======================================================================================
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd){

	//----------------------------
	//DirectInput�̍쐬
	//---------------------------- 
	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pDInput, NULL);
	if (FAILED(hr)){
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g����邱�Ƃ��ł��܂���ł����B", "�x��", MB_ICONWARNING);
		return hr;
	}

	//----------------------------
	//�L�[�{�[�h�̏�����
	//---------------------------- 
	if (FAILED(InitKeyboard(hInstance, hWnd)))
		return E_FAIL;

	//----------------------------
	//�Q�[���p�b�h�̏�����
	//---------------------------- 
	if (FAILED(InitJoyPad(hInstance, hWnd)))
		return E_FAIL;


	//----------------------------
	//�������I��
	//---------------------------- 
	return S_OK;
}

//---------------------------------------------------------------------------------------
//		�L�[�{�[�h�̏�����
//---------------------------------------------------------------------------------------
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd){

	//----------------------------
	//���[�J���ϐ��錾
	//---------------------------- 
	HRESULT hr;

	//----------------------------
	//���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬
	//---------------------------- 
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
	if (FAILED(hr)){
		MessageBox(hWnd, "�L�[�{�[�h�����o�o���܂���ł����B\n�L�[�{�[�h�ڑ����m�F���Ă��������B", "�L�[�{�[�h�����o", MB_ICONWARNING);
		return E_FAIL;
	}

	//----------------------------
	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	//---------------------------- 
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)){
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x��", MB_ICONWARNING);
		return E_FAIL;
	}

	//----------------------------
	//�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	//---------------------------- 
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr)){
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x��", MB_ICONWARNING);
		return E_FAIL;
	}

	//----------------------------
	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	//---------------------------- 
	g_pDIDevKeyboard->Acquire();


	//----------------------------
	//�L�[�{�[�h�̃��s�[�g�񐔃J�E���^������(�[���N���A�j
	//---------------------------- 
	memset(g_aKeyStateRepeatCnt, 0x00, sizeof(g_aKeyStateRepeatCnt));


	//----------------------------
	//�������I��
	//---------------------------- 
	return S_OK;
}

//---------------------------------------------------------------------------------------
//		�Q�[���p�b�h�̏�����
//---------------------------------------------------------------------------------------
HRESULT InitJoyPad(HINSTANCE hInstance, HWND hWnd){

	//----------------------------
	//���[�J���ϐ��錾
	//---------------------------- 
	HRESULT hr;

	//----------------------------
	//���̓f�o�C�X�i�Q�[���p�b�h�j�̍쐬
	//---------------------------- 
	hr = g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyPadCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(hr)){
		MessageBox(hWnd, "�Q�[���p�b�h�̃f�o�C�X�I�u�W�F�N�g���쐬�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	for (int i = 0; i < MAX_CONTROLER; i++){
		if (g_pDIDevJoyPad[i] == NULL)
			continue;

		hr = g_pDIDevJoyPad[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr)){
			MessageBox(hWnd, "�Q�[���p�b�h�̃f�[�^�t�H�[�}�b�g�̐ݒ肪�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return hr;
		}


		hr = g_pDIDevJoyPad[i]->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�Q�[���p�b�h�̋������x���̐ݒ肪�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return hr;
		}

		g_pDIDevJoyPad[i]->Acquire();
	}

	//----------------------------

	return S_OK;
}

//=======================================================================================
//
//		���͑��u�I������
//
//=======================================================================================
void UnInitInput(void){

	//----------------------------
	//�L�[�{�[�h�̏I������
	//----------------------------
	UnInitKeyboard();


	//----------------------------
	//�Q�[���p�b�h�̏I������
	//----------------------------
	UnInitJoyPad();


	//----------------------------
	//DirectInput�I�u�W�F�N�g�����
	//----------------------------
	if (g_pDInput != NULL){
		g_pDInput->Release();
		g_pDInput = NULL;
	}
}

//---------------------------------------------------------------------------------------
//		�L�[�{�[�h�̏I������
//---------------------------------------------------------------------------------------
void	UnInitKeyboard(void){

	//----------------------------
	// ���̓f�o�C�X�i�L�[�{�[�h�j�����
	//----------------------------
	if (g_pDIDevKeyboard != NULL){
		g_pDIDevKeyboard->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X��������i���͐���I���j
		g_pDIDevKeyboard->Release();
		g_pDIDevKeyboard = NULL;
	}
}

//---------------------------------------------------------------------------------------
//		�Q�[���p�b�h�̏I������
//---------------------------------------------------------------------------------------
void	UnInitJoyPad(void){

	for (int i = 0; i < MAX_CONTROLER; i++){
		if (g_pDIDevJoyPad[i] != NULL){
			g_pDIDevJoyPad[i]->Unacquire();
			g_pDIDevJoyPad[i]->Release();
			g_pDIDevJoyPad[i] = NULL;
		}
	}
}




//=======================================================================================
//
//		���͑��u�X�V
//
//=======================================================================================
void UpdateInput(void){

	//�L�[�{�[�h�̍X�V
	UpdateKeyboard();

	//�Q�[���p�b�h�̍X�V
	UpdateJoyPad();
}


//---------------------------------------------------------------------------------------
//
//		�L�[�{�[�h�̍X�V
//
//---------------------------------------------------------------------------------------
void	UpdateKeyboard(void){

	//----------------------------
	//���[�J���ϐ��錾
	//---------------------------- 
	BYTE aKeyState[NUM_KEY_MAX];

	if (SUCCEEDED(g_pDIDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState))){

		for (int nLoopKey = 0; nLoopKey < NUM_KEY_MAX; nLoopKey++){

			g_aKeyStateTrigger[nLoopKey] = (g_aKeyState[nLoopKey] ^ aKeyState[nLoopKey]) & aKeyState[nLoopKey];
			g_aKeyStateRelease[nLoopKey] = (g_aKeyState[nLoopKey] ^ aKeyState[nLoopKey]) & ~aKeyState[nLoopKey];

			if (aKeyState[nLoopKey]){
				if (g_aKeyStateRepeatCnt[nLoopKey] < LIMIT_COUNT_REPEAT){
					g_aKeyStateRepeatCnt[nLoopKey]++;
					if (g_aKeyStateRepeatCnt[nLoopKey] == 1) {
						g_aKeyStateRepeat[nLoopKey] = aKeyState[nLoopKey];
					}
					else if (g_aKeyStateRepeatCnt[nLoopKey] >= LIMIT_COUNT_REPEAT){
						g_aKeyStateRepeat[nLoopKey] = 0;
						g_aKeyStateRepeatCnt[nLoopKey] = 0;
					}
					else {
						g_aKeyStateRepeat[nLoopKey] = 0;
					}
				}
			}
			else{
				g_aKeyStateRepeat[nLoopKey] = 0;
				g_aKeyStateRepeatCnt[nLoopKey] = 0;
			}
			g_aKeyState[nLoopKey] = aKeyState[nLoopKey];
		}
	}
	else {
		g_pDIDevKeyboard->Acquire();
	}
}

//=======================================================================================
//		�L�[�{�[�h�̃v���X��Ԃ��擾
//=======================================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}


//=======================================================================================
//		�L�[�{�[�h�̃g���K�[��Ԃ��擾
//=======================================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=======================================================================================
//		�L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=======================================================================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//=======================================================================================
//		�L�[�{�[�h�̃����[�X��Ԃ��擾
//=======================================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}




//---------------------------------------------------------------------------------------
//
//		�Q�[���p�b�h�̍X�V
//
//---------------------------------------------------------------------------------------
void	UpdateJoyPad(void){

	HRESULT		hr;
	DWORD		dwPovPrev;
	DIJOYSTATE	joyPadStatePrev;

	for (int nLoopPad = 0; nLoopPad < MAX_CONTROLER; nLoopPad++){
		if (g_pDIDevJoyPad[nLoopPad]){
			
			joyPadStatePrev = g_aJoyPadState[nLoopPad];
			
			hr = g_pDIDevJoyPad[nLoopPad]->Poll();
			if (FAILED(hr)){
				hr = g_pDIDevJoyPad[nLoopPad]->Acquire();
				while (hr == DIERR_INPUTLOST){
					hr = g_pDIDevJoyPad[nLoopPad]->Acquire();
				}
			}

			hr = g_pDIDevJoyPad[nLoopPad]->GetDeviceState(sizeof(DIJOYSTATE), &g_aJoyPadState[nLoopPad]);
			if (SUCCEEDED(hr)){

				for (int nLoopButton = 0; nLoopButton < MAX_BUTTON; nLoopButton++){
#define JS_PRESS	(g_aJoyPadState[nLoopPad].rgbButtons[nLoopButton])
#define JS_PREV		(joyPadStatePrev.rgbButtons[nLoopButton])

					g_aJoyPadStateTrigger[nLoopPad].rgbButtons[nLoopButton] = (JS_PRESS ^ JS_PREV) & JS_PRESS;
					g_aJoyPadStateRelease[nLoopPad].rgbButtons[nLoopButton] = (JS_PRESS ^ JS_PREV) & JS_PREV;
				}

				dwPovPrev = g_aJoyPadState[nLoopPad].rgdwPOV[0];
				switch (dwPovPrev){
				case 0:
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_UP] = TRUE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_RIGHT] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_DOWN] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_LEFT] = FALSE;
					break;
				case 4500:
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_UP] = TRUE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_RIGHT] = TRUE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_DOWN] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_LEFT] = FALSE;
					break;
				case 9000:
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_UP] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_RIGHT] = TRUE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_DOWN] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_LEFT] = FALSE;
					break;
				case 13500:
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_UP] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_RIGHT] = TRUE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_DOWN] = TRUE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_LEFT] = FALSE;
					break;
				case 18000:
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_UP] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_RIGHT] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_DOWN] = TRUE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_LEFT] = FALSE;
					break;
				case 22500:
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_UP] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_RIGHT] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_DOWN] = TRUE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_LEFT] = TRUE;
					break;
				case 27000:
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_UP] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_RIGHT] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_DOWN] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_LEFT] = TRUE;
					break;
				case 31500:
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_UP] = TRUE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_RIGHT] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_DOWN] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_LEFT] = TRUE;
					break;
				default:
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_UP] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_RIGHT] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_DOWN] = FALSE;
					g_aJoyPadState[nLoopPad].rgdwPOV[PAD_ARROW_LEFT] = FALSE;
					break;
				}

				for (int nLoopArrow = 0; nLoopArrow < PAD_ARROW_NUM_MAX; nLoopArrow++){
#define AR_PRESS	(g_aJoyPadState[nLoopPad].rgdwPOV[nLoopArrow])
#define AR_PREV		(joyPadStatePrev.rgdwPOV[nLoopArrow])

					g_aJoyPadStateTrigger[nLoopPad].rgdwPOV[nLoopArrow] = (AR_PRESS ^ AR_PREV) & AR_PRESS;
					g_aJoyPadStateRelease[nLoopPad].rgdwPOV[nLoopArrow] = (AR_PRESS ^ AR_PREV) & AR_PREV;

				}
			}

			if (FAILED(hr)){
				g_pDIDevJoyPad[nLoopPad]->Acquire();
			}
		}
	}
}

//=======================================================================================
//		�Q�[���p�b�h�̃L�[���͏�Ԃ��擾
//=======================================================================================
bool  GetJoyPadButtonPress(const int& nPadNo, const int& nButton){


	if (g_nNumJoyPadCount < nPadNo)
		return false;

	return (g_aJoyPadState[nPadNo].rgbButtons[nButton] & 0x80) ? true : false;
}

//=======================================================================================
//		�Q�[���p�b�h�̃L�[���͏�Ԃ��擾(�g���K�[�j
//=======================================================================================
bool  GetJoyPadButtonTrigger(const int& nPadNo, const int& nButton){


	if (g_nNumJoyPadCount < nPadNo)
		return false;

	return (g_aJoyPadStateTrigger[nPadNo].rgbButtons[nButton] & 0x80) ? true : false;
}


//=======================================================================================
//		�Q�[���p�b�h�̃L�[���͏�Ԃ��擾(�����[�X�j
//=======================================================================================
bool  GetJoyPadButtonRelease(const int& nPadNo, const int& nButton){


	if (g_nNumJoyPadCount < nPadNo)
		return false;

	return (g_aJoyPadStateRelease[nPadNo].rgbButtons[nButton] & 0x80) ? true : false;
}


//=======================================================================================
//		�Q�[���p�b�h�̕����L�[���͏�Ԃ��擾
//=======================================================================================
bool  GetJoyPadArrowPress(const int& nPadNo, const ePadArrowType& arrow){


	if (g_nNumJoyPadCount < nPadNo)
		return false;

	return g_aJoyPadState[nPadNo].rgdwPOV[arrow] ? true : false;
}


//=======================================================================================
//		�Q�[���p�b�h�̕����L�[��Ԃ��擾�i�g���K�[�j
//=======================================================================================
bool  GetJoyPadArrowTrigger(const int& nPadNo, const ePadArrowType& arrow){


	if (g_nNumJoyPadCount < nPadNo)
		return false;

	return g_aJoyPadStateTrigger[nPadNo].rgdwPOV[arrow] ? true : false;
}


//=======================================================================================
//		�Q�[���p�b�h�̕����L�[��Ԃ��擾�i�����[�X�j
//=======================================================================================
bool  GetJoyPadArrowRelease(const int& nPadNo, const ePadArrowType& arrow){


	if (g_nNumJoyPadCount < nPadNo)
		return false;

	return g_aJoyPadStateRelease[nPadNo].rgdwPOV[arrow] ? true : false;
}


//----------------- �L�[�{�[�h�ƃQ�[���p�b�h�̑g�ݍ��킹�@-----------------
bool GetInputButtonPress(int nKey, int nPadNo, const int& nButton){
	return GetKeyboardPress(nKey) || GetJoyPadButtonPress(nPadNo, nButton);
}
bool GetInputButtonTrigger(int nKey, int nPadNo, const int& nButton){
	return GetKeyboardTrigger(nKey) || GetJoyPadButtonTrigger(nPadNo, nButton);
}
bool GetInputButtonRelease(int nKey, int nPadNo, const int& nButton){
	return GetKeyboardRelease(nKey) || GetJoyPadButtonRelease(nPadNo, nButton);
}
bool GetInputArrowPress(int nKey, int nPadNo, const ePadArrowType& arrow){
	return GetKeyboardPress(nKey) || GetJoyPadArrowPress(nPadNo, arrow);
}
bool GetInputArrowTrigger(int nKey, int nPadNo, const ePadArrowType& arrow){
	return GetKeyboardTrigger(nKey) || GetJoyPadArrowTrigger(nPadNo, arrow);
}
bool GetInputArrowRelease(int nKey, int nPadNo, const ePadArrowType& arrow){
	return GetKeyboardRelease(nKey) || GetJoyPadArrowRelease(nPadNo, arrow);
}




//---------------------------------------------------------------------------------------
//
//		�W���C�X�e�B�b�N�₢���킹�R�[���o�b�N�֐�
//
//---------------------------------------------------------------------------------------
BOOL CALLBACK EnumJoyPadCallback(const DIDEVICEINSTANCE* pDdi, VOID* pvRef){

	HRESULT hr;

	hr = g_pDInput->CreateDevice(pDdi->guidInstance, &g_pDIDevJoyPad[g_nNumJoyPadCount], NULL);
	if (FAILED(hr))
		return DIENUM_CONTINUE;

	DIDEVCAPS diDevCaps;
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = g_pDIDevJoyPad[g_nNumJoyPadCount]->GetCapabilities(&diDevCaps);
	if (FAILED(hr)){
		if (g_pDIDevJoyPad[g_nNumJoyPadCount] != NULL){
			g_pDIDevJoyPad[g_nNumJoyPadCount]->Release();
			g_pDIDevJoyPad[g_nNumJoyPadCount] = NULL;
		}
		return DIENUM_CONTINUE;
	}
	
	g_nNumJoyPadCount++;
	if (MAX_CONTROLER <= g_nNumJoyPadCount)
		return DIENUM_STOP;

	return DIENUM_CONTINUE;
}