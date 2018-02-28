//======================================================================
//	WinMain
//	
//	����ҁFWinMain
//	�T�v�@�F�Ԉ�@�Y��
//======================================================================



//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "Common.h"
#include "GameMain.h"
#include "Frame.h"

//------------------------------
// �}�N����`
//------------------------------
//----- Windows�֘A ------------
#define CLASS_NAME	"�p�p�A�������܂Ƃ��āI"	// �E�B���h�E�N���X��
#define WINDOW_NAME	"�p�p�A�������܂Ƃ��āI"	// �L���v�V������

#define WINDOW_MODE	(TRUE)		//FALSE�Ńt���X�N���[��

//-----------------------------
// �v���g�^�C�v�錾
//-----------------------------
//�E�C���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//=======================================================================================
//
//		main�֐�
//
//=======================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//----------------------------
	// ���[�J���ϐ��錾
	//----------------------------
	//----- Windows�֘A ------------
	// �E�C���h�E�N���X
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0, 0,
		hInstance, LoadIcon(hInstance, "ICON_JELLY"), LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1), NULL, CLASS_NAME, NULL
	};
	HWND hWnd;	// �E�C���h�E�n���h��
	MSG msg;	// ���b�Z�[�W


	//----------------------------
	// �������A�E�C���h�E�\��
	//----------------------------
	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL, NULL, hInstance, NULL);

	// --- ���������� --------------------
	if (FAILED(Init(hInstance, hWnd, WINDOW_MODE))){
		// --- �����������s�����@�I������ ----
		UnregisterClass(CLASS_NAME, wcex.hInstance);
		UnInit();
		// --- �����������s�����@���b�Z�[�W�\�� ----
		MessageBox(hWnd, "DirectX�̏������Ɏ��s���܂����B\nDirectX�̐ݒ�Ȃǂ��m�F���Ă��������B", "DirectX���������s", MB_OK | MB_ICONERROR);
		return (-1);
	}

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//----------------------------
	//���b�Z�[�W���[�v
	//----------------------------
	while (1){

		//----- Windows�Ƃ��Ă̏��� ------------
 		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0){

			// <Windows����@�A�v���P�[�V�����I���˗���> �I��
			if (msg.message == WM_QUIT)
				break;

			// <�I���˗��ȊO��Window���b�Z�[�W��M��> ���b�Z�[�W�̖|��Ƒ��o
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		//----- DirectX�Ƃ��Ă̏��� ------------
		else {
			if (CheckFrameUpdate()) {
				//�X�V����
				Update();
				//�`�揈��

				Draw();
			}
		}
	}

	//----------------------------
	// �I������
	//----------------------------
	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//�I������
	UnInit();

	//----------------------------
	// WinMain�I��
	//----------------------------
	return (int)msg.wParam;
}

//=======================================================================================
//
//		�E�C���h�E�v���V�[�W���i�R�[���o�b�N�֐��j
//
//=======================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	//----------------------------
	// ���[�J���ϐ��錾
	//----------------------------
	int nID; //�I���m�F���b�Z�[�W�{�b�N�X�p



	//----------------------------
	// ���b�Z�[�W���̏���
	//----------------------------
	switch (uMsg) {

	//----- �E�C���h�E�������@------------
	case WM_DESTROY:

		// �y���s�z WM_QUIT
		PostQuitMessage(0);
		break;



	//----- �~�{�^���N���b�N���@------------
	case WM_CLOSE:

		//�I���m�F���b�Z�[�W�\��
		nID = MessageBox(hWnd, "�Q�[�����I�����Ă��܂��B\n��낵���ł����H", "�Q�[���I��", (MB_YESNO | MB_DEFBUTTON1 | MB_ICONQUESTION));

		// ---- [YES]----- / ---- �y���s�z WM_DESTROY ----
		if (nID == IDYES) {
			DestroyWindow(hWnd);
		}
		// ---- [NO]----- / ---- �E�C���h�E�N���[�Y���L�����Z�� ----
		else {
			return 0;
		}
		break;
	


	// ---- �G�X�P�[�v�L�[������ ------------
	case WM_KEYDOWN:

		switch (wParam) {
		case VK_ESCAPE:

			//�y���s�z WM_CLOSE
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		}
		break; 
	}

	//----------------------------
	//�E�B���h�E�v���V�[�W���I��
	//----------------------------
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
