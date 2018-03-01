//=============================================================================
//  Net.cpp
//
//  ����F�㓡 ����
//  �T�v�F�Ԃ̏���
//
//	****** �f�ރv�b�V�����܂������I�H�I�H�I�H ******
//
//  ���o�[���͕����̓e���L�[�Ɍ����ĂĊi�[�i�i���Q�[����1P�R�}���h�\�L�j
//	789
//	456
//	123
//=============================================================================
//
//  AB�̌X����0.0f�̎����������߂�Ƃ���
//  0���Z���s���ăG���[���N���āA�\������Ȃ��Ȃ�B
//  Y���ɕ��s�Ȓ����̌X���͒�`�ł��Ȃ��H
//
//=============================================================================


//-------------------------------------
// �C���N���[�h��
//-------------------------------------
#include "Net_Type2.h"
#include "Texture.h"
#include "SceneGame.h"
#include "Input.h"
#include "debugproc.h"
#include "MathEX.h"
#include "sound.h"

#ifdef  _TYPE_2_


//-------------------------------------
// �萔�E�}�N����`
//-------------------------------------
//�g�p�{�^��
#define BOTTON_NET_LEFT			(AC_CON_BUTTON_E)
#define BOTTON_NET_RIGHT		(AC_CON_BUTTON_A)
#define BOTTON_NET_CENTER		(AC_CON_BUTTON_B)
//�e�N�X�`���T�C�Y
#define UKI_SIZE (20.0f)	//�����̃T�C�Y
#define ARROW_SIZE_X (300.0f)	//���̃T�C�Y
#define ARROW_SIZE_Y (120.0f)
//�X�s�[�h
#define MAX_SPEED	(15.5f)
#define DECRE_SPEED (0.1f)	//�P�t���[�����Ƃɏ������炷��
#define DECRE_THROW_SPEED	(0.1f)	//�܂���
//�҂�����
#define INTERVAL_THOROW_PULL	(20)	//������������グ�܂ł̑҂�����
//�����Ƃ�
#define PULL_WAIT	(15)	//�҂����ԁH
//���~
#define MIN_SPEED	(1.0f)	//�Œ�X�s�[�h
#define SPEED_HALFCIRCLE	(5)	//10/1�i��
//�΂ߓ����␳
#define ANG_NUM		(200.0f)
//�c�␳�l
#define ANG_Y_FIRST		(100.0f)
#define ANG_Y_SECOND	(ANG_Y_FIRST * 2.0f)
//����_�����߂�
#define CP_DIVIDE	(4)			//�����̕�����
#define CP_DISTANCE	((float)SCREEN_HEIGHT / 4.0f)	//�����Ƃ̋���

//�e�N�X�`���J���[
#define NET_TEX_SATURATION		(90.0f)
#define NET_TEX_VALUE			(100.0f)
#define NET_TEX_MAX_HUE			(360.0f)
#define NET_TEX_MIN_HUE			(0.0f)
#define NET_TEX_INCREMENT_HUE	(10.0f)

//=====================================================
//
//  �Ԃ̃R���X�g���N�^
//
//=====================================================
cNet::cNet() :
//---- �C�j�V�����C�U ----
gamePhase(PHASE_POST),
m_bDrawArrow(false),
m_bAllPress(false),
m_nLeverDirection(5),	//�j���[�g����
m_nFrameCnt(0),
m_postPhase(POST_NON),
m_fThrowSpeed(0.0f)
{

	//---- ���S�_�̏����� ----
	//m_centerPos = D3DXVECTOR2(SCREEN_WIDTH / 4.0f + (SCREEN_WIDTH / 4.0f * 3.0f / 2.0f), SCREEN_HEIGHT + 30.0f);
	m_centerPos = D3DXVECTOR2(GAME_SCREEN_LEFT + (GAME_SCREEN_RIGHT - GAME_SCREEN_LEFT) / 2.0f, SCREEN_HEIGHT + 30.0f);

	//---- �l���_�̏����� ----
	for (int i = 0; i < 3; i++)
		m_aPos[i] = m_centerPos;

	//---- �X�v���C�g�̏����� ----

	//����
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
				m_aNet[z][y][x].SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_NET));	// �e�N�X�`���̃Z�b�g
				m_aNet[z][y][x].SetAddBlend(true);
			}
		}
	}

	//�����E�l���_
	for (int i = 0; i < 3; i++){
		m_aFourUki[i].SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_UKI));
		m_aFourUki[i].SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));
	}
	m_aFourUki[0].LoadTexture("Image/Net/red.png");
	m_aFourUki[1].LoadTexture("Image/Net/blue.png");
	m_aFourUki[2].LoadTexture("Image/Net/yellow.png");

	//�����E�Z���^�[
	m_center.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_UKI));
	m_center.SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));

	//���
	m_arrow.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_ARROW));
	m_arrow.SetPos(D3DXVECTOR2(m_centerPos.x, SCREEN_HEIGHT - 80.0f));
	m_arrow.SetSize(D3DXVECTOR2(ARROW_SIZE_X, ARROW_SIZE_Y));
	m_arrow.SetRad(D3DX_PI);

	//���~
	m_halfCircle.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_HALFCIRCLE));
	m_halfCircle.SetPos(D3DXVECTOR2(GAME_SCREEN_LEFT + ((GAME_SCREEN_RIGHT - GAME_SCREEN_LEFT) / 2.0f), SCREEN_HEIGHT));
	m_halfCircle.SetSize(D3DXVECTOR2(GAME_SCREEN_RIGHT - GAME_SCREEN_LEFT, GAME_SCREEN_UNDER - GAME_SCREEN_TOP));
	m_halfCircle.SetScale(D3DXVECTOR2(0.0f, 0.0f));

	//--------- �����蔻��̏����� --------------
	m_aCollider[0].SetType(cCollider::CollisionType::TRIANGLE);
	m_aCollider[1].SetType(cCollider::CollisionType::TRIANGLE);
	m_aCollider[0].SetTriangleCollider(m_aPos[1], m_centerPos, m_aPos[0]);
	m_aCollider[1].SetTriangleCollider(m_aPos[2], m_centerPos, m_aPos[1]);

	//--- �e�N�X�`���J���[ ---
	m_fNetHue = NET_TEX_MIN_HUE;
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
				m_aNet[z][y][x].SetHSVColorFlag(true);
			}
		}
	}

	//�g��
	for (int i = 0; i < MAX_RIPPLE; i++){
		m_aRipple[i] = NULL;
	}

	//�p�[�e�B�N��
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){
		m_aPirticle[i] = NULL;
	}
}


