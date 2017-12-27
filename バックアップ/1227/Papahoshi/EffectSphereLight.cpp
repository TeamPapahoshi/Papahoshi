//======================================================================
//	EffectSphereLight.cpp
//	
//	�T�v�Q�F�ی^�̌��G�t�F�N�g����
//	����ҁF���� ����
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>		//HRESULT��

#include "SceneManeger.h"	//BaseScene
#include "debugproc.h"		//printdebug
#include "EffectSphereLight.h"

//-----------------------------
//�}�N����`
//-----------------------------

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------

//-----------------------------
//�O���[�o��
//-----------------------------

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cEffectSphereLight::Uninit(){
	//���I�m�ۂ����|�C���^�̍폜
	delete m_Sprite;
	m_Sprite = NULL;
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cEffectSphereLight::Update(){
	//���g�p�̃G�t�F�N�g�͏������Ȃ�
	if (!m_bEffectUseFlag)
	{
		return;
	}

	//�������Ԃ̌���
	if (m_nLifeFleam > 0)
		m_nLifeFleam--;

	//�X�v���C�g�̍X�V����
	m_Sprite->SetPos(m_Sprite->GetPos() + m_Sprite->GetMove());

	//�A���t�@�l�̌���
	m_Sprite->SetVtxColorA(m_Sprite->GetVtxColorA() - 255.0f / m_MaxLife);

	//�������Ԃ�0�ɂȂ����疢�g�p��Ԃ�
	if (m_nLifeFleam <= 0)
	{
		m_bEffectUseFlag = false;
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cEffectSphereLight::Draw(){
	//���g�p�̃G�t�F�N�g�͏������Ȃ�
	if (!m_bEffectUseFlag)
		return;

	m_Sprite->Draw();
}

//=======================================================================================
//
//		EffectCircle:�G�t�F�N�g�ݒ�֐�
//		����		:LPCSTR�^			  ptex		[�G�t�F�N�g�Ɏg�p����e�N�X�`���|�C���^]
//					 D3DXVECTOR2�^		  pos		[�G�t�F�N�g�̐������W]
//					 D3DXVECTOR2�^		  size		[�G�t�F�N�g�̃T�C�Y]
//					 D3DXVECTOR2�^		  move		[�G�t�F�N�g�̈ړ���]
//					 D3DXCOLOR�^		  color		[�G�t�F�N�g�̐F���]
//					 int�^				  life		[�G�t�F�N�g�̐�������]
//
//=======================================================================================
void cEffectSphereLight::SetEffect(LPDIRECT3DTEXTURE9 ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 move, D3DXCOLOR color, int life, int division)
{
	//���g�p�̃G�t�F�N�g�ɐݒ�
	if (!m_bEffectUseFlag)
	{
		//�g�p����|���S���̏�����
		//�X�v���C�g�̓��I�m��
		m_Sprite = new cSpriteParam;

		//�e�N�X�`���̐ݒ�
		m_Sprite->SetTexture(&ptex);

		//�F�̐ݒ�
		m_Sprite->SetVtxColor(color);

		//����������W�̐ݒ�
		m_Sprite->SetPos(pos);

		//��������T�C�Y�̐ݒ�
		m_Sprite->SetSize(size);

		//�ړ��ʂ̐ݒ�
		m_Sprite->SetMove(move);

		//�G�t�F�N�g�̐������Ԑݒ�
		m_nLifeFleam = m_MaxLife = life;

		//�G�t�F�N�g�g�p�t���O���I����
		m_bEffectUseFlag = true;

		return;
	}
}