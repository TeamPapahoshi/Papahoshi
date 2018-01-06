//============================================
//
//	XorShift乱数生成関数ヘッダ
//	内容  :XorShiftによる乱数の生成と利用
//	対応  :rand.cpp	
//
//	作成日:2017/11/09
//	作成者:安藤 光樹
//
//--------------------------------------------
//	<更新内容>
//	2017/11/09	作成開始
//  2017/11/11  乱数生成関数の完成
//--------------------------------------------
//	<運用方法>
//	rand.hを使いたいcppにインクルードする
//	1.乱数の生成をしたい場合
//	CRandam::RandamRange(最小値,最大値)
//	2.確率の判定をしたい場合
//	CRandam::RandProb(確率)
//============================================

#ifndef _RAND_H_
#define _RAND_H_

//----- 定数・マクロ定義 -----

//----- 構造体宣言 -----

//----- クラス定義 -----

class CRandam
{
private:
	static unsigned int unSeed;	//乱数格納用変数
	static unsigned int sunSeed[4];//乱数生成用配列

//-------------------------------
protected:
	static int GetRand(void);		//乱数取得用関数
//-------------------------------
public:
	//コンストラクタ
	CRandam();
	//デストラクタ
	~CRandam();
	//初期化処理
	static void InitRand();
	//一定範囲内での乱数の生成
	static int RandamRenge(int nMin, int nMax);
	//確率による合否判定
	static bool RandProb(int nProb);
};

//----- 名前空間の指定 -----

//----- プロトタイプ宣言 -----

#endif