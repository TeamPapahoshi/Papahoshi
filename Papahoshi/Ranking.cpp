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

//-----------------------------
//マクロ定義
//-----------------------------
#define DEFAULT_SCORE (1000)			//デフォルトのスコアの値

#define	RANKING_SIZE_X		(35.0f)		// ランキングスコアの数字の幅
#define	RANKING_SIZE_Y		(50.0f)		// ランキングスコアの数字の高さ
#define	RANKING_INTERVAL_X	(0.0f)		// ランキングスコアの数字の横方向表示間隔
#define	RANKING_INTERVAL_Y	(10.0f)		// ランキングスコアの数字の縦方向表示間隔

#define RANKING_POS_X       (50.0f)		// ランキングスコアの表示横座標
#define RANKING_POS_Y       (50.0f)		// ランキングスコアの表示縦座標

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
//		初期化
//
//=======================================================================================
void cRanking::Init(){

	//ファイルの読み込みに失敗したらデフォルトデータの設定
	if (!ReadRanking())
	{
		int defaultdata = DEFAULT_SCORE;

		for (int dataloop = MAX_RANKING; dataloop > 0; dataloop--)
		{
			m_nScoreData[dataloop - 1] = defaultdata;

			defaultdata += DEFAULT_SCORE;
		}
	}
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cRanking::UnInit(){

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
	for (int drawloop = 0; drawloop < MAX_RANKING; drawloop++)
	{
		PrintDebugProc("ランキング%d位:%d\n", drawloop + 1, m_nScoreData[drawloop]);
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

	return true;
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

}