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


//-----------------------------
// マクロ定義
//-----------------------------
#define STAR_SIZE	(100)

#define VACUUM_RANGE	(200)
#define DELETE_RANGE	(20)

#define RESPAWN_FREAM	(20)

//=======================================================================================
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
	m_pStarData = new cBlackHoleData[m_nMaxNum]();
	m_pRoot		= m_pStarData;							// 先頭アドレス保存



	// 初期化
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		


		m_pStarData->m_sprite.SetVtxColorA(10);
		m_pStarData->rad = 0;

		// 座標の決定
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// 代入


	}




}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cBlackHole::~cBlackHole(){

	m_pStarData = m_pRoot;
	delete[]  m_pStarData;
	m_pStarData = NULL;

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cBlackHole::Update(){

	// 先頭に戻す
	m_pStarData = m_pRoot;


	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
		
	

		// イベントが呼び出される感じ
		if (m_pStarData->m_bCreateEvent){
			Create();
		}






	}

	// デバッグキー
	if (GetKeyboardTrigger(DIK_K)){
		m_pStarData = m_pRoot;	// 先頭に戻す
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

			if (m_pStarData->m_bUse)
				continue;

			m_pStarData->m_bCreateEvent = true;
			break;
		}
	}



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
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++,m_pStarData++){

		if (!m_pStarData->m_bUse)
			continue;

			m_pStarData->m_sprite.Draw();
	}

	PrintDebugProc("Kキーで生成仮\n");
}


//=======================================================================================
//
//		生成
//
//=======================================================================================
void cBlackHole::Create(){
	
	// 生成イベントの開始
	if(!m_pStarData->m_bCreateEnd){



		// ここ以外は同じ処理になるはずだからコピぺでいいはず
		//****** ここに演出とか生成処理を書いていく **********
		m_pStarData->m_bUse = true;




		// 回転てきとう
		m_pStarData->rad += 0.01f;
		m_pStarData->m_sprite.SetRad(m_pStarData->m_sprite.GetRad() + m_pStarData->rad);

		//****************************************************



		// 演出がおわったら生成終了フラグを立てる
		//m_pStarData->m_bCreateEnd = true;

		// 今回はある程度回転したら終了
		if (m_pStarData->rad > 1.0f){
			m_pStarData->m_bCreateEnd = true;

		}

	}


	// 生成終了フラグが立ったらイベントフラグをオフにして終了
	if (m_pStarData->m_bCreateEnd){
		m_pStarData->m_bCreateEvent = false;
		return;
	}
}
