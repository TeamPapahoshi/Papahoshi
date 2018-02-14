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
	cSpriteParam m_ScoreSprite[MAX_RANKING];

	void SortRanking(void); //�����L���O�̓���ւ�
	bool ReadRanking(void);	//�t�@�C���f�[�^����X�R�A�̓ǂݍ���
	void WriteRanking(void);//�t�@�C���f�[�^�ɃX�R�A�̏�������
	//-----------------------------
protected:	//�N���X���ł̂ݎQ�Ɖ\

	//-----------------------------
public:		//�O������Q�Ɖ\

	cRanking();	//�R���X�g���N�^
	~cRanking();	//�f�X�g���N�^

	void Init(void);
	void UnInit(void);
	void Update(void);
	void Draw(void);
};

#endif	//!___RANKING_H___