//=====================================================
//
// �Ԃ̃f�X�g���N�^
//
//=====================================================
cNet::~cNet(){



}


//=====================================================
//
// �Ԃ̍X�V
//
//=====================================================
void cNet::Update(){

	//���͂���t
	Input();

	//�Q�[���t�F�C�Y���Ƃ̍X�V
	switch (gamePhase)
	{
	case PHASE_POST:	//�\��
		PostPhaseUpdate();
		break;
	case PHASE_SHOUT:	//����
		ShoutPhaseUpdate();
		break;
	case PHASE_PULL:	//����
		PullPhaseUpdate();
		break;
	}

	//���_���ɍ��킹�Ă��݂��͂�
	SetNet();

	//�e�N�X�`���J���[�̍X�V
	NetColorUpdate();

	//�g��̍X�V
	for (int i = 0; i < MAX_RIPPLE; i++){
		if (m_aRipple[i]){
			m_aRipple[i]->Update();
			if (m_aRipple[i]->GetFinFlug()){
				delete m_aRipple[i];
				m_aRipple[i] = NULL;
			}
		}
	}

	//�p�[�e�B�N���̍X�V
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){
		if (m_aPirticle[i]){
			m_aPirticle[i]->Update();
			if (m_aPirticle[i]->GetFinFlug()){
				delete m_aPirticle[i];
				m_aPirticle[i] = NULL;
			}
		}
	}

	//�����蔻����̍X�V
	m_aCollider[0].SetTriangleCollider(m_aPos[1], m_centerPos, m_aPos[0]);
	m_aCollider[1].SetTriangleCollider(m_aPos[2], m_centerPos, m_aPos[1]);

}

//=====================================================
//
// �Ԃ̕`��
//
//=====================================================
void cNet::Draw(){

	//�͂���
	for (int i = 0; i < MAX_RIPPLE; i++){
		if (m_aRipple[i])
			m_aRipple[i]->Draw();
	}

	//�p�[�e�B�N��
	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){
		if (m_aPirticle[i])
			m_aPirticle[i]->Draw();
	}

	//����
	//******
	// z = 0
	// y < NET_Y_NUM
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
				if (m_centerPos <= m_aPos[z] ||
					m_centerPos <= m_aPos[z + 1]){
					y = NET_Y_NUM + 1;
					break;
				}
				m_aNet[z][y][x].DrawFreePos();
			}
		}
	}

	//����
	for (int i = 0; i < 3; i++){
		m_aFourUki[i].Draw();
	}

	//���S�_
	m_center.Draw();

	//���(�\����Ԃ̎�)
	if (m_bDrawArrow)
		m_arrow.Draw();

	//���~(������Ԃ̎�)
	if (gamePhase == PHASE_SHOUT)
		m_halfCircle.Draw();

}


