//======================================================================
//	Sample
//	
//	�T�v�Q�F�R�s�[�p
//	����ҁF
//	
//======================================================================
#ifndef ___EFFECTCIRCLE_H___
#define ___EFFECTCIRCLE_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "EffectManeger.h"	

//-----------------------------
//�}�N����`
//-----------------------------
#define MAX_CIRCLEEFFECT_SPRITE (16)

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------
class cEffectCircle : public cBaseEffect
{
private:
	cSpriteParam* m_Sprite[MAX_CIRCLEEFFECT_SPRITE];	//�X�v���C�g���̃|�C���^(���I�m�ۂɎg�p)
	bool          m_bRandamFlag;						//�ړ������������_���ɂ���t���O
	float		  m_bAddRad;

//--------------------------------------
protected:
//--------------------------------------
public:
	cEffectCircle();		//�R���X�g���N�^
	~cEffectCircle();		//�f�X�g���N�^

	void Update(void);			//�X�V�֐�
	void Draw(void);			//�`��֐�
	void Uninit(void);			//�I���֐�

	void SetEffectCircle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, int division, bool flag);	//�~�`�G�t�F�N�g�̐ݒ�֐�
};

#endif	//!___EFFECTCIECLE_H___