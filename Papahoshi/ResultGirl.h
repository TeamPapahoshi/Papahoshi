//======================================================================
//	ResultGirl.h
//	
//	�T�v�Q�F���U���g��ʂ̏��̎q�\��
//	����ҁF���� ����
//	
//======================================================================
#ifndef ___RESULTGIRL_H___
#define ___RESULTGIRL_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Common.h"
#include "GameMain.h"	// �G�t�F�N�g�N���X�擾�p

//-----------------------------
//�}�N����`
//-----------------------------
#define   RESULTGIRL_POS_X (SCREEN_WIDTH - 320.0f)
#define   RESULTGIRL_POS_Y (SCREEN_HEIGHT - 150.0f)
#define   RESULTGIRL_SIZE_X (300.0f)
#define   RESULTGIRL_SIZE_Y (400.0f)

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------
// ���N���X:�N���X�T���v��
class cResultgirl
{
private:	//�O������Q�ƕs�\
	cSpriteParam m_cGirlsprite;
	int			 m_nAnimPattern;
	int			 m_nCurrentPattern;
	int			 m_nAnimFlame;
	bool		 m_nAnimFlag;	//true��max�́Afalse��min�̃e�N�X�`���\��

	//-----------------------------
protected:	//�N���X���ł̂ݎQ�Ɖ\

	//-----------------------------
public:		//�O������Q�Ɖ\

	cResultgirl();	//�R���X�g���N�^
	~cResultgirl();	//�f�X�g���N�^

	void Update(void);
	void Draw(void);

	bool GetResultGirlAnim(void)
	{
		return m_nAnimFlag;
	}
};

#endif	//!___SAMPLE_H___