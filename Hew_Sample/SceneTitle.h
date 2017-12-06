//======================================================================
//	Title
//	
//	概要＿：タイトル(仮)
//	制作者：
//	
//======================================================================

#ifndef ___SCENE_TITLE_H___
#define ___SCENE_TITLE_H___

//------------------------------
// インクルードファイル
//------------------------------
#include "SceneManeger.h"
#include <d3d9.h>




//------------------------------
// マクロ定義
//------------------------------
#define TEXTURE_FILNAME_ENEMY ("Image/Character/KingJelly.jpg")
#define TEXTURE_FILNAME_PLAYER ("Image/Character/Jelly.png")

//------------------------------
// クラス定義
//------------------------------
//----シーンタイトル-----
class cSceneTitle :public cBaseScene{

public:
	void Draw();	//描画
	void Update();	//更新
	cSceneTitle();	//コンストラクタ
	~cSceneTitle();	//デストラクタ

	// このシーンで使うテクスチャ
	enum Texture{
		PLAYER,
		ENEMY,
		MAX_TEXTURE,
	};

	void LoadTextureFromFile();	// テクスチャの読み込み

private:
	LPDIRECT3DTEXTURE9 m_pTex[MAX_TEXTURE];	// このシーンで使うテクスチャのポインタ配列

};
#endif //!___SCENE_TITLE_H___