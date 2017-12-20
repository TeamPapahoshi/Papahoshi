//======================================================================
//	StageManeger
//	
//	�T�v�Q�F�X�e�[�W�Ǘ�
//
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___STAGE_MANEGER_H___
#define ___STAGE_MANEGER_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------
//----�p���p �X�e�[�W��{�N���X----
class cBaseStage{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual ~cBaseStage(){}
};

//----�X�e�[�W�Ǘ��p�N���X----
class cStageManager{

public:
	//�V�[���ԍ��p�񋓑�
	enum STAGE{
		STAGE_01,		// �X�e�[�W01
		STAGE_02,		// �X�e�[�W02
		STAGE_MAX,
	};

	 static void	ChangeStage(STAGE stage);	// �X�e�[�W�������̃X�e�[�W�֍X�V
	 void	Update();					// ���݂̃X�e�[�W�̍X�V�֐�
	 void	Draw();						// ���݂̃X�e�[�W�̕`��֐�

	 void	Uninit();

	 static void	SetStageNum(STAGE stage);	// ���݂̃X�e�[�W�ԍ��̐ݒ�

private:
	static cBaseStage* m_pStage;			// ���݂̃X�e�[�W
	static STAGE		m_nCurrentStageNum;	// ���݂̃X�e�[�W�ԍ�
};
#endif	//!___STAGE_MANEGER_H___