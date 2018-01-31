//======================================================================
//	TitleRogo
//	
//	�T�v�Q�F�^�C�g�����S
//	����ҁF���� ����
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>		//HRESULT��

#include "debugproc.h"		//printdebug
#include "TitleRogo.h"
#include "Texture.h"

//-----------------------------
//�}�N����`
//-----------------------------
#define TITLEROGO_SIZE_X (60)
#define TITLEROGO_SIZE_Y (80)

#define TITLEROGO_POS_X ((SCREEN_WIDTH / 2 - (TITLEROGO_SIZE_X * ((MAX_TITLEROGO) / 2))))
#define TITLEROGO_POS_Y (SCREEN_HEIGHT / 2 - 100)

#define TITLEROGO_SPACE_X (0)

#define TITLEROGO_HOP_COUNT (40)	//�^�C�g�����S�̓���^�C�}�[

#define TITLEROGO_MOVE (-0.4f)		//�^�C�g�����S�̈ړ���

#define PUSHBUTTON_POS_X (SCREEN_WIDTH / 2)
#define PUSHBUTTON_POS_Y (SCREEN_HEIGHT / 2 + 100)

#define PUSHBUTTON_SIZE_X (200)
#define PUSHBUTTON_SIZE_Y (100)

#define PUSHBUTTON_SCALE_MAG (0.125f)		//�^�C�g�����S�̈ړ���

#define PUSHBUTTON_ALPHACHANGE_TIMER (10)	//�A���t�@�l�؂�ւ��̃^�C�}�[

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
//		�C���N�������g
//
//=======================================================================================
cTitleRogo::cTitleRogo()
{

}

//=======================================================================================
//
//		�f�N�������g
//
//=======================================================================================
cTitleRogo::~cTitleRogo()
{

}

//=======================================================================================
//
//		������
//
//=======================================================================================
void cTitleRogo::Init()
{
	for (int Initloop = 0; Initloop < MAX_TITLEROGO; Initloop++)
	{
		switch (Initloop)
		{
		case 0:
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(TITLEROGO_POS_X + TITLEROGO_SIZE_X / 2, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			break;
		case 2:
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(m_aTitlerogo[Initloop - 1].Rogosprite.GetPosX() + TITLEROGO_SIZE_X / 1.3f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X / 2.0f, TITLEROGO_SIZE_Y));
			break;
		case 8:
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(m_aTitlerogo[Initloop - 1].Rogosprite.GetPosX() + TITLEROGO_SIZE_X / 1.15f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X / 1.5f, TITLEROGO_SIZE_Y));
			break;
		default:
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(m_aTitlerogo[Initloop - 1].Rogosprite.GetPosX() + TITLEROGO_SIZE_X, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			break;
		}
		m_aTitlerogo[Initloop].nHopTimer = TITLEROGO_HOP_COUNT * Initloop;
		m_aTitlerogo[Initloop].fRadian = 0;
		switch (Initloop)
		{
		case 0:
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO01));
			break;
		case 1:
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO02));
			break;
		case 2:
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO03));
			break;
		case 3:
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO04));
			break;
		case 4:
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO05));
			break;
		case 5:
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO06));
			break;
		case 6:
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO07));
			break;
		case 7:
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO08));
			break;
		case 8:
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO09));
			break;
		case 9:
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO10));
			break;
		case 10:
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO11));
			break;
		default:
			break;
		}
	}
	m_Pushsprite.SetPos(D3DXVECTOR2(PUSHBUTTON_POS_X, PUSHBUTTON_POS_Y));
	m_Pushsprite.SetSize(D3DXVECTOR2(PUSHBUTTON_SIZE_X, PUSHBUTTON_SIZE_Y));

	m_nAlphaTimer = PUSHBUTTON_ALPHACHANGE_TIMER;
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cTitleRogo::UnInit()
{

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cTitleRogo::Update(bool bSceneChangeFlag)
{
	static float s_Radian = 0.0f;
	static float fwork;

	//���W�A���l�̍X�V
	s_Radian = ((float)(((int)s_Radian + 1) % MAX_RADIUS));

	//���W�A���l����Ɉړ��ʁE�g�嗦�̐ݒ�
	for (int Updateloop = 0; Updateloop < MAX_TITLEROGO; Updateloop++)
	{
		if (m_aTitlerogo[Updateloop].nHopTimer >= 0)
		{
			m_aTitlerogo[Updateloop].nHopTimer--;
		}
		else
		{
			m_aTitlerogo[Updateloop].fRadian = ((float)(((int)m_aTitlerogo[Updateloop].fRadian + 1) % MAX_RADIUS));

			m_aTitlerogo[Updateloop].Rogosprite.SetMoveY(SINCURVE(0, TITLEROGO_MOVE, m_aTitlerogo[Updateloop].fRadian / (MAX_RADIUS / 2)));

			//���W�̍X�V
			m_aTitlerogo[Updateloop].Rogosprite.SetPosY(m_aTitlerogo[Updateloop].Rogosprite.GetPosY() + m_aTitlerogo[Updateloop].Rogosprite.GetMoveY());
		}
	}

	fwork = COSCURVE(1.0f, PUSHBUTTON_SCALE_MAG, s_Radian / (MAX_RADIUS / 2));

	m_Pushsprite.SetScale(D3DXVECTOR2(fwork, fwork));


	//�V�[���`�F���W�̃t���O�����Ă΃��l�̐؂�ւ��J�n
	if (bSceneChangeFlag)
	{
		//�^�C�}�[�̒l����
		m_nAlphaTimer--;
		if (m_nAlphaTimer <= 0)
		{
			m_Pushsprite.SetVtxColorA(0);
		}
		if (m_nAlphaTimer <= -PUSHBUTTON_ALPHACHANGE_TIMER)
		{
			m_Pushsprite.SetVtxColorA(255);
			m_nAlphaTimer = PUSHBUTTON_ALPHACHANGE_TIMER;
		}
	}
	
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cTitleRogo::Draw()
{
	for (int Drawloop = 0; Drawloop < MAX_TITLEROGO; Drawloop++)
	{
		m_aTitlerogo[Drawloop].Rogosprite.Draw();
	}
	m_Pushsprite.Draw();
}