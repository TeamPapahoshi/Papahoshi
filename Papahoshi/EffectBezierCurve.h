//======================================================================
//	EffectVezierCurve.h
//	
//	概要＿：曲線を描く線のエフェクト(ベジェ使用)
//	制作者：安藤 光樹
//	
//======================================================================
#ifndef ___EFFECTBEZIERCURVE_H___
#define ___EFFECTBEZIERCURVE_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "EffectManeger.h"	

//-----------------------------
//マクロ定義
//-----------------------------
#define MAX_BEZIERCURVEFFECT_SPRITE (1)
#define MAX_POINT (3)

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------
class cEffectBezierCurve : public cBaseEffect
{
private:
	cSpriteParam* m_Sprite[MAX_BEZIERCURVEFFECT_SPRITE];	//スプライト情報のポインタ(動的確保に使用)
	D3DXVECTOR2   m_CPoint[MAX_POINT];						//制御点の情報
	float		  m_fPointTime;								//ベジェ曲線上を移動する時間
	float		  m_fPointInterval;							//ベジェ曲線上を移動する時間の間隔

	//--------------------------------------
protected:
	//--------------------------------------
public:
	cEffectBezierCurve();		//コンストラクタ
	~cEffectBezierCurve();		//デストラクタ

	void Update(void);			//更新関数
	void Draw(void);			//描画関数
	void Uninit(void);			//終了関数

	void SetEffectBezierCurve(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, D3DXVECTOR2 startpoint, D3DXVECTOR2 endpoint);	//円形エフェクトの設定関数
};

#endif	//!___EFFECTCIECLE_H___