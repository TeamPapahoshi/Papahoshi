//======================================================================
//	Gage.h
//	
//	�T�v�Q�F�Q�[�W�Ǘ��N���X
//	����ҁF���� ����
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Gage.h"
#include "input.h"
#include "Texture.h"

//-----------------------------
//�}�N����`
//-----------------------------
//�Q�[�W������
#define GAGE_ADD_VALUE		(4.0f)
#define GAGE_MINUS_VALUE	(0.2f)
#define MAX_GAGE_NUM (100.0f)

//�t���[���p
#define FLAME_SIZE_X (220.0f)
#define FLAME_SIZE_Y (60.0f)

#define FLAME_POS_X (FLAME_SIZE_X / 2.0f + 10.0f)
#define FLAME_POS_Y (SCREEN_HEIGHT - FLAME_SIZE_Y)

//�o�[�p
#define GAGE_SIZE_X (FLAME_SIZE_X - 40.0f)
#define GAGE_SIZE_Y (FLAME_SIZE_Y - 40.0f)

#define GAGE_POS_X (FLAME_POS_X)
#define GAGE_POS_Y (SCREEN_HEIGHT - FLAME_SIZE_Y / 1.35f)

#define GAGE_SET(GageNum) ((1.0f - (MAX_GAGE_NUM - GageNum) / MAX_GAGE_NUM))

//�G�t�F�N�g�p
#define GAGE_EFFECT_SET_FRAME (20)
#define GAGE_EFFECT_SIZE (40.0f)

//�~�`�G�t�F�N�g�p
#define GAGE_EFFECT_CIRCLE_SET_FRAME (20)
#define GAGE_EFFECT_CIRCLE_SIZE (12.5f)
#define GAGE_EFFECT_NUM_MAX (10)

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
//		������
//
//=======================================================================================
void cGage::Init(){
	//�o�[�X�v���C�g�̏�����
	m_GageSprite.SetPos(D3DXVECTOR2(GAGE_POS_X, GAGE_POS_Y));
	m_GageSprite.SetSize(D3DXVECTOR2(GAGE_SIZE_X, GAGE_SIZE_Y));
	m_GageSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_GAGE));
	m_GageSprite.SetVtxColor(D3DXCOLOR(0, 0, 128, 255));
	m_GageSprite.SetTexUVFlag();

	//�t���[���X�v���C�g�̏�����
	m_FlameSprite.SetPos(D3DXVECTOR2(FLAME_POS_X, FLAME_POS_Y));
	m_FlameSprite.SetSize(D3DXVECTOR2(FLAME_SIZE_X, FLAME_SIZE_Y));
	m_FlameSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_GAGEFLAME));
	m_FlameSprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));

	//�Q�[�W�̃X�e�[�^�X�̏�����
	m_fGageNum = 0.0f;
	m_bGageMax = false;
	m_nGageEffectNum = CRandam::RandamRenge(0, GAGE_EFFECT_SET_FRAME);

	m_bFeverStart = false;
	m_bFeverFin = false;
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cGage::UnInit(){

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cGage::Update(){

	if (m_bGageMax)
	{//�Q�[�W�}�b�N�X��Ԃ���Q�[�W�����X�Ɍ��炷
		m_fGageNum -= GAGE_MINUS_VALUE;
		if (m_fGageNum <= 0.0f)
		{
			m_bGageMax = false;
			m_bFeverFin = true;
			m_GageSprite.SetVtxColor(D3DXCOLOR(0, 0, 128, 255));
		}
	}
	//����E�������I�[�o�[���Ȃ��悤��
	if (m_fGageNum > MAX_GAGE_NUM)
		m_fGageNum = MAX_GAGE_NUM;
	if (m_fGageNum < 0.0f)
		m_fGageNum = 0.0f;

	//�Q�[�W�̃T�C�Y�ݒ�
	m_GageSprite.SetSizeX(GAGE_SIZE_X * GAGE_SET(m_fGageNum));
	m_GageSprite.SetPosX(GAGE_POS_X + m_GageSprite.GetSizeX() / 2 - GAGE_SIZE_X / 2);
	m_GageSprite.SetTexUVRatioX(1.0f * GAGE_SET(m_fGageNum));

	//----- �G�t�F�N�g�ݒ� ------
	//�Q�[�W���L�тĂ���ꍇ�̂݃G�t�F�N�g�o��
	if (m_GageSprite.GetSizeX() > 0)
	{
		//�G�t�F�N�g�J�E���^�̌���
		m_nGageEffectNum--;

		if (m_nGageEffectNum < 0)
		{
			GetEffectManeger()->SetEffectSparkle(cTextureManeger::GetTextureGame(TEX_GAME_EFFECT_SPARKLE),
				m_GageSprite.GetPos(),
				D3DXVECTOR2(GAGE_EFFECT_SIZE, GAGE_EFFECT_SIZE),
				D3DXCOLOR(255, 255, 255, 255),
				GAGE_EFFECT_SET_FRAME / 2,
				m_GageSprite.GetSize(),
				EFFECT_SPARKLE_TEX_DIVIDE_X, EFFECT_SPARKLE_TEX_DIVIDE_Y);

			m_nGageEffectNum = CRandam::RandamRenge(0, GAGE_EFFECT_SET_FRAME);
		}
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cGage::Draw(){
	m_FlameSprite.Draw();
	m_GageSprite.Draw();
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cGage::GageAdd()
{
	//�Q�[�W���}�b�N�X�łȂ����
		//�b��ŌŒ�l�ŃQ�[�W��������悤��
	m_fGageNum += GAGE_ADD_VALUE;

	//���Z���ɃG�t�F�N�g�ݒ�
	GetEffectManeger()->SetEffectCircle(cTextureManeger::GetTextureGame(TEX_GAME_STAR),
										D3DXVECTOR2(m_GageSprite.GetPos().x + m_GageSprite.GetSize().x / 2, m_GageSprite.GetPos().y),
										D3DXVECTOR2(GAGE_EFFECT_CIRCLE_SIZE, GAGE_EFFECT_CIRCLE_SIZE),
										m_GageSprite.GetVtxColor(),
										GAGE_EFFECT_CIRCLE_SET_FRAME,
										GAGE_EFFECT_NUM_MAX);

		//�ő�l�ɂȂ�����Q�[�W�}�b�N�X��Ԃ�
	if (m_fGageNum >= MAX_GAGE_NUM)
	{
		m_bGageMax = true;
		m_bFeverStart = true;
		m_GageSprite.SetVtxColor(D3DXCOLOR(0, 255, 128, 255));
	}
}