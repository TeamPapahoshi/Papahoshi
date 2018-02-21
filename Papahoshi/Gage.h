//======================================================================
//	Gage.h
//	
//	概要＿：ゲージ管理クラス
//	制作者：安藤 光樹
//	
//======================================================================
#ifndef ___GAGE_H___
#define ___GAGE_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Common.h"

//-----------------------------
//マクロ定義
//-----------------------------

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------
// 基底クラス:ゲージクラス
class cGage
{
private:	//外部から参照不可能
	cSpriteParam m_GageSprite;
	cSpriteParam m_FlameSprite;

	float		 m_fGageNum;
	bool		 m_bGageMax;
	int			 m_nGageEffectNum;

	//-----------------------------
protected:	//クラス内でのみ参照可能

	//-----------------------------
public:		//外部から参照可能
	void Init(void);
	void UnInit(void);
	void Update(void);
	void Draw(void);

	void GageAdd(void);	//ゲージ加算

	//----- ゲッタ ------
	bool GetGagemax(void)
	{
		return m_bGageMax;
	}

	cSpriteParam GetGageSprite(void)
	{
		return m_GageSprite;
	}
};

#endif	//!___SAMPLE_H___