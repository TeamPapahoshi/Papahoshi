//======================================================================
//	Star
//	
//	概要＿：星処理
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
#include "NormalStars.h"
#include "rand.h"
#include "Input.h"
#include <cmath>

//-----------------------------
//マクロ定義
//-----------------------------
#define STAR_SIZE	(20)
#define RESPAWN_FREAM (200)
#define MAX_NORMAL_STAR_NUM	(50)

//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cNormalStar::cNormalStar(){

	// 乱数の初期化
	CRandam::InitRand();

	// 使用数を格納ファイルから読み込むけどだいぶ変更したから
	m_nMaxNum = MAX_NORMAL_STAR_NUM;

	// 動的インスタンス
	m_pStarData = new cNormalStarData[m_nMaxNum]();	//ここ注意
	m_pRoot = m_pStarData;							// 先頭アドレス保存



	// 初期化
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// 初期生成
		m_pStarData->m_bDraw = true;
		SetCountAndUse(true);

		// サイズの変更
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));

		// テクスチャの設定
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR));

		// 座標の決定
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);

		//CreateRamdomPos = D3DXVECTOR2(SCREEN_WIDTH/2.0f+50, SCREEN_HEIGHT-100);
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// 代入

		// 当たり判定
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE/2.0f);

		// 移動の目的位置決定
		m_pStarData->m_PurposPos = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);
		// 目的地までの距離を測定
		m_pStarData->m_PurPosDist.x =fabs(m_pStarData->m_PurposPos.x - m_pStarData->m_sprite.GetPos().x);
		m_pStarData->m_PurPosDist.y = fabs(m_pStarData->m_PurposPos.y - m_pStarData->m_sprite.GetPos().y);

	}

}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cNormalStar::~cNormalStar(){


	// 先頭に戻す
	m_pStarData = m_pRoot;

	delete[] m_pStarData;
}
//=======================================================================================
//
//		更新
//
//=======================================================================================
void cNormalStar::Update(){

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// イベント格納ループ？
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// イベントが呼び出される感じ
		if (m_pStarData->m_bCreateEvent){
			Create();
		}

		else if (m_pStarData->m_bDestroyEvent){
			Destroy();
		}

		else if (m_pStarData->m_bRespawnEvent){
			Respawn();
		}
		
		// 当たり判定
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);


	}

	// イベントの起動
	// デバッグキー
	if (GetKeyboardTrigger(DIK_R)){
		m_pStarData = m_pRoot;	// 先頭に戻す
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
			m_pStarData->m_bDestroyEvent = true;
		}
	}
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
void cNormalStar::Draw(){

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// 描画
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bDraw)
			continue;

		m_pStarData->m_sprite.Draw();

		if (m_pStarData->m_bUse)
			m_pStarData->m_Collision.Draw();
	}

	// 先頭に戻す
	m_pStarData = m_pRoot;


	// デバッグプリント
	PrintDebugProc("━━━━━━モブ星━━━━━━\n");
	PrintDebugProc("現在の数 %d/%d\n", m_nCurrentNum, m_nMaxNum);
	PrintDebugProc("Rキーでリセット\n");
	PrintDebugProc("リスポーンインターバル確認 %d/%d\n", m_pStarData->m_nRespawnFrame, RESPAWN_FREAM);
	PrintDebugProc("━━━━━━━━━━━━━━━\n");


}
//=======================================================================================
//
//		生成
//
//=======================================================================================
void cNormalStar::Create(){

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
void cNormalStar::Destroy(){

	// 生成イベントの開始
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);

		// ここ以外は同じ処理になるはずだからコピぺでいいはず
		//****** ここに演出とか処理を書いていく **********




		//****************************************************


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
void cNormalStar::Respawn(){

	
	if (!m_pStarData->m_bRespawnEnd){

		// フレーム加算開始
		m_pStarData->m_nRespawnFrame++;

		if (m_pStarData->m_nRespawnFrame > RESPAWN_FREAM){

			// 座標の決定
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
			CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// 代入


			m_pStarData->m_PurposPos = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);
			m_pStarData->m_PurPosDist.x = fabs(m_pStarData->m_PurposPos.x - m_pStarData->m_sprite.GetPos().x);
			m_pStarData->m_PurPosDist.y = fabs(m_pStarData->m_PurposPos.y - m_pStarData->m_sprite.GetPos().y);

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
void cNormalStar::SetNetData(cNet* data){
	m_pNetData = data;
}

//--- 網と当たった時の処理 ---
void cNormalStar::OnCollidToNet(int num){

	// 先頭から何番目か
	m_pStarData = m_pRoot;
	m_pStarData += num;


	//// 網を引いているときのみ移動する
	//if (m_pNetData->GetPullFlug()){

	//	// 移動したい距離
	//	float DistGoalX = m_pStarData->m_PurPosDist.x / 3.0f;	// 三回に分けて移動する
	//	float DistGoalY = m_pStarData->m_PurPosDist.y / 3.0f;


	//	// 距離から移動量を算出(フレーム数で割る)
	//	m_pStarData->m_Move.x = DistGoalX / 50.0f;
	//	m_pStarData->m_Move.y = DistGoalY / 45.0f;



	//	// 移動量を反映
	//	if (m_pStarData->m_sprite.GetPosX() > m_pStarData->m_PurposPos.x){
	//		m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() - m_pStarData->m_Move.x);
	//	}
	//	else if ((m_pStarData->m_sprite.GetPosX() < m_pStarData->m_PurposPos.x)){
	//		m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() + m_pStarData->m_Move.x);
	//	}
	//	else{

	//	}
	//	if ((m_pStarData->m_sprite.GetPosY() < m_pStarData->m_PurposPos.y)){
	//		m_pStarData->m_sprite.SetPosY(m_pStarData->m_sprite.GetPosY() + m_pStarData->m_Move.y);
	//	}
	//	else if ((m_pStarData->m_sprite.GetPosY() > m_pStarData->m_PurposPos.y)){
	//		m_pStarData->m_sprite.SetPosY(m_pStarData->m_sprite.GetPosY() + m_pStarData->m_Move.y);
	//	}
	//	else{

	//	}

	//}

		// 移動したい距離
		float DistGoalX = m_pStarData->m_PurPosDist.x / 3.0f;	// 三回に分けて移動する
		float DistGoalY = m_pStarData->m_PurPosDist.y / 3.0f;


		// 距離から移動量を算出(フレーム数で割る)
		m_pStarData->m_Move.x = m_pStarData->m_PurPosDist.x/50.0f;
		m_pStarData->m_Move.y = m_pStarData->m_PurPosDist.y/50.0f;



		// 移動量を反映
		if (m_pStarData->m_sprite.GetPosX() >= m_pStarData->m_PurposPos.x){
			m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() - m_pStarData->m_Move.x);
		}
		else if ((m_pStarData->m_sprite.GetPosX() < m_pStarData->m_PurposPos.x)){
			m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() + m_pStarData->m_Move.x);
		}
		if ((m_pStarData->m_sprite.GetPosY() <= m_pStarData->m_PurposPos.y)){
			m_pStarData->m_sprite.SetPosY(m_pStarData->m_sprite.GetPosY() + m_pStarData->m_Move.y);
		}
		else if ((m_pStarData->m_sprite.GetPosY() > m_pStarData->m_PurposPos.y)){
			m_pStarData->m_sprite.SetPosY(m_pStarData->m_sprite.GetPosY() + m_pStarData->m_Move.y);
		}
}




//=======================================================================================
//
//		ブラックホールとの処理
//
//=======================================================================================
//---- ブラックホールの情報を取得 -----
void cNormalStar::SetBlackHoleData(cBlackHole* data){
	m_pBlackHoleData = data;

}

//---- ブラックホール吸い込み範囲に当たった時の処理 -----
void cNormalStar::OnCollidToBlackHole(int Normal, int Black){

	// 振動する
	//if (m_pStarData[Normal].t_bVibration){

	//	m_pStarData[Normal].t_nVibrationFrame++;
	//	m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() + 0.15f);

	//	if (m_pStarData[Normal].t_nVibrationFrame > 5){
	//		m_pStarData[Normal].t_bVibration = false;
	//		m_pStarData[Normal].t_nVibrationFrame = 0;
	//	}	
	//}

	//else if (!m_pStarData[Normal].t_bVibration){
	//	m_pStarData[Normal].t_nVibrationFrame++;
	//	m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() - 0.15f);
	//	if (m_pStarData[Normal].t_nVibrationFrame > 5){
	//		m_pStarData[Normal].t_bVibration = true;
	//		m_pStarData[Normal].t_nVibrationFrame = 0;
	//	}
	//}


	//// ブラックホールの中心を取得
	//D3DXVECTOR2 Center = m_pBlackHoleData->GetStarData()[Black].t_Sprite.GetPos();

	//// ブラックホールと星との距離を求める
	//D3DXVECTOR2 Distance;
	//Distance.x = sqrt((m_pStarData[Normal].t_Sprite.GetPosX() - Center.x)*(m_pStarData[Normal].t_Sprite.GetPosX() - Center.x));
	//Distance.y = sqrt((m_pStarData[Normal].t_Sprite.GetPosY() - Center.y)*(m_pStarData[Normal].t_Sprite.GetPosY() - Center.y));

	//// 距離から移動量を算出
	//m_pStarData[Normal].t_Move.x = Distance.x / 800.0f;
	//m_pStarData[Normal].t_Move.y = Distance.y / 800.0f;

	//// 移動量を反映
	//if (m_pStarData[Normal].t_Sprite.GetPosX() > Center.x){
	//	m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() - m_pStarData[Normal].t_Move.x);
	//}
	//if (m_pStarData[Normal].t_Sprite.GetPosX() < Center.x){
	//	m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() + m_pStarData[Normal].t_Move.x);
	//}

	//if (m_pStarData[Normal].t_Sprite.GetPosY() > Center.y){
	//	m_pStarData[Normal].t_Sprite.SetPosY(m_pStarData[Normal].t_Sprite.GetPosY() - m_pStarData[Normal].t_Move.y);
	//}
	//if (m_pStarData[Normal].t_Sprite.GetPosY() < Center.y){
	//	m_pStarData[Normal].t_Sprite.SetPosY(m_pStarData[Normal].t_Sprite.GetPosY() + m_pStarData[Normal].t_Move.y);
	//}

}

//---- ブラックホールの削除範囲に当たった時の処理 -----
void cNormalStar::OnCollidToDelete(int Normal){

	
}