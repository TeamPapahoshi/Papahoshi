//======================================================================
//	Ryusei
//	
//	概要＿：流星処理
//	制作者：加藤　遼
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>
#include <math.h>
#include <fstream>
#include "debugproc.h"
#include "Common.h"
#include "Texture.h"
#include "Ryusei.h"
#include "rand.h"
#include "Input.h"
#include "MathEX.h"
#include <cmath>
#include "GameUI.h"
#include "sound.h"
#include "Score.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define STAR_SIZE				(160)
#define RESPAWN_FREAM			(200)
#define MAX_NORMAL_RYUSEI_NUM	(50)
#define MOVE_SPEED				(4.5f)
#define SCORE_RYUSEI			(100)


#define LIMIT_METEOR_NOT_FEVER	(1)


//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cRyusei::cRyusei(){

	// 乱数の初期化
	CRandam::InitRand();

	// 使用数を格納ファイルから読み込むけどだいぶ変更したから
	m_nMaxNum = MAX_NORMAL_RYUSEI_NUM;

	// 動的インスタンス
	m_pStarData = new cRyuseiData[m_nMaxNum]();		//ここ注意
	m_pRoot = m_pStarData;							// 先頭アドレス保存


	// 初期化
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// サイズの設定
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		
		// テクスチャの設定
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_CYAN_METEOR));
		m_pStarData->m_sprite.SetAnimationFlag(true);
		m_pStarData->m_sprite.SetTexPatternDevide(10, 1);
		m_pStarData->m_sprite.SetIntervalChangePattern(7);

		// 色
		m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));

		// 加算合成ON
		//m_pStarData->m_sprite.SetAddBlend(true);

		// 座標の決定
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT + STAR_SIZE, GAME_SCREEN_RIGHT + 200);
		CreateRamdomPos.y = -(float)CRandam::RandamRenge(0, 800);
		//CreateRamdomPos = D3DXVECTOR2(SCREEN_CENTER);
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);


		//--- 流れる処理のための準備 ---
		m_pStarData->m_bStream = true;
		m_pStarData->m_StreamStartPos = CreateRamdomPos;																// 初期生成位置をスタート位置に指定
		m_pStarData->m_StreamGoalPos  = D3DXVECTOR2(CreateRamdomPos.x - 250.0, CreateRamdomPos.y + SCREEN_HEIGHT);		// 画面左下をゴールに指定
		m_pStarData->m_VecStreamMove  = m_pStarData->m_StreamGoalPos - m_pStarData->m_StreamStartPos;					// スタートとゴールから流れる方向のベクトルを求める
		m_pStarData->m_StremCos		  = (fabs(m_pStarData->m_StreamStartPos.x - m_pStarData->m_StreamGoalPos.x)			// 計算用のcosを求める
										/ VectorSize(m_pStarData->m_VecStreamMove));
		m_pStarData->m_StreamRad	  = acosf(m_pStarData->m_StremCos);													// Cosから計算用の角度を求める
		m_pStarData->m_sprite.SetRad(D3DX_PI/2.0f - m_pStarData->m_StreamRad);											// 計算結果より回転角度をセット
		m_pStarData->m_MoveSpped      = MOVE_SPEED * UnitVector(m_pStarData->m_VecStreamMove);							// 流れる方向の単位ベクトルを求めて速さをセット


		//--- 流星の光 ------
		m_pStarData->m_MeteorLight.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR_LIGHT));
		m_pStarData->m_MeteorLight.SetAddBlend(true);
		m_pStarData->m_MeteorLight.SetSize(D3DXVECTOR2(60, 60));
		m_pStarData->m_MeteorLight.SetPos(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x - 17, m_pStarData->m_sprite.GetPos().y + 50));

		// 初期生成でいくつか
		if (m_nCurrentNum < LIMIT_METEOR_NOT_FEVER)
			m_pStarData->m_bCreateEvent = true;

	}
	m_bFever = false;
}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cRyusei::~cRyusei(){

	StopSound(SOUND_LABEL_SE_STREAM_METEOR);
	StopSound(SOUND_LABEL_SE_STAR_GET);
	// 先頭に戻す
	m_pStarData = m_pRoot;
	delete[] m_pStarData;
	m_pStarData = NULL;
	m_pRoot = NULL;
}
//=======================================================================================
//
//		更新
//
//=======================================================================================
void cRyusei::Update(){

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// 更新
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bUse)
			continue;

	
		// 当たり判定
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x, m_pStarData->m_sprite.GetPos().y+30), STAR_SIZE / 4.0f);

		m_pStarData->m_MeteorLight.SetPos(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x-17, m_pStarData->m_sprite.GetPos().y + 50));

		// 網の方向に移動するための処理
		m_pStarData->m_Destination   = m_pNetData->GetNetStart();
		m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());// 星から目的地方向の単位ベクトルを求める

		// アニメーション
		m_pStarData->m_sprite.AnimationLoop();

		// 流れる処理
		if (m_pStarData->m_bStream){
			m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_MoveSpped);
		}


		// 画面外に出たらフラグオフ
		if (m_pStarData->m_sprite.GetPosY() >= GAME_SCREEN_UNDER-80 || m_pStarData->m_sprite.GetPosX() <= GAME_SCREEN_LEFT){

			m_pStarData->m_bDestroyEvent = true;
			m_pStarData->m_eDestroyType = SCREEN_OUT;
			

			// 画面外にでてなおかつ網に獲得されてたら
			if (m_pStarData->m_bCaptured){
				m_pStarData->m_eDestroyType = CAPTURED_NET;
			}

		}
	}

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// イベント格納
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (m_pStarData->m_bCreateEvent){

			//---- フィーバ中は常に生成 -------
			if (m_bFever){
				Create();
			}

			//---- フィーバ中でないときは個数制限をして生成 -----
			if (!m_bFever && m_nCurrentNum < LIMIT_METEOR_NOT_FEVER){
				Create();
			}
			if (!m_bFever && m_nCurrentNum >= LIMIT_METEOR_NOT_FEVER){
				m_pStarData->m_bCreateEvent = false;
			}
		}

		if (m_pStarData->m_bDestroyEvent){
			Destroy();
		}

		if (m_pStarData->m_bRespawnEvent){
			Respawn();
		}

	}

	// すべての流星が使用されなくなったら効果音を止める
	if (m_nCurrentNum <= LIMIT_METEOR_NOT_FEVER && !m_bFever){
		StopSound(SOUND_LABEL_SE_STREAM_METEOR);
	}

	// イベントの起動
	// デバッグキー
	//if (GetKeyboardTrigger(DIK_R)){
	//	m_pStarData = m_pRoot;	// 先頭に戻す
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		m_pStarData->m_bDestroyEvent = true;
	//	}
	//}
	//if (GetKeyboardTrigger(DIK_K)){
	//	m_pStarData = m_pRoot;	// 先頭に戻す
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (m_pStarData->m_bDraw)	// ここ注意
	//			continue;
	//		m_pStarData->m_bCreateEvent = true;
	//		break;
	//	}
	//}
	//// デバッグキー
	//if (GetKeyboardTrigger(DIK_D)){
	//	m_pStarData = m_pRoot;	// 先頭に戻す
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (!m_pStarData->m_bUse)	// ここ注意
	//			continue;
	//		m_pStarData->m_bDestroyEvent = true;
	//		break;
	//	}
	//}

}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cRyusei::Draw(){

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// 描画
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bDraw)
			continue;

		m_pStarData->m_sprite.Draw();
		m_pStarData->m_MeteorLight.Draw();
		//m_pStarData->m_Collision.Draw();

	}

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// デバッグプリント
	PrintDebugProc("━━━━━━流星━━━━━━\n");
	PrintDebugProc("現在の数 %d/%d\n", m_nCurrentNum, m_nMaxNum);
	PrintDebugProc("リスポーンインターバル確認 %d/%d\n", m_pStarData->m_nRespawnFrame, RESPAWN_FREAM);
	PrintDebugProc("━━━━━━━━━━━━━━━\n");

}
//=======================================================================================
//
//		生成
//
//=======================================================================================
void cRyusei::Create(){

	if (m_pStarData->m_bUse)
		return;

	// 生成イベントの開始
	if (!m_pStarData->m_bCreateEnd){

		// ここ以外は同じ処理になるはずだからコピぺでいいはず
		//****** ここに演出とか生成処理を書いていく **********
		//m_pStarData->m_bUse = true;->これでもできるけど今回は数もかぞえておきたいから
		m_pStarData->m_bDraw = true;

		//****************************************************

		// 演出がおわったら生成終了フラグを立てる->if(EffectEnd()){m_pStar->....}
		//m_pStarData->m_bCreateEnd = true;

		m_pStarData->m_bCreateEnd = true;

	}


	// 生成終了フラグが立ったらリセットして終了
	if (m_pStarData->m_bCreateEnd){

		//	リセット
		m_pStarData->m_bCreateEnd = false;

		// フラグオン
		SetCountAndUse(true);
		m_pStarData->m_bCreateEvent = false;
		return;
	}
}


