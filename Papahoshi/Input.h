//======================================================================
//	Input
//	
//	概要＿：入力関連
//	制作者：花井　雄矢
//	
//======================================================================

#ifndef ___INPUT_H___
#define ___INPUT_H___

//------------------------------
//インクルードファイル
//------------------------------
#include <Windows.h>	//HRESULT他

// DirectInput8
#define DIRECTINPUT_VERSION	(0x0800)
#include "dinput.h"

//------------------------------
//マクロ定義
//------------------------------
#define CONTROLER_NO		(0)	// コントローラ番号

#define JOY_BUTTON_A		(0)	// Aボタン(360コントローラ基準)
#define JOY_BUTTON_B		(1)	// Bボタン(360コントローラ基準)
#define JOY_BUTTON_X		(2)	// Xボタン(360コントローラ基準)
#define JOY_BUTTON_Y		(3)	// Yボタン(360コントローラ基準)
#define JOY_BUTTON_START	(7)	// STARTボタン（360コントローラー基準）

#define AC_CON_BUTTON_A		(0)	//左上
#define AC_CON_BUTTON_B		(3)	//左上からいっこ右
#define AC_CON_BUTTON_C		(5)	
#define AC_CON_BUTTON_D		(4)	//右上
#define AC_CON_BUTTON_E		(1)	//左下
#define AC_CON_BUTTON_F		(2)
#define AC_CON_BUTTON_G		(7)
#define AC_CON_BUTTON_H		(6)	//右下

//------------------------------
//列挙体定義
//------------------------------
enum ePadArrowType {
	PAD_ARROW_UP,
	PAD_ARROW_RIGHT,
	PAD_ARROW_DOWN,
	PAD_ARROW_LEFT,
	PAD_ARROW_NUM_MAX
};

//------------------------------
//プロトタイプ宣言
//------------------------------
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);	//初期化
void UnInitInput(void);								//終了処理
void UpdateInput(void);								//更新


bool GetKeyboardPress(int nKey);	//キーボードのプレス状態を取得
bool GetKeyboardTrigger(int nKey);	//キーボードのトリガー状態を取得
bool GetKeyboardRepeat(int nKey);	//キーボードのリピート状態を取得
bool GetKeyboardRelease(int nKey);	//キーボードのリリース状態を取得

bool  GetJoyPadButtonPress(const int& nPadNo, const int& nButton);
bool  GetJoyPadButtonTrigger(const int& nPadNo, const int& nButton);
bool  GetJoyPadButtonRelease(const int& nPadNo, const int& nButton);

bool  GetJoyPadArrowPress(const int& nPadNo, const ePadArrowType& arrow);
bool  GetJoyPadArrowTrigger(const int& nPadNo, const ePadArrowType& arrow);
bool  GetJoyPadArrowRelease(const int& nPadNo, const ePadArrowType& arrow);

//----------------- キーボードとゲームパッドの組み合わせ　-----------------
bool GetInputButtonPress(int nKey, int nPadNo, const int& nButton);
bool GetInputButtonTrigger(int nKey, int nPadNo, const int& nButton);
bool GetInputButtonRelease(int nKey, int nPadNo, const int& nButton);

bool GetInputArrowPress(int nKey, int nPadNo, const ePadArrowType& arrow);
bool GetInputArrowTrigger(int nKey, int nPadNo, const ePadArrowType& arrow);
bool GetInputArrowRelease(int nKey, int nPadNo, const ePadArrowType& arrow);


#endif //!___INPUT_H___