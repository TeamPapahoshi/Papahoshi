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
#include "Score.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define DEFAULT_SCORE (1000)			//デフォルトのスコアの値(閾値)

#define RANKING_EFFECT_FLAME (10)		//エフェクト生成のフレーム閾値
#define EFFECT_LIFE_TIME     (40)		//エフェクトの生存フレーム
#define EFFECT_SIZE          (50.0f)
#define EFFECTCOLOR_CHANGE_POINT (3)	//エフェクトの色切り替え閾値

#define	RANKING_SIZE_X		(55.0f)		// 順位表示の数字の幅
#define	RANKING_SIZE_Y		(55.0f)		// 順位表示の数字の高さ
#define	RANKING_INTERVAL_X	(0.0f)		// 順位表示の数字の横方向表示間隔
#define	RANKING_INTERVAL_Y	(3.0f)		// 順位表示の数字の縦方向表示間隔

#define RANKING_POS_X       (120.0f)		// 順位の表示横座標
#define RANKING_POS_Y       (180.0f)		// 順位の表示縦座標

#define RANKING_SCORE_POS_X (RANKING_POS_X + RANKING_SIZE_X * 4)	// スコアの表示横座標
#define RANKING_SCORE_POS_Y (RANKING_POS_Y)							// スコアの表示縦座標

#define NUMBER_TEX_DIVIDE_X (10)
#define NUMBER_TEX_DIVIDE_Y (1)

#define RANKING_ALPHA_CHANGE_NUM (8)	//加減算されるアルファ値

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------

//-----------------------------
//グローバル
//-----------------------------
bool g_bDefaultScore = false;	//スコアのリセット用フラグ(trueにするとデフォルトの値がランキングに入る)

//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cRanking::cRanking(){

	//ファイルの読み込み(失敗したらデフォルトデータの設定)
	if (!ReadRanking() || g_bDefaultScore)
	//if (g_bDefaultScore)
	{
		int defaultdata = DEFAULT_SCORE;

		for (int dataloop = MAX_RANKING; dataloop > 0; dataloop--)
		{
			m_nScoreData[dataloop - 1] = defaultdata;

			defaultdata += DEFAULT_SCORE;
		}
	}
	//初期化処理
	m_nScoreAlpha = 255;
	m_nScoreEffectFlame = 0;
	m_nChangeScorePoint = 0;
	m_nHSVColor         = 0;
	m_bChangeScoreFlag = false;
	m_bScoreAlphaChange = false;
	m_bHSVChange = false;

	//ランキングの入れ替え
	SortRanking();

	//ランキングの入れ替えに応じてエフェクトの色設定
	if (m_nChangeScorePoint < EFFECTCOLOR_CHANGE_POINT)
	{
		m_aEffectColorData = {0, 255, 255};
	}
	else
	{
		m_aEffectColorData = {0, 0, 255};
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

	//ランキング変更フラグが立っていれば処理
	if (m_bChangeScoreFlag)
	{
		//エフェクト生成フレームの減算
		m_nScoreEffectFlame--;

		//ランキングの入れ替えが3位以上で行われていたら
		if (m_nChangeScorePoint < EFFECTCOLOR_CHANGE_POINT)
		{
			if (m_bHSVChange)
			{
				m_nHSVColor++;
			}
			else
			{
				m_nHSVColor--;
			}

			if (m_nHSVColor <= 0)
			{
				m_nHSVColor = 0;
				m_bHSVChange = true;
			}
			else if (m_nHSVColor >= 360)
			{
				m_nHSVColor = 360;
				m_bHSVChange = false;
			}


			//HSVの色情報に反映
			m_aEffectColorData.h = m_nHSVColor;
		}

		//エフェクト生成フレームが一定値に達したらエフェクト設定
		if (m_nScoreEffectFlame < 0)
		{
			GetEffectManeger()->SetEffectSparkle(cTextureManeger::GetTextureResult(TEX_RESULT_EFFECT_SPARKLE),
				m_ScoreSprite[m_nChangeScorePoint][MAX_SCORE / 2].GetPos(),
				D3DXVECTOR2(EFFECT_SIZE, EFFECT_SIZE),
				m_aEffectColorData,
				EFFECT_LIFE_TIME,
				D3DXVECTOR2(RANKING_SIZE_X * (MAX_SCORE - 1), RANKING_SIZE_Y / 2),
				EFFECT_SPARKLE_TEX_DIVIDE_X, EFFECT_SPARKLE_TEX_DIVIDE_Y);

			if (m_nChangeScorePoint < EFFECTCOLOR_CHANGE_POINT)
			{
				m_nScoreEffectFlame = CRandam::RandamRenge(0, RANKING_EFFECT_FLAME);
			}
			else
			{
				m_nScoreEffectFlame = CRandam::RandamRenge(0, RANKING_EFFECT_FLAME * 3);
			}
		}

		//アルファ値が0ならα値の減算開始
		if (m_bScoreAlphaChange)
		{
			m_nScoreAlpha += RANKING_ALPHA_CHANGE_NUM;
		}
		else//アルファ値が最大値ならα値の減算開始
		{
			m_nScoreAlpha -= RANKING_ALPHA_CHANGE_NUM;
		}

		if (m_nScoreAlpha <= 0)
		{
			m_nScoreAlpha = 0;
			m_bScoreAlphaChange = true;
		}
		else if (m_nScoreAlpha >= 255)
		{
			m_nScoreAlpha = 255;
			m_bScoreAlphaChange = false;
		}


		//ランキング表示のα値の切り替え

		for (int Rankloop = 0; Rankloop < MAX_RANK; Rankloop++)
		{
			m_RankSprite[m_nChangeScorePoint][Rankloop].SetVtxColorA(m_nScoreAlpha);
		}

		for (int Scoreloop = 0; Scoreloop < MAX_SCORE; Scoreloop++)
		{
			m_ScoreSprite[m_nChangeScorePoint][Scoreloop].SetVtxColorA(m_nScoreAlpha);
		}
	}
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
void cRanking::SetNumber(cSpriteParam* data, int num, int digit){

	int nTempNumber;	//表示する桁


	for (int loop = digit; 0 < digit; digit--, data--)
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
	//現在スコア情報の受け取り
	int nScore = GetScore();

	//デバッグ用
	//nScore = 10000;

	//ランキングの最低スコアに満たない場合は処理をしない
	if (m_nScoreData[MAX_RANKING - 1] > nScore) return;

	//ランキングの変更される地点の確認処理
	for (int Checkloop = MAX_RANKING - 1; Checkloop >= 0; Checkloop--)
	{
		if (m_nScoreData[Checkloop] > nScore)
		{
			//保存されているスコアが現在スコアを上回るまでループし、上回ったらループの一つ前に現在スコアを保存
			//スコアの保存された場所を記録
			m_nChangeScorePoint = Checkloop + 1;

			//処理の終了
			break;

		}
		else if (m_nScoreData[0] <= nScore)
		{
			//保存されているスコアが現在スコアを上回らなかったら、配列の一番上に保存
			//スコアの保存される場所を記録
			m_nChangeScorePoint = 0;

			//処理の終了
			break;
		}

	}

	//ランキングの入れ替え処理
	for (int Changeloop = MAX_RANKING - 1; Changeloop >= m_nChangeScorePoint; Changeloop--)
	{
		//スコアの移動
		m_nScoreData[Changeloop] = m_nScoreData[Changeloop - 1];
	}
	//現在スコアの保存
	m_nScoreData[m_nChangeScorePoint] = nScore;

	m_bChangeScoreFlag = true;
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