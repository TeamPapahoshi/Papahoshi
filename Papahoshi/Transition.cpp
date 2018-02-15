//======================================================================
//	Transition
//	
//	概要＿：画面切り替え効果
//	制作者：後藤 愛生
//	
//======================================================================

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Transition.h"
#include "Common.h"
#include "SceneManeger.h"
#include <stdlib.h>
#include <time.h>

//-----------------------------
// 定数・マクロ定義
//-----------------------------
//テクスチャ
#define TEX_FILENAME_STAR "Image/Transition/Star.png"
#define TEX_FILENAME_WHITE "Image/Transition/White.png"

//ダイス系
#define MAX_SIZE_DICE (300.0f)
#define NEXT_MOVE_SIZE_DICE (80.0f)
#define INCREMENT_SIZE_DICE (5.0f)

//フェード系
#define INCREMENT_ALPHA (10)

//拡大系
#define MAX_SIZE_ONCE (SCREEN_WIDTH * 5.0f)
#define INCREMENT_SIZE_ONCE (60.0f)

//回転系
#define ROTATION_SPEED (0.04f)

//乱数系
#define UPDATE_FRAME (2)

bool cTransition::m_bFinish = false;

//====================================
// 終了報告関数
//====================================
bool cTransition::FinishCall(){
	return m_bFinish;
}

//====================================
// 次のシーン番号をセット
//====================================
void cTransition::SetTransition(int nextScene){
	m_nextScene = nextScene;
}


//***************************************************************************//
//******************************** フェード *********************************//
//***************************************************************************//

//========================================
// コンストラクタ
//========================================
cTransitonFade::cTransitonFade() : cTransition(){

	spriteParam.LoadTexture(TEX_FILENAME_WHITE);
	spriteParam.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
	spriteParam.SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	spriteParam.SetTexPatternDevide(1, 1);
	spriteParam.SetCurrentAnimPattern(0);
	spriteParam.SetVtxColorA(0);

}

//========================================
// デストラクタ
//========================================
cTransitonFade::~cTransitonFade(){



}

//========================================
// 更新処理
//========================================
void cTransitonFade::Update(){

	if (!m_bOut){
		spriteParam.SetVtxColorA(spriteParam.GetVtxColorA() + INCREMENT_ALPHA);
		if (spriteParam.GetVtxColorA() >= 255){
			spriteParam.SetVtxColorA(255);
			m_bOut = true;
			cSceneManeger::ChangeScene((cSceneManeger::SCENE)m_nextScene);
		}
	}
	else{
		spriteParam.SetVtxColorA(spriteParam.GetVtxColorA() - INCREMENT_ALPHA);
		if (spriteParam.GetVtxColorA() <= 0){
			spriteParam.SetVtxColorA(0);
			m_bFinish = true;
		}
	}

}

//========================================
// 描画処理
//========================================
void cTransitonFade::Draw(){

	spriteParam.Draw();

}



//***************************************************************************//
//******************* さいの目の画像が拡大縮小するやつ **********************//
//***************************************************************************//

//========================================
// コンストラクタ
//========================================
cTransitonDiceScaleChange::cTransitonDiceScaleChange() : cTransition(){

	D3DXVECTOR2 work;

	//画像情報の初期化
	for (int y = 0; y < DICE_Y_NUM; y++){
		for (int x = 0; x < DICE_X_NUM; x++){
			spriteParam[y][x].LoadTexture(TEX_FILENAME_STAR);
			work.x = (SCREEN_WIDTH / (DICE_X_NUM * 2)) + (SCREEN_WIDTH / DICE_X_NUM * x);
			work.y = (SCREEN_HEIGHT / (DICE_Y_NUM * 2)) + (SCREEN_HEIGHT / DICE_Y_NUM * y);
			spriteParam[y][x].SetPos(work);
			spriteParam[y][x].SetSize(D3DXVECTOR2(0.0f, 0.0f));
			spriteParam[y][x].SetTexPatternDevide(1, 1);
			spriteParam[y][x].SetCurrentAnimPattern(0);
		}
	}

}

//========================================
// デストラクタ
//========================================
cTransitonDiceScaleChange::~cTransitonDiceScaleChange(){



}

//========================================
// 更新処理
//========================================
void cTransitonDiceScaleChange::Update(){

	//大きくなるよ
	if (!m_bOut){
		for (int y = 0; y < DICE_Y_NUM; y++){
			if (y == 0 || spriteParam[y - 1][0].GetSizeX() >= NEXT_MOVE_SIZE_DICE){
				for (int x = 0; x < DICE_X_NUM; x++){
					spriteParam[y][x].SetSize(D3DXVECTOR2(spriteParam[y][0].GetSizeX() + INCREMENT_SIZE_DICE, spriteParam[y][0].GetSizeY() + INCREMENT_SIZE_DICE));
				}
			}
		}
		if (spriteParam[DICE_Y_NUM - 1][0].GetSizeX() >= MAX_SIZE_DICE){
			cSceneManeger::ChangeScene((cSceneManeger::SCENE)m_nextScene);
			m_bOut = true;
		}
	}
	//小さくなるよ
	else{
		for (int y = 0; y < DICE_Y_NUM; y++){
			for (int x = 0; x < DICE_X_NUM; x++){
				spriteParam[y][x].SetSize(D3DXVECTOR2(spriteParam[y][0].GetSizeX() - INCREMENT_SIZE_DICE, spriteParam[y][0].GetSizeY() - INCREMENT_SIZE_DICE));
				if (spriteParam[y][x].GetSizeX() < 0.0f)
					spriteParam[y][x].SetSize(D3DXVECTOR2(0.0f, 0.0f));
			}
		}
		if (spriteParam[0][0].GetSizeX() <= 0.0f)
			m_bFinish = true;
	}

}

