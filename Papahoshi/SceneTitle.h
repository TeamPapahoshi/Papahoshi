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


private:

};
#endif //!___SCENE_TITLE_H___