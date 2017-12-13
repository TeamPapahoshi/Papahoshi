//======================================================================
//	Direct3D
//	
//	�T�v�Q�FDirect�RD�֘A
//	����ҁF�Ԉ�@�Y��
//	
//======================================================================

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "Direct3D.h"

#include "Common.h"		//SCREEN_WIDTH��


//-----------------------------
// �O���[�o���ϐ�
//-----------------------------
static LPDIRECT3D9 g_pD3D = NULL;				//Direct3D�I�u�W�F�N�g
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3DDevice�I�u�W�F�N�g


//������
HRESULT InitDirect3D(HINSTANCE hInstance, HWND hWnd, BOOL bWindowed) {

	//----------------------------
	// ���[�J���ϐ��錾
	//----------------------------
	D3DPRESENT_PARAMETERS d3dpp;	//�e��p�����[�^
	D3DDISPLAYMODE d3ddm;			//�f�B�X�v���C���[�h

	//----------------------------
	// Direct3D�I�u�W�F�N�g�̐���
	//----------------------------
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
		return E_FAIL;

	//----------------------------
	// �f�B�X�v���C���[�h�̐ݒ�
	//----------------------------
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))	// ���݂̃f�B�X�v���C���[�h���擾
		return E_FAIL;

	//----------------------------
	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^��ݒ�
	//----------------------------
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// �[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;		// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// �Q�[����ʃT�C�Y�i�c�j
	d3dpp.BackBufferFormat = d3ddm.Format;		// �f�B�X�v���C���[�h���珑����ݒ�
	d3dpp.BackBufferCount = 1;					// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindowed;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;		// �f�v�X�o�b�t�@(Z�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	//----- �E�C���h�E���[�h ------------
	if (bWindowed){

		//���t���b�V�����[�g�i�w��ł��Ȃ�����0�j
		d3dpp.FullScreen_RefreshRateInHz = 0;

		//�C���^�[�o���ݒ�iVSync��҂����ɕ`��j
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	}
	//----- �t���X�N���[�����[�h ------------
	else{

		//���t���b�V�����[�g�i���ݑ��x�ɍ��킹��j
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

		//�C���^�[�o���iVSync��҂j
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	}

	//----------------------------
	// �f�o�C�X�I�u�W�F�N�g�̐���
	//----------------------------
	// ----- ���_�������n�[�h�E�F�A�ōs���ݒ�(�`�揈���F�n�[�h�j------------
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))){

		//----- ���_�������\�t�g�E�F�A�ōs���ݒ� (�`�揈���F�n�[�h�j ------------
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))){

			//----- ���_�������\�t�g�E�F�A�ōs���ݒ� (�`�揈���F�\�t�g�j ------------
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))){

				return E_FAIL;	// <�R�ݒ肢����ł��������ł��Ȃ��Ƃ�>�@���������s

			}
		}
	}

	//----------------------------
	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	//----------------------------
	//���ʂ��J�����O����ݒ�� // �J�����O(�J�����ɉf��Ȃ������̕`����s��Ȃ�)
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//�A���t�@�u�����h���s���ݒ�Ɂ@// �A���t�@�u�����h(������/��������)
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//�A���t�@�\�[�X�J���[�̐ݒ� // �A���t�@�\�[�X�J���[�i�A���t�@�����㏑�����̐ݒ�j
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//�A���t�@�f�X�e�B�l�[�V�����J���[�̐ݒ� // �A���t�@�f�B�X�e�B�l�[�V�����J���[�i�d�˂��鑤�̐ݒ�j
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//----------------------------
	// �e�N�X�`���X�e�[�W�̐ݒ�
	//----------------------------
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	//�A���t�@�v�f�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//----------------------------
	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	//----------------------------
	//�e�N�X�`������T���v�����O�i�f�[�^���o���j���s��

	// �e�N�X�`��U�l�i���j���J��Ԃ��ݒ�Ɂ@
	//   1.0�𒴂����0.0�ɖ߂�i���b�v�������j
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	// �e�N�X�`��V�l�i�c�j���J��Ԃ��ݒ�Ɂ@
	//   1.0�𒴂����0.0�ɖ߂�i���b�v�������j
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���k�����̕⊮�ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//�e�N�X�`���g�厞�̕⊮�ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	return S_OK;
}


//�I������
void UnInitDirect3D(void) {

	//----------------------------
	// Direct3D�f�o�C�X�����
	//----------------------------
	if (g_pD3DDevice != NULL){

		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;

	}

	//----------------------------
	// DirectX3D�I�u�W�F�N�g�����
	//----------------------------
	if (g_pD3D != NULL){

		g_pD3D->Release();
		g_pD3D = NULL;

	}
}

LPDIRECT3DDEVICE9 GetDevice(void) {

	return g_pD3DDevice;
}