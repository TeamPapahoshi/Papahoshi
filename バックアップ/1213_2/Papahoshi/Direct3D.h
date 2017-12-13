//======================================================================
//	Direct3D
//	
//	概要＿：Direct３D関連
//	制作者：花井　雄矢
//	
//======================================================================
#ifndef ___DIRECT3D_H____
#define ___DIRECT3D_H____

#include <Windows.h>	//HRESULT他
#include "d3dx9.h"		//LPDIRECT3DDEVICE9他



//---------------------------------
// ライブラリのリンク
//---------------------------------
#if 1
#pragma comment (lib, "d3d9.lib")	//Direct3D9
#pragma comment (lib, "d3dx9.lib")	//D3DX拡張ライブラリ
#pragma comment (lib, "dxguid.lib") //DirectXコンポーネント
#endif



//初期化
HRESULT InitDirect3D(HINSTANCE hInstance, HWND hWnd, BOOL bWindowed);
//終了処理
void UnInitDirect3D(void);

// Direct3Dデバイスの取得
LPDIRECT3DDEVICE9 GetDevice(void);

#endif //!___DIRECT3D_H____