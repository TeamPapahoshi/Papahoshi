//=============================================================================
//  Net.h
//
//  制作：後藤 愛生
//  概要：網の処理
//=============================================================================
#ifndef _NET_H_
#define _NET_H_

//----------------------------------------
// インクルード部
//----------------------------------------
#include "Common.h"
#include "Sprite.h"

//----------------------------------------
// 列挙型宣言
//----------------------------------------
enum{	//ネットの部品
	NET_PARTS_TOP,
	NET_PARTS_UNDER,
	NET_PARTS_RIGHT,
	NET_PARTS_LEFT,
	NET_PARTS_MAX,
};


//----------------------------------------
// 定数・マクロ定義
//----------------------------------------
#define NET_X_NUM	(6)	//あみの横分割数
#define NET_Y_NUM	(6)	//あみの縦分割数

//----------------------------------------
// クラス定義
//----------------------------------------
class cNet{

public:
	cNet();
	~cNet();

	void Update();	// 更新
	void Draw();	// 描画

private:
	//---- 列挙型宣言 -----
	enum GAME_PHASE{	//ゲームフェイズ
		PHASE_POST,	//構え
		PHASE_SHOUT,	//飛ばし
		PHASE_PULL,		//引く

		PHASE_MAX,
	};

	//---- スプライト ----
	cSpriteParam m_aNet[NET_PARTS_MAX][NET_Y_NUM][NET_X_NUM];	//あみ
	cSpriteParam m_aFourUki[4];	//四頂点のうき
	cSpriteParam m_center;		//中心点のうき
	cSpriteParam m_arrow;		//矢印
	D3DXVECTOR2 m_aPos[4];		//四頂点
	D3DXVECTOR2 m_centerPos;	//中心点

	//----- 変数宣言 -----
	GAME_PHASE gamePhase;	//ゲームフェイズ
	bool	m_bPressButton[4];	//四ボタンのプッシュ状況
	int		m_nLeverDirection;	//レバー入力方向、テンキー表記で格納

	//---- プロトタイプ宣言 ----
	void SetNet();	//各頂点に合わせてあみを貼る
	void Input();	//コントローラー入力を取得
	void PostPhaseUpdate();
	void ShoutPhaseUpdate();
	void PullPhaseUpdate();
};

#endif
