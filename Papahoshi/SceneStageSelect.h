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

	cStageSelect* GetStage(void);	//ステージ情報の取得用(暫定)

private:

};
#endif //!___SCENE_STAGESELECT_H___