//======================================================================
//	TitleRogo
//	
//	概要＿：タイトルロゴヘッダ
//	制作者：安藤 光樹
//	
//======================================================================
#ifndef ___TITLEROGO_H___
#define ___TITLEROGO_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Common.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define  MAX_TITLEROGO (13)

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//構造体定義
//-----------------------------
typedef struct
{

	cSpriteParam	Rogosprite;			// スプライトのステータス(ロゴ)
	int				nHopTimer;				// タイマー
	float			fRadian;
	bool			bMoveFlag;			//跳ねるフラグ
	float           fOriginPosY;		//元のY座標
}TITLEROGO;

//-----------------------------
//クラス定義
//-----------------------------

class cTitleRogo{
private:
	TITLEROGO       m_aTitlerogo[MAX_TITLEROGO];
	cSpriteParam    m_Pushsprite;
	int				m_nAlphaTimer;
//----------------------------------------------------------
protected:

//----------------------------------------------------------
public:
	cTitleRogo();	// コンストラクタ
	~cTitleRogo();	// デストラクタ

	// ここは何かから継承させてもいいかもオーバライド
	void Init();	// 初期化 テクスチャのポインタを受け取って
	void UnInit();	// 終了
	void Update(bool bSceneChangeFlag);	// 更新
	void Draw();	// 描画
};

#endif	//!___TITLEROGO_H___