//=====================================================
//
//	MasicSplitGirl		Score.cpp
//
//	Mei Goto.
//
//=====================================================


//-------------------------------
// インクルード部
//-------------------------------
#include "Score.h"
#include "Sprite.h"
#include "debugproc.h"
#include "Texture.h"

//-------------------------------
// 定数定義
//-------------------------------
#define DIGIT_SCORE		(6)		//スコア桁数
#define	DRAW_STAGING_SKIP_NUM	(7)		//スコア加算演出の1フレーム最大加算量
#define DRAW_STAGING_HISPEED_SKIP_NUM (77) //スコア加算演出の1フレーム加算量(高速)

#define HISPEED_CHANGE_LINE      (800) //スコア加算減算高速化の閾値

//-------------------------------
// グローバル変数
//-------------------------------
int	g_nScore;		//現在スコア
int g_nPrintScore;	//現在表示中のスコア

cSpriteParam g_aScoreSprite[DIGIT_SCORE];


//=================================================
//
//  スコア受け渡し
//
//=================================================
int GetScore(){
	return g_nScore;
}

//=================================================
//
// スコアセット
//
//=================================================
void SetScore(int score){
	g_nScore = score;
	g_nPrintScore = score;
}

//=================================================
//
// スコア加算
//
//=================================================
void AddScore(int score){
	g_nScore += score;
}

//=================================================
//
// 表示中のスコアのみリセット
//
//=================================================
void ResetPrintScore(){
	g_nPrintScore = 0;
}

//=================================================
//
// スコア描画
//
//=================================================
void DrawScore(D3DXVECTOR2 pos, D3DXVECTOR2 size){

	int work1, work2;
	work2 = g_nPrintScore;

	for (int i = DIGIT_SCORE - 1; i >= 0; i--)
	{
		//----- スコアのスプライト情報を更新 -----
		work1 = work2 % 10;
		work2 = work2 / 10;
		switch (cSceneManeger::GetSceneNum())
		{
		case cSceneManeger::GAME:
		case cSceneManeger::TRANING:
			g_aScoreSprite[i].SetTexture(cTextureManeger::GetTextureGame((TEX_GAME)(TEX_GAME_0 + work1)));
			break;
		case cSceneManeger::RESULT:
			g_aScoreSprite[i].SetTexture(cTextureManeger::GetTextureResult((TEX_RESULT)(TEX_RESULT_0 + work1)));
			break;
		default:
			break;
		}
		g_aScoreSprite[i].SetPos(D3DXVECTOR2(pos.x + (size.x * 0.8f) * i, pos.y));
		g_aScoreSprite[i].SetSize(size);

		//----- 描画 -----
		g_aScoreSprite[i].Draw();
	}

	//----- デバッグ表示 -----
	PrintDebugProc("スコア : %d\n", g_nPrintScore);
}

//==================================================
//
// スコア更新
//
//==================================================
void UpdateScore(){

	//---------- 加算・減算演出 ------------
	//加算
	if (g_nScore > g_nPrintScore){
		//差が一定値以上なら加算処理を高速化
		if (g_nScore - g_nPrintScore >= HISPEED_CHANGE_LINE)
			g_nPrintScore += DRAW_STAGING_HISPEED_SKIP_NUM;
		else
			g_nPrintScore += DRAW_STAGING_SKIP_NUM;
		if (g_nPrintScore > g_nScore)
			g_nPrintScore = g_nScore;	//値を同じに調整
	}
	//減算
	else if (g_nScore < g_nPrintScore){
		//差が一定値以上なら減算処理を高速化
		if (g_nPrintScore - g_nScore <= HISPEED_CHANGE_LINE)
			g_nPrintScore -= DRAW_STAGING_HISPEED_SKIP_NUM;
		else
			g_nPrintScore -= DRAW_STAGING_SKIP_NUM;
		if (g_nPrintScore < g_nScore)
			g_nPrintScore = g_nScore;	//値を同じに調整
	}

}