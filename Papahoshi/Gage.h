//======================================================================
//	Gage.h
//	
//	�T�v�Q�F�Q�[�W�Ǘ��N���X
//	����ҁF���� ����
//	
//======================================================================
#ifndef ___GAGE_H___
#define ___GAGE_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "Common.h"
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
// ���N���X:�Q�[�W�N���X
class cGage
{
private:	//�O������Q�ƕs�\
	cSpriteParam m_GageSprite;
	cSpriteParam m_FlameSprite;
	HSVCOLOR     m_aHSVColor[4];		//HSV�̒l
	bool		 m_bHSVColorChange[4];	//HSV�̐F�؂�ւ��t���O

	float		 m_fGageNum;
	bool		 m_bGageMax;	//�Q�[�W��ԃt���O(�Q�[�W���ő�l�ɂȂ�����true,0�ɂȂ�����false)
	int			 m_nGageEffectNum;

	bool	m_bFeverStart;
	bool	m_bFeverFin;

	//-----------------------------
protected:	//�N���X���ł̂ݎQ�Ɖ\

	//-----------------------------
public:		//�O������Q�Ɖ\
	void Init(void);
	void UnInit(void);
	void Update(void);
	void Draw(void);

	void GageAdd(void);	//�Q�[�W���Z

	//----- �Q�b�^ ------
	bool GetGagemax(void)
	{
		return m_bGageMax;
	}

	cSpriteParam GetGageSprite(void)
	{
		return m_GageSprite;
	}

	bool GetFeverStart(){
		return m_bFeverStart;
	}

	bool GetFeverFin(){
		return m_bFeverFin;
	}

	void SetFeverStart(bool flug){
		m_bFeverStart = flug;
	}

	void SetFeverFin(bool flug){
		m_bFeverFin = flug;
	}
};

#endif	//!___SAMPLE_H___