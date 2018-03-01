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
#define STARNUM_MAX (200)
#define STARNUM_MOVE (20)

#define STAR_POS_X	   (RESULTGIRL_POS_X)
#define STAR_POS_Y	   (RESULTGIRL_POS_Y - 5.0f)
#define STAR_POS_MIN_MARGIN_X (2.5f)
#define STAR_POS_MIN_MARGIN_Y (5.0f)
#define STAR_POS_MAX_MARGIN_X (9.0f)
#define STAR_POS_MAX_MARGIN_Y (5.0f)

#define STAR_SIZE	   (30.0f)
#define STAR_SIZE_MARGIN (20.0f)

#define STAR_GRAVITY    (0.1f)
#define STAR_MOVE_X_MARGIN   (20.0f)
#define STAR_MOVE_Y_MARGIN   (80.0f)
#define STAR_MOVE_RIMIT_Y (SCREEN_HEIGHT- STAR_SIZE / 2)

#define STAR_RAD        (0.003f)

#define STAR_SET_FRAME  (120)

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

	// �擪�ɖ߂�
	m_pMoveStarData = m_pMoveRoot;
	delete[] m_pMoveStarData;
}

//=======================================================================================
//
//		������
//
//=======================================================================================
void cResultStar::Init(){

	//���̐��̎w��
	if (m_pResultGirl->GetResultGirlAnim())
	{
		m_nStarNum = STARNUM_MAX;
		m_bStarFlag = true;
	}
	else
	{
		m_nStarNum = STARNUM_MIN;
		m_bStarFlag = false;
	}

	m_pStarData = new cResultStarData[m_nStarNum]();	//���̃A�h���X�𓮓I�m��
	m_pRoot = m_pStarData;							//�A�h���X�̐擪��ۑ�

	int   MarginX = 0;
	int   MarginY = 0;
	//���̏�����
	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{
		float size = (CRandam::RandamRenge(STAR_SIZE, STAR_SIZE + STAR_SIZE_MARGIN));
		//�}�[�W�͈̔͂��g��
		if (!(loop % 10))
		{
			MarginX += STAR_POS_MAX_MARGIN_X;
			MarginY += STAR_POS_MAX_MARGIN_Y;
		}

		//�X�v���C�g�̏�����
		if (m_bStarFlag)
			m_pStarData->m_sprite.SetPos(D3DXVECTOR2(STAR_POS_X + CRandam::RandamRenge(-(int)MarginX, (int)MarginX),
													 STAR_POS_Y + MarginY));
													 //STAR_POS_Y + CRandam::RandamRenge(-10, (int)STAR_POS_MAX_MARGIN_Y)));
		else
			m_pStarData->m_sprite.SetPos(D3DXVECTOR2(STAR_POS_X + CRandam::RandamRenge(-(int)STAR_POS_MIN_MARGIN_X, (int)STAR_POS_MIN_MARGIN_X),
													 STAR_POS_Y + CRandam::RandamRenge(0, (int)STAR_POS_MIN_MARGIN_Y)));
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(size, size));

		// �e�N�X�`���̐ݒ�
		m_pStarData->m_sprite.SetAnimationFlag(true);
		m_pStarData->m_sprite.SetIntervalChangePattern(CRandam::RandamRenge(20,40));
		
		// ���̐F�̌���
		m_pStarData->m_nStarColorNum = CRandam::RandamRenge(0, 4);
		switch (m_pStarData->m_nStarColorNum)
		{
		case 0:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_YELLOW_STAR_ANIM));
			m_pStarData->m_sprite.SetTexPatternDevide(4, 2);
			break;
		case 1:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_GREEN_STAR_ANIM));
			m_pStarData->m_sprite.SetTexPatternDevide(11, 2);
			break;
		case 2:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_PINK_STAR_ANIM));
			m_pStarData->m_sprite.SetTexPatternDevide(11, 2);
			break;
		case 3:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_BLUE_STAR_ANIM));
			m_pStarData->m_sprite.SetTexPatternDevide(4, 2);
			break;
		default:
			break;
		}

		//�g�p�t���O���I���ɂ���
		m_pStarData->m_bUse = true;

		m_pStarData->m_Light.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_STAR_LIGHT));
		m_pStarData->m_Light.SetAddBlend(true);
		m_pStarData->m_Light.SetSize(D3DXVECTOR2(m_pStarData->m_sprite.GetSize().x + 10, m_pStarData->m_sprite.GetSize().x + 10));
		m_pStarData->m_Light.SetPos(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x, m_pStarData->m_sprite.GetPos().y));

		if (m_bStarFlag)
			m_pStarData->m_Light.SetVtxColorA(120);
		else
			m_pStarData->m_Light.SetVtxColorA(255);
	}

	//�ړ����鐯�̏�����
	m_pMoveStarData = new cResultStarData[STARNUM_MOVE]();	//���̃A�h���X�𓮓I�m��
	m_pMoveRoot = m_pMoveStarData;							//�A�h���X�̐擪��ۑ�

	for (int loop = 0; loop < STARNUM_MOVE; loop++, m_pMoveStarData++)
	{
		//�o���O�͎g�p�t���O���I�t��
		m_pMoveStarData->m_bUse = false;
	}
	m_nSetMoveStarCount = 0;
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cResultStar::Uninit(){

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cResultStar::Update(){
	//�A�h���X��擪�ɖ߂�
	m_pStarData = m_pRoot;
	m_pMoveStarData = m_pMoveRoot;

	//�X�V����
	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{
		//�g�p�t���O���I���̏ꍇ�ɏ���
		if (!m_pStarData->m_bUse)	continue;

		//��]�̔��f
		m_pStarData->m_sprite.SetRad(m_pStarData->m_sprite.GetRad() + m_pStarData->m_fAddRad);

		// �A�j���[�V����
		m_pStarData->m_sprite.AnimationLoop();
	}

	//���̎q�̃A�j���[�V�����ɉ����čX�V�����̓��e��ς���
	if (m_bStarFlag)
	{//�X�R�A��臒l�ȏ�̏ꍇ�̏���

		//���̏o���J�E���^�𑝂₷
		m_nSetMoveStarCount++;
		if (m_nSetMoveStarCount >= STAR_SET_FRAME)
		{
			SetMoveStar();
			m_nSetMoveStarCount = 0;
		}

		for (int loop = 0; loop < STARNUM_MOVE; loop++, m_pMoveStarData++)
		{
			//�g�p�t���O���I���̏ꍇ�ɏ���
			if (!m_pMoveStarData->m_bUse)	continue;

			//��]�̔��f
			m_pMoveStarData->m_sprite.SetRad(m_pMoveStarData->m_sprite.GetRad() + m_pMoveStarData->m_fAddRad);

			//�ړ��ʂ̔��f
			m_pMoveStarData->m_sprite.SetPos(m_pMoveStarData->m_sprite.GetPos() + m_pMoveStarData->m_sprite.GetMove());
			m_pMoveStarData->m_Light.SetPos(m_pMoveStarData->m_sprite.GetPos());

			//�d�͂̔��f
			m_pMoveStarData->m_sprite.SetMoveY(m_pMoveStarData->m_sprite.GetMoveY() + STAR_GRAVITY);
			
			//��ʊO�ɏo����g�p�t���O���I�t�ɂ���
			if (m_pMoveStarData->m_sprite.GetPosY() >= STAR_MOVE_RIMIT_Y)
				m_pMoveStarData->m_bUse = false;
		}
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
	m_pMoveStarData = m_pMoveRoot;

	//�`�揈��
	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{
		//�g�p�t���O���I���̏ꍇ�ɏ���
		if (!m_pStarData->m_bUse)	continue;
		m_pStarData->m_Light.Draw();
		m_pStarData->m_sprite.Draw();

	}

	//�X�R�A��臒l�ȏ�̏ꍇ�̏���
	if (m_bStarFlag)
	{
		for (int loop = 0; loop < STARNUM_MOVE; loop++, m_pMoveStarData++)
		{
			//�g�p�t���O���I���̏ꍇ�ɏ���
			if (!m_pMoveStarData->m_bUse)	continue;
			m_pMoveStarData->m_Light.Draw();
			m_pMoveStarData->m_sprite.Draw();
		}
	}
}

//=======================================================================================
//
//		�ړ����鐯�̐ݒu
//
//=======================================================================================
void cResultStar::SetMoveStar()
{
	//�A�h���X��擪�ɖ߂�
	m_pMoveStarData = m_pMoveRoot;
	
	//�Z�b�g��������w��
	int nSetStar = CRandam::RandamRenge(5, STARNUM_MOVE);

	for (int loop = 0; loop < STARNUM_MOVE; loop++, m_pMoveStarData++)
	{
		//�g�p�t���O���I�t�̏ꍇ�ɏ���
		if (m_pMoveStarData->m_bUse)	continue;

		float size = (CRandam::RandamRenge(STAR_SIZE, STAR_SIZE + STAR_SIZE_MARGIN));

		m_pMoveStarData->m_sprite.SetPos(D3DXVECTOR2(STAR_POS_X + CRandam::RandamRenge(-(int)STAR_POS_MIN_MARGIN_X, (int)STAR_POS_MIN_MARGIN_X),
													 STAR_POS_Y + CRandam::RandamRenge(0, (int)STAR_POS_MIN_MARGIN_Y)));
		m_pMoveStarData->m_sprite.SetSize(D3DXVECTOR2(size, size));
		m_pMoveStarData->m_sprite.SetMove(D3DXVECTOR2((float)CRandam::RandamRenge(-STAR_MOVE_X_MARGIN, STAR_MOVE_X_MARGIN) / 10.0f,
												      (float)CRandam::RandamRenge(-STAR_MOVE_Y_MARGIN, -STAR_MOVE_Y_MARGIN / 2) / 10.0f));

		//�ړ��ʂɉ����ĉ�]���̉��Z
		m_pMoveStarData->m_fAddRad = m_pMoveStarData->m_sprite.GetMoveX() / 100.0f;

		// �e�N�X�`���̐ݒ�
		m_pMoveStarData->m_sprite.SetAnimationFlag(true);
		m_pMoveStarData->m_sprite.SetIntervalChangePattern(CRandam::RandamRenge(3, 10));

		// ���̐F�̌���
		m_pMoveStarData->m_nStarColorNum = CRandam::RandamRenge(0, 4);
		switch (m_pMoveStarData->m_nStarColorNum)
		{
		case 0:
			m_pMoveStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_YELLOW_STAR_ANIM));
			m_pMoveStarData->m_sprite.SetTexPatternDevide(4, 2);
			m_pMoveStarData->m_sprite.SetIntervalChangePattern(7);
			break;
		case 1:
			m_pMoveStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_GREEN_STAR_ANIM));
			m_pMoveStarData->m_sprite.SetTexPatternDevide(11, 2);
			m_pMoveStarData->m_sprite.SetIntervalChangePattern(7);
			break;
		case 2:
			m_pMoveStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_PINK_STAR_ANIM));
			m_pMoveStarData->m_sprite.SetTexPatternDevide(11, 2);
			m_pMoveStarData->m_sprite.SetIntervalChangePattern(7);
			break;
		case 3:
			m_pMoveStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_BLUE_STAR_ANIM));
			m_pMoveStarData->m_sprite.SetTexPatternDevide(4, 2);
			m_pMoveStarData->m_sprite.SetIntervalChangePattern(7);
			break;
		default:
			break;
		}

		//���̌��̐ݒ�
		m_pMoveStarData->m_Light.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_STAR_LIGHT));
		m_pMoveStarData->m_Light.SetAddBlend(true);
		m_pMoveStarData->m_Light.SetSize(D3DXVECTOR2(m_pMoveStarData->m_sprite.GetSize().x + 30, m_pMoveStarData->m_sprite.GetSize().x + 30));
		m_pMoveStarData->m_Light.SetPos(D3DXVECTOR2(m_pMoveStarData->m_sprite.GetPos().x, m_pMoveStarData->m_sprite.GetPos().y));
		m_pMoveStarData->m_Light.SetVtxColorA(255);
		
		//�o���������̎g�p�t���O���I����
		m_pMoveStarData->m_bUse = true;

		nSetStar--;
		//�S�ăZ�b�g���I������珈���𔲂���
		if (nSetStar <= 0)
			break;
	}
	
}