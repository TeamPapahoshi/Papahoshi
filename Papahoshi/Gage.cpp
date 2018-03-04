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

#include "sound.h"

//-----------------------------
//�}�N����`
//-----------------------------
//�Q�[�W������
#define GAGE_ADD_VALUE		(6.0f)
#define GAGE_MINUS_VALUE	(0.2f)
#define MAX_GAGE_NUM (100.0f)

//�t���[���p
#define FLAME_SIZE_X (250.0f)
#define FLAME_SIZE_Y (60.0f)

#define FLAME_POS_X (FLAME_SIZE_X / 2.0f + 20.0f)
#define FLAME_POS_Y (SCREEN_HEIGHT - FLAME_SIZE_Y)

//�o�[�p
#define GAGE_SIZE_X (FLAME_SIZE_X - 60.0f)
#define GAGE_SIZE_Y (FLAME_SIZE_Y - 40.0f)

#define GAGE_POS_X (FLAME_POS_X + 20.0f)
#define GAGE_POS_Y (SCREEN_HEIGHT - FLAME_SIZE_Y / 1.35f)

#define GAGE_SET(GageNum) ((1.0f - (MAX_GAGE_NUM - GageNum) / MAX_GAGE_NUM))

//�Q�[�W�����p
#define GAGE_FONT_SIZE_X (150.0f)
#define GAGE_FONT_SIZE_Y (42.0f)

#define GAGE_FONT_POS_X  (FLAME_POS_X + 20.0f)
#define GAGE_FONT_POS_Y  (FLAME_POS_Y - 20.0f)

//�G�t�F�N�g�p
#define GAGE_EFFECT_SET_FRAME (20)
#define GAGE_EFFECT_SIZE (40.0f)

//�~�`�G�t�F�N�g�p
#define GAGE_EFFECT_CIRCLE_SET_FRAME (20)
#define GAGE_EFFECT_CIRCLE_SIZE (22.5f)
#define GAGE_EFFECT_NUM_MAX (5)

//�Q�[�WHSV�ݒ�p
#define HSV_H_POINT1 (0)	//���_1��H�̒l
#define HSV_H_POINT2 (100)	//���_2��H�̒l
#define HSV_H_POINT3 (200)	//���_3��H�̒l
#define HSV_H_POINT4 (300)	//���_4��H�̒l

#define HSV_S_DEFAULT (0)
#define HSV_S_GAGEMAX (255)

#define HSV_V_DEFAULT (255)

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
	m_GageSprite.SetTexUVFlag();
	m_GageSprite.SetHSVColorFlag(true);
	//HSV�̐F�ݒ�
	for (int HSVLoop = 0; HSVLoop < 4; HSVLoop++)
	{
		//���[�v�񐔂ɉ����ĐF�ݒ�
		switch (HSVLoop)
		{
		case 0:
			m_aHSVColor[HSVLoop] = { HSV_H_POINT1, HSV_S_DEFAULT, HSV_V_DEFAULT };
			break;
		case 1:
			m_aHSVColor[HSVLoop] = { HSV_H_POINT2, HSV_S_DEFAULT, HSV_V_DEFAULT };
			break;
		case 2:
			m_aHSVColor[HSVLoop] = { HSV_H_POINT3, HSV_S_DEFAULT, HSV_V_DEFAULT };
			break;
		case 3:
			m_aHSVColor[HSVLoop] = { HSV_H_POINT4, HSV_S_DEFAULT, HSV_V_DEFAULT };
			break;
		}

		m_bHSVColorChange[HSVLoop] = false;

		//���_�ɐF����ݒ�
		m_GageSprite.SetHSVColorOne(m_aHSVColor[HSVLoop].h, m_aHSVColor[HSVLoop].s, m_aHSVColor[HSVLoop].v, HSVLoop);
	}

	//�t���[���X�v���C�g�̏�����
	m_FlameSprite.SetPos(D3DXVECTOR2(FLAME_POS_X, FLAME_POS_Y));
	m_FlameSprite.SetSize(D3DXVECTOR2(FLAME_SIZE_X, FLAME_SIZE_Y));
	m_FlameSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_GAGEFLAME));
	m_FlameSprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));

	//�t�H���g�X�v���C�g�̏�����
	m_FontSprite.SetPos(D3DXVECTOR2(GAGE_FONT_POS_X, GAGE_FONT_POS_Y));
	m_FontSprite.SetSize(D3DXVECTOR2(GAGE_FONT_SIZE_X, GAGE_FONT_SIZE_Y));
	m_FontSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_GAGE_FIVER));
	m_FontSprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));

	//�Q�[�W�̃X�e�[�^�X�̏�����
	m_fGageNum = 0.0f;
	m_bGageMax = false;
	m_nGageEffectNum = CRandam::RandamRenge(0, GAGE_EFFECT_SET_FRAME);

	m_bFeverStart = false;
	m_bFeverFin = false;

	//���ʉ��̉��ʒ���
	SetVolume(0.8f, SOUND_LABEL::SOUND_LABEL_SE_GAME_GAGEADD);
	SetVolume(0.8f, SOUND_LABEL::SOUND_LABEL_SE_GAME_GAGESUB);
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

			//HSV�̐F�ݒ�
			for (int HSVLoop = 0; HSVLoop < 4; HSVLoop++)
			{
				//���[�v�񐔂ɉ����ĐF�ݒ�
				switch (HSVLoop)
				{
				case 0:
					m_aHSVColor[HSVLoop] = { HSV_H_POINT1, HSV_S_DEFAULT, HSV_V_DEFAULT };
					break;
				case 1:
					m_aHSVColor[HSVLoop] = { HSV_H_POINT2, HSV_S_DEFAULT, HSV_V_DEFAULT };
					break;
				case 2:
					m_aHSVColor[HSVLoop] = { HSV_H_POINT3, HSV_S_DEFAULT, HSV_V_DEFAULT };
					break;
				case 3:
					m_aHSVColor[HSVLoop] = { HSV_H_POINT4, HSV_S_DEFAULT, HSV_V_DEFAULT };
					break;
				}

				m_bHSVColorChange[HSVLoop] = false;
			}
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

	//HSV�̐F�ݒ�
	for (int HSVLoop = 0; HSVLoop < 4; HSVLoop++)
	{
		//�Q�[�W�̏�ԂŐF��؂�ւ���
		if (m_bGageMax)
		{
			if (m_bHSVColorChange[HSVLoop])
			{
				m_aHSVColor[HSVLoop].h++;
			}
			else
			{
				m_aHSVColor[HSVLoop].h--;
			}

			//h�̒l��0�ȉ��Ȃ���Z�A360�ȏ�Ȃ猸�Z�ɐ؂�ւ���
			if (m_aHSVColor[HSVLoop].h <= 0)
			{
				m_aHSVColor[HSVLoop].h = 0;
				m_bHSVColorChange[HSVLoop] = true;
			}
			else if (m_aHSVColor[HSVLoop].h >= 360)
			{
				m_aHSVColor[HSVLoop].h = 360;
				m_bHSVColorChange[HSVLoop] = false;
			}
		}
		else
		{
			if (m_bHSVColorChange[HSVLoop])
			{
				//m_aHSVColor[HSVLoop].s += (HSVLoop + 1);
				m_aHSVColor[HSVLoop].s++;
			}
			else
			{
				//m_aHSVColor[HSVLoop].s -= (HSVLoop + 1);
				m_aHSVColor[HSVLoop].s--;
			}

			//s�̒l��0�ȉ��Ȃ���Z�A255�ȏ�Ȃ猸�Z�ɐ؂�ւ���
			if (m_aHSVColor[HSVLoop].s <= 0)
			{
				m_aHSVColor[HSVLoop].s = 0;
				m_bHSVColorChange[HSVLoop] = true;
			}
			else if (m_aHSVColor[HSVLoop].s >= 255)
			{
				m_aHSVColor[HSVLoop].s = 255;
				m_bHSVColorChange[HSVLoop] = false;
			}
		}

		//���_�ɐF����ݒ�
		m_GageSprite.SetHSVColorOne(m_aHSVColor[HSVLoop].h, m_aHSVColor[HSVLoop].s, m_aHSVColor[HSVLoop].v, HSVLoop);
	}

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
				HSVCOLOR{0, 0, 255},
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
	m_FontSprite.Draw();
}

