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

//----- �C���N���[�h����I�u�W�F�N�g ------
#include "TitleWave.h"
#include "TitleShip.h"

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

	void GetTitleWave(cTitleWave* data)
	{
		m_pTitleWave = data;
	}

	void GetTitleShip(cTitleShip* data)
	{
		m_pTitleShip = data;
	}

private:
	cSpriteParam sprite;
	cSpriteParam back;
	BG type;

	cTitleWave* m_pTitleWave;
	cTitleShip* m_pTitleShip;
};
#endif	//!___BG_H___