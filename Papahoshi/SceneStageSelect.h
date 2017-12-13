//======================================================================
//	SceneStageSelect
//	
//	概要＿：ステージ選択画面
//	制作者：安藤 光樹
//	
//======================================================================

#ifndef ___SCENE_STAGESELECT_H___
#define ___SCENE_STAGESELECT_H___

//------------------------------
// インクルードファイル
//------------------------------
#include <d3d9.h>
#include "SceneManeger.h"
#include "StageSelect.h"

#define TEXTURE_FILENAME_STAGESELECT ("Image/Character/KingJelly.jpg")	//仮のテクスチャ
#define TEXTURE_FILENAME_STAGECLEAR  ("data/texture/akira000.png")	//仮のテクスチャ2

//------------------------------
// クラス定義
//------------------------------
//----シーンゲーム-----
class cSceneStageSelect :public cBaseScene{

public:
	void Draw();	//描画
	void Update();	//更新
	cSceneStageSelect();	//コンストラクタ
	~cSceneStageSelect();	//デストラクタ

	// このシーンで使うテクスチャ
	enum Texture{
		STAGESELECT_TEXTURE,
		STAGECLEAR_TEXTURE,
		MAX_TEXTURE
	};

	void LoadTextureFromFile();

	cStageSelect* GetStage(void);	//ステージ情報の取得用(暫定)

private:
	LPDIRECT3DTEXTURE9 m_pTex[MAX_TEXTURE];	// このシーンで使うテクスチャのポインタ配列


};
#endif //!___SCENE_STAGESELECT_H___