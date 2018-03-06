//======================================================================
//	SampleStar
//	
//	概要＿：コピー用星　　このままコピーして使えるヘッダーと一緒に
//	制作者：加藤　遼				組みなおしたい泣
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
#include "SampleStar.h"
#include "Input.h"


//-----------------------------
// マクロ定義
//-----------------------------
#define DEFAULT_STAR_SIZE			(100)
#define MAX_SAMPLE_STAR_NUM			(50)

//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cSampleStar::cSampleStar(){

	// 乱数の初期化
	CRandam::InitRand();

	// 使用数を格納ファイルから読み込むけどだいぶ変更したから
	m_nMaxNum = MAX_SAMPLE_STAR_NUM;

	// 動的インスタンス
	m_pStarData = new cSampleStarData[m_nMaxNum]();//ここ注意
	m_pRoot = m_pStarData;							// 先頭アドレス保存



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
cSampleStar::~cSampleStar(){

	m_pStarData = m_pRoot;
	delete[]  m_pStarData;
	m_pStarData = NULL;

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSampleStar::Update(){

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
	}



	//// デバッグキー
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
void cSampleStar::Draw(){

	// 先頭に戻す
	m_pStarData = m_pRoot;

	// 描画
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bDraw)
			continue;

		m_pStarData->m_sprite.Draw();
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
void cSampleStar::Create(){

	// 生成イベントの開始
	if (!m_pStarData->m_bCreateEnd){



		// ここ以外は同じ処理になるはずだからコピぺでいいはず
		//****** ここに演出とか生成処理を書いていく **********
		//m_pStarData->m_bUse = true;->これでもできるけど今回は数もかぞえておきたいから
		m_pStarData->m_bDraw = true;

	




		// 回転てきとう
		m_pStarData->rad += 0.01f;
		m_pStarData->m_sprite.SetRad(m_pStarData->m_sprite.GetRad() + m_pStarData->rad);

		//****************************************************



		// 演出がおわったら生成終了フラグを立てる->if(EffectEnd()){m_pStar->....}
		//m_pStarData->m_bCreateEnd = true;

		// 今回はある程度回転したら終了->if(EffectEnd()){m_pStar->....}
		if (m_pStarData->rad > 1.0f){
			m_pStarData->m_bCreateEnd = true;

		}

	}


	// 生成終了フラグが立ったらリセットして終了
	if (m_pStarData->m_bCreateEnd){

		//	リセット
		m_pStarData->m_bCreateEnd = false;
		m_pStarData->rad = 0;					// ちゃんといニットとアンいニットにたいのつくるといいかも

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
void cSampleStar::Destroy(){

	// 生成イベントの開始
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);

		// ここ以外は同じ処理になるはずだからコピぺでいいはず
		//****** ここに演出とか処理を書いていく **********
	




		// 回転てきとう
		m_pStarData->rad += 0.01f;
		m_pStarData->m_sprite.SetRad(m_pStarData->m_sprite.GetRad() + m_pStarData->rad);

		//****************************************************


		// 演出がおわったら終了フラグを立てる->if(EffectEnd()){m_pStar->....}
		//m_pStarData->m_bCreateEnd = true;

		// 今回はある程度回転したら終了->if(EffectEnd()){m_pStar->....}
		if (m_pStarData->rad > 1.0f){
			m_pStarData->m_bDestroyEnd = true;
			//m_pStarData->m_bUse = false;
			

		}

	}

	// 生成終了フラグが立ったらリセットして終了
	if (m_pStarData->m_bDestroyEnd){

		//	リセット
		m_pStarData->m_bDestroyEnd = false;
		m_pStarData->rad = 0;
		m_pStarData->m_bDraw = false;
		m_pStarData->m_bDestroyEvent = false;
		return;
	}
}