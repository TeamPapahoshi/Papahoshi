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

	int  m_nChangeScorePoint;
	bool m_bChangeScoreFlag;

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
};

#endif	//!___RANKING_H___