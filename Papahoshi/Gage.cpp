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
//�t���[���p
#define FLAME_SIZE_X (180.0f)
#define FLAME_SIZE_Y (50.0f)

#define FLAME_POS_X (SCREEN_WIDTH - FLAME_SIZE_X)
#define FLAME_POS_Y (SCREEN_HEIGHT - FLAME_SIZE_Y)

//�o�[�p
#define GAGE_SIZE_X (140.0f)
#define GAGE_SIZE_Y (20.0f)

#define GAGE_POS_X (SCREEN_WIDTH - FLAME_SIZE_X)
#define GAGE_POS_Y (SCREEN_HEIGHT - FLAME_SIZE_Y / 1.5f)

#define MAX_GAGE_NUM (100.0f)

#define GAGE_SET(GageNum) ((1.0f - (MAX_GAGE_NUM - GageNum) / MAX_GAGE_NUM))

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

	if (!m_bGageMax)
	{//�Q�[�W���}�b�N�X�łȂ����
		//�b��ŃL�[���͂ŃQ�[�W��������悤��
		if (GetKeyboardPress(DIK_P))
			m_fGageNum += 0.5f;

		//�ő�l�ɂȂ�����Q�[�W�}�b�N�X��Ԃ�
		if (m_fGageNum >= MAX_GAGE_NUM)
		{
			m_bGageMax = true;
			m_GageSprite.SetVtxColor(D3DXCOLOR(0, 255, 128, 255));
		}
	}
	else
	{//�Q�[�W�}�b�N�X��Ԃ���Q�[�W�����X�Ɍ��炷
		m_fGageNum -= 0.8f;
		if (m_fGageNum <= 0.0f)
		{
			m_bGageMax = false;
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