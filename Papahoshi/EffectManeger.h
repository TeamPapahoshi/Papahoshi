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
#define MAX_EFFECT (200)

//----- �G�t�F�N�g�������̒�` -----
#define EFFECT_SPARKLE_TEX_DIVIDE_X (4)
#define EFFECT_SPARKLE_TEX_DIVIDE_Y (3)

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
	int			  m_nLifeFleam;		//�G�t�F�N�g�����t���[��
	bool		  m_bEffectUseFlag;	//�G�t�F�N�g�g�p�t���O
	int			  m_nDivision;		//�G�t�F�N�g�Ɏg�p����|���S���̌�
	D3DXVECTOR2   m_fEffectRadius;	//�G�t�F�N�g�𐶐����锼�a

public:
	virtual void Update() = 0;	//�K�{
	virtual void Draw() = 0;	//�K�{
	virtual ~cBaseEffect(){}	//�f�X�g���N�^
	
	//�G�t�F�N�g�ݒ�p���z�֐�
	virtual void SetEffectCircle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, int division){};
	virtual void SetEffectSphereLight(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 move, D3DXCOLOR color, int life){};
	virtual void SetEffectSparkle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, D3DXVECTOR2 radius, int texdividex, int texdividey){};
	virtual void SetEffectBezierCurve(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, D3DXVECTOR2 startpoint, D3DXVECTOR2 endpoint){};

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
	void Init();			//����������
	void Update();		//�X�V����
	void Draw();			//�`�揈��
	void Uninit();		//�I������

	//�G�t�F�N�g�ݒ蒇��p�֐�

	void SetEffectCircle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, int division);
	void SetEffectSphereLight(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 move, D3DXCOLOR color, int life);
	void SetEffectSparkle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, D3DXVECTOR2 radius, int texdividex, int texdividey);
	void SetEffectBezierCurve(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, D3DXVECTOR2 startpoint, D3DXVECTOR2 endpoint);

protected:

private:
	cBaseEffect* m_pEffect[MAX_EFFECT];
};


#endif	//!___EFFECTMANEGER_H___