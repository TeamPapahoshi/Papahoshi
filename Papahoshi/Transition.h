//======================================================================
//	Transition
//	
//	概要＿：シーン切り替え演出
//	制作者：後藤 愛生
//	
//======================================================================

#ifndef __TRANSITION_H__
#define __TRANSITION_H__

//---------------------------
// インクルード部
//---------------------------
#include "Sprite.h"


//---------------------------
// 定数・マクロ定義
//---------------------------
#define DICE_X_NUM (10)
#define DICE_Y_NUM (5)

//---------------------------
// クラス定義
//---------------------------
//----トランジション基本クラス----//
class cTransition{
public:
	enum TRANSITION_TYPE{
		TRANSITION_FADE,
		TRANSITION_DICE_SCALE_CHANGE,
		TRANSITION_ONCE_ROTATION,
		TRANSITION_TILE_CREATE_RANDOM,
	};

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ~cTransition(){}

	void SetTransition(int nextScene);	//次のシーン番号を設定
	bool FinishCall();

	cTransition() : m_bFinish(false),m_nextScene(0),m_bOut(false){}

protected:
	bool m_bFinish;
	int m_nextScene;
	bool m_bOut;
};

//---- フェードイン・アウト ----//
class cTransitonFade : public cTransition{
public:
	cTransitonFade();
	~cTransitonFade();
	void Update();
	void Draw();

private:
	cSpriteParam spriteParam;
};

//---- さいの目の画像が拡大縮小するやつ ----//
class cTransitonDiceScaleChange : public cTransition{
public:
	cTransitonDiceScaleChange();
	~cTransitonDiceScaleChange();
	void Update();
	void Draw();

private:
	cSpriteParam spriteParam[DICE_Y_NUM][DICE_X_NUM];
};

//---- 回転しながらおっきくなるよ ----//
class cTransitonOnceRotation : public cTransition{
public:
	cTransitonOnceRotation();
	~cTransitonOnceRotation();
	void Update();
	void Draw();

private:
	cSpriteParam spriteParam;
};

//---- ランダムにタイルを生成します！ ----//
class cTransitionTileCreateRandom : public cTransition{
public:
	cTransitionTileCreateRandom();
	~cTransitionTileCreateRandom();
	void Update();
	void Draw();

private:
	cSpriteParam spriteParam[DICE_Y_NUM][DICE_X_NUM];
	bool m_bPut[DICE_Y_NUM][DICE_X_NUM];
	int m_nFrame;
	int m_nPutNum;
};



#endif