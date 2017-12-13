//======================================================================
//	GameMain
//	
//	�T�v�Q�FInit, UnInit, Update, Draw
//	����ҁF�Ԉ�@�Y��
//	
//======================================================================

#ifndef ___GAME_MAIN_H___
#define ___GAME_MAIN_H___

//------------------------------
//�C���N���[�h�t�@�C��
//------------------------------
#include <Windows.h>	//HRESULT��


//-----------------------------
// �񋓑̐錾
//-----------------------------
// �V�[���񋓑�
enum eScene {

	SCENE_TITLE = 0,
	SCENE_STAGE_SELECT,
	SCENE_GAME,
	SCENE_RESULT,

};	//�Q�[���V�[���J��

//------------------------------
//�v���g�^�C�v�錾
//------------------------------
//������
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindowed);
//�I������
void UnInit(void);
//�X�V
void Update(void);
//�`��
void Draw(void);
void SetScene(int nScene);

#endif //!___GAME_MAIN_H___