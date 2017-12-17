//======================================================================
//	Texture
//	
//	概要：テクスチャ管理
//		使い方 
//		グローバルにあるシーンごとのファイル名用配列に、マクロで定義した
//		ファイルを追加していく
//		ヘッダーにあるシーンごとのenumにもファイル名と同じ名前で追加
//		
//		シーンごとでファイルを読み込むので同じファイル名でもシーンごとに
//		追加してください
//
//		またゲット用関数もシーンごとに分けたので注意してください
//
//		あと背景とか明らかに同じシーンで複数回ロードしないとわかっているものは
//		sprite.LoadTextureで直接ロードしたほうがいいかも
//
//	制作者：加藤 遼
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>		//HRESULT他
#include "debugproc.h"		//printdebug
#include<vector>
#include<iostream>
#include "Common.h"
#include"SceneManeger.h"
#include"Texture.h"


//-----------------------------
// マクロ
//-----------------------------
// テクスチャファイル
#define TEXTURE_FILNAME_KING_JELLY	("Image/Character/KingJelly.jpg")
#define TEXTURE_FILNAME_JELLY		("Image/Character/Jelly.png")
#define TEXTURE_FILNAME_STAR_LIGHT	("Image/Star/light.png")
#define TEXTURE_FILNAME_STAR		("Image/Star/Star.png")
#define TEXTURE_FILNAME_EF			("Image/Star/Effect.png")
#define TEXTURE_FILNAME_EF02		("Image/Star/Effect2.png")
#define TEXTURE_FILENAME_NET		("Image/Net/Net.png")
#define TEXTURE_FILENAME_UKI		("Image/Net/uki.jpg")
#define TEXTURE_FILENAME_ARROW		("Image/Net/arrow.png")

#define TEXTURE_FILENAME_STAGECLEAR  ("data/texture/akira000.png")	//仮のテクスチャ

//-----------------------------
// グローバル
//-----------------------------
//----Title-----
vector<char*> texTitle = {
	TEXTURE_FILNAME_KING_JELLY,
	TEXTURE_FILNAME_JELLY,		// 同じ画像でもシーンが違うときはもう一回書いて
};

//----StageSelect-----
vector<char*> texStageSelect = {
	TEXTURE_FILENAME_STAGECLEAR,// 同じ画像でもシーンが違うときはもう一回書いて
	TEXTURE_FILNAME_JELLY,
};

//----Game-----
vector<char*> texGame = {
	TEXTURE_FILNAME_JELLY,		// 同じ画像でもシーンが違うときはもう一回書いて
	TEXTURE_FILNAME_STAR_LIGHT,
	TEXTURE_FILNAME_STAR,
	TEXTURE_FILNAME_EF,
	TEXTURE_FILNAME_EF02,
	TEXTURE_FILENAME_NET,
	TEXTURE_FILENAME_UKI,
	TEXTURE_FILENAME_ARROW,
};

/*
//----Sample-----
vector<char*> texSample = {
TEXTURE_FILNAME_JELLY,
};

*/

// テクスチャのポインタ
vector<LPDIRECT3DTEXTURE9>  cTextureManeger::p_texture(1,NULL);	// 初期化(要素数,中身)


//=======================================================================================
//
//		シーンごとのテクスチャのロード
//		引数	シーン
//
//=======================================================================================
void cTextureManeger::LoadTexture(cSceneManeger::SCENE scene){

	//----------------------------
	//ローカル変数宣言
	//----------------------------
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// Direct3Dデバイス
	vector<char*> filename;						// ファイル名格納

	// 初期化処理
	p_texture.clear();
	p_texture.shrink_to_fit();	// 確保したメモリを配列のサイズに合わせる
	filename.clear();
	filename.shrink_to_fit();	// 確保したメモリを配列のサイズに合わせる


	//-----シーンによって読み込むテクスチャを分ける-----
	switch (scene){

	case cSceneManeger::TITLE:
		filename = texTitle;	// ファイル名をセット
		break;
	case cSceneManeger::STAGE_SELECT:
		filename = texStageSelect;	// ファイル名をセット
		break;
	case cSceneManeger::GAME:
		filename = texGame;		// ファイル名をセット
		break;
		/*
		case cSceneManeger::SAMPLE:
			// ファイル名をセット
			filename = texSample;
		*/
	default:
		break;
	}

	// テクスチャのポインタのリサイズ
	p_texture.resize(filename.size());

	// ロード
	for (int i = 0; i < (int)filename.size(); i++){
		D3DXCreateTextureFromFile(pDevice, filename[i], &p_texture[i]);
	}
}


//=======================================================================================
//
//		シーンごとのテクスチャの取得
//
//=======================================================================================
LPDIRECT3DTEXTURE9* cTextureManeger::GetTextureTitle(TEX_TITLE texNum){	//タイトル
	return &p_texture[texNum];
}

LPDIRECT3DTEXTURE9* cTextureManeger::GetTextureStageSelect(TEX_STAGE_SELECT texNum){	//ステージセレクト
	return &p_texture[texNum];
}

LPDIRECT3DTEXTURE9* cTextureManeger::GetTextureGame(TEX_GAME texNum){	//ゲームメイン
	return &p_texture[texNum];
}

