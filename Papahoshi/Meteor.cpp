//======================================================================
//	Meteor
//	
//	�T�v�Q�F�^�C�g���I�u�W�F�N�g/����
//	����ҁF���� ����
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>		//HRESULT��

#include "debugproc.h"		//printdebug
#include "Meteor.h"
#include "Texture.h"
#include "GameMain.h"	// �G�t�F�N�g�N���X�擾�p

//-----------------------------
//�}�N����`
//-----------------------------
#define METEOR_LIFETIME (60)
#define METEOR_SIZE (25.0f)
#define METEOR_MOVE (5.5f)

#define METEOR_ALPHA_SUB    (50.0f)

#define RANDAM_METEOR_POS_X (100)
#define RANDAM_METEOR_POS_Y (100)

#define RANDAM_METEOR_SET_X ((float)CRandam::RandamRenge(RANDAM_METEOR_POS_X, SCREEN_WIDTH - RANDAM_METEOR_POS_X))
#define RANDAM_METEOR_SET_Y ((float)CRandam::RandamRenge(RANDAM_METEOR_POS_Y, SCREEN_HEIGHT - RANDAM_METEOR_POS_Y))
#define RANDAM_METEOR_TIME (CRandam::RandamRenge(100, 250))

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
//		�R���X�g���N�^
//
//=======================================================================================
cMeteor::cMeteor(){

}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cMeteor::~cMeteor(){

}

//=======================================================================================
//
//		������
//
//=======================================================================================
void cMeteor::Init()
{
	//���̃^�C�~���O��m_aMeteor�̎Q�ƈʒu�������->�G���[�̌���
	
	for (int loop = 0; loop < MAX_METEOR; loop++)
	{
		m_aMeteor[loop].SetMakeTime(RANDAM_METEOR_TIME);
		m_aMeteor[loop].SetLifeTime(METEOR_LIFETIME);
		m_aMeteor[loop].SetUseFlag(false);

		//�X�v���C�g�̐ݒ�
		for (int Spriteloop = 0; Spriteloop < MAX_METEOR_SPRITE_NUM; Spriteloop++)
		{
			m_aMeteor[loop].Sprite[Spriteloop].SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_STAR_LIGHT));
			m_aMeteor[loop].Sprite[Spriteloop].SetVtxColorA(255.0f / (Spriteloop + 1));
			m_aMeteor[loop].Sprite[Spriteloop].SetMove(D3DXVECTOR2(-METEOR_MOVE, METEOR_MOVE));
			m_aMeteor[loop].Sprite[Spriteloop].SetSize(D3DXVECTOR2(METEOR_SIZE / (Spriteloop + 1), METEOR_SIZE / (Spriteloop + 1)));
			m_aMeteor[loop].Sprite[Spriteloop].SetAddBlend(true);
		}
	}
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cMeteor::UnInit()
{

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cMeteor::Update(){

	for (int loop = 0; loop < MAX_METEOR; loop++)
	{
		if (m_aMeteor[loop].GetUseFlag())
		{//�g�p���̏���
			for (int Spriteloop = MAX_METEOR_SPRITE_NUM - 1; Spriteloop >= 0; Spriteloop--)
			{
				if (Spriteloop == 0)
				{
					m_aMeteor[loop].Sprite[Spriteloop].SetPos(m_aMeteor[loop].Sprite[Spriteloop].GetPos() + m_aMeteor[loop].Sprite[Spriteloop].GetMove());
				}
				else
				{
					m_aMeteor[loop].Sprite[Spriteloop].SetPos(m_aMeteor[loop].Sprite[Spriteloop - 1].GetPos());
				}

				if (m_aMeteor[loop].GetLifeTime() <= 0)
				{
					m_aMeteor[loop].Sprite[Spriteloop].SetVtxColorA(m_aMeteor[loop].Sprite[Spriteloop].GetVtxColorA() - METEOR_ALPHA_SUB);
					if (m_aMeteor[loop].Sprite[Spriteloop].GetVtxColorA() < 0.0f)
						m_aMeteor[loop].Sprite[Spriteloop].SetVtxColorA(0.0f);
				}
			}

			m_aMeteor[loop].SetLifeTime(m_aMeteor[loop].GetLifeTime() - 1);		//�������Ԃ̌���


			if (m_aMeteor[loop].Sprite[0].GetVtxColorA() <= 0)
			{
				m_aMeteor[loop].SetUseFlag(false);
				m_aMeteor[loop].SetLifeTime(METEOR_LIFETIME);
			}
		}
		else
		{//���g�p�̏ꍇ�̏���
			m_aMeteor[loop].SetMakeTime(m_aMeteor[loop].GetMakeTime() - 1);	//�������Ԃ̌���

			if (m_aMeteor[loop].GetMakeTime() <= 0)
				SetMeteor();
		}
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cMeteor::Draw(){

	for (int loop = 0; loop < MAX_METEOR; loop++)
	{
		if (!m_aMeteor[loop].GetUseFlag())	return;	//���g�p�̏ꍇ�͏������Ȃ�

		for (int Spriteloop = 0; Spriteloop < MAX_METEOR_SPRITE_NUM; Spriteloop++)
		{
			m_aMeteor[loop].Sprite[Spriteloop].Draw();
		}
	}
}

//=======================================================================================
//
//		�����̐ݒ�
//
//=======================================================================================
void cMeteor::SetMeteor(){

	for (int loop = 0; loop < MAX_METEOR; loop++)
	{
		//�g�p���̏ꍇ�̓X���[
		if (m_aMeteor[loop].GetUseFlag())	return;

		m_aMeteor[loop].Sprite[0].SetPos(D3DXVECTOR2(RANDAM_METEOR_SET_X, RANDAM_METEOR_SET_Y));	//�o�����W�������_���ɐݒ�

		m_aMeteor[loop].SetUseFlag(true);					//�g�p�t���O�����Ă�
		m_aMeteor[loop].SetMakeTime(RANDAM_METEOR_TIME);	//�������Ԃ̍Đݒ�

		//�X�v���C�g�̐ݒ�
		for (int Spriteloop = 0; Spriteloop < MAX_METEOR_SPRITE_NUM; Spriteloop++)
		{
			m_aMeteor[loop].Sprite[Spriteloop].SetVtxColorA(255.0f / (Spriteloop + 1));
			m_aMeteor[loop].Sprite[Spriteloop].SetMove(D3DXVECTOR2(-METEOR_MOVE, METEOR_MOVE));
			m_aMeteor[loop].Sprite[Spriteloop].SetSize(D3DXVECTOR2(METEOR_SIZE, METEOR_SIZE));
		}

		//����������烋�[�v�𔲂���
		break;
	}
}