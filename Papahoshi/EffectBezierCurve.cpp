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

#include "EffectBezierCurve.h"	//

#include "MathEX.h"

#include "debugproc.h"		//printdebug

//-----------------------------
//�萔��}�N����`
//-----------------------------

//��ŏ���
#define MAX_RAD (2.0f * 3.14f)
#define ToRADIAN(a)	(((a) % 360) / 180.0f * 3.1415f)	// D��R�ϊ�

#define POINT_SET_X (50)		//����_�̈ʒu����p�w
#define POINT_SET_Y (50)		//����_�̈ʒu����p�x
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
cEffectBezierCurve::cEffectBezierCurve()
{
	//�����l�ݒ�
	m_bEffectUseFlag = false;
	m_fPointTime = 0.0f;
	m_fPointInterval = 0.0f;

	for (int initloop = 0; initloop < MAX_POINT; initloop++)
		m_CPoint[initloop] = D3DXVECTOR2(0.0f, 0.0f);
}

//=======================================================================================
//
//		EffectCircle:�f�X�g���N�^
//
//=======================================================================================
cEffectBezierCurve::~cEffectBezierCurve()
{

}

//=======================================================================================
//
//		EffectCircle:�X�V
//
//=======================================================================================
void cEffectBezierCurve::Update(void)
{
	//���g�p�̃G�t�F�N�g�͏������Ȃ�
	if (!m_bEffectUseFlag)
	{
		return;
	}

	//�ړ����Ԃ̉��Z
	m_fPointTime += m_fPointInterval;

	//�X�v���C�g�̍X�V����
	for (int UpdateSpriteloop = 0; UpdateSpriteloop < MAX_BEZIERCURVEFFECT_SPRITE; UpdateSpriteloop++)
	{
		//�Ȑ���̈ړ��̔��f
		m_Sprite[UpdateSpriteloop]->SetPos(BezierCurve(m_fPointTime, m_CPoint[0], m_CPoint[1], m_CPoint[1], m_CPoint[MAX_POINT - 1]));
	}

	//�������Ԃ̌���
	m_nLifeFleam--;
	if (m_nLifeFleam <= 0)
	{
		m_bEffectUseFlag = false;
	}

}

//=======================================================================================
//
//		EffectCircle:�`��
//
//=======================================================================================
void cEffectBezierCurve::Draw(void)
{
	//���g�p�̃G�t�F�N�g�͏������Ȃ�
	if (!m_bEffectUseFlag)
		return;

	//�X�v���C�g�̕`�揈��
	for (int DrawSpriteloop = 0; DrawSpriteloop < MAX_BEZIERCURVEFFECT_SPRITE; DrawSpriteloop++)
	{
		m_Sprite[DrawSpriteloop]->Draw();
	}
}

//=======================================================================================
//
//		EffectCircle:�I��
//
//=======================================================================================
void cEffectBezierCurve::Uninit(void)
{

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
void cEffectBezierCurve::SetEffectBezierCurve(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, D3DXVECTOR2 startpoint, D3DXVECTOR2 endpoint)
{
	//���g�p�̃G�t�F�N�g�ɐݒ�
	if (!m_bEffectUseFlag)
	{
		for (int SetEffectloop = 0; SetEffectloop < MAX_BEZIERCURVEFFECT_SPRITE; SetEffectloop++)
		{
			//�g�p����|���S���̏�����
			//�X�v���C�g�̓��I�m��
			m_Sprite[SetEffectloop] = new cSpriteParam;

			//�e�N�X�`���̐ݒ�
			m_Sprite[SetEffectloop]->SetTexture(ptex);

			//�F�̐ݒ�
			m_Sprite[SetEffectloop]->SetVtxColor(color);

			//���[�v�񐔂ɉ����ĐF�̒���

			//����������W�̐ݒ�
			m_Sprite[SetEffectloop]->SetPos(pos);

			//��������T�C�Y�̐ݒ�
			m_Sprite[SetEffectloop]->SetSize(size);

			//���Z�������I����
			m_Sprite[SetEffectloop]->SetAddBlend(true);
		}
		//�n�_�̐ݒ�
		m_CPoint[0] = startpoint;

		//�I�_�̐ݒ�
		m_CPoint[MAX_POINT - 1] = endpoint;

		//�n�_�ƏI�_���璆�Ԃ̐���_�̍��W��ݒ�
		if (m_CPoint[0].x < m_CPoint[2].x)
			m_CPoint[1].x = (4 * CRandam::RandamRenge(m_CPoint[0].x + POINT_SET_X, m_CPoint[2].x - POINT_SET_X) - m_CPoint[0].x - m_CPoint[2].x) / 2.0f;
		else
			m_CPoint[1].x = (4 * CRandam::RandamRenge(m_CPoint[2].x + POINT_SET_X, m_CPoint[0].x - POINT_SET_X) - m_CPoint[0].x - m_CPoint[2].x) / 2.0f;

		if (m_CPoint[0].x < m_CPoint[2].x)
			m_CPoint[1].y = (4 * CRandam::RandamRenge(m_CPoint[0].y - POINT_SET_Y, m_CPoint[2].y + POINT_SET_Y) - m_CPoint[0].y - m_CPoint[2].y) / 2.0f;
		else
			m_CPoint[1].y = (4 * CRandam::RandamRenge(m_CPoint[2].y - POINT_SET_Y, m_CPoint[0].y + POINT_SET_Y) - m_CPoint[0].y - m_CPoint[2].y) / 2.0f;

		//�G�t�F�N�g�̐������Ԑݒ�
		m_nLifeFleam = life;

		//�G�t�F�N�g�̐������Ԃ���x�W�F�Ȑ�����ړ�����Ԋu��ݒ�
		m_fPointInterval = 1.0f / m_nLifeFleam;

		//�G�t�F�N�g�g�p�t���O���I����
		m_bEffectUseFlag = true;

		return;
	}
}