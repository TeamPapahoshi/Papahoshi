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
		TEX_TITLE_SPHERE_LIGHT,
		TEX_TITLE_STAR_LIGHT,
		TEX_TITLE_SHIP,
		TEX_TITLE_WAVE,
		TEX_TITLE_ROGO01,
		TEX_TITLE_ROGO02,
		TEX_TITLE_ROGO03,
		TEX_TITLE_ROGO04,
		TEX_TITLE_ROGO05,
		TEX_TITLE_ROGO06,
		TEX_TITLE_ROGO07,
		TEX_TITLE_ROGO08,
		TEX_TITLE_ROGO09,
		TEX_TITLE_ROGO10,
		TEX_TITLE_ROGO11,
		TEX_TITLE_RYUSEI,
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
		TEX_GAME_GAGE,
		TEX_GAME_GAGEFLAME,
		TEX_GAME_SPACE_ROCK,
		TEX_GAME_EFFECT_SPARKLE,

		TEX_GAME_0,
		TEX_GAME_1,
		TEX_GAME_2,
		TEX_GAME_3,
		TEX_GAME_4,
		TEX_GAME_5,
		TEX_GAME_6,
		TEX_GAME_7,
		TEX_GAME_8,
		TEX_GAME_9,

		TEX_GAME_RYUSEI,

		TEX_KIRA_CIRCLE1,
		TEX_KIRA_CIRCLE2,
		TEX_KIRA_CIRCLE3,
		TEX_KIRA_PENTAGON1,
		TEX_KIRA_PENTAGON2,
		TEX_KIRA_LIGHT1,
		TEX_KIRA_LIGHT2,
		TEX_KIRA_CRYSTAL1,
		TEX_KIRA_CRYSTAL2,

		TEX_GAME_BLUE_STAR_ANIM,
		TEX_GAME_YELLOW_STAR_ANIM,
		TEX_GAME_GREEN_STAR_ANIM,
		TEX_GAME_PINK_STAR_ANIM,

		TEX_ANU_START,
		TEX_ANU_FEVER,
		TEX_ANU_FINISH,

		TEX_THEER_1,
		TEX_THEER_2,
		TEX_THEER_3,
		TEX_THEER_4,
		TEX_THEER_5,

		TEX_GAME_EXPLOSION,
		TEX_GAME_CYAN_METEOR,
		TEX_GAME_PINK_METEOR,
		TEX_GAME_PLANET03,

		TEX_GAME_MAX
	};

	enum TEX_RESULT{
		TEX_NUMBER,

		TEX_RESULT_0,
		TEX_RESULT_1,
		TEX_RESULT_2,
		TEX_RESULT_3,
		TEX_RESULT_4,
		TEX_RESULT_5,
		TEX_RESULT_6,
		TEX_RESULT_7,
		TEX_RESULT_8,
		TEX_RESULT_9,

		TEX_RESULT_GIRL_MAX_1,
		TEX_RESULT_GIRL_MAX_2,

		TEX_RESULT_GIRL_MIN_1,
		TEX_RESULT_GIRL_MIN_2,
		TEX_RESULT_GIRL_MIN_3,
		TEX_RESULT_GIRL_MIN_4,

		TEX_RESULT_EFFECT_SPARKLE,

		TEX_RESULT_FONT_SCORE,
		TEX_RESULT_FONT_RANK,
		TEX_RESULT_FONT_NEWRECORD,

		TEX_RESULT_BLUE_STAR_ANIM,
		TEX_RESULT_YELLOW_STAR_ANIM,
		TEX_RESULT_GREEN_STAR_ANIM,
		TEX_RESULT_PINK_STAR_ANIM,

		TEX_RESULT_MAX
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
	static LPDIRECT3DTEXTURE9* GetTextureResult(TEX_RESULT texNum);

	cTextureManeger(){}
	~cTextureManeger(){}

private:
	static vector<LPDIRECT3DTEXTURE9> p_texture;	// テクスチャのポインタの動的配列
};

#endif	//!___TEXTURE_H___