//====================================================
//
// �e���_�ɍ��킹�Ă��݂�\��
//
//====================================================
void cNet::SetNet(){

	//---- ���[�J���ϐ� ----
	D3DXVECTOR2 workPos[4];	//�ŏI�|�W�V����
	bool skip;	//�v�Z�X�L�b�v�t���u
	D3DXVECTOR2 cp1, cp2;	//�c���C���̐���_
	D3DXVECTOR2 cp3, cp4;	//�����C���̐���_
	D3DXVECTOR2	topXleft, topXright;		//���X�̗��[
	D3DXVECTOR2	underXleft, underXright;	//����
	D3DXVECTOR2	leftYtop, leftYunder;		//����
	D3DXVECTOR2	rightYtop, rightYunder;		//�E��
	float regula;	//������Ԃɍ��킹�Ē���

	//---- �E�L�̈ʒu��ݒ� ----
	for (int i = 0; i < 3; i++){
		m_aFourUki[i].SetPos(m_aPos[i]);
	}
	m_center.SetPos(m_centerPos);

	//---- �Ȑ���ɍ��W��ݒ� -----
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){

				//---- �ϐ��̏����� ----
				for (int i = 0; i < 4; i++){
					workPos[i] = m_centerPos;
				}
				skip = false;

				switch (z)
				{
				case NET_PARTS_RIGHT://RIGHT

					//------ �Ԓ��肪�K�v�Ȃ��ꍇ�͏������s��Ȃ� ------
					if (m_centerPos == m_aPos[0] ||
						m_centerPos == m_aPos[1]){
						skip = true;
						break;
					}

					//------- �l�̒��� --------------
					if (x == 0){

						//------ �ŏ��̈��̂݌v�Z ---------
						if (y == 0){

							//****** ����AO�̐���_���v�Z *******
							//�ϐ��錾
							D3DXVECTOR2 d, e;
							float aoSlop, aoInter, dfSlop, dfInter, egSlop, egInter;
							//�����_d,f�����߂�
							d = LineSplitPoint(m_aPos[0], m_centerPos, 1, CP_DIVIDE - 1);
							e = LineSplitPoint(m_aPos[0], m_centerPos, CP_DIVIDE - 1, 1);
							//����AO�̎������߂�
							aoSlop = LineSlope(m_aPos[0], m_centerPos);
							aoInter = LineIntercept(m_aPos[0], m_centerPos);
							//����AO�ƁA�����_d����_�Ƃ�������DF�����߂�
							dfSlop = VerticalLineSlope(aoSlop);
							dfInter = VerticalLineIntercept(d, aoSlop);
							//����AO�ƁA�����_e����_�Ƃ�������EG�����߂�
							egSlop = VerticalLineSlope(aoSlop);
							egInter = VerticalLineIntercept(e, aoSlop);
							//������Ԃɍ��킹�Ē����l�����߂�
							if (gamePhase == GAME_PHASE::PHASE_PULL){
								switch (m_nPullNum)
								{
								case 1:
									regula = 1.0f - (0.4f * ((float)m_nPullFrame / (float)PULL_FRAME));
									if (m_nFrameCnt)
										regula = 0.6f;
									break;
								case 2:
									regula = 1.0f - (0.3f * ((float)m_nPullFrame / (float)PULL_FRAME)) - 0.4f;
									if (m_nFrameCnt)
										regula = 0.3f;
									break;
								case 3:
									regula = 1.0f - (0.3f * ((float)m_nPullFrame / (float)PULL_FRAME)) - 0.7f;
									if (m_nFrameCnt)
										regula = 0.0f;
									break;
								default:
									regula = 1.0f;
									break;
								}
							}
							else{
								regula = 1.0f;
							}
							//����_F
							cp1.x = d.x - ((m_aPos[0].y - CP_DISTANCE) * regula);
							cp1.y = LineY(cp1.x, dfSlop, dfInter);
							//����_G
							cp2.x = e.x - ((m_aPos[0].y - CP_DISTANCE) * regula);
							cp2.y = LineY(cp2.x, egSlop, egInter);

							//********* ����AB�̐���_���v�Z *******
							//�����_d,f�����߂�
							d = LineSplitPoint(m_aPos[0], m_aPos[1], 1, CP_DIVIDE - 1);
							e = LineSplitPoint(m_aPos[0], m_aPos[1], CP_DIVIDE - 1, 1);
							//����AB�̎������߂�
							aoSlop = LineSlope(m_aPos[0], m_aPos[1]);
							aoInter = LineIntercept(m_aPos[0], m_aPos[1]);
							//����AB�ƁA�����_d����_�Ƃ�������DF�����߂�
							dfSlop = VerticalLineSlope(aoSlop);
							dfInter = VerticalLineIntercept(d, aoSlop);
							//����AB�ƁA�����_e����_�Ƃ�������EG�����߂�
							egSlop = VerticalLineSlope(aoSlop);
							egInter = VerticalLineIntercept(e, aoSlop);
							//����_F
							cp3.y = d.y + ((m_aPos[1].y - m_aPos[0].y) / 2.0f);
							cp3.x = LineX(cp3.y, dfSlop, dfInter);
							//����_G
							cp4.y = e.y + ((m_aPos[1].y - m_aPos[0].y) / 2.0f);
							cp4.x = LineY(cp4.y, egSlop, egInter);

						}

						//----- �s���ƂɌv�Z ----

						//***** ���X���C���̗��[�����߂� *****
						topXleft = BezierCurve((float)y / (float)NET_Y_NUM, m_aPos[0], cp1, cp2, m_centerPos);
						topXright = LineSplitPoint(m_aPos[1], m_centerPos, y, NET_Y_NUM - y);

						//***** ����X���C���̗��[�����߂� *****
						underXleft = BezierCurve(((float)y + 1.0f) / (float)NET_Y_NUM, m_aPos[0], cp1, cp2, m_centerPos);
						underXright = LineSplitPoint(m_aPos[1], m_centerPos, y + 1, NET_Y_NUM - (y + 1));

					}

					//---- ����v�Z���s�� -----

					//***** ����Y���C���̗��[�����߂� *****
					leftYtop = BezierCurve((float)x / (float)NET_X_NUM, m_aPos[0], cp3, cp4, m_aPos[1]);
					leftYunder = m_centerPos;

					//***** �E��Y���C���̗��[�����߂� *****
					rightYtop = BezierCurve(((float)x + 1.0f) / (float)NET_X_NUM, m_aPos[0], cp3, cp4, m_aPos[1]);
					rightYunder = m_centerPos;

					//***** �ŏI�|�W�V�������� *****
					workPos[0].x = LineSplitPoint(topXleft, topXright, x, NET_X_NUM - x).x;
					workPos[1].x = LineSplitPoint(topXleft, topXright, x + 1, NET_X_NUM - (x + 1)).x;
					workPos[2].x = LineSplitPoint(underXleft, underXright, x, NET_X_NUM - x).x;
					workPos[3].x = LineSplitPoint(underXleft, underXright, x + 1, NET_X_NUM - (x + 1)).x;

					workPos[0].y = LineSplitPoint(leftYtop, leftYunder, y, NET_Y_NUM - y).y;
					workPos[1].y = LineSplitPoint(rightYtop, rightYunder, y, NET_Y_NUM - y).y;
					workPos[2].y = LineSplitPoint(leftYtop, leftYunder, y + 1, NET_Y_NUM - (y + 1)).y;
					workPos[3].y = LineSplitPoint(rightYtop, rightYunder, y + 1, NET_Y_NUM - (y + 1)).y;
					break;

				case NET_PARTS_LEFT:

					//�Ԓ��肪�K�v�Ȃ��ꍇ�͏������s��Ȃ�
					if (m_centerPos == m_aPos[2] ||
						m_centerPos == m_aPos[1]){
						skip = true;
						break;
					}

					//�l�̒���
					if (x == 0){
						//�K�v�����v�Z
						if (y == 0){

							//****** ����CO�̐���_���v�Z *******
							//�ϐ��錾
							D3DXVECTOR2 d, e;
							float aoSlop, aoInter, dfSlop, dfInter, egSlop, egInter;
							//�����_d,f�����߂�
							d = LineSplitPoint(m_aPos[2], m_centerPos, 1, CP_DIVIDE - 1);
							e = LineSplitPoint(m_aPos[2], m_centerPos, CP_DIVIDE - 1, 1);
							//����CO�̎������߂�
							aoSlop = LineSlope(m_aPos[2], m_centerPos);
							aoInter = LineIntercept(m_aPos[2], m_centerPos);
							//����CO�ƁA�����_d����_�Ƃ�������DF�����߂�
							dfSlop = VerticalLineSlope(aoSlop);
							dfInter = VerticalLineIntercept(d, aoSlop);
							//����CO�ƁA�����_e����_�Ƃ�������EG�����߂�
							egSlop = VerticalLineSlope(aoSlop);
							egInter = VerticalLineIntercept(e, aoSlop);
							//������Ԃɍ��킹�Ē����l�����߂�
							if (gamePhase == GAME_PHASE::PHASE_PULL){
								switch (m_nPullNum)
								{
								case 1:
									regula = 1.0f - (0.4f * ((float)m_nPullFrame / (float)PULL_FRAME));
									if (m_nFrameCnt)
										regula = 0.6f;
									break;
								case 2:
									regula = 1.0f - (0.3f * ((float)m_nPullFrame / (float)PULL_FRAME)) - 0.4f;
									if (m_nFrameCnt)
										regula = 0.3f;
									break;
								case 3:
									regula = 1.0f - (0.3f * ((float)m_nPullFrame / (float)PULL_FRAME)) - 0.7f;
									if (m_nFrameCnt)
										regula = 0.0f;
									break;
								default:
									regula = 1.0f;
									break;
								}
							}
							else{
								regula = 1.0f;
							}
							//����_F
							cp1.x = d.x + ((m_aPos[2].y - CP_DISTANCE) * regula);
							cp1.y = LineY(cp1.x, dfSlop, dfInter);
							//����_G
							cp2.x = e.x + ((m_aPos[2].y - CP_DISTANCE) * regula);
							cp2.y = LineY(cp2.x, egSlop, egInter);

							//********* ����BC�̐���_���v�Z *******
							//�����_d,f�����߂�
							d = LineSplitPoint(m_aPos[1], m_aPos[2], 1, CP_DIVIDE - 1);
							e = LineSplitPoint(m_aPos[1], m_aPos[2], CP_DIVIDE - 1, 1);
							//����AB�̎������߂�
							aoSlop = LineSlope(m_aPos[1], m_aPos[2]);
							aoInter = LineIntercept(m_aPos[1], m_aPos[2]);
							//����AB�ƁA�����_d����_�Ƃ�������DF�����߂�
							dfSlop = VerticalLineSlope(aoSlop);
							dfInter = VerticalLineIntercept(d, aoSlop);
							//����AB�ƁA�����_e����_�Ƃ�������EG�����߂�
							egSlop = VerticalLineSlope(aoSlop);
							egInter = VerticalLineIntercept(e, aoSlop);
							//����_F
							cp3.y = d.y + ((m_aPos[1].y - m_aPos[2].y) / 2.0f);
							cp3.x = LineY(cp3.y, dfSlop, dfInter);
							//����_G
							cp4.y = e.y + ((m_aPos[1].y - m_aPos[2].y) / 2.0f);
							cp4.x = LineY(cp4.y, egSlop, egInter);
						}

						//----- �s���ƂɌv�Z ----

						//***** ���X���C���̗��[�����߂� *****
						topXleft = LineSplitPoint(m_aPos[1], m_centerPos, y, NET_Y_NUM - y);
						topXright = BezierCurve((float)y / (float)NET_Y_NUM, m_aPos[2], cp1, cp2, m_centerPos);

						//***** ����X���C���̗��[�����߂� *****
						underXleft = LineSplitPoint(m_aPos[1], m_centerPos, y + 1, NET_Y_NUM - (y + 1));
						underXright = BezierCurve(((float)y + 1.0f) / (float)NET_Y_NUM, m_aPos[2], cp1, cp2, m_centerPos);
					}

					//---- ����v�Z���s�� -----

					//***** ����Y���C���̗��[�����߂� *****
					leftYtop = BezierCurve((float)x / (float)NET_X_NUM, m_aPos[1], cp3, cp4, m_aPos[2]);
					leftYunder = m_centerPos;

					//***** �E��Y���C���̗��[�����߂� *****
					rightYtop = BezierCurve(((float)x + 1.0f) / (float)NET_X_NUM, m_aPos[1], cp3, cp4, m_aPos[2]);
					rightYunder = m_centerPos;

					//***** �ŏI�|�W�V�������� *****
					workPos[0].x = LineSplitPoint(topXleft, topXright, x, NET_X_NUM - x).x;
					workPos[1].x = LineSplitPoint(topXleft, topXright, x + 1, NET_X_NUM - (x + 1)).x;
					workPos[2].x = LineSplitPoint(underXleft, underXright, x, NET_X_NUM - x).x;
					workPos[3].x = LineSplitPoint(underXleft, underXright, x + 1, NET_X_NUM - (x + 1)).x;

					workPos[0].y = LineSplitPoint(leftYtop, leftYunder, y, NET_Y_NUM - y).y;
					workPos[1].y = LineSplitPoint(rightYtop, rightYunder, y, NET_Y_NUM - y).y;
					workPos[2].y = LineSplitPoint(leftYtop, leftYunder, y + 1, NET_Y_NUM - (y + 1)).y;
					workPos[3].y = LineSplitPoint(rightYtop, rightYunder, y + 1, NET_Y_NUM - (y + 1)).y;

					break;

				} //switch 

				//���݂̃|�W�V��������
				if (!skip)
					m_aNet[z][y][x].SetPosFree(workPos[0], workPos[1], workPos[2], workPos[3]);
			}
		}
	} //�Ȑ��I��

}


