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


};


//----�~�O����----
class cCircleOrbitStar :public cBaseStar{

public:
	 void Init();
	 void Update();
	 void Draw();
	 void UnInit();

	 ~cCircleOrbitStar(){}
	 cCircleOrbitStar() :m_center(D3DXVECTOR2(100.0f, 100.0f)), m_radius(D3DXVECTOR2(50.0f,50.0f)), m_rad(D3DX_PI){}

	 // ���̐ݒ�
	 void SetcCircleOrbitStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

private:
	cSpriteParam	m_sprite;		// �`��p
	cCollider		m_collision;	// �����蔻��	
	D3DXVECTOR2		m_center;		// �O���̒��S���W
	D3DXVECTOR2		m_radius;		// ���a
	float			m_rad;			// �p�x
	int				m_second;		// ����ɂ����鎞��(�b)
};



#endif	//!___STAR_H___