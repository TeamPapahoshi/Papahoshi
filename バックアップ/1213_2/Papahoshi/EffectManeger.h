//======================================================================
//	EffectManeger�w�b�_
//	
//	�T�v�Q�F�G�t�F�N�g�Ǘ��p
//	����ҁF���� ����
//	
//======================================================================
#ifndef ___EFFECTMANEGER_H___
#define ___EFFECTMANEGER_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Common.h"		
#include <Windows.h>	//HRESULT��
#include "d3dx9.h"		//D3DXVECTOR2��
#include "Sprite.h"		//CSprite�N���X�̓���
#include <vector>		//�ϒ��z��̓���

//-----------------------------
//�}�N����`
//-----------------------------
#define MAX_EFFECT (100)

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------

//----- �p���p:�G�t�F�N�g��{�N���X -----
class cBaseEffect
{
protected:
	int		m_nLifeFleam;		//�G�t�F�N�g�����t���[��
	bool	m_bEffectUseFlag;	//�G�t�F�N�g�g�p�t���O
	int		m_nDivision;		//�G�t�F�N�g�Ɏg�p����|���S���̌�

public:
	virtual void Update() = 0;	//�K�{
	virtual void Draw() = 0;	//�K�{
	virtual ~cBaseEffect(){}	//�f�X�g���N�^
	
	//�G�t�F�N�g�ݒ�p���z�֐�
	virtual void SetEffect(LPDIRECT3DTEXTURE9 ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, int division) = 0;

	//�g�p���t���O�̎擾
	bool GetUseFlag(void)
	{
		return m_bEffectUseFlag;
	}
};

//----- �G�t�F�N�g�Ǘ��p�N���X -----
class cEffectManeger
{
public:
	//�G�t�F�N�g�w��p�񋓑�
	enum EFFECT_NUM
	{
		EFFECT_CIRCLE,
		EFFECT_NUM_MAX
	};

	void Init();			//����������
	void Update();		//�X�V����
	void Draw();			//�`�揈��
	void Uninit();		//�I������
	void SetEffectBase(EFFECT_NUM effect, LPDIRECT3DTEXTURE9 ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, int division);

protected:

private:
	cBaseEffect* m_pEffect[MAX_EFFECT];
};


#endif	//!___EFFECTMANEGER_H___