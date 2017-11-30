//======================================================================
//	Scenegame
//	
//	概要＿：ゲームメイン(仮)
//	制作者：
//	
//======================================================================

#ifndef ___SCENE_GAME_H___
#define ___SCENE_GAME_H___

//------------------------------
// インクルードファイル
//------------------------------
#include "SceneManeger.h"

//------------------------------
// クラス定義
//------------------------------
//----シーンゲーム-----
class cSceneGame :public cBaseScene{

public:
	void Draw();	//描画
	void Update();	//更新
	cSceneGame();	//コンストラクタ
	~cSceneGame();	//デストラクタ

	// このシーンで使うテクスチャ
	enum Texture{
		MAX_TEXTURE,
	};

	void LoadTextureFromFile();

private:
	//LPDIRECT3DTEXTURE9 m_pTex[MAX_TEXTURE];	// このシーンで使うテクスチャのポインタ配列


};
#endif //!___SCENE_TITLE_H___