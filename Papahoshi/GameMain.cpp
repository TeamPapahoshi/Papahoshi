//======================================================================
//	GameMain
//	
//	�T�v�Q�FInit, UnInit, Update, Draw
//	����ҁF�Ԉ�@�Y��
//	
//======================================================================

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "GameMain.h"
#include "Direct3D.h"	//Direct3D
#include "Frame.h"		//�t���[���Ǘ�
#include "Sprite.h"		//�X�v���C�g�Ǘ�
#include "Input.h"		//���͑��u�Ǘ�
#include "SceneManeger.h"
#include "sound.h"

//�f�o�b�O
#ifdef _DEBUG
#include"debugproc.h"
#endif

//-----------------------------
// �O���[�o��
//-----------------------------
#ifdef _DEBUG
bool g_bDispDebug = true;	//�f�o�b�OON/OFF
#endif

cEffectManeger g_CEffectManeger;	//�G�t�F�N�g�Ǘ��p�N���X

//=======================================================================================
//
//		������
//
//=======================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindowed){

	//Direct3D�̏�����
	if (FAILED(InitDirect3D(hInstance, hWnd, bWindowed)))
		return E_FAIL;

#ifdef _DEBUG
	if (FAILED(InitDebugProc()))
		return E_FAIL;
#endif	// _DEBUG

	//�t���[���Ǘ��̏�����
	if (FAILED(InitFrame()))
		return E_FAIL;

	//�X�v���C�g�Ǘ��̏�����
	if (FAILED(CreateBufferSprite()))
		return E_FAIL;

	//�G�t�F�N�g�̏�����
	g_CEffectManeger.Init();

	//�����̏�����
	CRandam::InitRand();

	//���͑��u�Ǘ��̏�����
	if (FAILED(InitInput(hInstance, hWnd)))
		return E_FAIL;

	//�T�E���h�̏�����
	if (FAILED(InitSound(hWnd)))
		return E_FAIL;

	//�ŏ��̃V�[���̐ݒ�
	cSceneManeger::ChangeScene(cSceneManeger::GAME);	//�f�o�b�O�p�ɃX�e�[�W�Z���N�g��ʂ���J�n
	

	//����������
	return S_OK;
}

//=======================================================================================
//
//		�I������
//
//=======================================================================================
void UnInit(void){


#ifdef _DEBUG
	//�f�o�b�O�\���p�e�L�X�g�̏I������
	UninitDebugProc();
#endif	//_DEBUG

	// �t���[���Ǘ��̏I������
	UnInitFrame();

	// �X�v���C�g�Ǘ��̏I������
	ReleaseBufferSprite();

	//�G�t�F�N�g�̏�����
	g_CEffectManeger.Uninit();

	//�����̏�����
	CRandam::InitRand();

	// ���͑��u�Ǘ��̏I������
	UnInitInput();

	// �T�E���h�̏I������
	UninitSound();

	//Direct3D�̏I������
	UnInitDirect3D();

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void Update(void){

	//���͑��u���̍X�V
	UpdateInput();

	//�G�t�F�N�g�̏�����
	g_CEffectManeger.Update();

	//���݂̃V�[���̍X�V
	cSceneManeger::Update();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1))
	{// �f�o�b�O�\��ON/OFF
		g_bDispDebug = g_bDispDebug ? false : true;
	}
	//�f�o�b�O�\���p�e�L�X�g�̍X�V
	UpdateDebugProc();
#endif	//_DEBUG

}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void Draw(void){

	//----------------------------
	// ���[�J���ϐ��錾
	//----------------------------
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// Direct3D�f�o�C�X

	//----------------------------
	// �`�揀��
	//----------------------------
	//�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 0, 255, 0), 1.0f, 0);

	//----------------------------
	// �`��
	//----------------------------
	// �`��J�n
	if (SUCCEEDED(pDevice->BeginScene())){

		//���݂̃V�[���̕`��
		cSceneManeger::Draw();

		//�G�t�F�N�g�̏�����
		g_CEffectManeger.Draw();

#ifdef _DEBUG
		//�f�o�b�O�\���p�e�L�X�g�̕`��
		if (g_bDispDebug)
			DrawDebugProc();
#endif	//_DEBUG

		pDevice->EndScene(); 
	}	// �`��I��
	
	//----------------------------
	// �`����e����ʂɔ��f
	//----------------------------
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	pDevice->Present(NULL, NULL, NULL, NULL);

}

//==================================================================
//
//	�G�t�F�N�g�������n���֐�
//
//==================================================================
cEffectManeger* GetEffectManeger(void)
{
	return &g_CEffectManeger;
}



