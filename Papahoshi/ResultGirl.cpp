//======================================================================
//	ResultGirl.cpp
//	
//	�T�v�Q: ���U���g��ʂ̏��̎q
//	����ҁF���� ����
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "ResultGirl.h"
#include "Texture.h"
#include "Score.h"
#include "sound.h"

//-----------------------------
//�}�N����`
//-----------------------------

#define   TEXTURE_CHANGE_LINE (10000)	//�e�N�X�`���؂�ւ��̃X�R�A臒l(�b��)

#define   TEXTURE_PATTERN_MAX (2)
#define   TEXTURE_PATTERN_MIN (4)

#define   TEXTURE_ANIMATION_FLAME (60)	//�A�j���؂�ւ��̎���

#define   GINGLE_VOLUME (0.7f)
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
cResultgirl::cResultgirl(){
	//����������
	m_cGirlsprite.SetPos(D3DXVECTOR2(RESULTGIRL_POS_X, RESULTGIRL_POS_Y));
	m_cGirlsprite.SetSize(D3DXVECTOR2(RESULTGIRL_SIZE_X, RESULTGIRL_SIZE_Y));
	m_nCurrentPattern = 0;
	m_nAnimFlame = 0;
	//�X�R�A�����ȏゾ�����ꍇ
	if (GetScore() >= TEXTURE_CHANGE_LINE)
	//�f�o�b�O�p
	//if (1)
	{
		m_cGirlsprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_GIRL_MAX_1));
		m_nAnimPattern = TEXTURE_PATTERN_MAX;
		m_nAnimFlag = true;
		SetVolume(GINGLE_VOLUME, SOUND_LABEL::SOUND_LABEL_GINGLE_RESULT_MAX);
		PlaySound(SOUND_LABEL::SOUND_LABEL_GINGLE_RESULT_MAX);
	}
	else
	{
		m_cGirlsprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_GIRL_MIN_1));
		m_nAnimPattern = TEXTURE_PATTERN_MIN;
		m_nAnimFlag = false;
		SetVolume(GINGLE_VOLUME, SOUND_LABEL::SOUND_LABEL_GINGLE_RESULT_MIN);
		PlaySound(SOUND_LABEL::SOUND_LABEL_GINGLE_RESULT_MIN);
	}

}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cResultgirl::~cResultgirl(){

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cResultgirl::Update(){
	//�A�j���؂�ւ��t���[���̉��Z
	m_nAnimFlame++;

	//�؂�ւ��t���[�������l�ɒB������
	if (m_nAnimFlame >= TEXTURE_ANIMATION_FLAME)
	{
		//�e�N�X�`���̐؂�ւ�
		m_nCurrentPattern = (m_nCurrentPattern + 1 + m_nAnimPattern) % m_nAnimPattern;

		if (m_nAnimFlag)
		{
			m_cGirlsprite.SetTexture(cTextureManeger::GetTextureResult((TEX_RESULT)(TEX_RESULT_GIRL_MAX_1 + m_nCurrentPattern)));
		}
		else
		{
			m_cGirlsprite.SetTexture(cTextureManeger::GetTextureResult((TEX_RESULT)(TEX_RESULT_GIRL_MIN_1 + m_nCurrentPattern)));
		}

		m_nAnimFlame = 0;
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cResultgirl::Draw(){
	m_cGirlsprite.Draw();
}