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
#include "GameMain.h"	// �G�t�F�N�g�N���X�擾�p

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
	float   m_fAddRad = 0;
};

// ���N���X:�N���X�T���v��
class cResultStar
{
private:	//�O������Q�ƕs�\
	cResultStarData* m_pStarData;	//���̃f�[�^
	cResultStarData* m_pRoot;		//���̃f�[�^�擪�ʒu

	cResultStarData* m_pMoveStarData;	//�ړ����鐯�̃f�[�^
	cResultStarData* m_pMoveRoot;		//�ړ����鐯�̃f�[�^�擪�ʒu

	cResultgirl*   m_pResultGirl;
	bool		   m_bStarFlag;	//���̏o���؂�ւ��t���O

	int            m_nSetMoveStarCount; //�ړ����鐯�̏o���J�E���^

	int	    m_nStarNum = 0;	//���̐�

	void SetMoveStar(void);
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