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
#include "GameMain.h"	// エフェクトクラス取得用

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

	int m_nScoreEffectFlame;	//エフェクト生成フレーム
	HSVCOLOR m_aEffectColorData;//エフェクトの色情報(HSV形式)
	int m_nHSVColor;			//HSVの色相
	bool m_bHSVChange;			//HSVの色相切り替えフラグ

	int  m_nScoreAlpha;			//スコアのアルファ値
	bool m_bScoreAlphaChange;	//スコアのアルファ値切り替えフラグ
	int  m_nChangeScorePoint;	//スコアの変更された場所
	bool m_bChangeScoreFlag;	//スコアが変更されたかのフラグ

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

	//	スコア更新フラグの引き渡し
	bool GetChangeScoreFlag(void)
	{
		return m_bChangeScoreFlag;
	}
};

#endif	//!___RANKING_H___