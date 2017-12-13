//======================================================================
//	Input
//	
//	概要＿：入力装置関連の処理
//	制作者：花井　雄矢
//	
//======================================================================

//------------------------------
//インクルードファイル
//------------------------------
#include "Input.h"
#include "Direct3D.h"	//Direct3dデバイス

// DirectInput8
#pragma comment (lib, "dinput8.lib")


//------------------------------
//マクロ定義
//------------------------------
#define NUM_KEY_MAX			(256)	// キーボードキーの最大数

#define MAX_CONTROLER		(1)		//　ゲームパッド最大数
#define MAX_BUTTON			(32)	//　ゲームパッドボタン最大数

#define LIMIT_COUNT_REPEAT	(20)	// リピートカウントリミッター


//------------------------------
//グローバル変数宣言
//------------------------------
LPDIRECTINPUT8			g_pDInput = NULL;					// DirectInput

LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// 入力デバイス（キーボード）
BYTE					g_aKeyState[NUM_KEY_MAX];			// キーボードのプレス状態
BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー状態
BYTE					g_aKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート状態
BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース状態
int						g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピート回数カウンタ


LPDIRECTINPUTDEVICE8	g_pDIDevJoyPad[MAX_CONTROLER];			// 入力デバイス（ゲームパッド）]
static int				g_nNumJoyPadCount = 0;					// 見つかったゲームパッドの数
DIJOYSTATE				g_aJoyPadState[MAX_CONTROLER];			// ゲームパッドのプレス状態
DIJOYSTATE				g_aJoyPadStateTrigger[MAX_CONTROLER];	// ゲームパッドのトリガー状態
DIJOYSTATE				g_aJoyPadStateRepeat[MAX_CONTROLER];	// ゲームパッドのリピート状態
DIJOYSTATE				g_aJoyPadStateRelease[MAX_CONTROLER];	// ゲームパッドのリリース状態
int						g_aJoyPadStateRepeatCnt[MAX_CONTROLER];	// ゲームパッドのリピート回数カウンタ


//------------------------------
//プロトタイプ宣言
//------------------------------
// キーボードの初期化
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
// キーボードの終了処理
void	UnInitKeyboard(void);
// キーボードの更新
void	UpdateKeyboard(void);

// ゲームパッドの初期化
HRESULT InitJoyPad(HINSTANCE hInstance, HWND hWnd);
// ゲームパッドの終了処理
void	UnInitJoyPad(void);
// ゲームパッドの更新
void	UpdateJoyPad(void);

BOOL CALLBACK EnumJoyPadCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);



//=======================================================================================
//
//		入力装置初期化
//
//	[戻り値]	S_OK ： 初期化成功		E_FAIL : 初期化失敗
//
//=======================================================================================
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd){

	//----------------------------
	//DirectInputの作成
	//---------------------------- 
	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pDInput, NULL);
	if (FAILED(hr)){
		MessageBox(hWnd, "DirectInputオブジェクトを作ることができませんでした。", "警告", MB_ICONWARNING);
		return hr;
	}

	//----------------------------
	//キーボードの初期化
	//---------------------------- 
	if (FAILED(InitKeyboard(hInstance, hWnd)))
		return E_FAIL;

	//----------------------------
	//ゲームパッドの初期化
	//---------------------------- 
	if (FAILED(InitJoyPad(hInstance, hWnd)))
		return E_FAIL;


	//----------------------------
	//初期化終了
	//---------------------------- 
	return S_OK;
}

//---------------------------------------------------------------------------------------
//		キーボードの初期化
//---------------------------------------------------------------------------------------
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd){

	//----------------------------
	//ローカル変数宣言
	//---------------------------- 
	HRESULT hr;

	//----------------------------
	//入力デバイス（キーボード）の作成
	//---------------------------- 
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
	if (FAILED(hr)){
		MessageBox(hWnd, "キーボードが検出出来ませんでした。\nキーボード接続を確認してください。", "キーボード未検出", MB_ICONWARNING);
		return E_FAIL;
	}

	//----------------------------
	//データフォーマットの設定
	//---------------------------- 
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)){
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告", MB_ICONWARNING);
		return E_FAIL;
	}

	//----------------------------
	//協調モードを設定（フォアグラウンド＆非排他モード）
	//---------------------------- 
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr)){
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告", MB_ICONWARNING);
		return E_FAIL;
	}

	//----------------------------
	//キーボードへのアクセス権を獲得(入力制御開始)
	//---------------------------- 
	g_pDIDevKeyboard->Acquire();


	//----------------------------
	//キーボードのリピート回数カウンタ初期化(ゼロクリア）
	//---------------------------- 
	memset(g_aKeyStateRepeatCnt, 0x00, sizeof(g_aKeyStateRepeatCnt));


	//----------------------------
	//初期化終了
	//---------------------------- 
	return S_OK;
}

