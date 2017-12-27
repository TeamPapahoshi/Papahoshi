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
#include "Star.h"
#include "TitleRogo.h"
#include "TitleWave.h"
#include "TitleShip.h"

//------------------------------
// マクロ定義
//------------------------------
#define TEXTURE_FILNAME_ENEMY ("Image/Character/KingJelly.jpg")
#define TEXTURE_FILNAME_PLAYER ("Image/Character/Jelly.png")

#define CIRCLE_ORBIT_STAR_NUM (2)

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
	cTitleRogo* pTitleRogo;
	cTitleWave* pTitleWave;
	cTitleShip* pTitleShip;
	cCircleOrbitStar*	pCircleOrbitStar[CIRCLE_ORBIT_STAR_NUM];

};
#endif //!___SCENE_TITLE_H___