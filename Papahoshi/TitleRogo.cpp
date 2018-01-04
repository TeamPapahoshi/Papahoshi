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

//-----------------------------
//�}�N����`
//-----------------------------
#define TITLEROGO_POS_X (SCREEN_WIDTH / 2)
#define TITLEROGO_POS_Y (SCREEN_HEIGHT / 2 - 100)

#define TITLEROGO_SIZE_X (400)
#define TITLEROGO_SIZE_Y (200)

#define TITLEROGO_MOVE (0.2f)		//�^�C�g�����S�̈ړ���

#define PUSHBUTTON_POS_X (SCREEN_WIDTH / 2)
#define PUSHBUTTON_POS_Y (SCREEN_HEIGHT / 2 + 100)

#define PUSHBUTTON_SIZE_X (200)
#define PUSHBUTTON_SIZE_Y (100)

#define PUSHBUTTON_SCALE_MAG (0.125f)		//�^�C�g�����S�̈ړ���

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
	m_Rogosprite.SetPos(D3DXVECTOR2(TITLEROGO_POS_X, TITLEROGO_POS_Y));
	m_Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
	m_Pushsprite.SetPos(D3DXVECTOR2(PUSHBUTTON_POS_X, PUSHBUTTON_POS_Y));
	m_Pushsprite.SetSize(D3DXVECTOR2(PUSHBUTTON_SIZE_X, PUSHBUTTON_SIZE_Y));
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
void cTitleRogo::Update()
{
	static float s_Radian = 0.0f;
	static float fwork;

	//���W�A���l�̍X�V
	s_Radian = ((float)(((int)s_Radian + 1) % MAX_RADIUS));

	//���W�A���l����Ɉړ��ʁE�g�嗦�̐ݒ�
	m_Rogosprite.SetMoveY(COSCURVE(0, TITLEROGO_MOVE, s_Radian / (MAX_RADIUS / 2)));
	fwork = COSCURVE(1.0f, PUSHBUTTON_SCALE_MAG, s_Radian / (MAX_RADIUS / 2));
	
	//���W�̍X�V
	m_Rogosprite.SetPosY(m_Rogosprite.GetPosY() + m_Rogosprite.GetMoveY());
	m_Pushsprite.SetScale(D3DXVECTOR2(fwork, fwork));
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cTitleRogo::Draw()
{
	m_Rogosprite.Draw();
	m_Pushsprite.Draw();
}