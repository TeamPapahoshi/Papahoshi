//======================================================================
//	Scenegame
//	
//	概要＿：ゲームメイン(仮)
//	制作者：
//	
//======================================================================

//------------------------------
// インクルードファイル
//------------------------------
#include "SceneGame.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"


//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneGame::cSceneGame(){

	//----------------
	// インスタンス
	//----------------
	for (int i = 0; i < STAR_NUM; i++)			pStar[i] = new cCircleOrbitStar();	// 円軌道星
	for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i] = new cFixedStar();	// 恒星
	m_pBG = new cBG();	// 背景
	m_pPause = new cPause();

	//----------------
	// 初期化
	//----------------
	for (int i = 0; i < STAR_NUM; i++)	pStar[i]->Init();
	for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i]->Init();	// 恒星
	m_pBG->Init();
	m_pPause->Init();

	//----------------
	// セット
	//----------------
	// 星
	pStar[0]->SetCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(30.0f, 30.0f), 0);
	pStar[1]->SetCircleOrbitStar(D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 0);
	pStar[2]->SetCircleOrbitStar(D3DXVECTOR2(600.0f, 200.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 0);
	pStar[3]->SetCircleOrbitStar(D3DXVECTOR2(150.0f, 300.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 0);
	pStar[4]->SetCircleOrbitStar(D3DXVECTOR2(800, 400), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 0);

	// 恒星
	pFixedStar[0]->SetFixedStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 10);

	// 背景
	m_pBG->SetBG(cBG::GAME_SKY);

}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cSceneGame::~cSceneGame(){

	// 終了
	for (int i = 0; i < STAR_NUM; i++)			pStar[i]->UnInit();			// 円軌道星
	for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i]->UnInit();	// 恒星
	m_pBG->UnInit();	// 背景
	m_pPause->Uninit();	// ポーズ画面

	// デリート
	delete m_pBG;
	for (int i = 0; i < STAR_NUM; i++)			delete pStar[i];
	for (int i = 0; i < FIXED_STAR_NUM; i++)	delete pFixedStar[i];

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneGame::Update(){

	// 更新
	// ポーズ中は更新停止
	if (!m_pPause->GetPauseFlag())
	{
		for (int i = 0; i < STAR_NUM; i++)			pStar[i]->Update();			// 円軌道の星
		for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i]->Update();	// 恒星
		m_pBG->Update();	// 背景
	}
	m_pPause->Update();	// ポーズ画面

	// 見えるか見えないかの判定
	for (int i = 0; i < STAR_NUM; i++){
			pStar[i]->StarVisibility(CalculateDistanceAtoB(pStar[i]->GetPos(), pFixedStar[0]->GetPos()));
	}

	// シーン更新
	if (GetKeyboardTrigger(DIK_SPACE)){
		cSceneManeger::ChangeScene(cSceneManeger::TITLE);
	}

	m_pBG->Update();
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cSceneGame::Draw(){

	m_pBG->Draw();	// 背景
	for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i]->Draw();	// 恒星
	for (int i = 0; i < STAR_NUM; i++)			pStar[i]->Draw();		// 円軌道星
	m_pPause->Draw();	//ポーズ画面
}