//====================================================
//
// �Ԃ̃e�N�X�`���J���[�̍X�V
//
//====================================================
void cNet::NetColorUpdate(){

	float hue;

	m_fNetHue += NET_TEX_INCREMENT_HUE;
	if (m_fNetHue > NET_TEX_MAX_HUE){
		m_fNetHue = NET_TEX_MIN_HUE;
	}

	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){

				m_aNet[z][y][x].SetHSVColorFlag(true);

				hue = m_fNetHue + (NET_TEX_INCREMENT_HUE * y);
				while (hue > NET_TEX_MAX_HUE){
					hue -= NET_TEX_MAX_HUE;
				}

				m_aNet[z][y][x].SetHSVColorOne(hue, NET_TEX_SATURATION, NET_TEX_VALUE, 0);
				m_aNet[z][y][x].SetHSVColorOne(hue, NET_TEX_SATURATION, NET_TEX_VALUE, 1);
				//m_aNet[z][y][x].SetVtxColor(D3DXCOLOR(100.0f, 00.0f, 100.0f, 155.0f));

				hue += NET_TEX_INCREMENT_HUE;
				while (hue > NET_TEX_MAX_HUE){
					hue -= NET_TEX_MAX_HUE;
				}

				m_aNet[z][y][x].SetHSVColorOne(hue, NET_TEX_SATURATION, NET_TEX_VALUE, 2);
				m_aNet[z][y][x].SetHSVColorOne(hue, NET_TEX_SATURATION, NET_TEX_VALUE, 3);

			}
		}
	}

}


