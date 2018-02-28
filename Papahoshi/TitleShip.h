//======================================================================
//	TitleShip.h
//	
//	�T�v�Q�F�^�C�g���I�u�W�F�N�g/�D
//	����ҁF���� ����
//	
//======================================================================
#ifndef ___TITLESHIP_H___
#define ___TITLESHIP_H___

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
class cTitleShip
{
private:
	cSpriteParam m_sprite;
	int			 m_nMakeSmokeTime;
	int			 m_nPlaySEFlame;
	bool         m_bShipOutFlag;
//-----------------------------
protected:

//-----------------------------
public:
	cTitleShip();	//�R���X�g���N�^
	~cTitleShip();	//�f�X�g���N�^

	void Init();	//����������
	void UnInit();	//�I������	
	void Update(bool bSceneChangeFlag);	//�X�V����
	void Draw();	//�`�揈��

	bool GetShipOutFlag();	// �D���E�t���O�̎擾
};

#endif	//!___TITLESHIP_H___