//======================================================================
//	Scenegame
//	
//	概要＿：シーンゲーム
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
#include <fstream>
#include <vector>
#include "BaseStar.h"
#include "Transition.h"
#include "SceneManeger.h"
#include "sound.h"
#include "Common.h"

//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneGame::cSceneGame() : 
m_bHurryUp(false)
{

	// 網
	m_pNet = new cNet();

	// ブラックホール
	m_pBlackHole = new cBlackHole();
	m_pBlackHole->SetNetData(m_pNet);

	// 隕石
	m_pSpaceRock = new cSpaceRock();
	m_pSpaceRock->SetNetData(m_pNet);

	// サンプル
	m_pSampleStar = new cSampleStar();

	// 流星
	m_pRyusei = new cRyusei();
	m_pRyusei->SetNetData(m_pNet);

	// ゲージ
	m_pGage = new cGage();
	m_pGage->Init();

	// モブ星
	m_pNomalStar = new cNormalStar();
	m_pNomalStar->SetBlackHoleData(m_pBlackHole);
	m_pNomalStar->SetNetData(m_pNet);
	m_pNomalStar->SetGageData(m_pGage);

	// 星群れ
	m_pConsellation = new cConstellation();


	// UI
	m_pGameUI = new cGameUI();

	// タイマー
	m_pTimer = new cTimer();

	// 背景
	m_pBG = new cBG();
	m_pBG->SetBG(cBG::GAME_SKY);

	//プレイサポート
	m_pPlaySupport = new cPlaySupport();


	// ゲームの状態
#ifndef _DEBUG_DKIP_
	m_eGameState = GAME_STATE_SET;
#else
	m_eGameState = GAME_STATE_MAIN;
#endif
	m_bFever = false;


	//---- BGMの再生 ----
	PlaySound(SOUND_LABEL::SOUND_LABEL_BGM_GAME);
	SetVolume(GAME_BGM_VOLUME, SOUND_LABEL::SOUND_LABEL_BGM_GAME);
	SetVolume(FEVER_BGM_VOLUME, SOUND_LABEL::SOUND_LABEL_BGM_GAME_FEVER);

#ifndef _DEBUG_DKIP_
	//アナウンスのセット
	m_pAnnounce = new cAnnounce(cAnnounce::eAnnounceType::Start);
#endif
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cSceneGame::~cSceneGame(){

	// デリート
	delete m_pBG;
	delete m_pNomalStar;
	delete m_pSpaceRock;
	delete m_pRyusei;
	delete m_pGage;
	delete m_pBlackHole;
	delete m_pSampleStar;
	delete m_pNet;
	delete m_pGameUI;
	delete m_pTimer;
	delete m_pConsellation;
	delete m_pPlaySupport;

	//----- BGMの停止 -----
	StopSound(SOUND_LABEL::SOUND_LABEL_BGM_GAME);
	StopSound(SOUND_LABEL::SOUND_LABEL_BGM_GAME_FEVER);
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneGame::Update(){

	// ゲームの状態で分岐
	switch (m_eGameState)
	{
	case GAME_STATE_SET:
		SetUpdate();
		break;
	case GAME_STATE_MAIN:		// ここも関数にしてもいいかも
		MainUpdate();
		break;
	case GAME_STATE_END:
		EndUpdate();
		break;
	default:
		break;
	}
	
	// ↓すべての状態で更新↓

	// シーン更新
	if (GetKeyboardTrigger(DIK_G)){
		m_eGameState = GAME_STATE_MAIN;
	}
	// シーン更新
	if (GetKeyboardTrigger(DIK_SPACE)){
		cSceneManeger::ChangeScene(cSceneManeger::RESULT);
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cSceneGame::Draw(){


	// ゲームの状態で分岐(分ける必要ないかも)
	switch (m_eGameState)
	{
	case GAME_STATE_SET:
		PrintDebugProc("━━ゲームの状態━━\n");
		PrintDebugProc("SET\n");
		PrintDebugProc("Gキーでメインへ\n");
		PrintDebugProc("━━━━━━━━━━\n");
		break;
	case GAME_STATE_MAIN:
		PrintDebugProc("━━ゲームの状態━━\n");
		PrintDebugProc("MAIN\n");
		m_bFever ? PrintDebugProc("Fever\n") : PrintDebugProc("Normal\n");
		PrintDebugProc("Gキーでメインへ\n");
		PrintDebugProc("FキーでFEVER or NORMAL\n");
		PrintDebugProc("━━━━━━━━━━\n");
		break;
	case GAME_STATE_END:
		PrintDebugProc("━━ゲームの状態━━\n");
		PrintDebugProc("END\n");
		PrintDebugProc("Gキーでメインへ\n");
		PrintDebugProc("━━━━━━━━━━\n");
		break;
	default:
		break;
	}

	m_pBG->Draw();				// 背景
	m_pBlackHole->Draw();
	m_pSampleStar->Draw();
	m_pNomalStar->Draw();
	m_pSpaceRock->Draw();
	m_pRyusei->Draw();
	//m_pConsellation->Draw();
	m_pNet->Draw();

	m_pGameUI->Draw();
	m_pGage->Draw();
	m_pTimer->Draw();
	m_pPlaySupport->Draw();

	if (m_pAnnounce)
		m_pAnnounce->Draw();
}


//============================================
//
// SET
//
//============================================
void cSceneGame::SetUpdate(){

	m_pGameUI->Update();

	if (!cTransition::FinishCall())
		return;

	m_pAnnounce->Update();

	//アナウンス終了で次へ
	if (m_pAnnounce->CallFin()){
		delete m_pAnnounce;
		m_pAnnounce = NULL;
		m_eGameState = GAME_STATE_MAIN;
		m_pTimer->StartCountDown(LIMIT_TIME);
	}

}

//============================================
//
// MAIN
//
//============================================
void cSceneGame::MainUpdate(){

	m_pNet->Update();			// あみ
	m_pBG->Update();			// 背景
	m_pGage->Update();			// ゲージ
	m_pGameUI->Update();		// UI
	m_pTimer->Update();			// タイマー

	//--- 星 -----後でまとめる
	m_pNomalStar->Update();
	m_pBlackHole->Update();
	m_pSpaceRock->Update();
	m_pSampleStar->Update();
	m_pRyusei->Update();
	m_pConsellation->Update();

	m_pPlaySupport->Update(m_pNet->GetGamePhase(), m_pNet->GetAllPress(), m_pNet->GetRevor());


	//----- 残り時間で生成する星を指定 --------
	if (m_pTimer->GetTime() == 50){
		m_pBlackHole->SetCreateStart();

	}

	//----- 残り時間で生成する星を指定 --------
	if (m_pTimer->GetTime() == 40){
		m_pSpaceRock->SetCreateStart();

	}





	CheckCollision();			//当たり判定
	

#ifndef _DEBUG_DKIP_
	//アナウンスの更新
	if (m_pAnnounce){
		m_pAnnounce->Update();
		if (m_pAnnounce->CallFin()){
			delete m_pAnnounce;
			m_pAnnounce = NULL;
		}
	}
	//ゲーム終了でアナウンスを呼ぶ
	if(!(m_pTimer->GetTime())){
		m_pAnnounce = new cAnnounce(cAnnounce::eAnnounceType::Finish);
		m_eGameState = GAME_STATE_END;
	}
#endif


	//---- FEVERスタート ------
	if (m_pGage->GetFeverStart()){

		m_bFever = true;
		m_pGage->SetFeverStart(false);
		m_pRyusei->SetFeverStar();
		
		//--- アナウンス呼び出し -----
		if (m_bFever)
			m_pAnnounce = new cAnnounce(cAnnounce::eAnnounceType::Fever);

		//--- BGM変更 ---
		StopSound(SOUND_LABEL::SOUND_LABEL_BGM_GAME);
		PlaySound(SOUND_LABEL::SOUND_LABEL_BGM_GAME_FEVER);

		//---- UI変更 ----
		m_pGameUI->SetTheerMotion(cTheerGirl::eGirlMotion::FEVER);
		m_pGameUI->SetUiType(cGameUI::eUItype::FEVER);
	}

	//---- Fever終了 ------
	if (m_pGage->GetFeverFin()){

		m_bFever = false;
		m_pGage->SetFeverFin(false);
		m_pRyusei->SetFeverEnd();

		//--- BGM変更 ---
		StopSound(SOUND_LABEL::SOUND_LABEL_BGM_GAME_FEVER);
		PlaySound(SOUND_LABEL::SOUND_LABEL_BGM_GAME);

		//---- UI変更 ----
		m_pGameUI->SetTheerMotion(cTheerGirl::eGirlMotion::NOMAL);
		if (m_bHurryUp)
			m_pGameUI->SetUiType(cGameUI::eUItype::HURRY_UP);
		else
			m_pGameUI->SetUiType(cGameUI::eUItype::NOMAL);
	}

	//---- Hurry Up! -----
	if (m_pTimer->GetTime() <= 5 && !m_bHurryUp){
		m_bHurryUp = true;
		if (!m_bFever)
			m_pGameUI->SetUiType(cGameUI::eUItype::HURRY_UP);
	}

	
	if (GetKeyboardTrigger(DIK_F)){
		m_bFever ? m_bFever = false : m_bFever = true;
		if (m_bFever)
			m_pAnnounce = new cAnnounce(cAnnounce::eAnnounceType::Fever);
	}
	
}

//============================================
//
// END
//
//============================================
void cSceneGame::EndUpdate(){

	m_pGameUI->Update();

	if (!m_pAnnounce)
		return;

	m_pAnnounce->Update();

	//アナウンス終了で次へ
	if (m_pAnnounce->CallFin())
	{
		delete m_pAnnounce;
		m_pAnnounce = NULL;
		cSceneManeger::ChangeSceneSetTransition(cSceneManeger::SCENE::RESULT, cTransition::TRANSITION_TYPE::TRANSITION_DICE_SCALE_CHANGE);
	}

}



//============================================
//
// 当たり判定を取得
//
//============================================
void cSceneGame::CheckCollision(){


	// 後できれいにまとめる
	//************************************************************************************************************************************

	  //---網とモブ星の判定type2---
	  for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		  if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			  continue;

		  for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			  if (m_pNet->GetPullFlug()){
				  if (CheckCollisionCircleToLine(m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos, 
					  m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetLeft(), m_pNet->GetNetCenter())||
					  CheckCollisionCircleToLine(m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					  m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetCenter(), m_pNet->GetNetRight())){

					  m_pNomalStar->OnCollidToNet(nCountStar);
				  }
			  }
		  }
	  }


	  //---網と流星の判定type2---
	  for (int nCountStar = 0; nCountStar < m_pRyusei->GetMaxNum(); nCountStar++){

		  if (!m_pRyusei->GetStarData()[nCountStar].m_bUse)
			  continue;

		  for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			  if (m_pNet->GetPullFlug()){
				  if (CheckCollisionCircleToLine(m_pRyusei->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					  m_pRyusei->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetLeft(), m_pNet->GetNetCenter()) ||
					  CheckCollisionCircleToLine(m_pRyusei->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					  m_pRyusei->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetCenter(), m_pNet->GetNetRight())){

					  m_pRyusei->OnCollidToNet(nCountStar);
				  }
			  }


			  // 網の範囲内にいるときの処理
			  if (cCollider::CheckCollisionCircleToTriangle(m_pRyusei->GetStarData()[nCountStar].m_Collision, m_pNet->GetCollider()[nCountNet])){

				  m_pRyusei->OnCollidToNetArea(nCountStar);
			  }

			  if (!cCollider::CheckCollisionCircleToTriangle(m_pRyusei->GetStarData()[nCountStar].m_Collision, m_pNet->GetCollider()[0])
				  && !cCollider::CheckCollisionCircleToTriangle(m_pRyusei->GetStarData()[nCountStar].m_Collision, m_pNet->GetCollider()[1])){

				  m_pRyusei->SetStream(true, nCountStar);
			  }
		  
			 
		  }
		  
	  }

	  //---網と隕石の判定type2---
	  for (int nCountStar = 0; nCountStar < m_pSpaceRock->GetMaxNum(); nCountStar++){

		  if (!m_pSpaceRock->GetStarData()[nCountStar].m_bUse)
			  continue;

		  for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			  if (m_pNet->GetPullFlug()){
				  if (CheckCollisionCircleToLine(m_pSpaceRock->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					  m_pSpaceRock->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetLeft(), m_pNet->GetNetCenter()) ||
					  CheckCollisionCircleToLine(m_pSpaceRock->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					  m_pSpaceRock->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetCenter(), m_pNet->GetNetRight())){

					  m_pSpaceRock->OnCollidToNet(nCountStar);
				  }
			  }
		  }
	  }

	  //---網とブラックホールのの判定type2---
	  for (int nCountStar = 0; nCountStar < m_pBlackHole->GetMaxNum(); nCountStar++){

		  if (!m_pBlackHole->GetStarData()[nCountStar].m_bUse)
			  continue;

		  for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			  if (m_pNet->GetPullFlug()){
				  if (CheckCollisionCircleToLine(m_pBlackHole->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					  m_pBlackHole->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetLeft(), m_pNet->GetNetCenter()) ||
					  CheckCollisionCircleToLine(m_pBlackHole->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					  m_pBlackHole->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetCenter(), m_pNet->GetNetRight())){

					  m_pBlackHole->OnCollidToNet(nCountStar);
				  }
			  }
		  }
	  }

	  //************************************************************************************************************************************

	  //モブ星とブラックホール
	  for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		  if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			  continue;

		  for (int nCountBlackHole = 0; nCountBlackHole < m_pBlackHole->GetMaxNum(); nCountBlackHole++){

			  if (!m_pBlackHole->GetStarData()[nCountBlackHole].m_bUse)
				  continue;

			  // 吸い込み範囲
			  if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, m_pBlackHole->GetStarData()[nCountBlackHole].m_VacumeRange)){
				  m_pNomalStar->OnCollidToBlackHoleVacumeRange(nCountStar, nCountBlackHole);
			  }
			  // 削除範囲
			  if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, m_pBlackHole->GetStarData()[nCountBlackHole].m_DeleteRange)){
				  m_pNomalStar->OnCollidToBlackHoleDeleteRange(nCountStar, nCountBlackHole);

			  }
		  }
	  }

	  //モブ星と流星
	  for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		  if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			  continue;

		  for (int nCountSpaceRock = 0; nCountSpaceRock < m_pSpaceRock->GetMaxNum(); nCountSpaceRock++){

			  if (!m_pSpaceRock->GetStarData()[nCountSpaceRock].m_bUse)
				  continue;

			  if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, m_pSpaceRock->GetStarData()[nCountSpaceRock].m_Collision)){
				  m_pNomalStar->OnCollidToSpaceRock(nCountStar);
				  m_pSpaceRock->OnCollidToNormalStar(nCountSpaceRock);
			  }
			
		  }
	  }
}