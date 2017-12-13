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
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ~cBaseStar(){}
	cBaseStar(){}

protected:
	cSpriteParam	m_sprite;		// �`��p
};

//----�~�O���ړ��N���X------�~�O�����������N���X�ɂ�������(���ȊO�ɂ��g���܂�)
class cCircleOrbitMovement{

public:
	cCircleOrbitMovement();
	~cCircleOrbitMovement();

	D3DXVECTOR2 GetMove();	// �ړ���̍��W���擾


	//----�Z�b�g�p-----
	void SetCenter(D3DXVECTOR2 data){
		m_center = data;
	}
	void SetRadius(D3DXVECTOR2 data){	// �����͊�{�O�ł����͂�
		m_radius = data;
	}
	void SetRad(float data){
		m_fRad = data;
	}
	void SetSpped(float data){
		m_fSpeed = data;
	}

private:
	D3DXVECTOR2	m_center;	// �~�O���̒��S
	D3DXVECTOR2	m_radius;	// ���a
	float		m_fRad;		// �p�x
	float		m_fSpeed;	// ����
};

//******���u��********
class cNormalStar :public cBaseStar{

public:
	 void Update();
	 void Draw();

	 ~cNormalStar();
	 cNormalStar();

	 // ���̐ݒ�
	 void SetCircleOrbitStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

	 // �P���Ƃ̋����ɂ���Ă݂��邩�����Ȃ�����ς��鏈��
	 void StarVisibility(float distance);

	 // �v�Z�p�̈ʒu���擾
	 D3DXVECTOR2 GetPos(){
		 return m_sprite.GetPos();
	 }

private:
	cCircleOrbitMovement moveCircle;	// �~�O�����邽�߂ɕK�v
	
};


//******�P��********
class cFixedStar:public cBaseStar{

public:
	void Update();
	void Draw();

	~cFixedStar();
	cFixedStar();

	// ���̐ݒ�
	void SetFixedStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int time);

	// �v�Z�p�̈ʒu���擾
	D3DXVECTOR2 GetPos(){
		return m_sprite.GetPos();
	}

private:
	cCircleOrbitMovement moveCircle;
	bool m_bSizeSwitch;
	
};








// ���̐ݒ�p�\����
typedef struct _tSetCircleOrbitStar{

	D3DXVECTOR2		center;		// �O���̒��S���W
	D3DXVECTOR2		radius;		// ���a
	float			rad;		// �p�x
	int				second;		// ����ɂ����鎞��(�b)

}tSetCircleOrbitStaretStar;

typedef struct _tFixedStar{

	D3DXVECTOR2		center;		// �O���̒��S���W
	D3DXVECTOR2		radius;		// ���a
	float			rad;		// �p�x
	int				second;		// ����ɂ����鎞��(�b)

}tFixedStar;

// ���̐ݒ�p
//vector<tFixedStar>					a_SetFixedStarData;
//vector<tSetCircleOrbitStaretStar>	a_SetCircleOrbitStaretStar;

#endif	//!___STAR_H___