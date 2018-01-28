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

	// �v�Z�p�̈ʒu���擾
	D3DXVECTOR2 GetPos(){
		return m_sprite.GetPos();
	}

protected:
	cSpriteParam	m_sprite;		// 

	int					m_nMaxNum;
	int					m_nCurrentNum;
	//--- �t���O ---
	bool	m_bCapchared;	// �m�ۊ���
	//--- �t���[���֘A ---
	int m_nRespawnFream;	// ���X�|�[��
};


class cBaseStarData{

public:
	virtual void Create();
	virtual void Respawn();


protected:

	cSpriteParam			m_Sprite;			// �`��p
	cCollider				m_Collider;			// ������
	bool					m_bUse;				// �g�p�t���O
	int						m_nRespawnFrame;	// ���X�|�[���t���[��
	bool					m_bRespawn;			// ���X�|�[���t���O


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