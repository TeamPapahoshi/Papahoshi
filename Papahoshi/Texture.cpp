//======================================================================
//	Texture
//	
//	概要：テクスチ管理
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
#define TEXTURE_FILNAME_KING_JELLY ("Image/Character/KingJelly.jpg")
#define TEXTURE_FILNAME_JELLY     ("Image/Character/Jelly.png")


//-----------------------------
// グローバル
//-----------------------------
//----Title-----
vector<char*> texTitle = {
	TEXTURE_FILNAME_KING_JELLY,
	TEXTURE_FILNAME_JELLY
};

//----Game-----
vector<char*> texGame = {
	TEXTURE_FILNAME_JELLY,
};

/*
//----Sample-----
vector<char*> texSample = {
TEXTURE_FILNAME_JELLY,
};

*/

// テクスチャのポインタ
vector<LPDIRECT3DTEXTURE9>  cTextureManager::p_texture(1,NULL);



//=======================================================================================
//
//		シーンごとのテクスチャのロード
//		引数	シーン
//
//=======================================================================================
void cTextureManager::LoadTexture(cSceneManeger::SCENE scene){

	//----------------------------
	//ローカル変数宣言
	//----------------------------
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// Direct3Dデバイス
	vector<char*> filename;						// ファイル名格納


	//-----シーンによって読み込むテクスチャを分ける-----
	switch (scene){

	case cSceneManeger::TITLE:

		// ファイル名をセット
		filename = texTitle;

		// テクスチャのポインタのリサイズ
		p_texture.resize(TEX_TITLE_MAX);
	

		// ロード
		for (int i = 0; i < TEX_TITLE_MAX; i++){
			D3DXCreateTextureFromFile(pDevice, filename[i], &p_texture[i]);
		}
		break;

	case cSceneManeger::GAME:

		// ファイル名をセット
		filename = texGame;

		// テクスチャのポインタのリサイズ
		p_texture.resize(TEX_GAME_MAX);

		// ロード
		for (int i = 0; i < TEX_GAME_MAX; i++){
			D3DXCreateTextureFromFile(pDevice, filename[i], &p_texture[i]);
		}
		break;

		/*
		case cSceneManeger::SAMPLE:
			// ファイル名をセット
			filename = texSample;
		
			// テクスチャのポインタのリサイズ
			p_texture.resize(TEX_SAMPLE_MAX);

		for (int i = 0; i < TEX_SAMPLE_MAX; i++){
			D3DXCreateTextureFromFile(pDevice, filename[i], &p_texture[i]);
			}
		break;
		*/

		int i;
		for (; i < 5; i++){


		}
	default:
		break;
	}
}


//=======================================================================================
//
//		シーンごとのテクスチャの取得
//
//=======================================================================================
LPDIRECT3DTEXTURE9* cTextureManager::GetTextureTitle(TEX_TITLE texNum){
	return &p_texture[texNum];
}

LPDIRECT3DTEXTURE9* cTextureManager::GetTextureGame(TEX_GAME texNum){
	return &p_texture[texNum];
}

