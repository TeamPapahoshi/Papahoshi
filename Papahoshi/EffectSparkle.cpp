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

#include "EffectSparkle.h"	//

#include "debugproc.h"		//printdebug

//-----------------------------
//�萔��}�N����`
//-----------------------------

//��ŏ���
#define MAX_RAD (2.0f * 3.14f)
#define ToRADIAN(a)	(((a) % 360) / 180.0f * 3.1415f)	// D��R�ϊ�
#define EFFECTSPARKLE_DELETE_TIME (20)	//�|���S���̏k���J�n����

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
//		EffectSparkle:�R���X�g���N�^
//
//=======================================================================================
cEffectSparkle::cEffectSparkle()
{
	//�����l�ݒ�
	m_fEffectRadius = D3DXVECTOR2(0.0f, 0.0f);
	m_bEffectUseFlag = false;
}

//=======================================================================================
//
//		EffectSparkle:�f�X�g���N�^
//
//=======================================================================================
cEffectSparkle::~cEffectSparkle()
{

}

//=======================================================================================
//
//		EffectSparkle:�X�V
//
//=======================================================================================
void cEffectSparkle::Update(void)
{
	//���g�p�̃G�t�F�N�g�͏������Ȃ�
	if (!m_bEffectUseFlag)
		return;

	//�X�v���C�g�̍X�V����

	//�X�v���C�g�̉�]
	m_Sprite->SetRad(m_Sprite->GetRad() + 2.0f / m_nHalfLife);
	
	//�X�v���C�g�̊g��E�k��
	if (m_nLifeFleam > m_nHalfLife)
	{
		m_Sprite->SetScale(D3DXVECTOR2(m_Sprite->GetScale().x + 1.0f / m_nHalfLife, m_Sprite->GetScale().y + 1.0f / m_nHalfLife));
	}
	else
	{
		m_Sprite->SetScale(D3DXVECTOR2(m_Sprite->GetScale().x - 1.0f / m_nHalfLife, m_Sprite->GetScale().y - 1.0f / m_nHalfLife));
	}

	//���_��HSV���̔��f
	for (int loop = 0; loop < 4; loop++)
	{
		m_Sprite->SetHSVColorOne(m_aHSVColor.h, m_aHSVColor.s, m_aHSVColor.v, loop);
	}

	//�������Ԃ̌���
	if (m_nLifeFleam > 0)
	{
		m_nLifeFleam--;
		if (m_nLifeFleam <= 0)
			m_bEffectUseFlag = false;
	}
}

//=======================================================================================
//
//		EffectSparkle:�`��
//
//=======================================================================================
void cEffectSparkle::Draw(void)
{
	//���g�p�̃G�t�F�N�g�͏������Ȃ�
	if (!m_bEffectUseFlag)
		return;

	//�X�v���C�g�̕`�揈��
	m_Sprite->Draw();
}

//=======================================================================================
//
//		EffectSparkle:�I��
//
//=======================================================================================
void cEffectSparkle::Uninit(void)
{
	//�X�v���C�g�̏I������

	//���I�m�ۂ����|�C���^�̍폜
	delete m_Sprite;
	m_Sprite = NULL;
}

//=======================================================================================
//
//		EffectSparkle:�G�t�F�N�g�ݒ�֐�
//		����		:LPCSTR�^			  ptex		[�G�t�F�N�g�Ɏg�p����e�N�X�`���|�C���^]
//					 D3DXVECTOR2�^		  pos		[�G�t�F�N�g�̐������W]
//					 D3DXVECTOR2�^		  size		[�G�t�F�N�g�̃T�C�Y]
//					 HSVCOLOR�^			  color		[�G�t�F�N�g�̐F���]
//					 int�^				  life		[�G�t�F�N�g�̐�������]
//					 int�^				  division	[�G�t�F�N�g�̕�����]
//
//=======================================================================================
void cEffectSparkle::SetEffectSparkle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, HSVCOLOR color, int life, D3DXVECTOR2 radius, int texdividex, int texdividey)
{
	//�X�v���C�g�̓��I�m��
	m_Sprite = new cSpriteParam;

	//�e�N�X�`���̐ݒ�
	m_Sprite->SetTexture(ptex);

	//��������T�C�Y�̐ݒ�
	m_Sprite->SetSize(size);

	m_Sprite->SetScale(D3DXVECTOR2(0.0f, 0.0f));

	//�G�t�F�N�g�̐������Ԑݒ�
	m_nLifeFleam = life;
	m_nHalfLife = m_nLifeFleam / 2;

	//�G�t�F�N�g����������锼�a�̐ݒ�
	m_fEffectRadius = radius;

	//���a�ƍ��W����ɐ���������W�̐ݒ�
	m_Sprite->SetPos(D3DXVECTOR2(pos.x + CRandam::RandamRenge(-m_fEffectRadius.x, m_fEffectRadius.x),
								 pos.y + CRandam::RandamRenge(-m_fEffectRadius.y, m_fEffectRadius.y)));

	//�e�N�X�`��UV���W�̎w��
	m_Sprite->SetTexPatternDevide(texdividex, texdividey);

	m_Sprite->SetCurrentAnimPattern(CRandam::RandamRenge(0, texdividex * texdividey));

	//HSV�d�l�t���O���I����
	m_Sprite->SetHSVColorFlag(true);

	//HSV���̔��f
	m_aHSVColor = color;

	//�G�t�F�N�g�g�p�t���O���I����
	m_bEffectUseFlag = true;

	return;
}