//====================================================
//
// ���͎擾
//
//====================================================
void cNet::Input(){

	//---------------------------
	// ���o�[����
	//---------------------------
	if (GetInputArrowPress(DIK_W, 0, PAD_ARROW_UP) && GetInputArrowPress(DIK_A, 0, PAD_ARROW_LEFT))
		m_nLeverDirection = 7;
	else if (GetInputArrowPress(DIK_W, 0, PAD_ARROW_UP) && GetInputArrowPress(DIK_D, 0, PAD_ARROW_RIGHT))
		m_nLeverDirection = 9;
	else if (GetInputArrowPress(DIK_S, 0, PAD_ARROW_DOWN) && GetInputArrowPress(DIK_D, 0, PAD_ARROW_RIGHT))
		m_nLeverDirection = 3;
	else if (GetInputArrowPress(DIK_S, 0, PAD_ARROW_DOWN) && GetInputArrowPress(DIK_A, 0, PAD_ARROW_LEFT))
		m_nLeverDirection = 1;
	else if (GetInputArrowPress(DIK_W, 0, PAD_ARROW_UP))
		m_nLeverDirection = 8;
	else if (GetInputArrowPress(DIK_A, 0, PAD_ARROW_LEFT))
		m_nLeverDirection = 4;
	else if (GetInputArrowPress(DIK_D, 0, PAD_ARROW_RIGHT))
		m_nLeverDirection = 6;
	else if (GetInputArrowPress(DIK_S, 0, PAD_ARROW_DOWN))
		m_nLeverDirection = 2;
	else
		m_nLeverDirection = 5;

	//----------------------------
	// �{�^������
	//----------------------------
	if (GetInputButtonPress(DIK_N, 0, BOTTON_NET_LEFT))
		m_bPressButton[0] = true;
	else
		m_bPressButton[0] = false;
	if (GetInputButtonPress(DIK_U, 0, BOTTON_NET_RIGHT))
		m_bPressButton[1] = true;
	else
		m_bPressButton[1] = false;
	if (GetInputButtonPress(DIK_8, 0, BOTTON_NET_CENTER))
		m_bPressButton[2] = true;
	else
		m_bPressButton[2] = false;

	//---- �S�{�^���v�b�V����Ԃ��ǂ��� ----
	for (int i = 0; i < 3; i++){
		if (!m_bPressButton[i])
			break;
		if (i == 2){
			m_bAllPress = true;
			return;
		}
	}
	m_bAllPress = false;

}

