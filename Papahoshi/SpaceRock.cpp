//======================================================================
//	SpaceRock
//	
//	概要＿：隕石
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
#include "SpaceRock.h"
#include "Input.h"
#include "GameUI.h"
#include "MathEX.h"
#include "sound.h"

//-----------------------------
// マクロ定義
//-----------------------------
//---- 隕石 ----
#define CREATE_PATTERN		(2)
#define CREATE_POS_01		(D3DXVECTOR2(GAME_SCREEN_LEFT+500,200))
//#define CREATE_POS_01		(D3DXVECTOR2(GAME_SCREEN_LEFT+150,350))
//#define CREATE_POS_02		(D3DXVECTOR2(GAME_SCREEN_RIGHT-150,350)
#define CREATE_POS_02		(D3DXVECTOR2(GAME_SCREEN_LEFT+500,200))
#define STAR_SIZE			(150)
#define RESPAWN_FREAM		(500)
#define MAX_SPACE_ROCK_NUM	(1)
#define DESTROY_STAR		(20)

//---- 爆発関連 -----
#define EXPLOSION_FRAME		(40)		// 爆発時間
#define EXPLOSION_SIZE		(250)

//---- 正存時間 -------
#define LIFE_TIME			(600)


//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cSpaceRock::cSpaceRock(){

	// 乱数の初期化
	CRandam::InitRand();

	// 使用数を格納ファイルから読み込むけどだいぶ変更したから
	m_nMaxNum = MAX_SPACE_ROCK_NUM;

	// 動的インスタンス
	m_pStarData = new cSpaceRockData[m_nMaxNum]();	//ここ注意
	m_pRoot = m_pStarData;							// 先頭アドレス保存

	// 初期化
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// テクスチャの設定
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_SPACE_ROCK));
		m_pStarData->m_sprite.SetAnimationFlag(true);
		m_pStarData->m_sprite.SetTexPatternDevide(5, 4);
		m_pStarData->m_sprite.SetIntervalChangePattern(7);

		// 座標の決定
		D3DXVECTOR2 CreateRamdomPos;
		int RamdomNum = CRandam::RandamRenge(1, CREATE_PATTERN + 1);
		switch (RamdomNum)
		{
		case 1:
			CreateRamdomPos = CREATE_POS_01;
			break;
		case 2:
			CreateRamdomPos = CREATE_POS_02;
			break;
		default:
			break;
		}
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);

		// サイズの変更
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));

		// 当たり判定
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f-20.0f);

		// 破壊数を設定
		m_pStarData->m_nDestroyStarNum = DESTROY_STAR;

		// 爆発用
		m_pStarData->m_ExplosionAnim.SetPos(m_pStarData->m_sprite.GetPos());	// 
		m_pStarData->m_ExplosionAnim.SetSize(D3DXVECTOR2(EXPLOSION_SIZE, EXPLOSION_SIZE));
		m_pStarData->m_ExplosionAnim.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_EXPLOSION));
		m_pStarData->m_ExplosionAnim.SetAddBlend(true);
		m_pStarData->m_ExplosionAnim.SetAnimationFlag(true);
		m_pStarData->m_ExplosionAnim.SetCurrentAnimPattern(0);
		m_pStarData->m_ExplosionAnim.SetTexPatternDevide(8, 2);
		m_pStarData->m_ExplosionAnim.SetIntervalChangePattern(3);
		m_pStarData->m_ExplosionFrame = EXPLOSION_FRAME;				// 爆発時間
		m_pStarData->m_bExplosion = false;								// 開始用フラグ

		// 正存時間の指定
		m_pStarData->m_nLifeTime = LIFE_TIME;

		// αの設定
		m_pStarData->m_sprite.SetVtxColorA(0);

	}
}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cSpaceRock::~cSpaceRock(){

	// 先頭に戻す
	m_pStarData = m_pRoot;
	delete[] m_pStarData;

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSpaceRock::Update(){

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// 更新
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){


		if (!m_pStarData->m_bUse)
			continue;

		// 当たり判定
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f - 20.0f);

		// アニメーション更新
		m_pStarData->m_sprite.AnimationLoop();

		// 網との処理用
		m_pStarData->m_Destination = m_pNetData->GetNetStart();	// 移動の目的位置決定
		m_pStarData->m_Destination.y = m_pNetData->GetNetStart().y - 100.0f;	// 移動の目的位置決定
		m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());// 星から目的地方向の単位ベクトルを求める

		// 爆発の位置
		m_pStarData->m_ExplosionAnim.SetPos(m_pStarData->m_sprite.GetPos());


		//---- 爆発カウントによって色を変える -----
		float ratio = (float)m_pStarData->m_nLifeTime / (float)LIFE_TIME;
		m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 255 * ratio, 255 * ratio, 255));
		// 残り1で真っ赤に
		if (m_pStarData->m_nLifeTime <= 200){
			m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 0, 0, 255));

			// 振動する
			if (m_pStarData->m_bVibration){

				m_pStarData->m_nVibrationFrame++;
				m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() + 0.4f);

				if (m_pStarData->m_nVibrationFrame > 3){
					m_pStarData->m_bVibration = false;
					m_pStarData->m_nVibrationFrame = 0;
				}
			}

			else if (!m_pStarData->m_bVibration){

				m_pStarData->m_nVibrationFrame++;
				m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() - 0.4f);

				if (m_pStarData->m_nVibrationFrame > 3){
					m_pStarData->m_bVibration = true;
					m_pStarData->m_nVibrationFrame = 0;
				}
			}
		}

		// 目的位置についたら消去イベント開始Ｙ軸で決める
		if (m_pStarData->m_sprite.GetPos().y >= m_pStarData->m_Destination.y)
		{
			m_pStarData->m_bDestroyEvent = true;
		}

		//--- 正存時間を減らす ---
		m_pStarData->m_nLifeTime--;
		if (m_pStarData->m_nLifeTime <= 0){
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


	//if (GetKeyboardTrigger(DIK_2)){
	//	m_pStarData = m_pRoot;			// 先頭に戻す
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (!m_pStarData->m_bUse)	// ここ注意
	//		continue;
	//		m_pStarData->m_nDestroyStarNum--;
	//		m_pStarData = m_pRoot;		// 先頭に戻す
	//		break;
	//	}
	//}
	// イベントの起動
	// デバッグキー
	//if (GetKeyboardTrigger(DIK_B)){
	//	m_pStarData = m_pRoot;			// 先頭に戻す
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (m_pStarData->m_bDraw)	// ここ注意
	//			continue;
	//		m_pStarData->m_bCreateEvent = true;
	//		m_pStarData = m_pRoot;		// 先頭に戻す
	//		break;
	//	}
	//}
	//// デバッグキー
	//if (GetKeyboardTrigger(DIK_M)){
	//	m_pStarData = m_pRoot;			// 先頭に戻す
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (!m_pStarData->m_bUse)	// ここ注意
	//			continue;
	//		m_pStarData->m_bDestroyEvent = true;
	//		m_pStarData = m_pRoot;		// 先頭に戻す
	//		break;
	//	}
	//}
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
void cSpaceRock::Draw(){

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// 描画
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){


		if (m_pStarData->m_bExplosion)
			m_pStarData->m_ExplosionAnim.Draw();

		// 描画フラグがないものは飛ばす
		if (!m_pStarData->m_bDraw)
			continue;

		// 星
		m_pStarData->m_sprite.Draw();

		// ゲーム内で有効ならあたり判定を描画
		if (m_pStarData->m_bUse){
			//m_pStarData->m_Collision.Draw();
		}
	}

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// デバッグプリント
	PrintDebugProc("━━━━隕石━━━━\n");
	PrintDebugProc("現在の数 %d/%d\n", m_nCurrentNum, m_nMaxNum);
	//PrintDebugProc("2キーで破壊数更新");
	//PrintDebugProc("破壊数 %d/%d\n", m_pStarData->m_nDestroyStarNum, DESTROY_STAR);
	//PrintDebugProc("爆発時間 %d/%d\n", m_pStarData->m_ExplosionFrame, EXPLOSION_FRAME);
	PrintDebugProc("リスポーンインターバル %d/%d\n", m_pStarData->m_nRespawnFrame, RESPAWN_FREAM);
	PrintDebugProc("━━━━━━━━━━━━━━━\n");

}

