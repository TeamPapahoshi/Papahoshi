//======================================================================
//	Common
//	
//	�T�v�Q�F���ʕ���
//	����ҁF�Ԉ�@�Y��
//	
//======================================================================

#ifndef ___COMMON_H___
#define ___COMMON_H___

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include "d3dx9.h"		//D3DXVECTOR2��

//------------------------------
// �}�N����`
//------------------------------

//----- �X�N���[���̑傫�� ------------
#define SCREEN_WIDTH (950)	//����
#define SCREEN_HEIGHT (650) //����


//----- �f�o�b�O�p�@�\ ------------
//#define _DEBUG_TEXT_	//�f�o�b�O�p�e�L�X�g�\��

#ifdef _DEBUG_TEXT_
#define _FPS_MEASURE_		//FPS�v���@�\

#if 0	// --------- SCENE_GAME ---------
#define _DEBUG_TEXT_PLAYER_	//�v���C���[���@�f�o�b�O�\��
#define _DEBUG_HEART_
#endif


#endif

//---------------------------
// �񋓑̒�`
//---------------------------
enum eDirection {

	DIRECTION_LEFT = -1,
	DIRECTION_UP,
	DIRECTION_RIGHT,
	DIRECTION_DOWN
};


#endif //!___COMMON_H___