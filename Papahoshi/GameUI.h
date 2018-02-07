//=====================================================
//
//  Papahoshi  GameUI.h
//
//  Mei Goto.
//
//=====================================================

//-----------------------
// インクルード部
//-----------------------
#include "Sprite.h"


//------------------------
// クラス定義
//------------------------
class cGameUI{

public:
	cGameUI();
	~cGameUI();
	void Update();
	void Draw();

private:

	//UIのベースアイテム
	cSpriteParam m_baseSprite[4];

	//----- ベースUI ------
	void ChangeColorBaseUI();
	int		m_nChangeColorBaseUI;
	float	m_fDirectColorBaseUI;

};