//======================================================================
//	ResultGirl.h
//	
//	概要＿：リザルト画面の女の子表示
//	制作者：安藤 光樹
//	
//======================================================================
#ifndef ___RESULTGIRL_H___
#define ___RESULTGIRL_H___

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
// 基底クラス:クラスサンプル
class cResultgirl
{
private:	//外部から参照不可能

	//-----------------------------
protected:	//クラス内でのみ参照可能

	//-----------------------------
public:		//外部から参照可能

	cResultgirl();	//コンストラクタ
	~cResultgirl();	//デストラクタ

	void Init(void);
	void UnInit(void);
	void Update(void);
	void Draw(void);
};

#endif	//!___SAMPLE_H___