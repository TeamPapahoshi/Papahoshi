//======================================================================
//	BG
//	
//	概要＿：背景
//	制作者：加藤 遼
//	
//======================================================================
#ifndef ___BG_H___
#define ___BG_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Sprite.h"


//-----------------------------
//クラス定義
//-----------------------------
//----継承用 背景基本クラス----
class cBaseBG{

public:
	
	virtual ~cBaseBG(){}	// デストラクタ

	virtual void Init()=0;
	virtual void UnInit()=0;
	virtual void Update() = 0;
	virtual void Draw()=0;
};

//----背景管理用クラス----
class cBgManager{

public:
	enum BG{
		NIGHT_SKY,	// 夜空
	};

	void Init();
	void UnInit();
	void Draw();
	void Update();

	void SetBG(BG bg);

private:
	cBaseBG*   m_pBg;	// 背景ベースのポインタ

};

// 夜空
//class cBgNightSky :public cBaseBG{
//
//public:
//	void Init();
//	void UnInit();
//	void Update();
//	void Draw();
//
//	cBgNightSky(){
//
//	//	sprite.LoadTexture()
//
//	}
//
//private:
//	cSpriteParam sprite;	// 描画用
//};
#endif	//!___BG_H___