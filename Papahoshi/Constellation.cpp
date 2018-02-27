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
#define CENTER_STAR_SIZE			(D3DXVECTOR2(150,150))
#define OTHER_STAR_SIZE				(D3DXVECTOR2(30,30))
#define MAX_CONSTELLATION_NUM		(10)
#define RESPAWN_FREAM				(10)

//	生成位置
#define CREATE_PATTERN		(2)
//#define CREATE_POS_01		(D3DXVECTOR2(GAME_SCREEN_LEFT+DEFAULT_STAR_SIZE/2.0f,100))
//#define CREATE_POS_02		(D3DXVECTOR2(GAME_SCREEN_RIGHT-DEFAULT_STAR_SIZE/2.0f,100))

#define CREATE_POS_01		(D3DXVECTOR2(SCREEN_CENTER))
#define CREATE_POS_02		(D3DXVECTOR2(SCREEN_CENTER))

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

	
		D3DXVECTOR2 CreateCenterPos;

		//--- 星群の中心の設定 ----
		if (nCountStarNum == 0){
	
			// 座標の決定
			int RamdomNum = CRandam::RandamRenge(1, CREATE_PATTERN + 1);
			switch (RamdomNum)
			{
			case 1:
				CreateCenterPos = CREATE_POS_01;
				break;
			case CREATE_PATTERN:
				CreateCenterPos = CREATE_POS_02;
				break;
			default:
				break;
			}
			m_pStarData->m_sprite.SetPos(CreateCenterPos);

			// サイズの設定
			m_pStarData->m_sprite.SetSize(CENTER_STAR_SIZE);

			// テクスチャの設定
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_PLANET03));

			// アニメーションの設定
			m_pStarData->m_sprite.SetTexPatternDevide(10, 2);
			m_pStarData->m_sprite.SetIntervalChangePattern(7);
			m_pStarData->m_sprite.SetAnimationFlag(true);

			// 当たり判定
			m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
			// 当たり判定
			m_pStarData->m_Collision.SetCircleCollider(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x, m_pStarData->m_sprite.GetPos().y), CENTER_STAR_SIZE.x / 2.0f);

		}


		//--- 星群の周りの星の設定 ----
		else{

			// 星群の周りに星を生成
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = (float)CRandam::RandamRenge(CreateCenterPos.x - 200, CreateCenterPos.x + 200);
			CreateRamdomPos.y = (float)CRandam::RandamRenge(CreateCenterPos.y - 200, CreateCenterPos.y + 200);
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);
			// 星の色の決定
			m_pStarData->m_nStarColorNum = CRandam::RandamRenge(0, 3);
			switch (m_pStarData->m_nStarColorNum)
			{
			case 0:
				m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_YELLOW_STAR_ANIM));
				m_pStarData->m_sprite.SetTexPatternDevide(4, 2);
				m_pStarData->m_sprite.SetIntervalChangePattern(7);
				break;
			case 1:
				m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_GREEN_STAR_ANIM));
				m_pStarData->m_sprite.SetTexPatternDevide(11, 2);
				m_pStarData->m_sprite.SetIntervalChangePattern(7);
				break;
			case 2:
				m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_PINK_STAR_ANIM));
				m_pStarData->m_sprite.SetTexPatternDevide(11, 2);
				m_pStarData->m_sprite.SetIntervalChangePattern(7);
				break;
			default:
				break;
			}
			// アニメーションの設定
			m_pStarData->m_sprite.SetAnimationFlag(true);
		


			// サイズの設定
			m_pStarData->m_sprite.SetSize(OTHER_STAR_SIZE);

			// 円軌道の設定
			m_pStarData->m_CircleMoveData.SetCenter(CreateCenterPos);	// 円軌道の中心を星群れの中心にセット
			//m_pStarData->m_CircleMoveData.SetRadius(D3DXVECTOR2((float)CRandam::RandamRenge(100, 200), (float)CRandam::RandamRenge(100,200)));
			m_pStarData->m_CircleMoveData.SetRadius(D3DXVECTOR2(100, 100));
			m_pStarData->m_CircleMoveData.SetSpped(0.01f);
			m_pStarData->m_CircleMoveData.SetRad((float)CRandam::RandamRenge(0, 2*D3DX_PI ));

			// 当たり判定
			m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
			// 当たり判定
			m_pStarData->m_Collision.SetCircleCollider(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x, m_pStarData->m_sprite.GetPos().y), OTHER_STAR_SIZE.x / 2.0f);

		}
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


		//----- 中心のみ ---------
		if (nCountStarNum == 0){

			// 当たり判定
			m_pStarData->m_Collision.SetCircleCollider(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x, m_pStarData->m_sprite.GetPos().y), CENTER_STAR_SIZE.x / 2.0f);
		}


		//---- 中心以外 ----------
		if (nCountStarNum != 0){

			// 円軌道の設定
			m_pStarData->m_sprite.SetPos(m_pStarData->m_CircleMoveData.GetMove());

			// 当たり判定
			m_pStarData->m_Collision.SetCircleCollider(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x, m_pStarData->m_sprite.GetPos().y) , OTHER_STAR_SIZE.x / 2.0f);
		}


		//-----  共通 ------------
		// アニメーションの更新
		m_pStarData->m_sprite.AnimationLoop();


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


	//---- 0番目(星群の中心を一番前に描画するための処理) --------------------------------------------
	// 先頭+1
	m_pStarData = m_pRoot+1;

	// 描画
	for (int nCountStarNum = 1; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bDraw)
			continue;

		m_pStarData->m_sprite.Draw();
		m_pStarData->m_Collision.Draw();
	}

	// 先頭に戻す
	m_pStarData = m_pRoot;

	if (m_pStarData->m_bDraw){
		m_pStarData->m_sprite.Draw();
		m_pStarData->m_Collision.Draw();
	}
	
	//----------------------------------------------------------------------------------------------

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