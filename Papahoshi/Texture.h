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
#include <vector>
#include <iostream>
#include "debugproc.h"
#include "Common.h"
#include "SceneManeger.h"

//-----------------------------
// グローバル
//-----------------------------

//-----------------------------
// 列挙体
//-----------------------------
//***************************************
// シーンごとのテクスチャのポインタ番号
//***************************************
	enum TEX_TITLE{
		TEX_TITLE_KING_JELLY,
		TEX_TITLE_JELLY,
		TEX_TITLE_SPHERE_LIGHT,
		TEX_TITLE_SHIP,
		TEX_TITLE_WAVE,
		TEX_TITLE_MAX
	};

enum TEX_STAGE_SELECT{
	TEX_STAGESELECT_STAGE,
	TEX_STAGESELECT_KING_JELLY,
	TEX_STAGESELECT_MAX
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
		TEX_GAME_HALFCIRCLE,
		TEX_GAME_BLACK_HOLE,
		TEX_GAME_MAX
	};
	/*
	enum TEX_SAMPLE{
	TEX_SAMPLE_ENEMY,
	TEX_SAMPLE_MAX
	};
	*/



//-----------------------------
//クラス定義
//-----------------------------
//---- テクスチャー管理クラス ------
class cTextureManeger {
public:

	// テクスチャを読み込む
	void LoadTexture(cSceneManeger::SCENE scene);

	// テクスチャを取得する
	static LPDIRECT3DTEXTURE9* GetTextureTitle(TEX_TITLE texNum);
	static LPDIRECT3DTEXTURE9* GetTextureStageSelect(TEX_STAGE_SELECT texNum);
	static LPDIRECT3DTEXTURE9* GetTextureGame(TEX_GAME texNum);

	cTextureManeger(){}
	~cTextureManeger(){}

private:
	static vector<LPDIRECT3DTEXTURE9> p_texture;	// テクスチャのポインタの動的配列
};

#endif	//!___TEXTURE_H___