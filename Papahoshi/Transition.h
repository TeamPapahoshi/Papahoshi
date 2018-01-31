//======================================================================
//	Transition
//	
//	�T�v�Q�F�V�[���؂�ւ����o
//	����ҁF�㓡 ����
//	
//======================================================================

#ifndef __TRANSITION_H__
#define __TRANSITION_H__

//---------------------------
// �C���N���[�h��
//---------------------------
#include "Sprite.h"


//---------------------------
// �萔�E�}�N����`
//---------------------------
#define DICE_X_NUM (10)
#define DICE_Y_NUM (5)

//---------------------------
// �N���X��`
//---------------------------
//----�g�����W�V������{�N���X----//
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

	void SetTransition(int nextScene);	//���̃V�[���ԍ���ݒ�
	bool FinishCall();

	cTransition() : m_bFinish(false),m_nextScene(0),m_bOut(false){}

protected:
	bool m_bFinish;
	int m_nextScene;
	bool m_bOut;
};

//---- �t�F�[�h�C���E�A�E�g ----//
class cTransitonFade : public cTransition{
public:
	cTransitonFade();
	~cTransitonFade();
	void Update();
	void Draw();

private:
	cSpriteParam spriteParam;
};

//---- �����̖ڂ̉摜���g��k�������� ----//
class cTransitonDiceScaleChange : public cTransition{
public:
	cTransitonDiceScaleChange();
	~cTransitonDiceScaleChange();
	void Update();
	void Draw();

private:
	cSpriteParam spriteParam[DICE_Y_NUM][DICE_X_NUM];
};

//---- ��]���Ȃ��炨�������Ȃ�� ----//
class cTransitonOnceRotation : public cTransition{
public:
	cTransitonOnceRotation();
	~cTransitonOnceRotation();
	void Update();
	void Draw();

private:
	cSpriteParam spriteParam;
};

//---- �����_���Ƀ^�C���𐶐����܂��I ----//
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