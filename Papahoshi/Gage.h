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
#include "GameMain.h"	// エフェクトクラス取得用

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
	HSVCOLOR     m_aHSVColor[4];		//HSVの値
	bool		 m_bHSVColorChange[4];	//HSVの色切り替えフラグ

	float		 m_fGageNum;
	bool		 m_bGageMax;	//ゲージ状態フラグ(ゲージが最大値になったらtrue,0になったらfalse)
	int			 m_nGageEffectNum;

	bool	m_bFeverStart;
	bool	m_bFeverFin;

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

	bool GetFeverStart(){
		return m_bFeverStart;
	}

	bool GetFeverFin(){
		return m_bFeverFin;
	}

	void SetFeverStart(bool flug){
		m_bFeverStart = flug;
	}

	void SetFeverFin(bool flug){
		m_bFeverFin = flug;
	}
};

#endif	//!___SAMPLE_H___