//=======================================================================================
//
//		生成
//
//=======================================================================================
void cSpaceRock::Create(){

	// 生成イベントの開始
	if (!m_pStarData->m_bCreateEnd){

		// ここ以外は同じ処理になるはずだからコピぺでいいはず
		//****** ここに演出とか生成処理を書いていく **********
		//m_pStarData->m_bUse = true;->これでもできるけど今回は数もかぞえておきたいから
		m_pStarData->m_bDraw = true;


		// αを上げていく
		if (m_pStarData->m_sprite.GetVtxColorA()+5.0f <= 255){
			m_pStarData->m_sprite.SetVtxColorA(m_pStarData->m_sprite.GetVtxColorA() + 5.0f);
		}
		else{
			m_pStarData->m_sprite.SetVtxColorA(255);
		}


		//****************************************************



		// 演出がおわったら生成終了フラグを立てる->if(EffectEnd()){m_pStar->....}

		if (m_pStarData->m_sprite.GetVtxColorA() >= 255)
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
void cSpaceRock::Destroy(){

	// 削除イベントの開始
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);
		m_pStarData->m_bDraw = false;

		
		//****** ここに演出とか処理を書いていく *************

		// 爆発フレームの更新
		m_pStarData->m_ExplosionFrame--;


		// SE再生
		if (!m_pStarData->m_bExplosion)
		PlaySound(SOUND_LABEL_SE_SPACE_ROCK_BOMB);

		// フラグオン
		m_pStarData->m_bExplosion = true;

	

		// アニメーション
		m_pStarData->m_ExplosionAnim.AnimationLoop();

		//****************************************************

		// 演出がおわったら終了フラグを立てる->if(EffectEnd()){m_pStar->....}
		if (m_pStarData->m_ExplosionFrame <= 0)
			m_pStarData->m_bDestroyEnd = true;

	}

	// 生成終了フラグが立ったらリセットして終了
	if (m_pStarData->m_bDestroyEnd){


		if (m_pStarData->m_bCaptured){
			m_pGageData->GageChange(-50);
		}


		// αの設定
		m_pStarData->m_sprite.SetVtxColorA(0);

		// 座標の決定
		D3DXVECTOR2 CreateRamdomPos;
		int RamdomNum = CRandam::RandamRenge(1, CREATE_PATTERN + 1);
		switch (RamdomNum)
		{
		case 1:
			CreateRamdomPos = CREATE_POS_01;
			break;
		case CREATE_PATTERN:
			CreateRamdomPos = CREATE_POS_02;
			break;
		default:
			break;
		}
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);

		m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));
		m_pStarData->m_nDestroyStarNum = DESTROY_STAR;					// 破壊数を設定
		m_pStarData->m_ExplosionAnim.SetCurrentAnimPattern(0);
		m_pStarData->m_ExplosionFrame = EXPLOSION_FRAME;				// 爆発時間
		m_pStarData->m_bExplosion = false;								// 開始用フラグ
		m_pStarData->m_bCaptured = false;
		m_pStarData->m_nLifeTime = LIFE_TIME;							// 正存時間の指定


		// 終了したら即リスポーン準備
		m_pStarData->m_bRespawnEvent = true;

		// フラグオン
		m_pStarData->m_bExplosion = false;

		//	リセット
		m_pStarData->m_bDestroyEnd = false;
		m_pStarData->m_bDraw = false;
		m_pStarData->m_bDestroyEvent = false;

		return;
	}
}


