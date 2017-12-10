//======================================================================
//	Star
//	
//	�T�v�Q�F���N���X�Ȃ�
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___STAR_H___
#define ___STAR_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Sprite.h"
#include "Collision.h"



//-----------------------------
//�N���X��`
//-----------------------------
//----�p���p ����{�N���X----
class cBaseStar{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void UnInit() = 0;
	virtual ~cBaseStar(){}
	cBaseStar():m_center(D3DXVECTOR2(100.0f, 100.0f)), m_radius(D3DXVECTOR2(50.0f, 50.0f)), m_rad(D3DX_PI){}

protected:

	// �~�O������ۂɕK�v
	cSpriteParam	m_sprite;		// �`��p
	cCollider		m_collision;	// �����蔻��	
	D3DXVECTOR2		m_center;		// �O���̒��S���W
	D3DXVECTOR2		m_radius;		// ���a
	float			m_rad;			// �p�x
	int				m_second;		// ����ɂ����鎞��(�b)

	//

};


//-----���̌�------
//class cStarLight{
//
//public:
//
//	cStarLight(){
//
//	}
//	~cStarLight(){
//
//	}
//
//	void Init();
//	void Update();
//	void Draw();
//	void UnInit();
//
//	void SetPos(D3DXVECTOR2 pos);
//private:
//	cSpriteParam m_sprite;
//
//
//};


//******�~�O����********
class cCircleOrbitStar :public cBaseStar{

public:
	 void Init();
	 void Update();
	 void Draw();
	 void UnInit();

	 ~cCircleOrbitStar(){}
	 cCircleOrbitStar(){}

	 // ���̐ݒ�
	 void SetCircleOrbitStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

private:

	//bool			m_lightSwitch;	// ���������邩 
	//cStarLight		m_Light;		// ��
};


//******�P��********
class cFixedStar:public cBaseStar{

public:
	void Init();
	void Update();
	void Draw();
	void UnInit();

	~cFixedStar(){}
	cFixedStar() :m_bSizeSwitch(true){}

	// ���̐ݒ�
	void SetFixedStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);
private:
	bool m_bSizeSwitch;
};

#endif	//!___STAR_H___