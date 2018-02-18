//======================================================================
//	NormalStar
//	
//	概要＿：モブ星処理
//	制作者：加藤　遼
//	
//======================================================================

//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>
#include <math.h>
#include <fstream>
#include <cmath>

#include "debugproc.h"
#include "Common.h"
#include "Texture.h"
#include "NormalStars.h"
#include "rand.h"
#include "Input.h"
#include "MathEX.h"
#include "GameUI.h"

#include "Score.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define STAR_SIZE			(30)
#define STAR_SIZE_MARGIN	(20)
#define RESPAWN_FREAM		(200)
#define MAX_NORMAL_STAR_NUM	(50)

//光沢のエフェクト用
#define EFFECT_FRAME   (90)
#define EFFECT_SIZE    (40.0f)
#define EFFECT_RADIUS  (8.0f)

//ゲージに移動するときのエフェクト用
#define EFFECT_BEZIERCURVE_FRAME (60)
#define EFFECT_BEZIERCURVE_SIZE (22.0f)

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
		m_pStarData->m_nEffectSetTime = CRandam::RandamRenge(0, EFFECT_FRAME);

		// サイズの変更
		float size = (CRandam::RandamRenge(STAR_SIZE, STAR_SIZE + STAR_SIZE_MARGIN));
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(size, size));

		// テクスチャの設定
		m_pStarData->m_sprite.SetAnimationFlag(true);
		m_pStarData->m_sprite.SetTexPatternDevide(11, 2);
		m_pStarData->m_sprite.SetIntervalChangePattern(7);

		// 星の色の決定
		m_pStarData->m_nStarColorNum = CRandam::RandamRenge(0, 3);
		switch (m_pStarData->m_nStarColorNum)
		{
		case 0:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_YELLOW_STAR_ANIM));
			break;
		case 1:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_GREEN_STAR_ANIM));
			break;
		case 2:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_PINK_STAR_ANIM));
			break;
		default:
			break;
		}

		
	
		// 生成座標の決定
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT, GAME_SCREEN_RIGHT);
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT-100);
		//CreateRamdomPos = D3DXVECTOR2(SCREEN_CENTER);
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// 代入

		// 当たり判定
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE/2.0f);


		// 移動の目的位置決定
		m_pStarData->m_Destination = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);
		// 星から目的地方向の単位ベクトルを求める
		m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());

	

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

	// 更新
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){


		// 使用されていないのは飛ばす
		if (!m_pStarData->m_bUse)
			continue;

		// 当たり判定
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);


		// 目的位置についたら消去イベント開始Ｙ軸で決める
		if (m_pStarData->m_sprite.GetPos().y >= m_pStarData->m_Destination.y )
		{
			m_pStarData->m_bDestroyEvent = true;
			m_pStarData->m_bAddScore = true;

			if (!m_pStarData->m_bEffectSetFlag)
			{
				// エフェクトの設定
				GetEffectManeger()->SetEffectBezierCurve(cTextureManeger::GetTextureGame(TEX_GAME_UKI),
					m_pStarData->m_sprite.GetPos(),
					D3DXVECTOR2(EFFECT_BEZIERCURVE_SIZE, EFFECT_BEZIERCURVE_SIZE),
					D3DXCOLOR(255, 255, 255, 255),
					EFFECT_BEZIERCURVE_FRAME,
					m_pStarData->m_sprite.GetPos(),
					m_pGageData->GetGageSprite().GetPos() + m_pGageData->GetGageSprite().GetSize() / 2);

				//エフェクト使用フラグをOnに
				m_pStarData->m_bEffectSetFlag = true;

			}

		}

		// アニメーション
		m_pStarData->m_sprite.AnimationLoop();
	

		//エフェクト表示中
		if (m_pStarData->m_bEffectSetFlag)
		{
			//エフェクト表示フレームの加算
			m_pStarData->m_nEffectFrame++;
			if (!m_pGageData->GetGagemax() && m_pStarData->m_nEffectFrame == EFFECT_BEZIERCURVE_FRAME)
			{
				m_pGageData->GageAdd();
	}
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
		
		// 当たり判定
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);

		if (m_pStarData->m_bDraw)
		{
		// エフェクト生成フレームの加算
		m_pStarData->m_nEffectSetTime--;

		//フレームが一定値になったらエフェクトの生成
		if (m_pStarData->m_nEffectSetTime < 0)
		{
			GetEffectManeger()->SetEffectSparkle(cTextureManeger::GetTextureGame(TEX_GAME_EFFECT_SPARKLE),
												 m_pStarData->m_sprite.GetPos(),
												 D3DXVECTOR2(EFFECT_SIZE, EFFECT_SIZE),
												 m_pStarData->m_sprite.GetVtxColor(),
												 EFFECT_FRAME / 2,
												 D3DXVECTOR2(EFFECT_RADIUS, EFFECT_RADIUS),
																	  EFFECT_SPARKLE_TEX_DIVIDE_X, EFFECT_SPARKLE_TEX_DIVIDE_Y);

			m_pStarData->m_nEffectSetTime = CRandam::RandamRenge(0, EFFECT_FRAME);
		}
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
void cNormalStar::Draw(){

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// 描画
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bDraw)
			continue;

		m_pStarData->m_sprite.Draw();

		//if (m_pStarData->m_bUse)
		//	m_pStarData->m_Collision.Draw();
	}

	// 先頭に戻す
	m_pStarData = m_pRoot;


	// デバッグプリント
	PrintDebugProc("━━━━━━モブ星━━━━━━\n");
	PrintDebugProc("現在の数 %d/%d\n", m_nCurrentNum, m_nMaxNum);
	PrintDebugProc("Rキーでリセット\n");
	PrintDebugProc("リスポーンインターバル確認 %d/%d\n", m_pStarData->m_nRespawnFrame, RESPAWN_FREAM);
	PrintDebugProc("Anim %d\n", m_pStarData->m_sprite.GetCurrentAnimPattern());
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

		// スコア加算
		if (m_pStarData->m_bAddScore){
			AddScore(100);
			m_pStarData->m_bAddScore = false;
		}


		//	リセット
		m_pStarData->m_bDestroyEnd = false;
		m_pStarData->m_bDraw = false;
		m_pStarData->m_bDestroyEvent = false;

		// 終了したら即リスポーン準備
		m_pStarData->m_bRespawnEvent = true;

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

			// 生成座標の決定
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = (float)CRandam::RandamRenge(GAME_SCREEN_LEFT, GAME_SCREEN_RIGHT);
			CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// 代入

			// サイズの変更
			float size = (CRandam::RandamRenge(STAR_SIZE, STAR_SIZE + STAR_SIZE_MARGIN));
			m_pStarData->m_sprite.SetSize(D3DXVECTOR2(size, size));

			// 星から目的地方向の単位ベクトルを求める
			m_pStarData->m_VecStarToDest = UnitVector(m_pStarData->m_Destination - m_pStarData->m_sprite.GetPos());

			// 星の色の決定
			m_pStarData->m_nStarColorNum = CRandam::RandamRenge(0, 3);
			switch (m_pStarData->m_nStarColorNum)
			{
			case 0:
				m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_YELLOW_STAR_ANIM));
				break;
			case 1:
				m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_GREEN_STAR_ANIM));
				break;
			case 2:
				m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_PINK_STAR_ANIM));
				break;
			default:
				break;
			}



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


		m_pStarData->m_bEffectSetFlag = false;
		m_pStarData->m_nEffectFrame = 0;

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


	// Vector確認用
	m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_VecStarToDest*5);
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
void cNormalStar::OnCollidToBlackHoleVacumeRange(int Normal, int Black){

	m_pStarData = m_pRoot;
	m_pStarData += Normal;

	// 振動する
	if (m_pStarData->m_bVibration){

		m_pStarData->m_nVibrationFrame++;
		m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() + 0.15f);

		if (m_pStarData->m_nVibrationFrame > 5){
			m_pStarData->m_bVibration = false;
			m_pStarData->m_nVibrationFrame = 0;
		}	
	}

	else if (!m_pStarData->m_bVibration){

		m_pStarData->m_nVibrationFrame++;
		m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() - 0.15f);

		if (m_pStarData->m_nVibrationFrame > 5){
			m_pStarData->m_bVibration = true;
			m_pStarData->m_nVibrationFrame = 0;
		}
	}


	// ブラックホールの中心を取得
	D3DXVECTOR2 Center = m_pBlackHoleData->GetStarData()[Black].m_sprite.GetPos();

	// 星からブラックホール方向への単位ベクトルを求める
	D3DXVECTOR2 VecStarToBlack;
	VecStarToBlack = UnitVector(Center - m_pStarData->m_sprite.GetPos())*0.1f;

	// 移動反映
	m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + VecStarToBlack);
	

}

//---- ブラックホールの削除範囲に当たった時の処理 -----
void cNormalStar::OnCollidToBlackHoleDeleteRange(int Normal){

	m_pStarData = m_pRoot;
	m_pStarData += Normal;

	m_pStarData->m_bDestroyEvent = true;
	m_pStarData->m_bAddScore = false;
	
}


//=======================================================================================
//
//		隕石との処理
//
//=======================================================================================
void cNormalStar::OnCollidToSpaceRock(int num){

	m_pStarData = m_pRoot;
	m_pStarData += num;




	m_pStarData->m_bDestroyEvent = true;
	m_pStarData->m_bAddScore = false;
}

//=======================================================================================
//
//		ゲージとの処理
//
//=======================================================================================
//---- ゲージの情報を取得 -----
void cNormalStar::SetGageData(cGage* data)
{
	m_pGageData = data;
}