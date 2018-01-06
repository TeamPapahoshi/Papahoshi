//======================================================================
//	Sample
//	
//	�T�v�Q�F�R�s�[�p
//	����ҁF
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>		//HRESULT��

#include "SceneManeger.h"	//BaseScene

#include "EffectCircle.h"	//

#include "debugproc.h"		//printdebug

//-----------------------------
//�萔��}�N����`
//-----------------------------

//��ŏ���
#define MAX_RAD (2.0f * 3.14f)
#define ToRADIAN(a)	(((a) % 360) / 180.0f * 3.1415f)	// D��R�ϊ�
#define EFFECTCIECLE_DELETE_TIME (15)	//�|���S���̏k���J�n����
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
//		EffectCircle:�R���X�g���N�^
//
//=======================================================================================
cEffectCircle::cEffectCircle()
{
	//�����l�ݒ�
	m_nDivision = 0;
	m_bEffectUseFlag = false;
}

//=======================================================================================
//
//		EffectCircle:�f�X�g���N�^
//
//=======================================================================================
cEffectCircle::~cEffectCircle()
{

}

//=======================================================================================
//
//		EffectCircle:�X�V
//
//=======================================================================================
void cEffectCircle::Update(void)
{
	//���g�p�̃G�t�F�N�g�͏������Ȃ�
	if (!m_bEffectUseFlag)
	{
		return;
	}

	//�X�v���C�g�̍X�V����
	for (int SetSpriteloop = 0; SetSpriteloop < m_nDivision; SetSpriteloop++)
	{
		//���W�̍X�V
		m_Sprite[SetSpriteloop]->SetPos(m_Sprite[SetSpriteloop]->GetPos() + m_Sprite[SetSpriteloop]->GetMove());

		//�������Ԃ����l�ȉ��ɂȂ�����
		if (m_nLifeFleam <= EFFECTCIECLE_DELETE_TIME)
		{
			//�T�C�Y�̏k��
			m_Sprite[SetSpriteloop]->SetSizeX(m_Sprite[SetSpriteloop]->GetSizeX() / 1.1f);
			m_Sprite[SetSpriteloop]->SetSizeY(m_Sprite[SetSpriteloop]->GetSizeY() / 1.1f);

			//�������Ԃ�0�ɂȂ����疢�g�p��Ԃɖ߂�
			if (m_nLifeFleam <= 0)
			{
				m_bEffectUseFlag = false;
				m_nDivision = 0;
			}
		}

	}

	//�������Ԃ̌���
	if (m_nLifeFleam > 0)
		m_nLifeFleam--;
}

//=======================================================================================
//
//		EffectCircle:�`��
//
//=======================================================================================
void cEffectCircle::Draw(void)
{
	//���g�p�̃G�t�F�N�g�͏������Ȃ�
	if (!m_bEffectUseFlag)
		return;	

		//�X�v���C�g�̕`�揈��
	for (int SetSpriteloop = 0; SetSpriteloop < m_nDivision; SetSpriteloop++)
	{
		m_Sprite[SetSpriteloop]->Draw();
	}
}

//=======================================================================================
//
//		EffectCircle:�I��
//
//=======================================================================================
void cEffectCircle::Uninit(void)
{
		//�X�v���C�g�̏I������
	for (int SetSpriteloop = 0; SetSpriteloop < MAX_CIRCLEEFFECT_SPRITE; SetSpriteloop++)
	{
		//���I�m�ۂ����|�C���^�̍폜
		delete m_Sprite[SetSpriteloop];
		m_Sprite[SetSpriteloop] = NULL;
	}
}

//=======================================================================================
//
//		EffectCircle:�G�t�F�N�g�ݒ�֐�
//		����		:LPCSTR�^			  ptex		[�G�t�F�N�g�Ɏg�p����e�N�X�`���|�C���^]
//					 D3DXVECTOR2�^		  pos		[�G�t�F�N�g�̐������W]
//					 D3DXVECTOR2�^		  size		[�G�t�F�N�g�̃T�C�Y]
//					 D3DXCOLOR�^		  color		[�G�t�F�N�g�̐F���]
//					 int�^				  life		[�G�t�F�N�g�̐�������]
//					 int�^				  division	[�G�t�F�N�g�̕�����]
//
//=======================================================================================
void cEffectCircle::SetEffectCircle(LPDIRECT3DTEXTURE9 ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, int division)
{
	//���g�p�̃G�t�F�N�g�ɐݒ�
	if (!m_bEffectUseFlag)
	{
		//�g�p����|���S���̏�����
		m_nDivision = division;

		for (int SetSpriteloop = 0; SetSpriteloop < m_nDivision; SetSpriteloop++)
		{
			//�X�v���C�g�̓��I�m��
			m_Sprite[SetSpriteloop] = new cSpriteParam;
			
			//�e�N�X�`���̐ݒ�
			m_Sprite[SetSpriteloop]->SetTexture(&ptex);

			//�F�̐ݒ�
			m_Sprite[SetSpriteloop]->SetVtxColor(color);

			//����������W�̐ݒ�
			m_Sprite[SetSpriteloop]->SetPos(pos);
			//��������T�C�Y�̐ݒ�
			m_Sprite[SetSpriteloop]->SetSize(size);

			//�p�x�ƈړ��ʂ̐ݒ�
			m_Sprite[SetSpriteloop]->SetRad(MAX_RAD / m_nDivision * SetSpriteloop);	//���̈���

			m_Sprite[SetSpriteloop]->SetMoveX(sinf(m_Sprite[SetSpriteloop]->GetRad()));	//�������ւ̈ړ���
			m_Sprite[SetSpriteloop]->SetMoveY(cosf(m_Sprite[SetSpriteloop]->GetRad()));	//�c�����ւ̈ړ���
		}

		//�G�t�F�N�g�̐������Ԑݒ�
		m_nLifeFleam = life;

		//�G�t�F�N�g�g�p�t���O���I����
		m_bEffectUseFlag = true;

		return;
	}
}