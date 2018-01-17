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
#include "rand.h"		//乱数生成用クラス
#include "GameMain.h"	//エフェクトクラス取得用


//------------------------------
// 名前空間の指定
//------------------------------
using namespace std;

//------------------------------
// マクロ定義
//------------------------------

//----- スクリーンの大きさ ------------
#define SCREEN_WIDTH (950)	//横幅
#define SCREEN_HEIGHT (650) //高さ

#define SINCURVE(UnderFloat, RandFloat, Radian) (UnderFloat + (RandFloat * sinf(Radian * 3.14f)))	//サインカーブ
#define COSCURVE(UnderFloat, RandFloat, Radian) (UnderFloat + (RandFloat * cosf(Radian * 3.14f)))	//コサインカーブ

#define MAX_RADIUS (200)	//Radiusの最高値

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