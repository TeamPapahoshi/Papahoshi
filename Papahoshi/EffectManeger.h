//======================================================================
//	EffectManegerヘッダ
//	
//	概要＿：エフェクト管理用
//	制作者：安藤 光樹
//	
//======================================================================
#ifndef ___EFFECTMANEGER_H___
#define ___EFFECTMANEGER_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Common.h"		
#include <Windows.h>	//HRESULT他
#include "d3dx9.h"		//D3DXVECTOR2他
#include "Sprite.h"		//CSpriteクラスの導入
#include <vector>		//可変長配列の導入

//-----------------------------
//マクロ定義
//-----------------------------
#define MAX_EFFECT (200)

//----- エフェクト分割数の定義 -----
#define EFFECT_SPARKLE_TEX_DIVIDE_X (4)
#define EFFECT_SPARKLE_TEX_DIVIDE_Y (3)

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------

//----- 継承用:エフェクト基本クラス -----
class cBaseEffect
{
protected:
	int			  m_nLifeFleam;		//エフェクト生存フレーム
	bool		  m_bEffectUseFlag;	//エフェクト使用フラグ
	int			  m_nDivision;		//エフェクトに使用するポリゴンの個数
	D3DXVECTOR2   m_fEffectRadius;	//エフェクトを生成する半径

public:
	virtual void Update() = 0;	//必須
	virtual void Draw() = 0;	//必須
	virtual ~cBaseEffect(){}	//デストラクタ
	
	//エフェクト設定用仮想関数
	virtual void SetEffectCircle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, int division){};
	virtual void SetEffectSphereLight(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 move, D3DXCOLOR color, int life){};
	virtual void SetEffectSparkle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, D3DXVECTOR2 radius, int texdividex, int texdividey){};
	virtual void SetEffectBezierCurve(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, D3DXVECTOR2 startpoint, D3DXVECTOR2 endpoint){};

	//使用中フラグの取得
	bool GetUseFlag(void)
	{
		return m_bEffectUseFlag;
	}
};

//----- エフェクト管理用クラス -----
class cEffectManeger
{
public:
	void Init();			//初期化処理
	void Update();		//更新処理
	void Draw();			//描画処理
	void Uninit();		//終了処理

	//エフェクト設定仲介用関数

	void SetEffectCircle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, int division);
	void SetEffectSphereLight(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 move, D3DXCOLOR color, int life);
	void SetEffectSparkle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, D3DXVECTOR2 radius, int texdividex, int texdividey);
	void SetEffectBezierCurve(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, D3DXVECTOR2 startpoint, D3DXVECTOR2 endpoint);

protected:

private:
	cBaseEffect* m_pEffect[MAX_EFFECT];
};


#endif	//!___EFFECTMANEGER_H___