//========================================
// 描画処理
//========================================
void cTransitonDiceScaleChange::Draw(){

	for (int y = 0; y < DICE_Y_NUM; y++){
		for (int x = 0; x < DICE_X_NUM; x++){
			spriteParam[y][x].Draw();
		}
	}

}


//***************************************************************************//
//************************ 回転しながら大きくなるよ *************************//
//***************************************************************************//

//========================================
// コンストラクタ
//========================================
cTransitonOnceRotation::cTransitonOnceRotation() : cTransition(){

	spriteParam.LoadTexture(TEX_FILENAME_STAR);
	spriteParam.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
	spriteParam.SetSize(D3DXVECTOR2(0.0f, 0.0f));
	spriteParam.SetTexPatternDevide(1, 1);
	spriteParam.SetCurrentAnimPattern(0);

}

//========================================
// デストラクタ
//========================================
cTransitonOnceRotation::~cTransitonOnceRotation(){



}

//========================================
// 更新処理
//========================================
void cTransitonOnceRotation::Update(){

	if (!m_bOut){
		spriteParam.SetSize(D3DXVECTOR2(spriteParam.GetSizeX() + INCREMENT_SIZE_ONCE, spriteParam.GetSizeY() + INCREMENT_SIZE_ONCE));
		if (spriteParam.GetSizeX() >= MAX_SIZE_ONCE){
			m_bOut = true;
			cSceneManeger::ChangeScene((cSceneManeger::SCENE)m_nextScene);
		}
	}
	else{
		spriteParam.SetSize(D3DXVECTOR2(spriteParam.GetSizeX() - INCREMENT_SIZE_ONCE, spriteParam.GetSizeY() - INCREMENT_SIZE_ONCE));
		if (spriteParam.GetSizeX() <= 0.0f){
			m_bFinish = true;
		}
	}

	//回転
	spriteParam.SetRad(spriteParam.GetRad() + ROTATION_SPEED);

}

//========================================
// 描画処理
//========================================
void cTransitonOnceRotation::Draw(){

	spriteParam.Draw();

}



//***************************************************************************//
//******************* ランダムタイル生成 ************************************//
//***************************************************************************//

//========================================
// コンストラクタ
//========================================
cTransitionTileCreateRandom::cTransitionTileCreateRandom() : cTransition(), m_nPutNum(0), m_nFrame(0){

	D3DXVECTOR2 work;

	//画像情報の初期化
	for (int y = 0; y < DICE_Y_NUM; y++){
		for (int x = 0; x < DICE_X_NUM; x++){
			spriteParam[y][x].LoadTexture(TEX_FILENAME_WHITE);
			work.x = (SCREEN_WIDTH / (DICE_X_NUM * 2)) + (SCREEN_WIDTH / DICE_X_NUM * x);
			work.y = (SCREEN_HEIGHT / (DICE_Y_NUM * 2)) + (SCREEN_HEIGHT / DICE_Y_NUM * y);
			spriteParam[y][x].SetPos(work);
			spriteParam[y][x].SetSize(D3DXVECTOR2(SCREEN_WIDTH / DICE_X_NUM, SCREEN_HEIGHT / DICE_Y_NUM));
			spriteParam[y][x].SetTexPatternDevide(1, 1);
			spriteParam[y][x].SetCurrentAnimPattern(0);
			m_bPut[y][x] = false;
		}
	}

}

//========================================
// デストラクタ
//========================================
cTransitionTileCreateRandom::~cTransitionTileCreateRandom(){



}

//========================================
// 更新処理
//========================================
void cTransitionTileCreateRandom::Update(){

	//乱数のシード値設定
	srand((unsigned)time(NULL));

	//フレームの加算
	m_nFrame++;

	if (m_nFrame < UPDATE_FRAME)
		return;

	m_nFrame = 0;

	int x, y,cnt = 0;

	while (true)
	{
		//乱数で生成
		x = rand() % DICE_X_NUM;
		y = rand() % DICE_Y_NUM;

		if (!m_bOut){
			if (!m_bPut[y][x]){
				m_bPut[y][x] = true;
				m_nPutNum++;
				if (m_nPutNum >= DICE_X_NUM * DICE_Y_NUM){
					cSceneManeger::ChangeScene((cSceneManeger::SCENE)m_nextScene);
					m_bOut = true;
				}
				return;
			}
		}
		else{
			if (m_bPut[y][x]){
				m_bPut[y][x] = false;
				m_nPutNum--;
				if (m_nPutNum <= 0){
					m_bFinish = true;
				}
				return;
			}
		}

		cnt++;

	}

}

//========================================
// 描画処理
//========================================
void cTransitionTileCreateRandom::Draw(){

	for (int y = 0; y < DICE_Y_NUM; y++){
		for (int x = 0; x < DICE_X_NUM; x++){
			if (m_bPut[y][x])
				spriteParam[y][x].Draw();
		}
	}

}