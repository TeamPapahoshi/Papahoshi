//======================================================================
//	BG
//	
//	�T�v�Q�F�w�i
//	����ҁF���� ��
//	
//======================================================================
#ifndef ___BG_H___
#define ___BG_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Sprite.h"


//-----------------------------
//�N���X��`
//-----------------------------
//----�w�i�N���X----
class cBG{

public:

	enum BG{
		TITLE,
		GAME_MAIN,
		GAME_SKY,
		RESULT,
	};

	cBG();
	~cBG();

	void Update();
	void Draw();

	void SetBG(BG bg);

private:
	cSpriteParam sprite;
	BG type;
};
#endif	//!___BG_H___