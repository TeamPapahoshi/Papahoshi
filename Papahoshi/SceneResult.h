//======================================================================
//	Title
//	
//	概要＿：リザルト(仮)
//	制作者：
//	
//======================================================================

#ifndef ___SCENE_RESULT_H___
#define ___SCENE_RESULT_H___

//------------------------------
// インクルードファイル
//------------------------------
#include "SceneManeger.h"
#include <d3d9.h>

//------ 使用するオブジェクト -------
#include "Ranking.h"
#include "BG.h"
#include "ResultGirl.h"
#include "ResultFont.h"
#include "ResultStar.h"

//------------------------------
// マクロ定義
//------------------------------

//------------------------------
// クラス定義
//------------------------------
//----シーンタイトル-----
class cSceneResult :public cBaseScene{

public:
	void Draw();	//描画
	void Update();	//更新
	cSceneResult();	//コンストラクタ
	~cSceneResult();	//デストラクタ

private:
	cRanking*	 m_pRanking;
	cBG*		 m_pBG;
	cResultgirl* m_pResultgirl;
	cResultFont* m_pResultFont;
	cResultStar* m_pResultStar;

	int          m_nResultBGMFlame;
	bool		 m_bBGMFlag;
};
#endif //!___SCENE_RESULT_H___