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
//----�p���p �w�i��{�N���X----
class cBaseBG{

public:
	
	virtual ~cBaseBG(){}	// �f�X�g���N�^

	virtual void Init()=0;
	virtual void UnInit()=0;
	virtual void Update() = 0;
	virtual void Draw()=0;
};

//----�w�i�Ǘ��p�N���X----
class cBgManager{

public:
	enum BG{
		NIGHT_SKY,	// ���
	};

	void Init();
	void UnInit();
	void Draw();
	void Update();

	void SetBG(BG bg);

private:
	cBaseBG*   m_pBg;	// �w�i�x�[�X�̃|�C���^

};

// ���
//class cBgNightSky :public cBaseBG{
//
//public:
//	void Init();
//	void UnInit();
//	void Update();
//	void Draw();
//
//	cBgNightSky(){
//
//	//	sprite.LoadTexture()
//
//	}
//
//private:
//	cSpriteParam sprite;	// �`��p
//};
#endif	//!___BG_H___