//====================================================
//
// �w�\���x���̍X�V
//
//====================================================
void cNet::PostPhaseUpdate(){

	//----- �S�{�^���v���X���ȊO���^�[�� -----
	if (!m_bAllPress){
		m_bDrawArrow = false;
		m_postPhase = POST_NON;
		return;
	}

	switch (m_postPhase)
	{
		//------ �������ĂȂ��Ƃ� -----
	case POST_NON:
		//-----	���o�[�������Ċp�x���� -----
		if (m_nLeverDirection <= 3){

			//���̕\��
			m_bDrawArrow = true;

			//�p�x�̐ݒ�
			m_nPostAngle = m_nLeverDirection;

			//��������ݒ�
			m_postPhase = POST_PULL;

		}

		//----- ���p�x������ -----
		if (m_nPostAngle == 1){
			m_arrow.SetRad(D3DX_PI + (D3DX_PI / 4.0f));
		}
		else if (m_nPostAngle == 3){
			m_arrow.SetRad(D3DX_PI - (D3DX_PI / 4.0f));
		}
		else{
			m_arrow.SetRad(D3DX_PI);
		}
		break;
		//------- ������ ------
	case POST_PULL:
		//-----	���o�[�������Ċp�x���� -----
		if (m_nLeverDirection <= 3){

			//���̕\��
			m_bDrawArrow = true;

			//�p�x�̐ݒ�
			m_nPostAngle = m_nLeverDirection;
		}

		//----- ���p�x������ -----
		if (m_nPostAngle == 1){
			m_arrow.SetRad(D3DX_PI + (D3DX_PI / 4.0f));
		}
		else if (m_nPostAngle == 3){
			m_arrow.SetRad(D3DX_PI - (D3DX_PI / 4.0f));
		}
		else{
			m_arrow.SetRad(D3DX_PI);
		}

		//----- ���o�[�j���[�g������Ԃ̂Ƃ��Ɍo�߃t���[�����v��
		if (m_nLeverDirection < 7 && m_nLeverDirection > 3){
			m_nFrameCnt++;
			m_postPhase = POST_N;
		}

		break;
		//----- �j���[�g������� -----
	case POST_N:
		//----- ���o�[�j���[�g������Ԃ̂Ƃ��Ɍo�߃t���[�����v�� -----
		if (m_nLeverDirection < 7 && m_nLeverDirection > 3){
			m_nFrameCnt++;
		}

		//----- ���o�[�O�|���Ńt�F�C�Y�ڍs -----
		if (m_nLeverDirection > 6){
			m_postPhase = POST_PUSH;
		}

		break;
		//------- �O�|����� -------
	case POST_PUSH:

		//----- �X�s�[�h���v�Z -----
		m_fThrowSpeed = MAX_SPEED - (DECRE_SPEED * m_nFrameCnt);
		if (m_fThrowSpeed < 0.0f)
			m_fThrowSpeed = 0.0f;

		//----- ���~�̏����v�Z ------
		m_fMaxHalfCircle = m_fThrowSpeed / 10.0f;
		if (m_fMaxHalfCircle > 1.0f)
			m_fMaxHalfCircle = 1.0f;
		m_fDirectHalfCircle = 1.0f;
		m_fSpeed = m_fThrowSpeed * 0.001f;
		m_fHalfCircleSize = 0.0f;

		//----- �\����ԏI�� -----
		gamePhase = PHASE_SHOUT;
		PlaySound(SOUND_LABEL::SOUND_LABEL_SE_NET_GAGE);
		m_bDrawArrow = false;
		m_nFrameCnt = 0;		//�t���[���J�E���g�̏�����
		for (int i = 0; i < 3; i++){
			m_bThrow[i] = false;
			m_bRipple[i] = false;
		}
		break;
	}

}


