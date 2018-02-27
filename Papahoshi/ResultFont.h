//======================================================================
//	ResultFont
//	
//	概要＿：リザルト画面文字表示
//	制作者：安藤 光樹
//	
//======================================================================
#ifndef ___RESULTFONT_H___
#define ___RESULTFONT_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Common.h"

//----- 他クラスからのインクルード -----
#include "Ranking.h"

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
class cResultFont
{
private:	//外部から参照不可能
	cSpriteParam m_cScoreFont;
	cSpriteParam m_cRankFont;
	cSpriteParam m_cNewRecordFont;

	cRanking*    m_pRanking;

	int			 m_nNewRecordAlpha;
	bool		 m_bNewRecordAlphaChangeFlag;

	//-----------------------------
protected:	//クラス内でのみ参照可能

	//-----------------------------
public:		//外部から参照可能

	cResultFont();	//コンストラクタ
	~cResultFont();	//デストラクタ

	void Update(void);
	void Draw(void);

	void GetRankingData(cRanking* data)
	{
		m_pRanking = data;
	}
};

#endif	//!___SAMPLE_H___