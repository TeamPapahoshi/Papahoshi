//======================================================================
//	Sample
//	
//	概要＿：コピー用
//	制作者：
//	
//======================================================================
#ifndef ___EFFECTSPARKLE_H___
#define ___EFFECTSPARKLE_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "EffectManeger.h"	

//-----------------------------
//マクロ定義
//-----------------------------
#define MAX_SPARKLEEFFECT_SPRITE (10)

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------
class cEffectSparkle : public cBaseEffect
{
private:
	cSpriteParam* m_Sprite;	//スプライト情報のポインタ(動的確保に使用)
	int			  m_nHalfLife;
	HSVCOLOR      m_aHSVColor;

	//--------------------------------------
protected:
	//--------------------------------------
public:
	cEffectSparkle();		//コンストラクタ
	~cEffectSparkle();		//デストラクタ

	void Update(void);			//更新関数
	void Draw(void);			//描画関数
	void Uninit(void);			//終了関数

	void SetEffectSparkle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, HSVCOLOR color, int life, D3DXVECTOR2 radius, int texdividex, int texdividey);	//円形エフェクトの設定関数
};

#endif	//!___EFFECTCIECLE_H___