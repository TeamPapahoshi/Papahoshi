//=====================================================
//
//	MasicSplitGirl		Score.cpp
//
//	Mei Goto.
//
//=====================================================


//-------------------------------
// �C���N���[�h��
//-------------------------------
#include "Score.h"
#include "Sprite.h"
#include "debugproc.h"
#include "Texture.h"

//-------------------------------
// �萔��`
//-------------------------------
#define DIGIT_SCORE		(6)		//�X�R�A����
#define	DRAW_STAGING_SKIP_NUM	(7)		//�X�R�A���Z���o��1�t���[���ő���Z��
#define DRAW_STAGING_HISPEED_SKIP_NUM (77) //�X�R�A���Z���o��1�t���[�����Z��(����)

#define HISPEED_CHANGE_LINE      (800) //�X�R�A���Z���Z��������臒l

//-------------------------------
// �O���[�o���ϐ�
//-------------------------------
int	g_nScore;		//���݃X�R�A
int g_nPrintScore;	//���ݕ\�����̃X�R�A

cSpriteParam g_aScoreSprite[DIGIT_SCORE];


//=================================================
//
//  �X�R�A�󂯓n��
//
//=================================================
int GetScore(){
	return g_nScore;
}

//=================================================
//
// �X�R�A�Z�b�g
//
//=================================================
void SetScore(int score){
	g_nScore = score;
	g_nPrintScore = score;
}

//=================================================
//
// �X�R�A���Z
//
//=================================================
void AddScore(int score){
	g_nScore += score;
}

//=================================================
//
// �\�����̃X�R�A�̂݃��Z�b�g
//
//=================================================
void ResetPrintScore(){
	g_nPrintScore = 0;
}

//=================================================
//
// �X�R�A�`��
//
//=================================================
void DrawScore(D3DXVECTOR2 pos, D3DXVECTOR2 size){

	int work1, work2;
	work2 = g_nPrintScore;

	for (int i = DIGIT_SCORE - 1; i >= 0; i--)
	{
		//----- �X�R�A�̃X�v���C�g�����X�V -----
		work1 = work2 % 10;
		work2 = work2 / 10;
		switch (cSceneManeger::GetSceneNum())
		{
		case cSceneManeger::GAME:
		case cSceneManeger::TRANING:
			g_aScoreSprite[i].SetTexture(cTextureManeger::GetTextureGame((TEX_GAME)(TEX_GAME_0 + work1)));
			break;
		case cSceneManeger::RESULT:
			g_aScoreSprite[i].SetTexture(cTextureManeger::GetTextureResult((TEX_RESULT)(TEX_RESULT_0 + work1)));
			break;
		default:
			break;
		}
		g_aScoreSprite[i].SetPos(D3DXVECTOR2(pos.x + (size.x * 0.8f) * i, pos.y));
		g_aScoreSprite[i].SetSize(size);

		//----- �`�� -----
		g_aScoreSprite[i].Draw();
	}

	//----- �f�o�b�O�\�� -----
	PrintDebugProc("�X�R�A : %d\n", g_nPrintScore);
}

//==================================================
//
// �X�R�A�X�V
//
//==================================================
void UpdateScore(){

	//---------- ���Z�E���Z���o ------------
	//���Z
	if (g_nScore > g_nPrintScore){
		//�������l�ȏ�Ȃ���Z������������
		if (g_nScore - g_nPrintScore >= HISPEED_CHANGE_LINE)
			g_nPrintScore += DRAW_STAGING_HISPEED_SKIP_NUM;
		else
			g_nPrintScore += DRAW_STAGING_SKIP_NUM;
		if (g_nPrintScore > g_nScore)
			g_nPrintScore = g_nScore;	//�l�𓯂��ɒ���
	}
	//���Z
	else if (g_nScore < g_nPrintScore){
		//�������l�ȏ�Ȃ猸�Z������������
		if (g_nPrintScore - g_nScore <= HISPEED_CHANGE_LINE)
			g_nPrintScore -= DRAW_STAGING_HISPEED_SKIP_NUM;
		else
			g_nPrintScore -= DRAW_STAGING_SKIP_NUM;
		if (g_nPrintScore < g_nScore)
			g_nPrintScore = g_nScore;	//�l�𓯂��ɒ���
	}

}