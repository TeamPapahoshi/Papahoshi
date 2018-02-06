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

	float		 m_fGageNum;
	bool		 m_bGageMax;
	int			 m_nGageEffectNum;

	//-----------------------------
protected:	//�N���X���ł̂ݎQ�Ɖ\

	//-----------------------------
public:		//�O������Q�Ɖ\



	void Init(void);
	void UnInit(void);
	void Update(void);
	void Draw(void);

	//----- �Q�b�^ ------
	bool GetGagemax(void)
	{
		return m_bGageMax;
	}
};

#endif	//!___SAMPLE_H___