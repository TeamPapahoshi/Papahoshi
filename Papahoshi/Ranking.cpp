//======================================================================
//	Ranking.cpp
//	
//	�T�v�Q�F�����L���O�\��
//	����ҁF���� ����
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Ranking.h"
#include "debugproc.h"		//printdebug
#include "Texture.h"
#include "Score.h"

//-----------------------------
//�}�N����`
//-----------------------------
#define DEFAULT_SCORE (1000)			//�f�t�H���g�̃X�R�A�̒l(臒l)

#define RANKING_EFFECT_FLAME (10)		//�G�t�F�N�g�����̃t���[��臒l
#define EFFECT_LIFE_TIME     (40)		//�G�t�F�N�g�̐����t���[��
#define EFFECT_SIZE          (50.0f)
#define EFFECTCOLOR_CHANGE_POINT (3)	//�G�t�F�N�g�̐F�؂�ւ�臒l

#define	RANKING_SIZE_X		(55.0f)		// ���ʕ\���̐����̕�
#define	RANKING_SIZE_Y		(55.0f)		// ���ʕ\���̐����̍���
#define	RANKING_INTERVAL_X	(0.0f)		// ���ʕ\���̐����̉������\���Ԋu
#define	RANKING_INTERVAL_Y	(3.0f)		// ���ʕ\���̐����̏c�����\���Ԋu

#define RANKING_POS_X       (120.0f)		// ���ʂ̕\�������W
#define RANKING_POS_Y       (180.0f)		// ���ʂ̕\���c���W

#define RANKING_SCORE_POS_X (RANKING_POS_X + RANKING_SIZE_X * 4)	// �X�R�A�̕\�������W
#define RANKING_SCORE_POS_Y (RANKING_POS_Y)							// �X�R�A�̕\���c���W

#define NUMBER_TEX_DIVIDE_X (10)
#define NUMBER_TEX_DIVIDE_Y (1)

#define RANKING_ALPHA_CHANGE_NUM (8)	//�����Z�����A���t�@�l

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------

//-----------------------------
//�O���[�o��
//-----------------------------
bool g_bDefaultScore = false;	//�X�R�A�̃��Z�b�g�p�t���O(true�ɂ���ƃf�t�H���g�̒l�������L���O�ɓ���)

