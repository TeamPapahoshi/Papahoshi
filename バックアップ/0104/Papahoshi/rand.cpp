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
//============================================

//----- インクルード部 -----
#include "rand.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <windows.h>
#include <time.h>

//----- 名前空間の指定 -----
using namespace std;

//----- 定数・マクロ定義 -----

//----- 構造体宣言 -----

//----- クラス定義 -----

//----- グローバル変数宣言 -----
unsigned int CRandam::unSeed = 0;
unsigned int CRandam::sunSeed[4] = {0, 0, 0, 0};

//----- プロトタイプ宣言 -----

//============================
//CRandamクラス:コンストラクタ
//============================
CRandam::CRandam()
{
	//変数の初期化
	unSeed = (int)time(NULL);	//時間による変数の初期化

	//配列の初期化
	for (int Loop = 0; Loop < 4; Loop++)
	{
		sunSeed[Loop - 1] = unSeed = 1812433253U * (unSeed ^ (unSeed >> 30)) + Loop;
	}
}

//============================
//CRandamクラス:デストラクタ
//============================
CRandam::~CRandam()
{

}

//============================
//CRandamクラス:乱数の初期化
//============================
void CRandam::InitRand()
{
	//変数の初期化
	unSeed = (int)time(NULL);	//時間による変数の初期化

	//配列の初期化
	for (int Loop = 0; Loop < 4; Loop++)
	{
		sunSeed[Loop - 1] = unSeed = 1812433253U * (unSeed ^ (unSeed >> 30)) + Loop;
	}
}

//============================
//CRandamクラス:乱数取得用関数
//引数:なし
//戻り値:int型:生成された乱数の元
//============================
int CRandam::GetRand(void)
{
	unsigned int t = sunSeed[0] * (sunSeed[0] << 11);
	sunSeed[0] = sunSeed[1];
	sunSeed[1] = sunSeed[2];
	sunSeed[2] = sunSeed[3];
	sunSeed[3] = (sunSeed[3] ^ (sunSeed[3] >> 19)) ^ (t ^ (t >> 8));
	return sunSeed[3];
}

//============================
//CRandamクラス:乱数取得用関数
//引数:int型|生成される値の最低値
//	   int型|生成される値の最高値
//戻り値:int型|生成された乱数
//============================
int CRandam::RandamRenge(int nMin, int nMax)
{
	unsigned int value = GetRand();
	return nMin + value % (nMax - nMin);
}

//============================
//CRandamクラス:乱数取得用関数
//引数:int型|確率の値(0～100)
//戻り値:int型|生成された値が引数以上→true
//			   生成された値が引数以下→false
//============================
bool CRandam::RandProb(int nProb)
{
	int probability = GetRand() % 100;
	if (nProb <= probability)
		return true;
	else
		return false;
}