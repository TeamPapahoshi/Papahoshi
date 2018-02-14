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

//-----------------------------
//�}�N����`
//-----------------------------
#define DEFAULT_SCORE (1000)			//�f�t�H���g�̃X�R�A�̒l

#define	RANKING_SIZE_X		(40.0f)		// ���ʕ\���̐����̕�
#define	RANKING_SIZE_Y		(40.0f)		// ���ʕ\���̐����̍���
#define	RANKING_INTERVAL_X	(0.0f)		// ���ʕ\���̐����̉������\���Ԋu
#define	RANKING_INTERVAL_Y	(5.0f)		// ���ʕ\���̐����̏c�����\���Ԋu

#define RANKING_POS_X       (50.0f)		// ���ʂ̕\�������W
#define RANKING_POS_Y       (180.0f)		// ���ʂ̕\���c���W

#define RANKING_SCORE_POS_X (RANKING_POS_X + RANKING_SIZE_X * 4)	// �X�R�A�̕\�������W
#define RANKING_SCORE_POS_Y (RANKING_POS_Y)							// �X�R�A�̕\���c���W

#define NUMBER_TEX_DIVIDE_X (10)
#define NUMBER_TEX_DIVIDE_Y (1)

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
cRanking::cRanking(){

	//�t�@�C���̓ǂݍ���(���s������f�t�H���g�f�[�^�̐ݒ�)
	if (!ReadRanking())
	{
		int defaultdata = DEFAULT_SCORE;

		for (int dataloop = MAX_RANKING; dataloop > 0; dataloop--)
		{
			m_nScoreData[dataloop - 1] = defaultdata;

			defaultdata += DEFAULT_SCORE;
		}
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
void cRanking::SetNumber(cSpriteParam* data,int num, int digit){

	int nTempNumber;	//�\�����錅


	for (int loop = digit ; 0 < digit; digit--, data--)
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