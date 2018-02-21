//=====================================================
//
//  Papahoshi  GameUI.h
//
//  Mei Goto.
//
//=====================================================
//
// ���`�A�K�[������
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

#define GAME_SCREEN_LEFT	(SCREEN_WIDTH / UI_WIDTH_DIVIDE)
#define GAME_SCREEN_RIGHT	(SCREEN_WIDTH - (SCREEN_HEIGHT / UI_HEIGHT_DIVIDE))
#define GAME_SCREEN_TOP		(SCREEN_HEIGHT / UI_HEIGHT_DIVIDE)
#define GAME_SCREEN_UNDER	(SCREEN_HEIGHT - (SCREEN_HEIGHT / UI_HEIGHT_DIVIDE))	

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
	cGameUI();
	~cGameUI();
	void Update();
	void Draw();

	void SetTheerMotion(cTheerGirl::eGirlMotion motion){
		m_pTheerGirl->SetMotion(motion);
	}

private:

	//----- �x�[�XUI ------
	cSpriteParam m_baseSprite[4];
	void ChangeColorBaseUI();
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

};


#endif