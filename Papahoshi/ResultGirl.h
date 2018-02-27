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
#include "GameMain.h"	// エフェクトクラス取得用

//-----------------------------
//マクロ定義
//-----------------------------
#define   RESULTGIRL_POS_X (SCREEN_WIDTH - 320.0f)
#define   RESULTGIRL_POS_Y (SCREEN_HEIGHT - 150.0f)
#define   RESULTGIRL_SIZE_X (300.0f)
#define   RESULTGIRL_SIZE_Y (400.0f)

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
	cSpriteParam m_cGirlsprite;
	int			 m_nAnimPattern;
	int			 m_nCurrentPattern;
	int			 m_nAnimFlame;
	bool		 m_nAnimFlag;	//trueでmaxの、falseでminのテクスチャ表示

	//-----------------------------
protected:	//クラス内でのみ参照可能

	//-----------------------------
public:		//外部から参照可能

	cResultgirl();	//コンストラクタ
	~cResultgirl();	//デストラクタ

	void Update(void);
	void Draw(void);

	bool GetResultGirlAnim(void)
	{
		return m_nAnimFlag;
	}
};

#endif	//!___SAMPLE_H___