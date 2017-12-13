//======================================================================
//	Input
//	
//	�T�v�Q�F���͊֘A
//	����ҁF�Ԉ�@�Y��
//	
//======================================================================

#ifndef ___INPUT_H___
#define ___INPUT_H___

//------------------------------
//�C���N���[�h�t�@�C��
//------------------------------
#include <Windows.h>	//HRESULT��

// DirectInput8
#define DIRECTINPUT_VERSION	(0x0800)
#include "dinput.h"

//------------------------------
//�}�N����`
//------------------------------
#define CONTROLER_NO		(0)	// �R���g���[���ԍ�

#define JOY_BUTTON_A		(0)	// A�{�^��(360�R���g���[���)
#define JOY_BUTTON_B		(1)	// B�{�^��(360�R���g���[���)
#define JOY_BUTTON_X		(2)	// X�{�^��(360�R���g���[���)
#define JOY_BUTTON_Y		(3)	// Y�{�^��(360�R���g���[���)
#define JOY_BUTTON_START	(7)	// START�{�^���i360�R���g���[���[��j


//------------------------------
//�񋓑̒�`
//------------------------------
enum ePadArrowType {
	PAD_ARROW_UP,
	PAD_ARROW_RIGHT,
	PAD_ARROW_DOWN,
	PAD_ARROW_LEFT,
	PAD_ARROW_NUM_MAX
};

//------------------------------
//�v���g�^�C�v�錾
//------------------------------
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);	//������
void UnInitInput(void);								//�I������
void UpdateInput(void);								//�X�V


bool GetKeyboardPress(int nKey);	//�L�[�{�[�h�̃v���X��Ԃ��擾
bool GetKeyboardTrigger(int nKey);	//�L�[�{�[�h�̃g���K�[��Ԃ��擾
bool GetKeyboardRepeat(int nKey);	//�L�[�{�[�h�̃��s�[�g��Ԃ��擾
bool GetKeyboardRelease(int nKey);	//�L�[�{�[�h�̃����[�X��Ԃ��擾

bool  GetJoyPadButtonPress(const int& nPadNo, const int& nButton);
bool  GetJoyPadButtonTrigger(const int& nPadNo, const int& nButton);
bool  GetJoyPadButtonRelease(const int& nPadNo, const int& nButton);

bool  GetJoyPadArrowPress(const int& nPadNo, const ePadArrowType& arrow);
bool  GetJoyPadArrowTrigger(const int& nPadNo, const ePadArrowType& arrow);
bool  GetJoyPadArrowRelease(const int& nPadNo, const ePadArrowType& arrow);

//----------------- �L�[�{�[�h�ƃQ�[���p�b�h�̑g�ݍ��킹�@-----------------
bool GetInputButtonPress(int nKey, int nPadNo, const int& nButton);
bool GetInputButtonTrigger(int nKey, int nPadNo, const int& nButton);
bool GetInputButtonRelease(int nKey, int nPadNo, const int& nButton);

bool GetInputArrowPress(int nKey, int nPadNo, const ePadArrowType& arrow);
bool GetInputArrowTrigger(int nKey, int nPadNo, const ePadArrowType& arrow);
bool GetInputArrowRelease(int nKey, int nPadNo, const ePadArrowType& arrow);


#endif //!___INPUT_H___