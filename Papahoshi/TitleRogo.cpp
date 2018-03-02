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
#define TITLEROGO_SIZE_X (120)
#define TITLEROGO_SIZE_Y (120)

#define TITLEROGO_POS_X ((SCREEN_WIDTH / 2 - (TITLEROGO_SIZE_X * ((MAX_TITLEROGO) / 2))) + 60)
#define TITLEROGO_POS_Y (SCREEN_HEIGHT / 2 - 160.0f)

#define TITLEROGO_SPACE_X (-20)

#define TITLEROGO_HOP_COUNT (20)	//�^�C�g�����S�̓���^�C�}�[

#define TITLEROGO_MOVE (-20.0f)		//�^�C�g�����S�̈ړ���

#define PUSHBUTTON_POS_X (SCREEN_WIDTH / 2)
#define PUSHBUTTON_POS_Y (SCREEN_HEIGHT / 2 + 100)

#define PUSHBUTTON_SIZE_X (500)
#define PUSHBUTTON_SIZE_Y (90)

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
	m_Pushsprite.LoadTexture("Image/GameUI/press_any_button.png");
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
		case 0://�p
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x - 298.0f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO01));
			break;
		case 1://�p
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x - 205.0f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO02));
			break;
		case 2://�A
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x - 158.0f, TITLEROGO_POS_Y + 10.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X / 3.0f, TITLEROGO_SIZE_Y / 1.6f));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO03));
			break;
		case 3://��
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x - 108.0f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO04));
			break;
		case 4://��(�傫��)
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x - 22.0f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X , TITLEROGO_SIZE_Y * 1.1f));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO05));
			break;
		case 5://��
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 55.0f, TITLEROGO_POS_Y + 4.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO06));
			break;
		case 6://��
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 130.0f, TITLEROGO_POS_Y - 6.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO07));
			break;
		case 7://��
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 203.0f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO08));
			break;
		case 8://��
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 260.0f, TITLEROGO_POS_Y + 5.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X / 3.0f, TITLEROGO_SIZE_Y / 1.5f));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO09));
			break;
		case 9://��
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 300.0f, TITLEROGO_POS_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO10));
			break;
		case 10://�I(��)
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 354.0f, TITLEROGO_POS_Y + 2.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X / 1.4f, TITLEROGO_SIZE_Y));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO11));
			break;
		case 11://�I(��)
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x + 350.0f, TITLEROGO_POS_Y + 50.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(35.0f, 35.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO12));
			break;
		case 12://��
			m_aTitlerogo[Initloop].Rogosprite.SetPos(D3DXVECTOR2(SCREEN_CENTER.x - 10.0f, TITLEROGO_POS_Y + 55.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetSize(D3DXVECTOR2(720.0f, 30.0f));
			m_aTitlerogo[Initloop].Rogosprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_ROGO13));
			break;
		default:
			break;
		}
		//���̍��W��ۑ�
		m_aTitlerogo[Initloop].fOriginPosY = m_aTitlerogo[Initloop].Rogosprite.GetPosY();
		m_aTitlerogo[Initloop].nHopTimer = TITLEROGO_HOP_COUNT * Initloop;
		m_aTitlerogo[Initloop].bMoveFlag = false;
		m_aTitlerogo[Initloop].fRadian = 0;
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
	for (int Updateloop = 0; Updateloop < MAX_TITLEROGO - 1; Updateloop++)
	{
		//�^�C�}�[����
		if (m_aTitlerogo[Updateloop].nHopTimer >= 0)
		{//�^�C�}�[�̒l����
			m_aTitlerogo[Updateloop].nHopTimer--;
		}
		else
		{
			//�ړ��t���O���I����
			m_aTitlerogo[Updateloop].bMoveFlag = true;
		}

		//�ړ��t���O���I���ɂȂ��Ă���Έړ������̊J�n
		if (m_aTitlerogo[Updateloop].bMoveFlag)
		{
			if (Updateloop >= 0 && Updateloop < 10)
			{	//���������̈ړ�����
				m_aTitlerogo[Updateloop].fRadian = ((float)(((int)m_aTitlerogo[Updateloop].fRadian + 2) % MAX_RADIUS));

				//���W�̍X�V
				m_aTitlerogo[Updateloop].Rogosprite.SetPosY(SINCURVE(m_aTitlerogo[Updateloop].fOriginPosY, TITLEROGO_MOVE, m_aTitlerogo[Updateloop].fRadian / (MAX_RADIUS / 2)));

				//�����W��艺�Ɉړ������ꍇ
				if (m_aTitlerogo[Updateloop].fRadian >= MAX_RADIUS / 2)
				{
					//�����W�ɖ߂�
					m_aTitlerogo[Updateloop].Rogosprite.SetPosY(m_aTitlerogo[Updateloop].fOriginPosY);
					//�^�C�}�[�̍Đݒ�
					m_aTitlerogo[Updateloop].nHopTimer = TITLEROGO_HOP_COUNT * (MAX_TITLEROGO - 2);
					//���W�A���l�̏�����
					m_aTitlerogo[Updateloop].fRadian = 0;
					//�ړ��t���O���I�t��
					m_aTitlerogo[Updateloop].bMoveFlag = false;
				}
			}
			else if (Updateloop == 11)
			{//�������̈ړ�����
				m_aTitlerogo[Updateloop].fRadian = ((float)(((int)m_aTitlerogo[Updateloop].fRadian + 2) % MAX_RADIUS));

				m_aTitlerogo[Updateloop].Rogosprite.SetRad(m_aTitlerogo[Updateloop].fRadian / 16);

				//���]�����ꍇ
				if (m_aTitlerogo[Updateloop].fRadian == MAX_RADIUS / 2)
				{
					//�^�C�}�[�̍Đݒ�
					m_aTitlerogo[Updateloop].nHopTimer = TITLEROGO_HOP_COUNT * (MAX_TITLEROGO - 2);
					//���W�A���l�̏�����
					m_aTitlerogo[Updateloop].fRadian = 0;
					//�ړ��t���O���I�t��
					m_aTitlerogo[Updateloop].bMoveFlag = false;
				}
			}
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
	for (int Drawloop = MAX_TITLEROGO - 1; Drawloop >= 0; Drawloop--)
	{
		m_aTitlerogo[Drawloop].Rogosprite.Draw();
	}
	m_Pushsprite.Draw();
}