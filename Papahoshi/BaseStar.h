//======================================================================
//	BaseStar
//	
//	�T�v�Q�F���N���X�Ȃ�
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___BASE_STAR_H___
#define ___BASE_STAR_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Sprite.h"
#include "Collision.h"
#include "Common.h"
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

	// �t���O�̃I���I�t�Ɛ��̐��𐔂���
	virtual void SetCountAndUse(bool flag)=0;


protected:
	int					m_nMaxNum;
	int					m_nCurrentNum=0;
};


// �p�����č\���݂̂����Ɏg��
class cBaseStarData{

public:
	virtual ~cBaseStarData(){}

	cBaseStarData(){
		m_bUse = false;
		m_bDraw = false;
		m_bCreateEvent = false;
		m_bCreateEnd	= false;
		m_bDestroyEvent = false;
		m_bDestroyEnd = false;
		m_bRespawnEvent = false;
		m_bRespawnEnd = false;
		m_nRespawnFrame = 0;
	}

	// �ǂ̐��ł��g�����
	cSpriteParam	m_sprite;
	cCollider		m_Collision;

	
	bool			m_bUse;			// �Q�[���Ȃ��ŗL���������蔻��Ƃ�
	bool			m_bDraw;		// �`��t���O

	bool			m_bCreateEvent;	// �����C�x���g
	bool			m_bCreateEnd;

	bool			m_bDestroyEvent;// �폜�C�x���g
	bool			m_bDestroyEnd;

	bool			m_bRespawnEvent;// ���X�|�[���C�x���g
	bool			m_bRespawnEnd;
	int				m_nRespawnFrame;
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

#endif	//!___BASE_STAR_H___