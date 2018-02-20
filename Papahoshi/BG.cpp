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
#define BG_STAR        ("Image/BG/bgstar.jpg")
#define BG_RESULT	   ("Image/BG/bgresult.jpg")

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
		break;
	case GAME_MAIN:
		break;
	case GAME_SKY:
		//sprite.LoadTexture(BG_FILNAME_SKY);
		sprite.SetVtxColorOne(D3DXCOLOR(0, 0, 0, 255), 0);
		sprite.SetVtxColorOne(D3DXCOLOR(0, 0, 0, 255), 1);
		sprite.SetVtxColorOne(D3DXCOLOR(0, 0, 0, 255), 2);
		sprite.SetVtxColorOne(D3DXCOLOR(0, 0, 0, 255), 3);
		break;
	case RESULT:
		sprite.LoadTexture(BG_RESULT);
		sprite.SetVtxColor(D3DXCOLOR(128,128,128,255));
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

	if (!a)
		i += 1.0f;

	else 
		i -= 1.0f;

	if (i >= 200){
		a = true;
	}
	if (i <= 0){
		a = false;
	}

	sprite.SetVtxColorOne(D3DXCOLOR(0, 0, 0, 255), 0);
	sprite.SetVtxColorOne(D3DXCOLOR(0, 0, i, 255), 1);
	sprite.SetVtxColorOne(D3DXCOLOR(0, 0, 0, 255), 2);
	sprite.SetVtxColorOne(D3DXCOLOR(0, 0, 0, 255), 3);
}

//=======================================================================================
//
//	
//	描画
//	
//	
//=======================================================================================
void cBG::Draw(){

	sprite.Draw();
}