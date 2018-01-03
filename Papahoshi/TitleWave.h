//======================================================================
//	TitleWave.h
//	
//	概要＿：タイトルオブジェクト・波
//	制作者：安藤 光樹
//	
//======================================================================
#ifndef ___TITLEWAVE_H___
#define ___TITLEWAVE_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Common.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define WAVE_SIZE_X (SCREEN_WIDTH / 5)
#define WAVE_SIZE_Y (100)

#define MAX_WAVE (SCREEN_WIDTH / WAVE_SIZE_X + 1)

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------
class cTitleWave
{
private:
	cSpriteParam	m_TitleWave[MAX_WAVE];			// スプライトのステータス
	//----------------------------------------------------------
protected:

	//----------------------------------------------------------
public:
	cTitleWave();	// コンストラクタ
	~cTitleWave();	// デストラクタ

	// ここは何かから継承させてもいいかもオーバライド
	void Init();	// 初期化 テクスチャのポインタを受け取って
	void UnInit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

};

#endif	//!___TITLEWAVE_H___