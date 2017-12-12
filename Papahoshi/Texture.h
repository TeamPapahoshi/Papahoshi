//======================================================================
//	Texture
//
//	概要＿：テクスチャー管理
//	制作者：加藤 遼
//	
//======================================================================
#ifndef ___TEXTURE_H___
#define ___TEXTURE_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>		//HRESULT他
#include "debugproc.h"		//printdebug
#include<vector>
#include<iostream>
#include "Common.h"
#include"SceneManeger.h"




//-----------------------------
// グローバル
//-----------------------------

// 名前空間の指定
using namespace std;


//-----------------------------
//クラス定義
//-----------------------------
//---- テクスチャー管理クラス ------
// クラス定義
class cTextureManager {
public:

	// ここにも追加
	enum TEX_TITLE{
		TEX_TITLE_KING_JELLY,
		TEX_TITLE_JELLY,
		TEX_TITLE_MAX
	};
	enum TEX_GAME{
		TEX_GAME_JELLY,
		TEX_GAME_STAR_LIGHT,
		TEX_GAME_STAR,
		TEX_GAME_FE,
		TEX_GAME_FE02,
		TEX_GAME_NET,
		TEX_GAME_UKI,
		TEX_GAME_ARROW,
		TEX_GAME_MAX
	};
	/*
	enum TEX_SAMPLE{
	TEX_SAMPLE_ENEMY,
	TEX_SAMPLE_MAX
	};
	*/

	// テクスチャを読み込む
	void LoadTexture(cSceneManeger::SCENE scene);

	// テクスチャを取得する
	static LPDIRECT3DTEXTURE9* GetTextureTitle(TEX_TITLE texNum);
	static LPDIRECT3DTEXTURE9* GetTextureGame(TEX_GAME texNum);

	cTextureManager(){}
	~cTextureManager(){}

private:
	static vector<LPDIRECT3DTEXTURE9> p_texture;	// テクスチャのポインタの動的配列
};

#endif	//!___TEXTURE_H___