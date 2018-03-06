//======================================================================
//	Common
//	
//	概要＿：共通部分
//	制作者：加藤　遼
//	
//======================================================================

#ifndef ___COMMON_H___
#define ___COMMON_H___

// デバッグ用　イベントスキップ・タイムストップ
//#define _DEBUG_DKIP_

// プレゼンテーション
//#define _PRESEN_KEY_

//------------------------------
// インクルードファイル
//------------------------------
#include "d3dx9.h"		// D3DXVECTOR2他
#include "rand.h"		// 乱数生成用クラス
#include "Sprite.h"		// CSpriteクラスの導入
#include <iostream>		// cout
#include <fstream>		// fstream
#include <vector>		// vector

//------------------------------
// 名前空間の指定
//------------------------------
using namespace std;

//------------------------------
// マクロ定義
//------------------------------
//----- スクリーンの大きさ ------------
#define SCREEN_WIDTH (1366)	//横幅
#define SCREEN_HEIGHT (768) //高さ

// 画面比率合わせたい
//#define SCREEN_WIDTH (950)	//横幅
//#define SCREEN_HEIGHT (550)	//高さ

//横：1366  ×  縦 : 768

//----- 中心座標 -------
#define SCREEN_CENTER (D3DXVECTOR2(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f))

#define SINCURVE(UnderFloat, RandFloat, Radian) (UnderFloat + (RandFloat * sinf(Radian * 3.14f)))	//サインカーブ
#define COSCURVE(UnderFloat, RandFloat, Radian) (UnderFloat + (RandFloat * cosf(Radian * 3.14f)))	//コサインカーブ

#define MAX_RADIUS (200)	//Radiusの最高値

//----- SAFE DELETE ------
#define SAFE_DELETE(x)	if(x!=NULL){delete x; x=NULL})

#define _FPS_MEASURE_		//FPS計測機能



#endif //!___COMMON_H___