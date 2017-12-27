//======================================================================
//	EffectSphereLight.h
//	
//	�T�v�Q�F�ی^�̌��G�t�F�N�g
//	����ҁF���� ����
//	
//======================================================================
#ifndef ___EFFECTSPHERELIGHT_H___
#define ___EFFECTSPHERELIGHT_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "EffectManeger.h"

//-----------------------------
//�}�N����`
//-----------------------------

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------
class cEffectSphereLight : public cBaseEffect
{
private:
	cSpriteParam* m_Sprite;	//�X�v���C�g���̃|�C���^(���I�m��)
	int			  m_MaxLife;	//��������
//-----------------------------
protected:


//-----------------------------
public:

	cEffectSphereLight(){};		//�R���X�g���N�^
	~cEffectSphereLight(){};		//�f�X�g���N�^

	void Update(void);			//�X�V�֐�
	void Draw(void);			//�`��֐�
	void Uninit(void);			//�I���֐�

	void SetEffect(LPDIRECT3DTEXTURE9 ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 move, D3DXCOLOR color, int life, int division);	//�~�`�G�t�F�N�g�̐ݒ�֐�
};


#endif	//!___EFFECTSPHERELIGHT_H___