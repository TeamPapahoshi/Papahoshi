//======================================================================
//	Stage01(チュートリアルステージ？)
//	
//	概要＿：ステージ01(仮)
//	制作者：
//	
//======================================================================

//------------------------------
// インクルードファイル
//------------------------------
#include "Stage01.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"
#include "sound.h"

#include "StageManager.h"


//=======================================================================================
//
//		初期化
//
//=======================================================================================
cStage01::cStage01(){
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cStage01::~cStage01(){

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cStage01::Update(){

	if (GetKeyboardTrigger(DIK_0)){
		cStageManager::ChangeStage(cStageManager::STAGE_02);
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cStage01::Draw(){

}

