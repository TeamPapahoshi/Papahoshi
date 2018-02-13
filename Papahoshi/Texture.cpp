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
#define TEXTURE_FILNAME_KING_JELLY		("Image/Character/KingJelly.jpg")
#define TEXTURE_FILNAME_JELLY			("Image/Character/Jelly.png")
#define TEXTURE_FILNAME_STAR_LIGHT		("Image/Star/light.png")
#define TEXTURE_FILNAME_STAR			("Image/Star/Star.png")
#define TEXTURE_FILNAME_RYUSEI			("Image/Star/Ryusei.jpg")
#define TEXTURE_FILNAME_EF				("Image/Star/Effect.png")
#define TEXTURE_FILNAME_EF02			("Image/Star/Effect2.png")
#define TEXTURE_FILENAME_NET			("Image/Net/Net.png")
#define TEXTURE_FILENAME_UKI			("Image/Net/uki.jpg")
#define TEXTURE_FILENAME_ARROW			("Image/Net/arrow.png")
#define TEXTURE_FILENAME_HALFCIRCLE		("Image/Net/half.png")
#define TEXTURE_FILENAME_BLACK_HOLE		("Image/Star/blackhole.png")
#define TEXTURE_FILENAME_SPACE_ROCK		("Image/Star/SpaceRock.png")
#define TEXTURE_FILENAME_SPHERE_LIGHT	("Image/Collision/Circle/Circle.png")
#define TEXTURE_FILENAME_SHIP			("data/texture/gyosen_big.png")
#define TEXTURE_FILENAME_WAVE			("data/texture/line_wave1.png")
#define TEXTURE_FILENAME_GAGE			("Image/GAGE/gage1.png")
#define TEXTURE_FILENAME_GAGEFLAME		("Image/GAGE/gageflamecover2.png")
#define TEXTURE_FILENAME_EFFECT_SPARKLE ("Image/Pirticle/kirakira2.png")
#define TEXTURE_FILENAME_SHIP			("data/texture/gyosen_big.png")
#define TEXTURE_FILENAME_WAVE			("data/texture/line_wave1.png")
#define TEXTURE_FILENAME_GAGE			("Image/GAGE/gage1.png")
#define TEXTURE_FILENAME_GAGEFLAME		("Image/GAGE/gageflamecover2.png")

//キラキラ
#define TEXTURE_FILENAME_CIRCLE1	("Image/Pirticle/S__109092866.jpg")
#define TEXTURE_FILENAME_CIRCLE2	("Image/Pirticle/S__109092868.jpg")
#define TEXTURE_FILENAME_CIRCLE3	("Image/Pirticle/S__109092873.jpg")
#define TEXTURE_FILENAME_PENTAGON1	("Image/Pirticle/S__109092867.jpg")
#define TEXTURE_FILENAME_PENTAGON2	("Image/Pirticle/S__109092874.jpg")
#define TEXTURE_FILENAME_LIGHT1		("Image/Pirticle/S__109092870.jpg")
#define TEXTURE_FILENAME_LIGHT2		("Image/Pirticle/S__109092869.jpg")
#define TEXTURE_FILENAME_CRYSTAL1	("Image/Pirticle/S__109092871.jpg")
#define TEXTURE_FILENAME_CRYSTAL2	("Image/Pirticle/S__109092872.jpg")

// タイトルロゴ
#define TEXTURE_FILENAME_ROGO01 ("Image/ROGO/logo_01.png")
#define TEXTURE_FILENAME_ROGO02 ("Image/ROGO/logo_02.png")
#define TEXTURE_FILENAME_ROGO03 ("Image/ROGO/logo_03.png")
#define TEXTURE_FILENAME_ROGO04 ("Image/ROGO/logo_04.png")
#define TEXTURE_FILENAME_ROGO05 ("Image/ROGO/logo_05.png")
#define TEXTURE_FILENAME_ROGO06 ("Image/ROGO/logo_06.png")
#define TEXTURE_FILENAME_ROGO07 ("Image/ROGO/logo_07.png")
#define TEXTURE_FILENAME_ROGO08 ("Image/ROGO/logo_08.png")
#define TEXTURE_FILENAME_ROGO09 ("Image/ROGO/logo_09.png")
#define TEXTURE_FILENAME_ROGO10 ("Image/ROGO/logo_10.png")
#define TEXTURE_FILENAME_ROGO11 ("Image/ROGO/logo_11+12.png")

