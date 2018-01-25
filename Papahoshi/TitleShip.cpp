//======================================================================
//	TitleShip.cpp
//	
//	�T�v�Q�F�^�C�g���I�u�W�F�N�g/�D
//	����ҁF���� ����
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>		//HRESULT��

#include "debugproc.h"		//printdebug
#include "TitleShip.h"
#include "Texture.h"

//-----------------------------
//�}�N����`
//-----------------------------
#define TITLESHIP_POS_X (700)
#define TITLESHIP_POS_Y (540)
#define TITLESHIP_SIZE_X (200)
#define TITLESHIP_SIZE_Y (100)

#define TITLESHIP_MOVE_X (0.01f)			//�D��X�������ړ���
#define TITLESHIP_MOVE_Y (0.15f)		//�D��Y�������ړ���

#define MAKE_SMOKE_TIME  (35)			//���̐����Ԋu����
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
cTitleShip::cTitleShip(){

}

//=======================================================================================
//
//		�f�N�������g
//
//=======================================================================================
cTitleShip::~cTitleShip(){

}


//=======================================================================================
//
//		������
//
//=======================================================================================
void cTitleShip::Init(){
	//�X�v���C�g���̏����ݒ�
	m_sprite.SetPos(D3DXVECTOR2(TITLESHIP_POS_X, TITLESHIP_POS_Y));
	m_sprite.SetSize(D3DXVECTOR2(TITLESHIP_SIZE_X,TITLESHIP_SIZE_Y));
	m_sprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_SHIP));

	m_nMakeSmokeTime = 0;	//���������Ԃ̏�����
	m_bShipOutFlag = false;	//�D���E�t���O�̏�����
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cTitleShip::UnInit(){

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cTitleShip::Update(bool bSceneChangeFlag){

	static float s_Radian = 0.0f;
	static float fwork;

	//���W�A���l�̍X�V
	s_Radian = ((float)(((int)s_Radian + 1) % MAX_RADIUS));

	//���W�A���l����Ɉړ��ʁE�g�嗦�̐ݒ�
	m_sprite.SetMoveY(COSCURVE(0, TITLESHIP_MOVE_Y, s_Radian / (MAX_RADIUS / 2)));

	//�V�[���`�F���W�̃t���O�������Ă����X�����̈ړ��ʂ�ݒ�
	if (bSceneChangeFlag)
		m_sprite.SetMoveX(m_sprite.GetMoveX() + TITLESHIP_MOVE_X);

	//���W�̍X�V
	m_sprite.SetPos(m_sprite.GetPos() + m_sprite.GetMove());

	//���������Ԃ̌���
	m_nMakeSmokeTime--;

	if (m_nMakeSmokeTime <= 0)
	{
		//���G�t�F�N�g�̐ݒ�
		GetEffectManeger()->SetEffectBase(GetEffectManeger()->EFFECT_SPHERE_LIGHT,
										  *cTextureManeger::GetTextureTitle(TEX_TITLE_SPHERE_LIGHT),
										  m_sprite.GetPos() + D3DXVECTOR2(65.0f, -40.0f),
										  D3DXVECTOR2(25.0f, 25.0f),
										  D3DXVECTOR2(0.3f, -1.0f),
										  m_sprite.GetVtxColor(),
										  90, 0);
		//�������Ԃ̍Đݒ�
		m_nMakeSmokeTime = MAKE_SMOKE_TIME;
	}

	//��ʊO�ɑD���o����t���O�𗧂Ă�
	if (m_sprite.GetPosX() > SCREEN_WIDTH)
		m_bShipOutFlag = true;
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cTitleShip::Draw(){
	m_sprite.Draw();
}

//=======================================================================================
//
//		�D���E�t���O�̎擾�֐�
//
//=======================================================================================
bool cTitleShip::GetShipOutFlag()
{
	return m_bShipOutFlag;
}