//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cRanking::cRanking(){

	//�t�@�C���̓ǂݍ���(���s������f�t�H���g�f�[�^�̐ݒ�)
	if (!ReadRanking() || g_bDefaultScore)
	//if (g_bDefaultScore)
	{
		int defaultdata = DEFAULT_SCORE;

		for (int dataloop = MAX_RANKING; dataloop > 0; dataloop--)
		{
			m_nScoreData[dataloop - 1] = defaultdata;

			defaultdata += DEFAULT_SCORE;
		}
	}
	//����������
	m_nScoreAlpha = 255;
	m_nScoreEffectFlame = 0;
	m_nChangeScorePoint = 0;
	m_nHSVColor         = 0;
	m_bChangeScoreFlag = false;
	m_bScoreAlphaChange = false;
	m_bHSVChange = false;

	//�����L���O�̓���ւ�
	SortRanking();

	//�����L���O�̓���ւ��ɉ����ăG�t�F�N�g�̐F�ݒ�
	if (m_nChangeScorePoint < EFFECTCOLOR_CHANGE_POINT)
	{
		m_aEffectColorData = {0, 255, 255};
	}
	else
	{
		m_aEffectColorData = {0, 0, 255};
	}

	//�l�̏�����
	for (int Initloop = 0; Initloop < MAX_RANKING; Initloop++)
	{
		//���ʕ\���X�v���C�g�̏�����
		for (int Rankloop = 0; Rankloop < MAX_RANK; Rankloop++)
		{
			m_RankSprite[Initloop][Rankloop].SetPos(D3DXVECTOR2(RANKING_POS_X + ((RANKING_SIZE_X + RANKING_INTERVAL_X) * Rankloop),
				RANKING_POS_Y + ((RANKING_SIZE_Y + RANKING_INTERVAL_Y) * Initloop)));
			m_RankSprite[Initloop][Rankloop].SetSize(D3DXVECTOR2(RANKING_SIZE_X, RANKING_SIZE_Y));
			m_RankSprite[Initloop][Rankloop].SetTexture(cTextureManeger::GetTextureResult(TEX_NUMBER));
			m_RankSprite[Initloop][Rankloop].SetTexPatternDevide(NUMBER_TEX_DIVIDE_X, NUMBER_TEX_DIVIDE_Y);
		}

		//�X�R�A�\���X�v���C�g�̏�����
		for (int Scoreloop = 0; Scoreloop < MAX_SCORE; Scoreloop++)
		{
			m_ScoreSprite[Initloop][Scoreloop].SetPos(D3DXVECTOR2(RANKING_SCORE_POS_X + ((RANKING_SIZE_X + RANKING_INTERVAL_X) * Scoreloop),
				RANKING_SCORE_POS_Y + ((RANKING_SIZE_Y + RANKING_INTERVAL_Y) * Initloop)));
			m_ScoreSprite[Initloop][Scoreloop].SetSize(D3DXVECTOR2(RANKING_SIZE_X, RANKING_SIZE_Y));
			m_ScoreSprite[Initloop][Scoreloop].SetTexture(cTextureManeger::GetTextureResult(TEX_NUMBER));
			m_ScoreSprite[Initloop][Scoreloop].SetTexPatternDevide(NUMBER_TEX_DIVIDE_X, NUMBER_TEX_DIVIDE_Y);
		}

		//�ԍ��X�v���C�g�̐ݒ�
		SetNumber(&m_RankSprite[Initloop][MAX_RANK - 1], Initloop + 1, MAX_RANK);
		SetNumber(&m_ScoreSprite[Initloop][MAX_SCORE - 1], m_nScoreData[Initloop], MAX_SCORE);

	}

}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cRanking::~cRanking(){

	//�t�@�C���ւ̏�������
	WriteRanking();
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cRanking::Update(){

	//�����L���O�ύX�t���O�������Ă���Ώ���
	if (m_bChangeScoreFlag)
	{
		//�G�t�F�N�g�����t���[���̌��Z
		m_nScoreEffectFlame--;

		//�����L���O�̓���ւ���3�ʈȏ�ōs���Ă�����
		if (m_nChangeScorePoint < EFFECTCOLOR_CHANGE_POINT)
		{
			if (m_bHSVChange)
			{
				m_nHSVColor++;
			}
			else
			{
				m_nHSVColor--;
			}

			if (m_nHSVColor <= 0)
			{
				m_nHSVColor = 0;
				m_bHSVChange = true;
			}
			else if (m_nHSVColor >= 360)
			{
				m_nHSVColor = 360;
				m_bHSVChange = false;
			}


			//HSV�̐F���ɔ��f
			m_aEffectColorData.h = m_nHSVColor;
		}

		//�G�t�F�N�g�����t���[�������l�ɒB������G�t�F�N�g�ݒ�
		if (m_nScoreEffectFlame < 0)
		{
			GetEffectManeger()->SetEffectSparkle(cTextureManeger::GetTextureResult(TEX_RESULT_EFFECT_SPARKLE),
				m_ScoreSprite[m_nChangeScorePoint][MAX_SCORE / 2].GetPos(),
				D3DXVECTOR2(EFFECT_SIZE, EFFECT_SIZE),
				m_aEffectColorData,
				EFFECT_LIFE_TIME,
				D3DXVECTOR2(RANKING_SIZE_X * (MAX_SCORE - 1), RANKING_SIZE_Y / 2),
				EFFECT_SPARKLE_TEX_DIVIDE_X, EFFECT_SPARKLE_TEX_DIVIDE_Y);

			if (m_nChangeScorePoint < EFFECTCOLOR_CHANGE_POINT)
			{
				m_nScoreEffectFlame = CRandam::RandamRenge(0, RANKING_EFFECT_FLAME);
			}
			else
			{
				m_nScoreEffectFlame = CRandam::RandamRenge(0, RANKING_EFFECT_FLAME * 3);
			}
		}

		//�A���t�@�l��0�Ȃ烿�l�̌��Z�J�n
		if (m_bScoreAlphaChange)
		{
			m_nScoreAlpha += RANKING_ALPHA_CHANGE_NUM;
		}
		else//�A���t�@�l���ő�l�Ȃ烿�l�̌��Z�J�n
		{
			m_nScoreAlpha -= RANKING_ALPHA_CHANGE_NUM;
		}

		if (m_nScoreAlpha <= 0)
		{
			m_nScoreAlpha = 0;
			m_bScoreAlphaChange = true;
		}
		else if (m_nScoreAlpha >= 255)
		{
			m_nScoreAlpha = 255;
			m_bScoreAlphaChange = false;
		}


		//�����L���O�\���̃��l�̐؂�ւ�

		for (int Rankloop = 0; Rankloop < MAX_RANK; Rankloop++)
		{
			m_RankSprite[m_nChangeScorePoint][Rankloop].SetVtxColorA(m_nScoreAlpha);
		}

		for (int Scoreloop = 0; Scoreloop < MAX_SCORE; Scoreloop++)
		{
			m_ScoreSprite[m_nChangeScorePoint][Scoreloop].SetVtxColorA(m_nScoreAlpha);
		}
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cRanking::Draw(){

	//�X�v���C�g�̕\��
	for (int Drawloop = 0; Drawloop < MAX_RANKING; Drawloop++)
	{
		//���ʂ̕\��
		for (int Rankloop = 0; Rankloop < MAX_RANK; Rankloop++)
		{
			m_RankSprite[Drawloop][Rankloop].Draw();
		}

		//�X�R�A�̕\��
		for (int Scoreloop = 0; Scoreloop < MAX_SCORE; Scoreloop++)
		{
			m_ScoreSprite[Drawloop][Scoreloop].Draw();
		}
	}

}

//=======================================================================================
//
//		�ԍ��e�N�X�`���̐ݒ�
//
//=======================================================================================
void cRanking::SetNumber(cSpriteParam* data, int num, int digit){

	int nTempNumber;	//�\�����錅


	for (int loop = digit; 0 < digit; digit--, data--)
	{
		//��ԉ��̌����𒊏o
		nTempNumber = num % 10;

		//��ԉ��̌���\������ԍ��Ƃ��ăZ�b�g
		data->SetCurrentAnimPattern(nTempNumber);

		//������E�ɂ��炷
		num = num / 10;
	}
}

//=======================================================================================
//
//		�����L���O�f�[�^�̓���ւ�
//
//=======================================================================================
void cRanking::SortRanking(){
	//���݃X�R�A���̎󂯎��
	int nScore = GetScore();

	//�f�o�b�O�p
	//nScore = 10000;

	//�����L���O�̍Œ�X�R�A�ɖ����Ȃ��ꍇ�͏��������Ȃ�
	if (m_nScoreData[MAX_RANKING - 1] > nScore) return;

	//�����L���O�̕ύX�����n�_�̊m�F����
	for (int Checkloop = MAX_RANKING - 1; Checkloop >= 0; Checkloop--)
	{
		if (m_nScoreData[Checkloop] > nScore)
		{
			//�ۑ�����Ă���X�R�A�����݃X�R�A������܂Ń��[�v���A�������烋�[�v�̈�O�Ɍ��݃X�R�A��ۑ�
			//�X�R�A�̕ۑ����ꂽ�ꏊ���L�^
			m_nChangeScorePoint = Checkloop + 1;

			//�����̏I��
			break;

		}
		else if (m_nScoreData[0] <= nScore)
		{
			//�ۑ�����Ă���X�R�A�����݃X�R�A������Ȃ�������A�z��̈�ԏ�ɕۑ�
			//�X�R�A�̕ۑ������ꏊ���L�^
			m_nChangeScorePoint = 0;

			//�����̏I��
			break;
		}

	}

	//�����L���O�̓���ւ�����
	for (int Changeloop = MAX_RANKING - 1; Changeloop >= m_nChangeScorePoint; Changeloop--)
	{
		//�X�R�A�̈ړ�
		m_nScoreData[Changeloop] = m_nScoreData[Changeloop - 1];
	}
	//���݃X�R�A�̕ۑ�
	m_nScoreData[m_nChangeScorePoint] = nScore;

	m_bChangeScoreFlag = true;
}

//=======================================================================================
//
//		�����L���O�f�[�^�̓ǂݍ���
//
//=======================================================================================
bool cRanking::ReadRanking(){

	ifstream ifs;	//�t�@�C���ǂݍ��ݗp

	//�t�@�C���̓W�J
	ifs.open("data/Ranking/Ranking.bin", ios_base::in | ios_base::binary);

	//���s������false��Ԃ��ăf�t�H���g�f�[�^�̐ݒ�
	if (!ifs) {
		return false;
	}

	//�t�@�C���̒��g��ǂݍ���
	ifs.read((char*)m_nScoreData, sizeof(int) * MAX_RANKING);

	//�t�@�C���ǂݍ��݂ɐ���
	return true;

	//�t�@�C���͎����I�ɕ�����
}

//=======================================================================================
//
//		�����L���O�f�[�^�̏�������
//
//=======================================================================================
void cRanking::WriteRanking(){

	ofstream ofs;	//�t�@�C���������ݗp

	//�t�@�C����V�K�쐬���ď������݊J�n
	ofs.open("data/Ranking/Ranking.bin", ios_base::out | ios_base::trunc | ios_base::binary);

	//char*�^�ɕϊ����ăX�R�A���̏�������
	ofs.write((char*)m_nScoreData, sizeof(int) * MAX_RANKING);

	//�t�@�C���͎����I�ɕ�����
}