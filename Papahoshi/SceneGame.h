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

// このシーンで使うオブジェクト
#include "BG.h"
#include "Star.h"

#define STAR_NUM		(5)	//仮
#define FIXED_STAR_NUM	(1)	//仮

//------------------------------
// クラス定義
//------------------------------
//----シーンゲーム-----
class cSceneGame :public cBaseScene{

public:
	//---- 列挙型宣言 ----
	enum GAME_PHASE{	//ゲームフェイズ
		PHASE_POST,	//構え
		PHASE_SHOUT,	//飛ばし
		PHASE_PULL,		//引く

		PHASE_MAX,
	};

	//---- プロトタイプ宣言 ----
	void Draw();	//描画
	void Update();	//更新
	cSceneGame();	//コンストラクタ
	~cSceneGame();	//デストラクタ

	GAME_PHASE GetGamePhase();

private:
	// このシーンでインスタンスするもののポインタ
	cBG*				m_pBG;
	cCircleOrbitStar*	pStar[STAR_NUM];
	cFixedStar*			pFixedStar[FIXED_STAR_NUM];

	GAME_PHASE			m_gamePhase;	//ゲームフェイズを保管

};
#endif //!___SCENE_TITLE_H___