//---------------------------------------------------------------------------------------
//		ゲームパッドの初期化
//---------------------------------------------------------------------------------------
HRESULT InitJoyPad(HINSTANCE hInstance, HWND hWnd){

	//----------------------------
	//ローカル変数宣言
	//---------------------------- 
	HRESULT hr;

	//----------------------------
	//入力デバイス（ゲームパッド）の作成
	//---------------------------- 
	hr = g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyPadCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(hr)){
		MessageBox(hWnd, "ゲームパッドのデバイスオブジェクトが作成できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	for (int i = 0; i < MAX_CONTROLER; i++){
		if (g_pDIDevJoyPad[i] == NULL)
			continue;

		hr = g_pDIDevJoyPad[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr)){
			MessageBox(hWnd, "ゲームパッドのデータフォーマットの設定ができませんでした。", "警告！", MB_ICONWARNING);
			return hr;
		}


		hr = g_pDIDevJoyPad[i]->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ゲームパッドの協調レベルの設定ができませんでした。", "警告！", MB_ICONWARNING);
			return hr;
		}

		g_pDIDevJoyPad[i]->Acquire();
	}

	//----------------------------

	return S_OK;
}

//=======================================================================================
//
//		入力装置終了処理
//
//=======================================================================================
void UnInitInput(void){

	//----------------------------
	//キーボードの終了処理
	//----------------------------
	UnInitKeyboard();


	//----------------------------
	//ゲームパッドの終了処理
	//----------------------------
	UnInitJoyPad();


	//----------------------------
	//DirectInputオブジェクトを解放
	//----------------------------
	if (g_pDInput != NULL){
		g_pDInput->Release();
		g_pDInput = NULL;
	}
}

//---------------------------------------------------------------------------------------
//		キーボードの終了処理
//---------------------------------------------------------------------------------------
void	UnInitKeyboard(void){

	//----------------------------
	// 入力デバイス（キーボード）を解放
	//----------------------------
	if (g_pDIDevKeyboard != NULL){
		g_pDIDevKeyboard->Unacquire();	// キーボードへのアクセス権を解放（入力制御終了）
		g_pDIDevKeyboard->Release();
		g_pDIDevKeyboard = NULL;
	}
}

//---------------------------------------------------------------------------------------
//		ゲームパッドの終了処理
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
//		入力装置更新
//
//=======================================================================================
void UpdateInput(void){

	//キーボードの更新
	UpdateKeyboard();

	//ゲームパッドの更新
	UpdateJoyPad();
}


//---------------------------------------------------------------------------------------
//
//		キーボードの更新
//
//---------------------------------------------------------------------------------------
void	UpdateKeyboard(void){

	//----------------------------
	//ローカル変数宣言
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
//		キーボードのプレス状態を取得
//=======================================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}


//=======================================================================================
//		キーボードのトリガー状態を取得
//=======================================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=======================================================================================
//		キーボードのリピート状態を取得
//=======================================================================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//=======================================================================================
//		キーボードのリリース状態を取得
//=======================================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}




//---------------------------------------------------------------------------------------
//
//		ゲームパッドの更新
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
//		ゲームパッドのキー入力状態を取得
//=======================================================================================
bool  GetJoyPadButtonPress(const int& nPadNo, const int& nButton){


	if (g_nNumJoyPadCount < nPadNo)
		return false;

	return (g_aJoyPadState[nPadNo].rgbButtons[nButton] & 0x80) ? true : false;
}

//=======================================================================================
//		ゲームパッドのキー入力状態を取得(トリガー）
//=======================================================================================
bool  GetJoyPadButtonTrigger(const int& nPadNo, const int& nButton){


	if (g_nNumJoyPadCount < nPadNo)
		return false;

	return (g_aJoyPadStateTrigger[nPadNo].rgbButtons[nButton] & 0x80) ? true : false;
}


//=======================================================================================
//		ゲームパッドのキー入力状態を取得(リリース）
//=======================================================================================
bool  GetJoyPadButtonRelease(const int& nPadNo, const int& nButton){


	if (g_nNumJoyPadCount < nPadNo)
		return false;

	return (g_aJoyPadStateRelease[nPadNo].rgbButtons[nButton] & 0x80) ? true : false;
}


//=======================================================================================
//		ゲームパッドの方向キー入力状態を取得
//=======================================================================================
bool  GetJoyPadArrowPress(const int& nPadNo, const ePadArrowType& arrow){


	if (g_nNumJoyPadCount < nPadNo)
		return false;

	return g_aJoyPadState[nPadNo].rgdwPOV[arrow] ? true : false;
}


//=======================================================================================
//		ゲームパッドの方向キー状態を取得（トリガー）
//=======================================================================================
bool  GetJoyPadArrowTrigger(const int& nPadNo, const ePadArrowType& arrow){


	if (g_nNumJoyPadCount < nPadNo)
		return false;

	return g_aJoyPadStateTrigger[nPadNo].rgdwPOV[arrow] ? true : false;
}


//=======================================================================================
//		ゲームパッドの方向キー状態を取得（リリース）
//=======================================================================================
bool  GetJoyPadArrowRelease(const int& nPadNo, const ePadArrowType& arrow){


	if (g_nNumJoyPadCount < nPadNo)
		return false;

	return g_aJoyPadStateRelease[nPadNo].rgdwPOV[arrow] ? true : false;
}


//----------------- キーボードとゲームパッドの組み合わせ　-----------------
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
//		ジョイスティック問い合わせコールバック関数
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