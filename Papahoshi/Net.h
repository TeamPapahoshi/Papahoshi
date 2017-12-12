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
enum{
	NET_PARTS_TOP,
	NET_PARTS_UNDER,
	NET_PARTS_RIGHT,
	NET_PARTS_LEFT,
	NET_PARTS_MAX,
};


//----------------------------------------
// 定数・マクロ定義
//----------------------------------------
#define NET_X_NUM	(5)
#define NET_Y_NUM	(5)

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
	cSpriteParam m_aNet[NET_PARTS_MAX][NET_Y_NUM][NET_X_NUM];
	cSpriteParam m_aFourUki[4];	//四頂点
	cSpriteParam m_center;		//中心点
	D3DXVECTOR2 m_aPos[4];	//四頂点
	D3DXVECTOR2 m_centerPos;	//中心点

	void SetNet();	//各頂点に合わせてあみを貼る

};

#endif
