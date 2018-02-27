//======================================================================
//	Ranking.h
//	
//	�T�v�Q�F�����L���O�\��
//	����ҁF���� ����
//	
//======================================================================
#ifndef ___RANKING_H___
#define ___RANKING_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Common.h"
#include "GameMain.h"	// �G�t�F�N�g�N���X�擾�p

//-----------------------------
//�}�N����`
//-----------------------------
#define MAX_RANKING (10)
#define MAX_SCORE (5)
#define MAX_RANK  (2)

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------
// ���N���X:�N���X�T���v��
class cRanking
{
private:	//�O������Q�ƕs�\
	int m_nScoreData[MAX_RANKING];
	cSpriteParam m_ScoreSprite[MAX_RANKING][MAX_SCORE];
	cSpriteParam m_RankSprite[MAX_RANKING][MAX_RANK];

	int m_nScoreEffectFlame;	//�G�t�F�N�g�����t���[��
	HSVCOLOR m_aEffectColorData;//�G�t�F�N�g�̐F���(HSV�`��)
	int m_nHSVColor;			//HSV�̐F��
	bool m_bHSVChange;			//HSV�̐F���؂�ւ��t���O

	int  m_nScoreAlpha;			//�X�R�A�̃A���t�@�l
	bool m_bScoreAlphaChange;	//�X�R�A�̃A���t�@�l�؂�ւ��t���O
	int  m_nChangeScorePoint;	//�X�R�A�̕ύX���ꂽ�ꏊ
	bool m_bChangeScoreFlag;	//�X�R�A���ύX���ꂽ���̃t���O

	void SetNumber(cSpriteParam* sprite, int num, int digit);	//�ԍ��e�N�X�`���̐ݒ�
	void SortRanking(void); //�����L���O�̓���ւ�
	bool ReadRanking(void);	//�t�@�C���f�[�^����X�R�A�̓ǂݍ���
	void WriteRanking(void);//�t�@�C���f�[�^�ɃX�R�A�̏�������
	//-----------------------------
protected:	//�N���X���ł̂ݎQ�Ɖ\

	//-----------------------------
public:		//�O������Q�Ɖ\

	cRanking();	//�R���X�g���N�^
	~cRanking();	//�f�X�g���N�^

	void Update(void);
	void Draw(void);

	//	�X�R�A�X�V�t���O�̈����n��
	bool GetChangeScoreFlag(void)
	{
		return m_bChangeScoreFlag;
	}
};

#endif	//!___RANKING_H___