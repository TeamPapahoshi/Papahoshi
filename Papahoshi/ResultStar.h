//======================================================================
//	ResultStar.h
//	
//	�T�v�Q�F���U���g��ʐ��\��
//	����ҁF���� ����
//	
//======================================================================
#ifndef ___RESULTSTAR_H___
#define ___RESULTSTAR_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Common.h"
#include "BaseStar.h"
#include "ResultGirl.h"

//-----------------------------
//�}�N����`
//-----------------------------

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------
class cResultStarData :public cBaseStarData{
public:
	int		m_nEffectFrame = 0;
	int		m_nStarColorNum = 0;
	int		m_nLifeTime = 0;

};

// ���N���X:�N���X�T���v��
class cResultStar
{
private:	//�O������Q�ƕs�\
	cResultStarData* m_pStarData;	//���̃f�[�^
	cResultStarData* m_pRoot;		//���̃f�[�^�擪�ʒu

	cResultgirl*   m_pResultGirl;
	int			   m_nStarNum;	//���̐�

	//-----------------------------
protected:	//�N���X���ł̂ݎQ�Ɖ\

	//-----------------------------
public:		//�O������Q�Ɖ\

	cResultStar();	//�R���X�g���N�^
	~cResultStar();	//�f�X�g���N�^

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void GetResultGirlData(cResultgirl* data)
	{
		m_pResultGirl = data;
	}
};

#endif	//!___SAMPLE_H___