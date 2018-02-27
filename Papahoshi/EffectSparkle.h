//======================================================================
//	Sample
//	
//	�T�v�Q�F�R�s�[�p
//	����ҁF
//	
//======================================================================
#ifndef ___EFFECTSPARKLE_H___
#define ___EFFECTSPARKLE_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "EffectManeger.h"	

//-----------------------------
//�}�N����`
//-----------------------------
#define MAX_SPARKLEEFFECT_SPRITE (10)

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------
class cEffectSparkle : public cBaseEffect
{
private:
	cSpriteParam* m_Sprite;	//�X�v���C�g���̃|�C���^(���I�m�ۂɎg�p)
	int			  m_nHalfLife;
	HSVCOLOR      m_aHSVColor;

	//--------------------------------------
protected:
	//--------------------------------------
public:
	cEffectSparkle();		//�R���X�g���N�^
	~cEffectSparkle();		//�f�X�g���N�^

	void Update(void);			//�X�V�֐�
	void Draw(void);			//�`��֐�
	void Uninit(void);			//�I���֐�

	void SetEffectSparkle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, HSVCOLOR color, int life, D3DXVECTOR2 radius, int texdividex, int texdividey);	//�~�`�G�t�F�N�g�̐ݒ�֐�
};

#endif	//!___EFFECTCIECLE_H___