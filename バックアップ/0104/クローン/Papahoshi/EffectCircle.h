//======================================================================
//	Sample
//	
//	概要＿：コピー用
//	制作者：
//	
//======================================================================
#ifndef ___EFFECTCIRCLE_H___
#define ___EFFECTCIRCLE_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "EffectManeger.h"	

//-----------------------------
//マクロ定義
//-----------------------------
#define MAX_CIRCLEEFFECT_SPRITE (16)

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------
class cEffectCircle : public cBaseEffect
{
private:
	cSpriteParam* m_Sprite[MAX_CIRCLEEFFECT_SPRITE];	//スプライト情報のポインタ(動的確保に使用)

//--------------------------------------
protected:
//--------------------------------------
public:
	cEffectCircle();		//コンストラクタ
	~cEffectCircle();		//デストラクタ

	void Update(void);			//更新関数
	void Draw(void);			//描画関数
	void Uninit(void);			//終了関数

	void SetEffect(LPDIRECT3DTEXTURE9 ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 move, D3DXCOLOR color, int life, int division);	//円形エフェクトの設定関数
};

#endif	//!___EFFECTCIECLE_H___