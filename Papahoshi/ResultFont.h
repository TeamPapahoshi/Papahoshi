//======================================================================
//	ResultFont
//	
//	�T�v�Q�F���U���g��ʕ����\��
//	����ҁF���� ����
//	
//======================================================================
#ifndef ___RESULTFONT_H___
#define ___RESULTFONT_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Common.h"

//----- ���N���X����̃C���N���[�h -----
#include "Ranking.h"

//-----------------------------
//�}�N����`
//-----------------------------

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------
// ���N���X:�N���X�T���v��
class cResultFont
{
private:	//�O������Q�ƕs�\
	cSpriteParam m_cScoreFont;
	cSpriteParam m_cRankFont;
	cSpriteParam m_cNewRecordFont;

	cRanking*    m_pRanking;

	int			 m_nNewRecordAlpha;
	bool		 m_bNewRecordAlphaChangeFlag;

	//-----------------------------
protected:	//�N���X���ł̂ݎQ�Ɖ\

	//-----------------------------
public:		//�O������Q�Ɖ\

	cResultFont();	//�R���X�g���N�^
	~cResultFont();	//�f�X�g���N�^

	void Update(void);
	void Draw(void);

	void GetRankingData(cRanking* data)
	{
		m_pRanking = data;
	}
};

#endif	//!___SAMPLE_H___