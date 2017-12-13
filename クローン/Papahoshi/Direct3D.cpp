//======================================================================
//	Direct3D
//	
//	概要＿：Direct３D関連
//	制作者：花井　雄矢
//	
//======================================================================

//------------------------------
// インクルードファイル
//------------------------------
#include "Direct3D.h"

#include "Common.h"		//SCREEN_WIDTH他


//-----------------------------
// グローバル変数
//-----------------------------
static LPDIRECT3D9 g_pD3D = NULL;				//Direct3Dオブジェクト
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3DDeviceオブジェクト


//初期化
HRESULT InitDirect3D(HINSTANCE hInstance, HWND hWnd, BOOL bWindowed) {

	//----------------------------
	// ローカル変数宣言
	//----------------------------
	D3DPRESENT_PARAMETERS d3dpp;	//各種パラメータ
	D3DDISPLAYMODE d3ddm;			//ディスプレイモード

	//----------------------------
	// Direct3Dオブジェクトの生成
	//----------------------------
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
		return E_FAIL;

	//----------------------------
	// ディスプレイモードの設定
	//----------------------------
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))	// 現在のディスプレイモードを取得
		return E_FAIL;

	//----------------------------
	// デバイスのプレゼンテーションパラメータを設定
	//----------------------------
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// ゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;		// ゲーム画面サイズ(横)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// ゲーム画面サイズ（縦）
	d3dpp.BackBufferFormat = d3ddm.Format;		// ディスプレイモードから書式を設定
	d3dpp.BackBufferCount = 1;					// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed = bWindowed;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;		// デプスバッファ(Zバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// デプスバッファとして16bitを使う

	//----- ウインドウモード ------------
	if (bWindowed){

		//リフレッシュレート（指定できないため0）
		d3dpp.FullScreen_RefreshRateInHz = 0;

		//インターバル設定（VSyncを待たずに描画）
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	}
	//----- フルスクリーンモード ------------
	else{

		//リフレッシュレート（現在速度に合わせる）
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

		//インターバル（VSyncを待つ）
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	}

	//----------------------------
	// デバイスオブジェクトの生成
	//----------------------------
	// ----- 頂点処理をハードウェアで行う設定(描画処理：ハード）------------
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))){

		//----- 頂点処理をソフトウェアで行う設定 (描画処理：ハード） ------------
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))){

			//----- 頂点処理をソフトウェアで行う設定 (描画処理：ソフト） ------------
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))){

				return E_FAIL;	// <３設定いずれでも初期化できないとき>　初期化失敗

			}
		}
	}

	//----------------------------
	// レンダリングステートパラメータの設定
	//----------------------------
	//裏面をカリングする設定に // カリング(カメラに映らない部分の描画を行わない)
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//アルファブレンドを行う設定に　// アルファブレンド(半透明/透明処理)
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//アルファソースカラーの設定 // アルファソースカラー（アルファを持つ上書き側の設定）
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//アルファデスティネーションカラーの設定 // アルファディスティネーションカラー（重ねられる側の設定）
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//----------------------------
	// テクスチャステージの設定
	//----------------------------
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	//アルファ要素の設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//----------------------------
	// サンプラーステートパラメータの設定
	//----------------------------
	//テクスチャからサンプリング（データ取り出し）を行う

	// テクスチャU値（横）を繰り返し設定に　
	//   1.0を超えると0.0に戻る（ラップ＝包装する）
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	// テクスチャV値（縦）を繰り返し設定に　
	//   1.0を超えると0.0に戻る（ラップ＝包装する）
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャ縮小時の補完設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//テクスチャ拡大時の補完設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	return S_OK;
}


//終了処理
void UnInitDirect3D(void) {

	//----------------------------
	// Direct3Dデバイスを解放
	//----------------------------
	if (g_pD3DDevice != NULL){

		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;

	}

	//----------------------------
	// DirectX3Dオブジェクトを解放
	//----------------------------
	if (g_pD3D != NULL){

		g_pD3D->Release();
		g_pD3D = NULL;

	}
}

LPDIRECT3DDEVICE9 GetDevice(void) {

	return g_pD3DDevice;
}