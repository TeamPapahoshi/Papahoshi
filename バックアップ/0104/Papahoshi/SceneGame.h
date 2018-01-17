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
#include "Net.h"
#include "Net_Type2.h"

// ステージ
#include "StageManager.h"

// このステージで使うオブジェクト
#include "BG.h"
#include "NormalStars.h"
#include "FixedStars.h"


// 呼び出す星の数
#define STAR_NUM		(5)	//仮
#define FIXED_STAR_NUM	(1)	//仮

//------------------------------
// クラス定義
//------------------------------
//----シーンゲーム-----
class cSceneGame :public cBaseScene{

public:
	//---- プロトタイプ宣言 ----
	void Draw();	//描画
	void Update();	//更新
	cSceneGame();	//コンストラクタ
	~cSceneGame();	//デストラクタ

private:
	// このシーンでインスタンスするもののポインタ
	cBG*				m_pBG;
	cNet *pNet;

	vector<cNormalStar*>		m_pNomalStar;		// モブ星
	vector<cFixedStar*>			m_pFixedStar;		// 恒星
	
	cStageManager*				m_pStageManager;	// ステージマネージャー
};

#endif //!___SCENE_TITLE_H___