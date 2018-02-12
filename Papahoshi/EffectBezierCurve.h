//======================================================================
//	EffectVezierCurve.h
//	
//	�T�v�Q�F�Ȑ���`�����̃G�t�F�N�g(�x�W�F�g�p)
//	����ҁF���� ����
//	
//======================================================================
#ifndef ___EFFECTBEZIERCURVE_H___
#define ___EFFECTBEZIERCURVE_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "EffectManeger.h"	

//-----------------------------
//�}�N����`
//-----------------------------
#define MAX_BEZIERCURVEFFECT_SPRITE (1)
#define MAX_POINT (3)

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------
class cEffectBezierCurve : public cBaseEffect
{
private:
	cSpriteParam* m_Sprite[MAX_BEZIERCURVEFFECT_SPRITE];	//�X�v���C�g���̃|�C���^(���I�m�ۂɎg�p)
	D3DXVECTOR2   m_CPoint[MAX_POINT];						//����_�̏��
	float		  m_fPointTime;								//�x�W�F�Ȑ�����ړ����鎞��
	float		  m_fPointInterval;							//�x�W�F�Ȑ�����ړ����鎞�Ԃ̊Ԋu

	//--------------------------------------
protected:
	//--------------------------------------
public:
	cEffectBezierCurve();		//�R���X�g���N�^
	~cEffectBezierCurve();		//�f�X�g���N�^

	void Update(void);			//�X�V�֐�
	void Draw(void);			//�`��֐�
	void Uninit(void);			//�I���֐�

	void SetEffectBezierCurve(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, D3DXVECTOR2 startpoint, D3DXVECTOR2 endpoint);	//�~�`�G�t�F�N�g�̐ݒ�֐�
};

#endif	//!___EFFECTCIECLE_H___