//======================================================================
//	EffectSphereLight.h
//	
//	概要＿：丸型の光エフェクト
//	制作者：安藤 光樹
//	
//======================================================================
#ifndef ___EFFECTSPHERELIGHT_H___
#define ___EFFECTSPHERELIGHT_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "EffectManeger.h"

//-----------------------------
//マクロ定義
//-----------------------------

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------
class cEffectSphereLight : public cBaseEffect
{
private:
	cSpriteParam* m_Sprite;	//スプライト情報のポインタ(動的確保)
	int			  m_MaxLife;	//生存時間
//-----------------------------
protected:


//-----------------------------
public:

	cEffectSphereLight(){};		//コンストラクタ
	~cEffectSphereLight(){};		//デストラクタ

	void Update(void);			//更新関数
	void Draw(void);			//描画関数
	void Uninit(void);			//終了関数

	void SetEffect(LPDIRECT3DTEXTURE9 ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 move, D3DXCOLOR color, int life, int division);	//円形エフェクトの設定関数
};


#endif	//!___EFFECTSPHERELIGHT_H___