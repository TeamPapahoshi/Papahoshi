//======================================================================
//	ResultFont.cpp
//	
//	�T�v�Q�F���U���g��ʕ����\��
//	����ҁF���� ����
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "ResultFont.h"
#include "Texture.h"

//-----------------------------
//�}�N����`
//-----------------------------
//�X�R�A�\��
#define FONT_SCORE_POS_X (SCREEN_WIDTH  - 390.0f)
#define FONT_SCORE_POS_Y (SCREEN_HEIGHT - 690.0f)

#define FONT_SCORE_SIZE_X (360.0f)
#define FONT_SCORE_SIZE_Y (144.0f)

//�����N�\��
#define FONT_RANK_POS_X (SCREEN_WIDTH  - 1030.0f)
#define FONT_RANK_POS_Y (SCREEN_HEIGHT - 690.0f)

#define FONT_RANK_SIZE_X (280.0f)
#define FONT_RANK_SIZE_Y (140.0f)

//�j���[���R�[�h�\��
#define FONT_NEWRECORD_POS_X (SCREEN_WIDTH  - 380.0f)
#define FONT_NEWRECORD_POS_Y (SCREEN_HEIGHT - 380.0f)

#define FONT_NEWRECORD_SIZE_X (400.0f)
#define FONT_NEWRECORD_SIZE_Y (100.0f)

#define FONT_NEWRECORD_ALPHA_CHANGE_FLAME (30)	//�A���t�@�l�؂�ւ��t���[��
#define FONT_NEWRECORD_ALPHA_CHANGE_NUM   (8)	//�����Z����郿�l

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
cResultFont::cResultFont(){
	
	m_cScoreFont.SetPos(D3DXVECTOR2(FONT_SCORE_POS_X, FONT_SCORE_POS_Y));
	m_cScoreFont.SetSize(D3DXVECTOR2(FONT_SCORE_SIZE_X, FONT_SCORE_SIZE_Y));
	m_cScoreFont.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_FONT_SCORE));

	m_cRankFont.SetPos(D3DXVECTOR2(FONT_RANK_POS_X, FONT_RANK_POS_Y));
	m_cRankFont.SetSize(D3DXVECTOR2(FONT_RANK_SIZE_X, FONT_RANK_SIZE_Y));
	m_cRankFont.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_FONT_RANK));

	m_cNewRecordFont.SetPos(D3DXVECTOR2(FONT_NEWRECORD_POS_X, FONT_NEWRECORD_POS_Y));
	m_cNewRecordFont.SetSize(D3DXVECTOR2(FONT_NEWRECORD_SIZE_X, FONT_NEWRECORD_SIZE_Y));
	m_cNewRecordFont.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_FONT_NEWRECORD));

	m_nNewRecordAlpha = 255;
	m_bNewRecordAlphaChangeFlag = false;
}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cResultFont::~cResultFont(){

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cResultFont::Update(){

	//�j���[���R�[�h�\���̍X�V
	//�����L���O���X�V����Ă����ꍇ
	if (m_pRanking->GetChangeScoreFlag())
	{

		//�A���t�@�l��0�Ȃ烿�l�̌��Z�J�n
		if (m_bNewRecordAlphaChangeFlag)
		{
			m_nNewRecordAlpha += FONT_NEWRECORD_ALPHA_CHANGE_NUM;
		}
		else//�A���t�@�l���ő�l�Ȃ烿�l�̌��Z�J�n
		{
			m_nNewRecordAlpha -= FONT_NEWRECORD_ALPHA_CHANGE_NUM;
		}

		if (m_nNewRecordAlpha <= 0)
		{
			m_nNewRecordAlpha = 0;
			m_bNewRecordAlphaChangeFlag = true;
		}
		else if (m_nNewRecordAlpha >= 255)
		{
			m_nNewRecordAlpha = 255;
			m_bNewRecordAlphaChangeFlag = false;
		}

		//�j���[���R�[�h�\���̃��l�̐؂�ւ�
		m_cNewRecordFont.SetVtxColorA((float)m_nNewRecordAlpha);
			
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cResultFont::Draw(){
	m_cScoreFont.Draw();
	m_cRankFont.Draw();
	if (m_pRanking->GetChangeScoreFlag())
		m_cNewRecordFont.Draw();
}