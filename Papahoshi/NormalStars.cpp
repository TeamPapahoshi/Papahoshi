//======================================================================
//	Star
//	
//	概要＿：星処理
//	制作者：加藤　遼
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>
#include <math.h>
#include "debugproc.h"
#include "Common.h"
#include "Texture.h"

#include "NormalStars.h"
#include <fstream>


//-----------------------------
//マクロ定義
//-----------------------------



//****************************************************************************************************************
// 普通の星
//****************************************************************************************************************
//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cNormalStar::cNormalStar(){

	// Sprite
	m_sprite.SetPos(D3DXVECTOR2(0.0f, 0.0f));
	m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR));
	m_sprite.SetVtxColorA(200);

}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cNormalStar::~cNormalStar(){

}
//=======================================================================================
//
//		更新
//
//=======================================================================================
void cNormalStar::Update(){

	// 座標更新
	m_sprite.SetPos(moveCircle.GetMove());

}
//=======================================================================================
//
//		描画
//
//=======================================================================================
void cNormalStar::Draw(){
	m_sprite.Draw();
}

//=======================================================================================
//
//		星の設定
//
//=======================================================================================
void cNormalStar::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

	moveCircle.SetCenter(center);
	moveCircle.SetRadius(radius);
	m_sprite.SetSize(size);
	moveCircle.SetSpped(second);

}

//=======================================================================================
//
//		星が見えるか見えないかの設定
//
//=======================================================================================
void cNormalStar::StarVisibility(float distance){

	// α値の変化
	m_sprite.SetVtxColorA(255 / distance * 15);
	
}



//=======================================================================================
//
//		星のファイル読み込み
//
//=======================================================================================
void cNormalStar::SetStarFromFile(int loop){


	// 読込専用でファイルを開く
	fstream file;
	file.open("data/StarData/NormalStarData_Stage1.bin", ios::binary | ios::in);


	// ステージの星の数に合わせてリサイズ
	// 今後はステージ番号は外からもらう
	switch (stageNum){

	case STAGE_01:
		a_Data.resize(STAGE_01_STAR_NUM);
		break;

	default:
		break;
	}


	// 読込
	for (int i = 0; i < (int)a_Data.size(); i++){
		file.read((char*)&a_Data[i], sizeof(a_Data[i]));
	}

	// 読み込んだデータの引数番目を代入する
	Set(a_Data[loop].center, a_Data[loop].radius, a_Data[loop].size, a_Data[loop].speed);
}



//控え
/*m_pNomalStar[0]->Set(D3DXVECTOR2(100, 100), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
m_pNomalStar[1]->Set(D3DXVECTOR2(200, 250), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
m_pNomalStar[2]->Set(D3DXVECTOR2(300, 200), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
m_pNomalStar[3]->Set(D3DXVECTOR2(700, 400), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
m_pNomalStar[4]->Set(D3DXVECTOR2(500, 500), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
*/