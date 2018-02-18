//======================================================================
//	BlackHole
//	
//	概要＿：ブラックホール
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
#include "rand.h"
#include "BlackHole.h"
#include "Input.h"
#include "GameUI.h"
#include "MathEX.h"

//-----------------------------
// マクロ定義
//-----------------------------
#define STAR_SIZE			(200)	// サイズ
#define RESPAWN_FREAM		(100)	// リスポーンのインターバルフレーム
#define MAX_BLACK_HOLE_NUM	(1)		// 最大数
#define VACUUM_RANGE		(200)	// 吸い込み範囲
#define DELETE_RANGE		(10)	// 削除範囲

//===================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cBlackHole::cBlackHole(){

	// 乱数の初期化
	CRandam::InitRand();

	// 使用数を格納ファイルから読み込むけどだいぶ変更したから
	m_nMaxNum = MAX_BLACK_HOLE_NUM;

	// 動的インスタンス
	m_pStarData = new cBlackHoleData[m_nMaxNum]();	//ここ注意
	m_pRoot = m_pStarData;							// 先頭アドレス保存

	// 初期化
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// 初期生成
		m_pStarData->m_bDraw = true;
		SetCountAndUse(true);

		// サイズの変更
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));

		// テクスチャの設定
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_BLACK_HOLE));
		m_pStarData->m_sprite.SetTexPatternDevide(10, 6);
		m_pStarData->m_sprite.SetIntervalChangePattern(4);
		m_pStarData->m_sprite.SetAnimationFlag(true);
	
		// 座標の決定
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT + m_pStarData->m_sprite.GetSizeX(), GAME_SCREEN_RIGHT - m_pStarData->m_sprite.GetSizeX());
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0 + m_pStarData->m_sprite.GetSizeY(), SCREEN_HEIGHT - m_pStarData->m_sprite.GetSizeY());
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);

		// 当たり判定
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f-30);

		// 吸い込み範囲
		m_pStarData->m_VacumeRange.SetType(cCollider::CIRCLE);
		m_pStarData->m_VacumeRange.SetCircleCollider(m_pStarData->m_sprite.GetPos(), VACUUM_RANGE);

		// 削除範囲
		m_pStarData->m_DeleteRange.SetType(cCollider::CIRCLE);
		m_pStarData->m_DeleteRange.SetCircleCollider(m_pStarData->m_sprite.GetPos(), DELETE_RANGE);

	}
}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cBlackHole::~cBlackHole(){

	// 先頭に戻す
	m_pStarData = m_pRoot;
	delete[] m_pStarData;

}
//=======================================================================================
//
//		更新
//
//=======================================================================================
void cBlackHole::Update(){

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// 更新
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// 当たり判定
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f - 30);
		m_pStarData->m_VacumeRange.SetCircleCollider(m_pStarData->m_sprite.GetPos(), VACUUM_RANGE);
		m_pStarData->m_DeleteRange.SetCircleCollider(m_pStarData->m_sprite.GetPos(), DELETE_RANGE);
		m_pStarData->m_sprite.AnimationLoop();

		// 移動の目的位置決定
		m_pStarData->m_Destination = m_pNetData->GetNetStart();
		// 星から目的地方向の単位ベクトルを求める
		m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());

		// 目的位置についたら消去イベント開始Ｙ軸で決める
		if (m_pStarData->m_sprite.GetPos().y >= m_pStarData->m_Destination.y)
		{
			m_pStarData->m_bDestroyEvent = true;
		}
	}

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// イベント格納
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// イベントが呼び出される感じ
		if (m_pStarData->m_bCreateEvent){
			Create();
		}
		if (m_pStarData->m_bDestroyEvent){
			Destroy();
		}
		if (m_pStarData->m_bRespawnEvent){
			Respawn();
		}

	}

	// イベントの起動
	// デバッグキー
	if (GetKeyboardTrigger(DIK_B)){
		m_pStarData = m_pRoot;	// 先頭に戻す
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

			if (m_pStarData->m_bDraw)	// ここ注意
				continue;

			m_pStarData->m_bCreateEvent = true;
			m_pStarData = m_pRoot;	// 先頭に戻す
			break;
		}
	}
	// デバッグキー
	if (GetKeyboardTrigger(DIK_M)){
		m_pStarData = m_pRoot;	// 先頭に戻す
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

			if (!m_pStarData->m_bUse)	// ここ注意
				continue;
			m_pStarData->m_bDestroyEvent = true;
			m_pStarData = m_pRoot;	// 先頭に戻す
			break;
		}
	}
	//if (GetKeyboardTrigger(DIK_R)){
	//	m_pStarData = m_pRoot;	// 先頭に戻す
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		m_pStarData->m_bDestroyEvent = true;
	//	}
	//}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cBlackHole::Draw(){

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// 描画
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// 描画フラグがないものは飛ばす
		if (!m_pStarData->m_bDraw)
			continue;

		// 星
		m_pStarData->m_sprite.Draw();

		// ゲーム内で有効ならあたり判定を描画
		if (m_pStarData->m_bUse){
			m_pStarData->m_Collision.Draw();
			//m_pStarData->m_VacumeRange.Draw();
			//m_pStarData->m_DeleteRange.Draw();
		}
	}

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// デバッグプリント
	PrintDebugProc("━━━━ブラックホール━━━━\n");
	PrintDebugProc("現在の数 %d/%d\n", m_nCurrentNum, m_nMaxNum);
	PrintDebugProc("Bキーで生成\n");
	PrintDebugProc("Mキーで削除\n");
	PrintDebugProc("削除後自動リスポーン\n");
	PrintDebugProc("リスポーンインターバル確認 %d/%d\n", m_pStarData->m_nRespawnFrame, RESPAWN_FREAM);
	PrintDebugProc("%d\n", m_pStarData->m_sprite.GetCurrentAnimPattern());
	PrintDebugProc("━━━━━━━━━━━━━━━\n");
}
//=======================================================================================
//
//		生成
//
//=======================================================================================
void cBlackHole::Create(){

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
void cBlackHole::Destroy(){

	// 削除イベントの開始
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);

		// ここ以外は同じ処理になるはずだからコピぺでいいはず
		//********** ここに演出とか処理を書いていく *************
		//*******************************************************

		// 演出がおわったら終了フラグを立てる->if(EffectEnd()){m_pStar->....}
		m_pStarData->m_bDestroyEnd = true;

	}

	// 生成終了フラグが立ったらリセットして終了
	if (m_pStarData->m_bDestroyEnd){

		// 終了したら即リスポーン準備
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
void cBlackHole::Respawn(){


	if (!m_pStarData->m_bRespawnEnd){

		// フレーム加算開始
		m_pStarData->m_nRespawnFrame++;

		if (m_pStarData->m_nRespawnFrame > RESPAWN_FREAM){

			// 座標の決定
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT + m_pStarData->m_sprite.GetSizeX(), GAME_SCREEN_RIGHT - m_pStarData->m_sprite.GetSizeX());
			CreateRamdomPos.y = (float)CRandam::RandamRenge(0 + m_pStarData->m_sprite.GetSizeY(), SCREEN_HEIGHT - m_pStarData->m_sprite.GetSizeY());
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);

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
void cBlackHole::SetNetData(cNet* data){
	m_pNetData = data;
}

//--- 網と当たった時の処理 ---
void cBlackHole::OnCollidToNet(int num){

	// 先頭から何番目か
	m_pStarData = m_pRoot;
	m_pStarData += num;

	// Vector確認用
	m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_VecStarToDest * 5);

}