//=======================================================================================
//
//		削除(一応作った)
//
//=======================================================================================
void cRyusei::Destroy(){

	if (!m_pStarData->m_bUse)
		return;

	// 生成イベントの開始
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);

		// ここ以外は同じ処理になるはずだからコピぺでいいはず
		//****** ここに演出とか処理を書いていく **********
		//************************************************

		// 演出がおわったら終了フラグを立てる->if(EffectEnd()){m_pStar->....}
		m_pStarData->m_bDestroyEnd = true;

	}

	// 生成終了フラグが立ったらリセットして終了
	if (m_pStarData->m_bDestroyEnd){

		// 削除の種類によって処理を変更
		switch (m_pStarData->m_eDestroyType)
		{
		case SCREEN_OUT:
			break;
		case CAPTURED_NET:
			AddScore(SCORE_RYUSEI);
			PlaySound(SOUND_LABEL_SE_STAR_GET);
			break;
		default:
			break;
		}


		m_pStarData->m_eDestroyType = NONE;
		m_pStarData->m_bRespawnEvent = true;
		//	リセット
		m_pStarData->m_bDestroyEnd = false;
		m_pStarData->m_bDraw = false;
		m_pStarData->m_bDestroyEvent = false;

		return;
	}
}

////=======================================================================================
////
////		リスポーン
////
////=======================================================================================
void cRyusei::Respawn(){

	if (m_pStarData->m_bUse)
		return;

	if (!m_pStarData->m_bRespawnEnd){

		// フレーム加算開始
		m_pStarData->m_nRespawnFrame++;

		if (m_pStarData->m_nRespawnFrame > RESPAWN_FREAM){

			// 座標の決定
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT + STAR_SIZE, GAME_SCREEN_RIGHT + 200);
			CreateRamdomPos.y = -(float)CRandam::RandamRenge(0, 800);
			//CreateRamdomPos = D3DXVECTOR2(SCREEN_CENTER);
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);

			//--- 流れる処理のための準備 ---
			m_pStarData->m_bStream = true;
			m_pStarData->m_StreamStartPos = CreateRamdomPos;																// 初期生成位置をスタート位置に指定
			m_pStarData->m_StreamGoalPos = D3DXVECTOR2(CreateRamdomPos.x - 250.0, CreateRamdomPos.y + SCREEN_HEIGHT);		// 画面左下をゴールに指定
			m_pStarData->m_VecStreamMove = m_pStarData->m_StreamGoalPos - m_pStarData->m_StreamStartPos;					// スタートとゴールから流れる方向のベクトルを求める
			m_pStarData->m_StremCos = (fabs(m_pStarData->m_StreamStartPos.x - m_pStarData->m_StreamGoalPos.x)			// 計算用のcosを求める
				/ VectorSize(m_pStarData->m_VecStreamMove));
			m_pStarData->m_StreamRad = acosf(m_pStarData->m_StremCos);													// Cosから計算用の角度を求める
			m_pStarData->m_sprite.SetRad(D3DX_PI / 2.0f - m_pStarData->m_StreamRad);										// 計算結果より回転角度をセット
			m_pStarData->m_MoveSpped = MOVE_SPEED * UnitVector(m_pStarData->m_VecStreamMove);							// 流れる方向の単位ベクトルを求めて速さをセット


			m_pStarData->m_MeteorLight.SetPos(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x - 17, m_pStarData->m_sprite.GetPos().y + 50));
			// 移動方向の単位ベクトルを求める
			m_pStarData->m_MoveSpped = MOVE_SPEED * UnitVector(D3DXVECTOR2(CreateRamdomPos.x - 250.0f, CreateRamdomPos.y + SCREEN_HEIGHT) - CreateRamdomPos);

			// 星から目的地方向の単位ベクトルを求める
			m_pStarData->m_Destination = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);
			m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());

			m_pStarData->m_bCaptured = false;

			m_pStarData->m_bRespawnEnd = true;
		}
	}

	// 生成終了フラグが立ったらリセットして終了
	if (m_pStarData->m_bRespawnEnd){

		// 生成イベント開始
		m_pStarData->m_bCreateEvent = true;

		//	リセット
		m_pStarData->m_nRespawnFrame = 0;
		m_pStarData->m_bRespawnEnd = false;
		m_pStarData->m_bRespawnEvent = false;
		return;
	}
}

//=======================================================================================
//
//		網との処理
//
//=======================================================================================
//--- 網のデータ取得 ---
void cRyusei::SetNetData(cNet* data){
	m_pNetData = data;
}

//--- 網と当たった時の処理 ---
void cRyusei::OnCollidToNet(int num){

	// 先頭から何番目か
	m_pStarData = m_pRoot;
	m_pStarData += num;

	m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_VecStarToDest * 5);

	m_pStarData->m_bStream = false;
	m_pStarData->m_bCaptured = true;


}

//--- 網の中に流星があるとき ---
void cRyusei::OnCollidToNetArea(int num){

	// 先頭から何番目か
	m_pStarData = m_pRoot;
	m_pStarData += num;

	if (!m_pStarData->m_bUse)
		return;

	m_pStarData->m_bStream = false;
	
}