//=====================================================
//
//  Papahoshi  GameUI.h
//
//  Mei Goto.
//
//=====================================================

//-----------------------
// �C���N���[�h��
//-----------------------
#include "Sprite.h"


//------------------------
// �N���X��`
//------------------------
class cGameUI{

public:
	cGameUI();
	~cGameUI();
	void Update();
	void Draw();

private:

	//UI�̃x�[�X�A�C�e��
	cSpriteParam m_baseSprite[4];

	//----- �x�[�XUI ------
	void ChangeColorBaseUI();
	int		m_nChangeColorBaseUI;
	float	m_fDirectColorBaseUI;

};