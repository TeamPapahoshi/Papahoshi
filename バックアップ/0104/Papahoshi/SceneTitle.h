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
#include "TitleRogo.h"
#include "TitleWave.h"
#include "TitleShip.h"
#include "Meteor.h"

//------------------------------
// マクロ定義
//------------------------------
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
	cMeteor*	pMeteor;
	//cCircleOrbitStar*	pCircleOrbitStar[CIRCLE_ORBIT_STAR_NUM];

};
#endif //!___SCENE_TITLE_H___