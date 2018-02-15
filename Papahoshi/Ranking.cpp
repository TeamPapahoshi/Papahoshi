//======================================================================
//	Ranking.cpp
//	
//	概要＿：ランキング表示
//	制作者：安藤 光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include "Ranking.h"
#include "debugproc.h"		//printdebug
#include "Texture.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define DEFAULT_SCORE (1000)			//デフォルトのスコアの値

#define	RANKING_SIZE_X		(40.0f)		// 順位表示の数字の幅
#define	RANKING_SIZE_Y		(40.0f)		// 順位表示の数字の高さ
#define	RANKING_INTERVAL_X	(0.0f)		// 順位表示の数字の横方向表示間隔
#define	RANKING_INTERVAL_Y	(5.0f)		// 順位表示の数字の縦方向表示間隔

#define RANKING_POS_X       (50.0f)		// 順位の表示横座標
#define RANKING_POS_Y       (180.0f)		// 順位の表示縦座標

#define RANKING_SCORE_POS_X (RANKING_POS_X + RANKING_SIZE_X * 4)	// スコアの表示横座標
#define RANKING_SCORE_POS_Y (RANKING_POS_Y)							// スコアの表示縦座標

#define NUMBER_TEX_DIVIDE_X (10)
#define NUMBER_TEX_DIVIDE_Y (1)

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------

//-----------------------------
//グローバル
//-----------------------------


//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cRanking::cRanking(){

	//ファイルの読み込み(失敗したらデフォルトデータの設定)
	if (!ReadRanking())
	{
		int defaultdata = DEFAULT_SCORE;

		for (int dataloop = MAX_RANKING; dataloop > 0; dataloop--)
		{
			m_nScoreData[dataloop - 1] = defaultdata;

			defaultdata += DEFAULT_SCORE;
		}
	}

	//値の初期化
	for (int Initloop = 0; Initloop < MAX_RANKING; Initloop++)
	{
		//順位表示スプライトの初期化
		for (int Rankloop = 0; Rankloop < MAX_RANK; Rankloop++)
		{
			m_RankSprite[Initloop][Rankloop].SetPos(D3DXVECTOR2(RANKING_POS_X + ((RANKING_SIZE_X + RANKING_INTERVAL_X) * Rankloop),
																RANKING_POS_Y + ((RANKING_SIZE_Y + RANKING_INTERVAL_Y) * Initloop)));
			m_RankSprite[Initloop][Rankloop].SetSize(D3DXVECTOR2(RANKING_SIZE_X, RANKING_SIZE_Y));
			m_RankSprite[Initloop][Rankloop].SetTexture(cTextureManeger::GetTextureResult(TEX_NUMBER));
			m_RankSprite[Initloop][Rankloop].SetTexPatternDevide(NUMBER_TEX_DIVIDE_X, NUMBER_TEX_DIVIDE_Y);
		}

		//スコア表示スプライトの初期化
		for (int Scoreloop = 0; Scoreloop < MAX_SCORE; Scoreloop++)
		{
			m_ScoreSprite[Initloop][Scoreloop].SetPos(D3DXVECTOR2(RANKING_SCORE_POS_X + ((RANKING_SIZE_X + RANKING_INTERVAL_X) * Scoreloop),
																   RANKING_SCORE_POS_Y + ((RANKING_SIZE_Y + RANKING_INTERVAL_Y) * Initloop)));
			m_ScoreSprite[Initloop][Scoreloop].SetSize(D3DXVECTOR2(RANKING_SIZE_X, RANKING_SIZE_Y));
			m_ScoreSprite[Initloop][Scoreloop].SetTexture(cTextureManeger::GetTextureResult(TEX_NUMBER));
			m_ScoreSprite[Initloop][Scoreloop].SetTexPatternDevide(NUMBER_TEX_DIVIDE_X, NUMBER_TEX_DIVIDE_Y);
		}

		//番号スプライトの設定
		SetNumber(&m_RankSprite[Initloop][MAX_RANK - 1], Initloop + 1, MAX_RANK);
		SetNumber(&m_ScoreSprite[Initloop][MAX_SCORE - 1], m_nScoreData[Initloop], MAX_SCORE);

	}
}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cRanking::~cRanking(){

	//ファイルへの書き込み
	WriteRanking();
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cRanking::Update(){
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cRanking::Draw(){

	//スプライトの表示
	for (int Drawloop = 0; Drawloop < MAX_RANKING; Drawloop++)
	{
		//順位の表示
		for (int Rankloop = 0; Rankloop < MAX_RANK; Rankloop++)
		{
			m_RankSprite[Drawloop][Rankloop].Draw();
		}

		//スコアの表示
		for (int Scoreloop = 0; Scoreloop < MAX_SCORE; Scoreloop++)
		{
			m_ScoreSprite[Drawloop][Scoreloop].Draw();
		}
	}

}

//=======================================================================================
//
//		番号テクスチャの設定
//
//=======================================================================================
void cRanking::SetNumber(cSpriteParam* data,int num, int digit){

	int nTempNumber;	//表示する桁


	for (int loop = digit ; 0 < digit; digit--, data--)
	{
		//一番下の桁数を抽出
		nTempNumber = num % 10;

		//一番下の桁を表示する番号としてセット
		data->SetCurrentAnimPattern(nTempNumber);

		//桁を一つ右にずらす
		num = num / 10;
	}
}

//=======================================================================================
//
//		ランキングデータの入れ替え
//
//=======================================================================================
void cRanking::SortRanking(){

}

//=======================================================================================
//
//		ランキングデータの読み込み
//
//=======================================================================================
bool cRanking::ReadRanking(){

	ifstream ifs;	//ファイル読み込み用

	//ファイルの展開
	ifs.open("data/Ranking/Ranking.bin", ios_base::in | ios_base::binary);

	//失敗したらfalseを返してデフォルトデータの設定
	if (!ifs) {
		return false;
	}

	//ファイルの中身を読み込み
	ifs.read((char*)m_nScoreData, sizeof(int) * MAX_RANKING);

	//ファイル読み込みに成功
	return true;

	//ファイルは自動的に閉じられる
}

//=======================================================================================
//
//		ランキングデータの書き込み
//
//=======================================================================================
void cRanking::WriteRanking(){

	ofstream ofs;	//ファイル書き込み用
	
	//ファイルを新規作成して書き込み開始
  	ofs.open("data/Ranking/Ranking.bin", ios_base::out | ios_base::trunc | ios_base::binary);
	
	//char*型に変換してスコア情報の書き込み
	ofs.write((char*)m_nScoreData, sizeof(int) * MAX_RANKING);

	//ファイルは自動的に閉じられる
}