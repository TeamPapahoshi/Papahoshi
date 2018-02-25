//======================================================================
//	星群
//	
//	概要＿：
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
#include "Constellation.h"
#include "Input.h"
#include "GameUI.h"


//-----------------------------
// マクロ定義
//-----------------------------
#define DEFAULT_STAR_SIZE			(100)
#define MAX_CONSTELLATION_NUM		(5)
#define RESPAWN_FREAM				(10)

//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cConstellation::cConstellation(){

	// 乱数の初期化
	CRandam::InitRand();

	// 使用数を格納ファイルから読み込むけどだいぶ変更したから
	m_nMaxNum = MAX_CONSTELLATION_NUM;

	// 動的インスタンス
	m_pStarData = new cConstellationData[m_nMaxNum]();//ここ注意
	m_pRoot = m_pStarData;							// 先頭アドレス保存



	// 初期化
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// 初期生成
		m_pStarData->m_bDraw = true;
		SetCountAndUse(true);
		m_pStarData->m_bCreateEvent = true;

		// 星群れのちゅうしん


		// 座標の決定
		D3DXVECTOR2 CreateRamdomPos = D3DXVECTOR2(SCREEN_CENTER);
		CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
		CreateRamdomPos = D3DXVECTOR2(SCREEN_CENTER);
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// 代入


	}




}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cConstellation::~cConstellation(){

	m_pStarData = m_pRoot;
	delete[]  m_pStarData;
	m_pStarData = NULL;

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cConstellation::Update(){

	// 先頭に戻す
	m_pStarData = m_pRoot;


	// 更新
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){


		// 使ってないのは飛ばす
		if (!m_pStarData->m_bUse)
			continue;
	}



	// 先頭に戻す
	m_pStarData = m_pRoot;

	// イベント格納
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){


		// イベントが呼び出される感じ
		if (m_pStarData->m_bCreateEvent){
			Create();
		}

		else if (m_pStarData->m_bDestroyEvent){
			Destroy();
		}
		if (m_pStarData->m_bRespawnEvent){
			Respawn();
		}
	}



	// イベントの起動
	// デバッグキー
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
void cConstellation::Draw(){

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// 描画
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bDraw)
			continue;

		//m_pStarData->m_sprite.Draw();
	}


	// デバッグプリント
	/*PrintDebugProc("━━━━サンプル━━━\n");
	PrintDebugProc("現在の数 %d/%d\n", m_nCurrentNum, m_nMaxNum);
	PrintDebugProc("Kキーで生成\n");
	PrintDebugProc("Dキーで削除\n");
	PrintDebugProc("━━━━━━━━━━━\n");*/
}


//=======================================================================================
//
//		生成
//
//=======================================================================================
void cConstellation::Create(){

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
void cConstellation::Destroy(){

	// 生成イベントの開始
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);

		// ここ以外は同じ処理になるはずだからコピぺでいいはず
		//****** ここに演出とか処理を書いていく **********






		//****************************************************


		// 演出がおわったら終了フラグを立てる->if(EffectEnd()){m_pStar->....}
		//m_pStarData->m_bCreateEnd = true;

		// 今回はある程度回転したら終了->if(EffectEnd()){m_pStar->....}

			m_pStarData->m_bDestroyEnd = true;
			//m_pStarData->m_bUse = false;

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
void cConstellation::Respawn(){


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