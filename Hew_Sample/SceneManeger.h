//======================================================================
//	SceneManeger
//	
//	�T�v�Q�F�V�[���Ǘ�
//			������cpp�ɃV�[����ǉ����Ă���main��ς���K�v�͂���܂���B
//	����ҁF�����@��
//	
//======================================================================
#ifndef ___SCENE_MANEGER_H___
#define ___SCENE_MANEGER_H___

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------
//----�p���p �V�[����{�N���X----
class cBaseScene{
public:
	virtual void Update() = 0;	// �K�{
	virtual void Draw() = 0;	// �K�{
 
	virtual ~cBaseScene(){}		// �f�X�g���N�^���I�[�o���C�h�����邽��
};

//----�V�[���Ǘ��p�N���X----
class cSceneManeger{

public:
	//�V�[���ԍ��p�񋓑�
	enum SCENE{
		TITLE,	//�^�C�g��
		GAME,	//�Q�[�����C��
		//RESULT,	//���U���g
	};

	static void ChangeScene(SCENE scene);	// ���݂̃V�[���������̃V�[���֍X�V
	static void	Update();					// ���݂̃V�[���̍X�V�֐�
	static void	Draw();						// ���݂̃V�[���̕`��֐�

	static void Uninit();

	static void SetSceneNum(SCENE scene);	// ���݂̃V�[���ԍ��̐ݒ�

private:
	static	cBaseScene* m_pScene;			// ���݂̃V�[��
	static  SCENE		m_nCurrentSceneNum;	// ���݂̃V�[���ԍ�
};
#endif	//!___SCENE_MANEGER_H___