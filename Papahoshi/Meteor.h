//======================================================================
//	Meteor
//	
//	概要＿：タイトルオブジェクト/流星
//	制作者：安藤 光樹
//	
//======================================================================
#ifndef ___METEOR_H___
#define ___METEOR_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Common.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define MAX_METEOR (10)
#define MAX_METEOR_SPRITE_NUM (3)
#define METEOR_LIFETIME (60)

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//構造体定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------

class cObjMETEOR
{
private:	//外部から参照不可
	int nMakeTime;	//流星の生成までの時間
	int nLifeTime;	//流星の生存時間
	bool bUseFlag;	//使用フラグ

	//----------------------------
protected:	//クラス内でのみ参照可

	//-----------------------------
public:		//どこからでも参照可

	cObjMETEOR(){}	// コンストラクタ
	~cObjMETEOR(){}	// デストラクタ

	//------- ゲッタ --------
	int GetMakeTime(void)
	{
		return nMakeTime;
	}
	int GetLifeTime(void)
	{
		return nLifeTime;
	}
	bool GetUseFlag(void)
	{
		return bUseFlag;
	}
	//------- セッタ --------
	void SetLifeTime(int LifeTime)
	{
		nLifeTime = LifeTime;
	}
	void SetMakeTime(int MakeTime)
	{
		nMakeTime = MakeTime;
	}
	void SetUseFlag(bool Flag)
	{
		bUseFlag = Flag;
	}

	cSpriteParam Sprite[MAX_METEOR_SPRITE_NUM];
};

//クラステンプレート
class cMeteor
{
private:	//外部から参照不可
	cObjMETEOR m_aMeteor[MAX_METEOR];

	//-----------------------------
protected:	//クラス内でのみ参照可

	//-----------------------------
public:		//どこからでも参照可

	cMeteor();	// コンストラクタ
	~cMeteor();	// デストラクタ

	// ここは何かから継承させてもいいかもオーバライド
	void Init();	// 初期化 テクスチャのポインタを受け取って
	void UnInit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

	void SetMeteor();	//流星の設定
};

#endif	//!___METEOR_H___