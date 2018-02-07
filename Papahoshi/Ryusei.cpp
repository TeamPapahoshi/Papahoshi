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

//-----------------------------
//マクロ定義
//-----------------------------
#define STAR_SIZE	(20)
#define RESPAWN_FREAM (200)
#define MAX_NORMAL_RYUSEI_NUM	(1)

float g_t=0;
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

		// 初期生成
		m_pStarData->m_bDraw = true;
		SetCountAndUse(true);

		// サイズの変更
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));

		// テクスチャの設定
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_RYUSEI));

		// 色
		m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));

		// 加算合成ON
		m_pStarData->m_sprite.SetAddBlend(true);

		// 座標の決定
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
		CreateRamdomPos = D3DXVECTOR2(0,SCREEN_HEIGHT/2.0f);

		CreateRamdomPos = D3DXVECTOR2(SCREEN_CENTER);
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);

		// ベジェ曲線関連
		m_pStarData->cp1 = D3DXVECTOR2(SCREEN_WIDTH, 0);
		m_pStarData->cp2 = D3DXVECTOR2(SCREEN_WIDTH, 0);
		m_pStarData->cp3 = D3DXVECTOR2(SCREEN_WIDTH, 0);
		m_pStarData->cp4 = D3DXVECTOR2(0, SCREEN_HEIGHT);
	}

	// CORE
	m_pStarData->m_Core.SetPos(m_pStarData->m_sprite.GetPos());
	// サイズの変更
	m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
	// テクスチャの設定
	m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_RYUSEI));
	// 色
	m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(0, 0, 255, 255));



	// インスタンス
	m_pLine = new cRyuseiLine();
}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cRyusei::~cRyusei(){

	delete m_pLine;

	// 先頭に戻す
	m_pStarData = m_pRoot;
	delete[] m_pStarData;
}
//=======================================================================================
//
//		更新
//
//=======================================================================================
void cRyusei::Update(){

	m_pLine->Update(m_pStarData->m_sprite.GetPos());

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// 更新
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// 当たり判定
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);

		// ベジェ曲線上を動かす
		g_t += 0.002f;
		m_pStarData->m_sprite.SetPos(BezierCurve(g_t, m_pStarData->cp1, m_pStarData->cp2, m_pStarData->cp3, m_pStarData->cp4));


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
void cRyusei::Draw(){

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// 描画
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bDraw)
			continue;

		m_pStarData->m_sprite.Draw();


		//if (m_pStarData->m_bUse)
			//m_pStarData->m_Collision.Draw();
	}

	// 先頭に戻す
	m_pStarData = m_pRoot;


	m_pLine->Draw();
	

	// デバッグプリント
	PrintDebugProc("━━━━━━流星━━━━━━\n");
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
void cRyusei::Create(){

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
void cRyusei::Respawn(){


	if (!m_pStarData->m_bRespawnEnd){

		// フレーム加算開始
		m_pStarData->m_nRespawnFrame++;

		if (m_pStarData->m_nRespawnFrame > RESPAWN_FREAM){

			// 座標の決定
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
			CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// 代入


			m_pStarData->m_Destination = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);
			m_pStarData->m_PurPosDist.x = fabs(m_pStarData->m_Destination.x - m_pStarData->m_sprite.GetPos().x);
			m_pStarData->m_PurPosDist.y = fabs(m_pStarData->m_Destination.y - m_pStarData->m_sprite.GetPos().y);
			// 星から目的地方向の単位ベクトルを求める
			m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());

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