//====================================================
//
// �w������x���̍X�V
//
//====================================================
void cNet::ShoutPhaseUpdate(){

	bool xFin[3];
	bool yFin[3];

	for (int i = 0; i < 3; i++){
		xFin[i] = false;
		yFin[i] = false;
	}

	//------ �{�^�����������`�F�b�N ------
	for (int i = 0; i < 3; i++){
		if (!m_bPressButton[i] && !m_bThrow[i]){
			//------- �������u�ԂɖړI�ʒu���� ----------
			if (i == 1)
				m_ThreePurposePos[i].x = m_centerPos.x;
			else if (i == 0)
				m_ThreePurposePos[i].x = (m_centerPos.x) - ((SCREEN_WIDTH * m_fHalfCircleSize) / 2.0f);
			else
				m_ThreePurposePos[i].x = (m_centerPos.x) + ((SCREEN_WIDTH * m_fHalfCircleSize) / 2.0f);
			m_ThreePurposePos[i].y = SCREEN_HEIGHT - (SCREEN_HEIGHT * m_fHalfCircleSize);
			m_bThrow[i] = true;

			//---------- �΂ߓ����␳ ------------
			if (m_nPostAngle == ANG_LEFT)
				m_ThreePurposePos[i].x += ANG_NUM;
			else if (m_nPostAngle == ANG_RIGHT)
				m_ThreePurposePos[i].x -= ANG_NUM;

			//------- Y�̕␳�l ------
			if (m_nPostAngle == ANG_STRAIGHT){
				if (i != 1){
					m_ThreePurposePos[i].y += ANG_Y_FIRST;
				}
			}
			else if (m_nPostAngle == ANG_RIGHT){
				if (i == 0){
					m_ThreePurposePos[i].y += ANG_Y_SECOND;
				}
				else if (i == 1){
					m_ThreePurposePos[i].y += ANG_Y_FIRST;
				}
			}
			else if (m_nPostAngle == ANG_LEFT){
				if (i == 2){
					m_ThreePurposePos[i].y += ANG_Y_SECOND;
				}
				else if (i == 1){
					m_ThreePurposePos[i].y += ANG_Y_FIRST;
				}
			}

			//------ SE�̍Đ� ------
			PlaySound(SOUND_LABEL::SOUND_LABEL_SE_NET_SHOOT);

			//--- �p�[�e�B�N���̐��� ---
			SetPirticle(D3DXVECTOR2(m_centerPos.x, m_centerPos.y - 100.0f));
		}
	}

	//----- �e�l���_�̏��� ------
	for (int i = 0; i < 3; i++){

		if (m_bThrow[i]){
			//----- �{�^�������[�X�Œ��_�Ƃ΂����I -----
			float fSp;	//�X�s�[�h
			//Y����
			fSp = (m_aPos[i].y - m_ThreePurposePos[i].y) / SPEED_HALFCIRCLE;
			if (fSp < MIN_SPEED)
				fSp = MIN_SPEED;
			m_aPos[i].y -= fSp;
			if (m_aPos[i].y < m_ThreePurposePos[i].y){
				m_aPos[i].y = m_ThreePurposePos[i].y;
				yFin[i] = true;
			}
			//X����
			if (m_ThreePurposePos[i].x < m_aPos[i].x){
				fSp = (m_aPos[i].x - m_ThreePurposePos[i].x) / SPEED_HALFCIRCLE;
				if (fSp < MIN_SPEED)
					fSp = MIN_SPEED;
				m_aPos[i].x -= fSp;
				if (m_aPos[i].x < m_ThreePurposePos[i].x){
					m_aPos[i].x = m_ThreePurposePos[i].x;
					xFin[i] = true;
				}
			}
			else{
				fSp = (m_ThreePurposePos[i].x - m_aPos[i].x) / SPEED_HALFCIRCLE;
				if (fSp < MIN_SPEED)
					fSp = MIN_SPEED;
				m_aPos[i].x += fSp;
				if (m_aPos[i].x > m_ThreePurposePos[i].x){
					m_aPos[i].x = m_ThreePurposePos[i].x;
					xFin[i] = true;
				}
			}
		}

	}

	//------ ���~�̊g��k�� ----------
	m_fHalfCircleSize += (m_fSpeed * m_fDirectHalfCircle);
	if (m_fHalfCircleSize > m_fMaxHalfCircle)
		m_fDirectHalfCircle = -1.0f;
	if (m_fHalfCircleSize <= 0.0f)
		m_fDirectHalfCircle = 0.0f;
	m_halfCircle.SetScale(D3DXVECTOR2(m_fHalfCircleSize, m_fHalfCircleSize));
	m_halfCircle.SetPosY(SCREEN_HEIGHT - m_halfCircle.GetSizeY() * m_halfCircle.GetScaleY() * 0.5f);

	//---- �����I���ň����グ -----
	for (int i = 0; i < 3; i++){
		if (!xFin[i] || !yFin[i])
			break;
		if (!m_bRipple[i]){ //�g�䐶��
			SetRipple(m_aPos[i]);
			m_bRipple[i] = true;
		}
		if (i == 2){
			m_fHalfCircleSize = 0.0f;
			StopSound(SOUND_LABEL::SOUND_LABEL_SE_NET_GAGE);
		}
	}

	//------ �����������Đ��b����������グ ------
	if (m_fHalfCircleSize <= 0.0f){

		//���������Ă��Ȃ��ꍇ�̓Q�[�W��������x�g��
		if (!m_bThrow[0] || !m_bThrow[1] || !m_bThrow[2]){
			m_fDirectHalfCircle = 1.0f;
		}
		else{
			m_nFrameCnt++;
			if (m_nFrameCnt >= INTERVAL_THOROW_PULL){
				m_nFrameCnt = 0;	//������
				m_bPurpose = false;
				gamePhase = PHASE_PULL;
				StopSound(SOUND_LABEL::SOUND_LABEL_SE_NET_GAGE);
			}
		}
	}

}