#define TEXTURE_FILENAME_STAGECLEAR		("data/texture/akira000.png")	//仮のテクスチャ
#define TEXTURE_FILENAME_SHIP			("data/texture/gyosen_big.png")
#define TEXTURE_FILENAME_WAVE			("data/texture/line_wave1.png")
#define TEXTURE_FILENAME_STAGECLEAR		("data/texture/akira000.png")	//仮のテクスチャ
#define TEXTURE_FILENAME_0				("Image/GameUI/0.png")
#define TEXTURE_FILENAME_1				("Image/GameUI/1.png")
#define TEXTURE_FILENAME_2				("Image/GameUI/2.png")
#define TEXTURE_FILENAME_3				("Image/GameUI/3.png")
#define TEXTURE_FILENAME_4				("Image/GameUI/4.png")
#define TEXTURE_FILENAME_5				("Image/GameUI/5.png")
#define TEXTURE_FILENAME_6				("Image/GameUI/6.png")
#define TEXTURE_FILENAME_7				("Image/GameUI/7.png")
#define TEXTURE_FILENAME_8				("Image/GameUI/8.png")
#define TEXTURE_FILENAME_9				("Image/GameUI/9.png")

// 星スプライト
#define TEXTURE_FILENAME_BULE_STAR_ANIM		("Image/Star/buleStarAnim.png")

//アナウンス
#define TEXTURE_FILENAME_ANU_START		("Image/GameUI/start!.png")
#define TEXTURE_FILENAME_ANU_FIEVER		("Image/GameUI/fever!.png")
#define TEXTURE_FILENAME_ANU_FINISH		("Image/GameUI/finish!.png")


//-----------------------------
// グローバル
//-----------------------------
//----Title-----
vector<char*> texTitle = {
	TEXTURE_FILNAME_KING_JELLY,
	TEXTURE_FILNAME_JELLY,		// 同じ画像でもシーンが違うときはもう一回書いて
	TEXTURE_FILENAME_SPHERE_LIGHT,
	TEXTURE_FILENAME_SHIP,
	TEXTURE_FILENAME_WAVE,
	TEXTURE_FILENAME_ROGO01,
	TEXTURE_FILENAME_ROGO02,
	TEXTURE_FILENAME_ROGO03,
	TEXTURE_FILENAME_ROGO04,
	TEXTURE_FILENAME_ROGO05,
	TEXTURE_FILENAME_ROGO06,
	TEXTURE_FILENAME_ROGO07,
	TEXTURE_FILENAME_ROGO08,
	TEXTURE_FILENAME_ROGO09,
	TEXTURE_FILENAME_ROGO10,
	TEXTURE_FILENAME_ROGO11,
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
	TEXTURE_FILENAME_HALFCIRCLE,
	TEXTURE_FILENAME_BLACK_HOLE,
	TEXTURE_FILENAME_GAGE,
	TEXTURE_FILENAME_GAGEFLAME,
	TEXTURE_FILENAME_SPACE_ROCK,
	TEXTURE_FILENAME_EFFECT_SPARKLE,
	TEXTURE_FILENAME_0,
	TEXTURE_FILENAME_1,
	TEXTURE_FILENAME_2,
	TEXTURE_FILENAME_3,
	TEXTURE_FILENAME_4,
	TEXTURE_FILENAME_5,
	TEXTURE_FILENAME_6,
	TEXTURE_FILENAME_7,
	TEXTURE_FILENAME_8,
	TEXTURE_FILENAME_9,
	TEXTURE_FILNAME_RYUSEI,
	TEXTURE_FILENAME_CIRCLE1,
	TEXTURE_FILENAME_CIRCLE2,
	TEXTURE_FILENAME_CIRCLE3,
	TEXTURE_FILENAME_PENTAGON1,
	TEXTURE_FILENAME_PENTAGON2,
	TEXTURE_FILENAME_LIGHT1,
	TEXTURE_FILENAME_LIGHT2,
	TEXTURE_FILENAME_CRYSTAL1,
	TEXTURE_FILENAME_CRYSTAL2,
	TEXTURE_FILENAME_BULE_STAR_ANIM,
	TEXTURE_FILENAME_ANU_START,
	TEXTURE_FILENAME_ANU_FIEVER,
	TEXTURE_FILENAME_ANU_FINISH,
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

