//======================================================================
//	Direct3D
//	
//	�T�v�Q�FDirect�RD�֘A
//	����ҁF�Ԉ�@�Y��
//	
//======================================================================
#ifndef ___DIRECT3D_H____
#define ___DIRECT3D_H____

#include <Windows.h>	//HRESULT��
#include "d3dx9.h"		//LPDIRECT3DDEVICE9��



//---------------------------------
// ���C�u�����̃����N
//---------------------------------
#if 1
#pragma comment (lib, "d3d9.lib")	//Direct3D9
#pragma comment (lib, "d3dx9.lib")	//D3DX�g�����C�u����
#pragma comment (lib, "dxguid.lib") //DirectX�R���|�[�l���g
#endif



//������
HRESULT InitDirect3D(HINSTANCE hInstance, HWND hWnd, BOOL bWindowed);
//�I������
void UnInitDirect3D(void);

// Direct3D�f�o�C�X�̎擾
LPDIRECT3DDEVICE9 GetDevice(void);

#endif //!___DIRECT3D_H____