//=======================================================================================
//
//		�Q�[�W�̑���
//
//=======================================================================================
void cGage::GageChange(int value)
{
	//�Q�[�W���}�b�N�X�łȂ����
		//�b��ŌŒ�l�ŃQ�[�W��������悤��
	m_fGageNum += value;

	//���Z���ɃG�t�F�N�g�ݒ�
	GetEffectManeger()->SetEffectCircle(cTextureManeger::GetTextureGame(TEX_GAME_STAR),
										D3DXVECTOR2(m_GageSprite.GetPos().x + m_GageSprite.GetSize().x / 2, m_GageSprite.GetPos().y),
										D3DXVECTOR2(GAGE_EFFECT_CIRCLE_SIZE, GAGE_EFFECT_CIRCLE_SIZE),
										D3DXCOLOR(255, 255, 255, 255),
										GAGE_EFFECT_CIRCLE_SET_FRAME,
										GAGE_EFFECT_NUM_MAX,
										false);

	//�����ɉ����Č��ʉ��̍Đ�
	if (value > 0)
	{
		PlaySound(SOUND_LABEL::SOUND_LABEL_SE_GAME_GAGEADD);
	}
	else
	{
		PlaySound(SOUND_LABEL::SOUND_LABEL_SE_GAME_GAGESUB);
	}

		//�ő�l�ɂȂ�����Q�[�W�}�b�N�X��Ԃ�
	if (m_fGageNum >= MAX_GAGE_NUM)
	{
		m_bGageMax = true;
		m_bFeverStart = true;
		//HSV�̐F�ݒ�
		for (int HSVLoop = 0; HSVLoop < 4; HSVLoop++)
		{
			//���[�v�񐔂ɉ����ĐF�ݒ�
			switch (HSVLoop)
			{
			case 0:
				m_aHSVColor[HSVLoop] = { HSV_H_POINT1, HSV_S_GAGEMAX, HSV_V_DEFAULT };
				break;
			case 1:
				m_aHSVColor[HSVLoop] = { HSV_H_POINT2, HSV_S_GAGEMAX, HSV_V_DEFAULT };
				break;
			case 2:
				m_aHSVColor[HSVLoop] = { HSV_H_POINT3, HSV_S_GAGEMAX, HSV_V_DEFAULT };
				break;
			case 3:
				m_aHSVColor[HSVLoop] = { HSV_H_POINT4, HSV_S_GAGEMAX, HSV_V_DEFAULT };
				break;
			}

			m_bHSVColorChange[HSVLoop] = true;

			//���_�ɐF����ݒ�
			m_GageSprite.SetHSVColorOne(m_aHSVColor[HSVLoop].h, m_aHSVColor[HSVLoop].s, m_aHSVColor[HSVLoop].v, HSVLoop);
		}

	}
}