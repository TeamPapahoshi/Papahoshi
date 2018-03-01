//======================================================================
//	BG
//	
//	概要＿：背景
//			使いたいシーンでインスタンス化して、Initなどを呼び出して
//			セット
//	制作者：加藤　遼
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>		//HRESULT他
#include "debugproc.h"		//printdebug
#include "Common.h"

#include"BG.h"


//---------------------
// マクロ
//---------------------
#define BG_FILNAME_SKY ("Image/BG/black.png")
#define BG_STAR        ("Image/BG/bgstar3.png")
#define BG_RESULT	   ("Image/BG/bgresult3.png")

#define BG_ADD_TEXROLL_X (0.0007f)
#define BG_ADD_TEXROLL_Y (0.0004f)

float i=0;
bool	a=false;
//=======================================================================================
//
//
//		呼び出す背景の指定
//	
//
//=======================================================================================
void cBG::SetBG(BG bg){

	type = bg;

	sprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));

	// 背景は同じものを複数ロードしないのでここで直接ロードします
	switch (type)
	{
	case TITLE:
		sprite.LoadTexture(BG_STAR);
		sprite.SetHSVColorFlag(true);
		sprite.SetTexRollFlag(true);
		sprite.SetAddBlend(true);
		break;
	case GAME_MAIN:
		sprite.LoadTexture(BG_FILNAME_SKY);
		break;
	case GAME_SKY:
		sprite.SetVtxColor(D3DXCOLOR(0, 0, 0, 255));
		sprite.SetHSVColorFlag(true);
		//sprite.LoadTexture(BG_FILNAME_SKY);
		
		break;
	case RESULT:
		sprite.LoadTexture(BG_RESULT);
		sprite.SetVtxColor(D3DXCOLOR(192, 192, 192, 255));
		sprite.SetTexRollFlag(true);
		break;
	default:
		break;
	}


}

//=======================================================================================
//
//	
//	コンストラクタ
//	
//	
//=======================================================================================
cBG::cBG(){

	sprite.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
	sprite.SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	back.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
	back.SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	back.SetVtxColor(D3DXCOLOR(0, 0, 0, 255));
	type = TITLE;

}


//=======================================================================================
//
//	
//	デストラクタ
//	
//	
//=======================================================================================
cBG::~cBG(){


}

//=======================================================================================
//
//	
//	更新
//	
//	
//=======================================================================================
void cBG::Update(){

	switch (type)
	{

	case TITLE:
		//タイトル画面は普段は波の動きと同じ値で背景を動かす
		sprite.SetTexRollNumX(sprite.GetTexRollNumX() - BG_ADD_TEXROLL_X);

		if (!a)
			i += 1.0f;

		else
			i -= 1.0f;

		if (i >= 360){
			a = true;
		}
		if (i <= 0){
			a = false;
		}

		sprite.SetHSVColorOne(i, 155, 155, 0);
		sprite.SetHSVColorOne(i + 50, 155, 155, 1);
		sprite.SetHSVColorOne(i + 100, 155, 155, 2);
		sprite.SetHSVColorOne(i + 150, 155, 155, 3);
		break;
	case RESULT:
		//リザルト画面は一定の値を加算
		sprite.SetTexRollNumX(sprite.GetTexRollNumX() + BG_ADD_TEXROLL_X);
		sprite.SetTexRollNumY(sprite.GetTexRollNumY() - BG_ADD_TEXROLL_Y);

		break;
	default:
		break;

	}
	}

	


//=======================================================================================
//
//	
//	描画
//	
//	
//=======================================================================================
void cBG::Draw(){
	back.Draw();
	sprite.Draw();
}