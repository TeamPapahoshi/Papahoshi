//======================================================================
//	Ranking.h
//	
//	概要＿：ランキング表示
//	制作者：安藤 光樹
//	
//======================================================================
#ifndef ___RANKING_H___
#define ___RANKING_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Common.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define MAX_RANKING (10)
#define MAX_SCORE (5)
#define MAX_RANK  (2)

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------
// 基底クラス:クラスサンプル
class cRanking
{
private:	//外部から参照不可能
	int m_nScoreData[MAX_RANKING];
	cSpriteParam m_ScoreSprite[MAX_RANKING][MAX_SCORE];
	cSpriteParam m_RankSprite[MAX_RANKING][MAX_RANK];

	int  m_nChangeScorePoint;
	bool m_bChangeScoreFlag;

	void SetNumber(cSpriteParam* sprite, int num, int digit);	//番号テクスチャの設定
	void SortRanking(void); //ランキングの入れ替え
	bool ReadRanking(void);	//ファイルデータからスコアの読み込み
	void WriteRanking(void);//ファイルデータにスコアの書き込み
	//-----------------------------
protected:	//クラス内でのみ参照可能

	//-----------------------------
public:		//外部から参照可能

	cRanking();	//コンストラクタ
	~cRanking();	//デストラクタ

	void Update(void);
	void Draw(void);
};

#endif	//!___RANKING_H___