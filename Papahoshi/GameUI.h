//=====================================================
//
//  Papahoshi  GameUI.h
//
//  Mei Goto.
//
//=====================================================

#ifndef __GAME_UI_H__
#define __GAME_UI_H__

//-----------------------
// �C���N���[�h��
//-----------------------
#include "Sprite.h"

//-----------------------
// �萔��`
//-----------------------
#define MAX_BASEUI_ITEM		(50)

#define UI_WIDTH_DIVIDE		(4.0f)
#define UI_HEIGHT_DIVIDE	(50.0f)

#define GAME_SCREEN_LEFT	((float)SCREEN_WIDTH / UI_WIDTH_DIVIDE)
#define GAME_SCREEN_RIGHT	((float)SCREEN_WIDTH - ((float)SCREEN_HEIGHT / UI_HEIGHT_DIVIDE))
#define GAME_SCREEN_TOP		((float)SCREEN_HEIGHT / UI_HEIGHT_DIVIDE)
#define GAME_SCREEN_UNDER	((float)SCREEN_HEIGHT - ((float)SCREEN_HEIGHT / UI_HEIGHT_DIVIDE))	

//�w�i�J���[
#define START_COLOR			(D3DXCOLOR(255.0f, 199.0f, 199.0f, 255.0f))
#define START_CHANGE_COL	(3)	//R1 G2 B3
#define START_UNDER_COL		(199.0f)
#define COLOR_CHANGE_SPEED	(1.0f)    

//FEVER�w�i�J���[
#define FEVER_START_COLOR	(D3DXCOLOR(255.0f, 255.0f, 61.0f, 255.0f))
#define FEVER_COLOR_CHANGE_SPEED		(8.0f)

//HurryUo�w�i�J���[
#define HURRY_UP_MAX_COLOR	(D3DXCOLOR(255.0f, 20.0f, 20.0f, 255.0f))
#define HURRY_UP_MIN_COLOR	(D3DXCOLOR(255.0f, 120.0f, 120.0f, 255.0f))
#define HURRY_UP_CHANGE_SPEED	(4.0f)

//------------------------
// �N���X��`
//------------------------
//----- UI�A�C�e�� ------
class cUIItem{

public:
	enum ITEM_TYPE{
		CIRCLE1,
		CIRCLE2,
		CIRCLE3,
		PENTAGON1,
		PENTAGON2,
		LIGHT1,
		LIGHT2,
		CRYSTAL1,
		CRYSTAL2,
		MAX,
	};

	cUIItem(ITEM_TYPE Tex, D3DXVECTOR2 pos, float size, D3DXCOLOR col, float speed);
	~cUIItem();
	void Update();
	void Draw();

	bool CallFin(){
		return m_bFin;
	}

private:
	cSpriteParam	m_sprite;
	float			m_fSpeed;
	bool			m_bFin;
};

//----- �`�A�K�[�� ------
class cTheerGirl{

public:
	
	//--- �񋓌^ ----
	enum eGirlMotion{
		NOMAL,
		FEVER,
	};

	cTheerGirl();
	~cTheerGirl();
	void Update();
	void Draw();

	void SetMotion(eGirlMotion motion){
		m_motionType = motion;
		m_nMotionNum = -1;
		m_nMotionFrame = 999;
	}


private:
	eGirlMotion		m_motionType;	//���[�V����
	int				m_nMotionNum;	//���݂̃��[�V�����ԍ�
	int				m_nMotionFrame;	//�t���[����

	cSpriteParam	m_sprite;
};

//----- UI�N���X ------
class cGameUI{

public:

	enum eUItype{
		NOMAL,
		FEVER,
		HURRY_UP,
	};

	cGameUI();
	~cGameUI();
	void Update();
	void Draw();

	void SetTheerMotion(cTheerGirl::eGirlMotion motion){
		m_pTheerGirl->SetMotion(motion);
	}

	void SetUiType(eUItype type){
		m_type = type;

		switch (type)
		{
		case cGameUI::NOMAL:
			for (int i = 0; i < 4; i++){
				m_baseSprite[i].SetVtxColor(START_COLOR);
				m_nChangeColorBaseUI = START_CHANGE_COL;
				m_fDirectColorBaseUI = COLOR_CHANGE_SPEED;
			}
			break;
		case cGameUI::FEVER:
			for (int i = 0; i < 4; i++){
				m_baseSprite[i].SetVtxColor(FEVER_START_COLOR);
				m_fDirectColorBaseUI = -COLOR_CHANGE_SPEED;
			}
			break;
		case cGameUI::HURRY_UP:
			for (int i = 0; i < 4; i++){
				m_baseSprite[i].SetVtxColor(HURRY_UP_MIN_COLOR);
				m_fDirectColorBaseUI = -COLOR_CHANGE_SPEED;
			}
			break;
		}
	}

private:

	//----- �x�[�XUI ------
	cSpriteParam m_baseSprite[4];
	int		m_nChangeColorBaseUI;
	float	m_fDirectColorBaseUI;

	//----- �x�[�XUI�̃L���L������ ------
	cUIItem*	m_aItem[MAX_BASEUI_ITEM];
	void		UpdateItem();
	int			SetItem();

	//------ �����\�� -----
	cSpriteParam m_scoreString;
	cSpriteParam m_timeString;

	//------ �`�A�K�[�� -----
	cTheerGirl*	m_pTheerGirl;

	//---- UI��� ----
	eUItype		m_type;

	//---- BaseUI�̍X�V�֐� -----
	void NomalUiUpdate();
	void FeverUiUpdate();
	void HurryUpUiUpdate();

};


#endif