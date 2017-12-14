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
#include <d3d9.h>
#include "SceneManeger.h"
#include "Common.h"

// このシーンで使うオブジェクト
#include "BG.h"
#include "NormalStars.h"
#include "FixedStars.h"


#define STAR_NUM		(5)	//仮
#define FIXED_STAR_NUM	(1)	//仮

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

private:
	// このシーンでインスタンスするもののポインタ
	cBG*						m_pBG;			// 背景
	vector<cNormalStar*>		m_pNomalStar;	// モブ星
	vector<cFixedStar*>			m_pFixedStar;	// 恒星
	

};
#endif //!___SCENE_TITLE_H___