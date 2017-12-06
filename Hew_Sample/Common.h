//======================================================================
//	Common
//	
//	概要＿：共通部分
//	制作者：花井　雄矢
//	
//======================================================================

#ifndef ___COMMON_H___
#define ___COMMON_H___

//------------------------------
// インクルードファイル
//------------------------------
#include "d3dx9.h"		//D3DXVECTOR2他

//------------------------------
// マクロ定義
//------------------------------

//----- スクリーンの大きさ ------------
#define SCREEN_WIDTH (950)	//横幅
#define SCREEN_HEIGHT (650) //高さ


//----- デバッグ用機能 ------------
//#define _DEBUG_TEXT_	//デバッグ用テキスト表示

#ifdef _DEBUG_TEXT_
#define _FPS_MEASURE_		//FPS計測機能

#if 0	// --------- SCENE_GAME ---------
#define _DEBUG_TEXT_PLAYER_	//プレイヤー情報　デバッグ表示
#define _DEBUG_HEART_
#endif


#endif

//---------------------------
// 列挙体定義
//---------------------------
enum eDirection {

	DIRECTION_LEFT = -1,
	DIRECTION_UP,
	DIRECTION_RIGHT,
	DIRECTION_DOWN
};


#endif //!___COMMON_H___