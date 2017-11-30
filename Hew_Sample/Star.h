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
	virtual void Update() = 0;	// �K�{
	virtual void Draw() = 0;	// �K�{
	virtual ~cBaseStar(){}		// �f�X�g���N�^���I�[�o���C�h�����邽��
};


//----�p���p �~�O����----
class cCircleOrbitStar :public cBaseStar{

public:



	 void Init(LPDIRECT3DTEXTURE9* pTex);	// ������ �e�N�X�`���̃|�C���^���󂯎����
	 void Update();				// �K�{
	 void Draw();				// �K�{
	 void Uninit();				// �I��

	 ~cCircleOrbitStar(){}		// �f�X�g���N�^
	 cCircleOrbitStar();		// �R���X�g���N�^
private:
	cSpriteParam	m_sprite;		// �`��p
	cCollider		m_collision;	// �����蔻��	
	D3DXVECTOR2		m_fMove;		// �ړ���

};



#endif	//!___STAR_H___