//=======================================================================================
//
//		リスポーン
//
//=======================================================================================
void cSpaceRock::Respawn(){

	if (!m_pStarData->m_bRespawnEnd){

		// フレーム加算開始
		m_pStarData->m_nRespawnFrame++;

		if (m_pStarData->m_nRespawnFrame > RESPAWN_FREAM){

			// αの設定
			m_pStarData->m_sprite.SetVtxColorA(0);

			// 座標の決定
			D3DXVECTOR2 CreateRamdomPos;
			int RamdomNum = CRandam::RandamRenge(1, CREATE_PATTERN + 1);
			switch (RamdomNum)
			{
			case 1:
				CreateRamdomPos = CREATE_POS_01;
				break;
			case CREATE_PATTERN:
				CreateRamdomPos = CREATE_POS_02;
				break;
			default:
				break;
			}
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);

			m_pStarData->m_sprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));
			m_pStarData->m_nDestroyStarNum = DESTROY_STAR;					// 破壊数を設定
			m_pStarData->m_ExplosionAnim.SetCurrentAnimPattern(0);
			m_pStarData->m_ExplosionFrame = EXPLOSION_FRAME;				// 爆発時間
			m_pStarData->m_bExplosion = false;								// 開始用フラグ
			m_pStarData->m_bCaptured = false;
			m_pStarData->m_nLifeTime = LIFE_TIME;							// 正存時間の指定

			// リスポーン処理終了
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
void cSpaceRock::SetNetData(cNet* data){
	m_pNetData = data;
}

void cSpaceRock::OnCollidToNet(int count){


	// 先頭から何番目か
	m_pStarData = m_pRoot;
	m_pStarData += count;

	m_pStarData->m_bCaptured = true;


	// Vector確認用
	m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_VecStarToDest * 5);

}

//=======================================================================================
//
//		モブ星との処理
//
//=======================================================================================
void cSpaceRock::SetNormalStarData(cNormalStar* data){
	m_pNormalStarData = data;
}


void cSpaceRock::OnCollidToNormalStar(int num){

	// 先頭から何番目か
	m_pStarData = m_pRoot;
	m_pStarData += num;

	m_pStarData->m_nDestroyStarNum--;

	//m_pStarData->m_bDestroyEvent = true;




}

//=======================================================================================
//
//		ゲージとの処理
//
//=======================================================================================
//---- ゲージの情報を取得 -----
void cSpaceRock::SetGageData(cGage* data)
{
	m_pGageData = data;
}