//====================================================
//
// �w�����x���̍X�V
//
//====================================================
void cNet::PullPhaseUpdate(){

	//------ �҂����Ԃ�����ꍇ�͎��s���Ȃ� --------
	if (m_nFrameCnt){
		m_nFrameCnt--;
		if (m_nFrameCnt)
			return;
	}

	//------ �ړI�ʒu���Z�b�g --------
	if (!m_bPurpose){

		//�����グ�񐔈��ȏ�ŏI��
		if (m_nPullNum >= PULL_NUM){
			//�V�[���ړ��H
			m_nPullNum = -1;
			m_bPurpose = false;
			gamePhase = PHASE_POST;
			m_aPos[0] = m_aPos[1] = m_aPos[2] = m_centerPos;
			m_postPhase = POST_NON;
		}

		//����ݒ�
		if (!m_nPullNum){
			for (int i = 0; i < 3; i++){
				if (m_aPos[i].x < m_centerPos.x)
					m_oncePullPos[i].x = (m_centerPos.x - m_aPos[i].x) / PULL_NUM;
				else
					m_oncePullPos[i].x = -(m_aPos[i].x - m_centerPos.x) / PULL_NUM;
				m_oncePullPos[i].y = (m_centerPos.y - m_aPos[i].y) / PULL_NUM;
				m_pullSpeed[i].x = m_oncePullPos[i].x / PULL_FRAME;
				m_pullSpeed[i].y = m_oncePullPos[i].y / PULL_FRAME;
			}
		}

		//�����グ�񐔂����Z
		m_nPullNum++;
		m_bPurpose = true;

		//�ړI�ʒu��ݒ�
		for (int i = 0; i < 3; i++){
			m_purposePos[i].x = m_aPos[i].x + m_oncePullPos[i].x;
			m_purposePos[i].y = m_aPos[i].y + m_oncePullPos[i].y;
		}

		//SE�̍Đ�
		if (m_nPullNum)
			PlaySound(SOUND_LABEL::SOUND_LABEL_SE_NET_PULL);

	}

	//------ �ړI�ʒu�ɋ߂Â��� --------
	for (int i = 0; i < 3; i++){
		m_aPos[i].x += m_pullSpeed[i].x;
		m_aPos[i].y += m_pullSpeed[i].y;
	}
	m_nPullFrame++;

	//------ �ړI�ʒu�ɒ������玟�� --------
	if (m_nPullFrame >= PULL_FRAME){
		m_nFrameCnt = PULL_WAIT;
		m_nPullFrame = 0;
		m_bPurpose = false;
	}

}



//====================================================
//
//  �Ԃ̓����蔻����擾
//
//====================================================
cCollider* cNet::GetCollider(){
	return m_aCollider;
}

//===========================================
//
// �g�䐶��
//
//===========================================
void cNet::SetRipple(D3DXVECTOR2 pos){

	for (int i = 0; i < MAX_RIPPLE; i++){

		if (m_aRipple[i])
			continue;


		m_aRipple[i] = new cRipple(pos);

		return;

	}

}

//===========================================
//
// �p�[�e�B�N������
//
//===========================================
void cNet::SetPirticle(D3DXVECTOR2 pos){

	for (int i = 0; i < MAX_PIRTICLE_NUM; i++){

		if (m_aPirticle[i])
			continue;

		m_aPirticle[i] = new cNetPirticleManage(pos);

		return;
	}
}


#endif