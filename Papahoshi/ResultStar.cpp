//======================================================================
//	ResultStar.cpp
//	
//	�T�v�Q�F���U���g��ʐ��\��
//	����ҁF���� ����
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "ResultStar.h"
#include "Texture.h"

//-----------------------------
//�}�N����`
//-----------------------------
#define STARNUM_MIN (5)
#define STARNUM_MAX (50)

#define STAR_POS_X	   (RESULTGIRL_POS_X)
#define STAR_POS_Y	   (RESULTGIRL_POS_Y + 9.0f)
#define STAR_POS_MIN_MARGIN_X (5.0f)
#define STAR_POS_MIN_MARGIN_Y (10.0f)
#define STAR_POS_MAX_MARGIN_X (30.0f)
#define STAR_POS_MAX_MARGIN_Y (40.0f)

#define STAR_SIZE	   (15.0f)
#define STAR_SIZE_MARGIN (15.0f)

#define STAR_GRAVITY    (0.1f)
#define STAR_MOVE_RIMIT_Y (RESULTGIRL_POS_Y - 50.0f)
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
cResultStar::cResultStar(){

}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cResultStar::~cResultStar(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;
	delete[] m_pStarData;
}

//=======================================================================================
//
//		������
//
//=======================================================================================
void cResultStar::Init(){

	//���̐��̎w��
	if (m_pResultGirl->GetResultGirlAnim())
		m_nStarNum = STARNUM_MAX;
	else
		m_nStarNum = STARNUM_MIN;

	m_pStarData = new cResultStarData[m_nStarNum]();	//���̃A�h���X�𓮓I�m��
	m_pRoot = m_pStarData;							//�A�h���X�̐擪��ۑ�

	//���̏�����
	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{
		float size = (CRandam::RandamRenge(STAR_SIZE, STAR_SIZE + STAR_SIZE_MARGIN));

		//�X�v���C�g�̏�����
		m_pStarData->m_sprite.SetPos(D3DXVECTOR2(STAR_POS_X + CRandam::RandamRenge(0, (int)STAR_POS_MIN_MARGIN_X),
												 STAR_POS_Y + CRandam::RandamRenge(0, (int)STAR_POS_MIN_MARGIN_Y)));
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(size, size));

		// �e�N�X�`���̐ݒ�
		m_pStarData->m_sprite.SetAnimationFlag(true);
		m_pStarData->m_sprite.SetTexPatternDevide(11, 2);
		m_pStarData->m_sprite.SetIntervalChangePattern(CRandam::RandamRenge(3,10));

		// ���̐F�̌���
		m_pStarData->m_nStarColorNum = CRandam::RandamRenge(0, 3);
		switch (m_pStarData->m_nStarColorNum)
		{
		case 0:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_YELLOW_STAR_ANIM));
			break;
		case 1:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_GREEN_STAR_ANIM));
			break;
		case 2:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_PINK_STAR_ANIM));
			break;
		case 3:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_BLUE_STAR_ANIM));
			break;
		default:
			break;
		}
	}
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cResultStar::Uninit(){
	//�A�h���X��擪�ɖ߂�
	m_pStarData = m_pRoot;

	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{

	}
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cResultStar::Update(){
	//�A�h���X��擪�ɖ߂�
	m_pStarData = m_pRoot;

	//�X�V����
	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{
		//���̎q�̃A�j���[�V�����ɉ����čX�V�����̓��e��ς���
		if (m_pResultGirl->GetResultGirlAnim())
		{//�X�R�A��臒l�ȏ�̏ꍇ�̏���
			/*
			//�d�͂̔��f
			if (m_pStarData->m_sprite.GetPosY() > STAR_MOVE_RIMIT_Y)
			{
				m_pStarData->m_sprite.SetMoveY(m_pStarData->m_sprite.GetMoveY() - STAR_GRAVITY);
				m_pStarData->m_sprite.SetPos(m_pStarData->m_sprite.GetPos() + m_pStarData->m_sprite.GetMove());
				if (m_pStarData->m_sprite.GetPosY() <= STAR_MOVE_RIMIT_Y)
				{
					m_pStarData->m_sprite.SetPosY(STAR_MOVE_RIMIT_Y);
				}
			}
			*/
		}
		else
		{//�X�R�A��臒l�ȉ��̏ꍇ�̏���

		}

		// �A�j���[�V����
		m_pStarData->m_sprite.AnimationLoop();
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cResultStar::Draw(){
	//�A�h���X��擪�ɖ߂�
	m_pStarData = m_pRoot;

	//�`�揈��
	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{
		m_pStarData->m_sprite.Draw();
	}
}