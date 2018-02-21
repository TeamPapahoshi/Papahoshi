//======================================================================
//	BG
//	
//	�T�v�Q�F�w�i
//			�g�������V�[���ŃC���X�^���X�����āAInit�Ȃǂ��Ăяo����
//			�Z�b�g
//	����ҁF�����@��
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>		//HRESULT��
#include "debugproc.h"		//printdebug
#include "Common.h"

#include"BG.h"


//---------------------
// �}�N��
//---------------------
#define BG_FILNAME_SKY ("Image/BG/black.png")
#define BG_STAR        ("Image/BG/bgstar.jpg")
#define BG_RESULT	   ("Image/BG/bgresult.jpg")

float i=0;
bool	a=false;
//=======================================================================================
//
//
//		�Ăяo���w�i�̎w��
//	
//
//=======================================================================================
void cBG::SetBG(BG bg){

	type = bg;

	sprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));

	// �w�i�͓������̂𕡐����[�h���Ȃ��̂ł����Œ��ڃ��[�h���܂�
	switch (type)
	{
	case TITLE:
		sprite.LoadTexture(BG_STAR);
		break;
	case GAME_MAIN:
		//sprite.LoadTexture(BG_FILNAME_SKY);
		sprite.SetHSVColorFlag(true);
		sprite.SetHSVColorOne(100, 50, 100, 0);
		sprite.SetHSVColorOne(50, 50, 100, 1);
		sprite.SetHSVColorOne(100, 50, 100, 2);
		sprite.SetHSVColorOne(50, 50, 100, 3);
		break;
	case GAME_SKY:
		//sprite.LoadTexture(BG_FILNAME_SKY);
		sprite.SetHSVColorFlag(true);
		sprite.SetHSVColorOne(100, 50, 100, 0);
		sprite.SetHSVColorOne(50, 50, 100, 1);
		sprite.SetHSVColorOne(100, 50, 100, 2);
		sprite.SetHSVColorOne(50, 50, 100, 3);
		/*sprite.SetVtxColorOne(D3DXCOLOR(80, 100, 100, 255), 0);
		sprite.SetVtxColorOne(D3DXCOLOR(0, 0, 0, 255), 1);
		sprite.SetVtxColorOne(D3DXCOLOR(0, 0, 0, 255), 2);
		sprite.SetVtxColorOne(D3DXCOLOR(0, 0, 0, 255), 3);
		sprite.SetVtxColorOne(D3DXCOLOR(80, 100, 100, 255), 1);
		sprite.SetVtxColorOne(D3DXCOLOR(80, 100, 100, 255), 2);
		sprite.SetVtxColorOne(D3DXCOLOR(80, 100, 100, 255), 3);*/


		break;
	case RESULT:
		sprite.LoadTexture(BG_RESULT);
		sprite.SetVtxColor(D3DXCOLOR(128,128,128,255));
		break;
	default:
		break;
	}


}

//=======================================================================================
//
//	
//	�R���X�g���N�^
//	
//	
//=======================================================================================
cBG::cBG(){

	sprite.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
	sprite.SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	type = TITLE;

}


//=======================================================================================
//
//	
//	�f�X�g���N�^
//	
//	
//=======================================================================================
cBG::~cBG(){


}

//=======================================================================================
//
//	
//	�X�V
//	
//	
//=======================================================================================
void cBG::Update(){


		if (!a)
			i += 1.0f;

		else
			i -= 1.0f;

		if (i >= 360){
			a = true;
		}
		if (i <= 0){
			a = false;
		}

		//	/*sprite.SetVtxColorOne(D3DXCOLOR(i, 0, 0, 255), 0);
		//	sprite.SetVtxColorOne(D3DXCOLOR(i, 0, 0, 255), 1);
		//	sprite.SetVtxColorOne(D3DXCOLOR(0, 0, i, 255), 2);
		//	sprite.SetVtxColorOne(D3DXCOLOR(0, 0, i, 255), 3);*/
		//sprite.SetHSVColorFlag(true);
		//sprite.SetHSVColorOne(i, 155, 155, 0);
		//sprite.SetHSVColorOne(i+50, 155, 155, 1);
		//sprite.SetHSVColorOne(i+100, 155, 155, 2);
		//sprite.SetHSVColorOne(i+150, 155, 155, 3);
	}

	/*sprite.SetHSVColorOne(100, 50, 100, 0);
	sprite.SetHSVColorOne(50, 50, 100, 1);
	sprite.SetHSVColorOne(100, 50, 100, 2);
	sprite.SetHSVColorOne(50, 50, 100, 3);*/


//=======================================================================================
//
//	
//	�`��
//	
//	
//=======================================================================================
void cBG::Draw(){

	sprite.Draw();
}