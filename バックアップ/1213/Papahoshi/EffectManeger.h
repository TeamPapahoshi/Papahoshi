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
#define MAX_EFFECT (100)

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
	int		m_nLifeFleam;		//エフェクト生存フレーム
	bool	m_bEffectUseFlag;	//エフェクト使用フラグ
	int		m_nDivision;		//エフェクトに使用するポリゴンの個数

public:
	virtual void Update() = 0;	//必須
	virtual void Draw() = 0;	//必須
	virtual ~cBaseEffect(){}	//デストラクタ
	
	//エフェクト設定用仮想関数
	virtual void SetEffect(LPDIRECT3DTEXTURE9 ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, int division) = 0;

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
	//エフェクト指定用列挙体
	enum EFFECT_NUM
	{
		EFFECT_CIRCLE,
		EFFECT_NUM_MAX
	};

	void Init();			//初期化処理
	void Update();		//更新処理
	void Draw();			//描画処理
	void Uninit();		//終了処理
	void SetEffectBase(EFFECT_NUM effect, LPDIRECT3DTEXTURE9 ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, int division);

protected:

private:
	cBaseEffect* m_pEffect[MAX_EFFECT];
};


#endif	//!___EFFECTMANEGER_H___