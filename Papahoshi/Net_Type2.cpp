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
/*
�E���݂̂͂肩���̒����@12/15  �N���A�I
�E�܂�������΂��Ďw�𗣂����璸�_�L����@12/18

����邱��
���݂̃A���_�[�̃f�o�b�N
�����炭y�֌W�ɖ�肠��
*/


//-------------------------------------
// �C���N���[�h��
//-------------------------------------
#include "Net_Type2.h"
#include "Texture.h"
#include "SceneGame.h"
#include "Input.h"
#include "debugproc.h"

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
#define MAX_SPEED	(12.5f)
#define DECRE_SPEED (0.1f)	//�P�t���[�����Ƃɏ������炷��
#define DECRE_THROW_SPEED	(0.1f)	//�܂���
//�҂�����
#define INTERVAL_THOROW_PULL	(90)	//������������グ�܂ł̑҂�����
//�����Ƃ�
#define PULL_NUM	(3)		//�Y�b�Y�b�ĂȂ��
#define PULL_FRAME	(50)	//�����t���[��
#define PULL_WAIT	(30)	//�҂����ԁH
//���~
#define MIN_SPEED	(1.0f)	//�Œ�X�s�[�h
#define SPEED_HALFCIRCLE	(10)	//10/1�i��

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
	m_centerPos = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT + 30.0f);

	//---- �l���_�̏����� ----
	for (int i = 0; i < 3; i++)
		m_aPos[i] = m_centerPos;

	//---- �X�v���C�g�̏����� ----

	//����
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
				m_aNet[z][y][x].SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_NET));	// �e�N�X�`���̃Z�b�g
			}
		}
	}

	//�����E�l���_
	for (int i = 0; i < 3; i++){
		m_aFourUki[i].SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_UKI));
		m_aFourUki[i].SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));
	}

	//�����E�Z���^�[
	m_center.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_UKI));
	m_center.SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));

	//���
	m_arrow.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_ARROW));
	m_arrow.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 80.0f));
	m_arrow.SetSize(D3DXVECTOR2(ARROW_SIZE_X, ARROW_SIZE_Y));
	m_arrow.SetRad(D3DX_PI);

	//���~
	m_halfCircle.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_HALFCIRCLE));
	m_halfCircle.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT));
	m_halfCircle.SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	m_halfCircle.SetScale(D3DXVECTOR2(0.0f, 0.0f));

	//--------- �����蔻��̏����� --------------
	m_aCollider[0].SetType(cCollider::CollisionType::TRIANGLE);
	m_aCollider[1].SetType(cCollider::CollisionType::TRIANGLE);
	m_aCollider[0].SetTriangleCollider(m_aPos[1], m_centerPos, m_aPos[0]);
	m_aCollider[1].SetTriangleCollider(m_aPos[2], m_centerPos, m_aPos[1]);

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

	//����
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
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

	D3DXVECTOR2 workPos[4];
	float tlx, ulx, trx, urx, tdisX, udisX, trY, tly, ury, uly, tdisY, udisY, yAng, xAng, LtoCdisX, CtoRdisX;


	//---- �E�L�̈ʒu��ݒ� ----
	for (int i = 0; i < 3; i++){
		m_aFourUki[i].SetPos(m_aPos[i]);
	}
	m_center.SetPos(m_centerPos);

	//** TOP�ȊO�����f **//
	//----- ���݂̃|�W�V������ݒ�(�Ƃ肠����������) -----
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){

				switch (z)
				{
				case NET_PARTS_RIGHT://RIGHT
					//�l�̒���
					if (x == 0){
						//�K�v�����v�Z
						if (y == 0){
							tlx = ulx = m_aPos[0].x;
							trx = urx = m_aPos[1].x;
							tdisX = udisX = trx - tlx;
							tly = uly = m_aPos[0].y;
							trY = ury = m_aPos[1].y;
							trY >= tly ? tdisY = udisY = trY - tly : tdisY = udisY = tly - trY;
							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.x - m_aPos[0].x;
							CtoRdisX = m_aPos[1].x - m_centerPos.x;
							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.x - m_aPos[0].x;
							CtoRdisX = m_aPos[1].x - m_centerPos.x;
						}

						//X�̒���
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						urx = m_aPos[1].x - ((((CtoRdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						ulx = m_aPos[0].x + ((((LtoCdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						udisX = urx - ulx;

						//Y�̒���
						tly = uly;
						trY = ury;
						tdisY = udisY;
						uly = m_aPos[0].y + ((((m_centerPos.y - m_aPos[0].y) / NET_Y_NUM) * (y + 1)));
						ury = m_aPos[1].y + ((((m_centerPos.y - m_aPos[1].y) / NET_Y_NUM) * (y + 1)));
						ury >= uly ? udisY = ury - uly : udisY = uly - ury;
					}

					//���W�̐ݒ�
					workPos[0].x = tlx + ((tdisX / NET_X_NUM) * x);
					workPos[1].x = tlx + ((tdisX / NET_X_NUM) * (x + 1));
					workPos[2].x = ulx + ((udisX / NET_X_NUM) * x);
					workPos[3].x = ulx + ((udisX / NET_X_NUM) * (x + 1));

					if (yAng){	//�݂��̂ق������ɂ���
						workPos[0].y = tly + (tdisY / NET_X_NUM) * (x);
						workPos[1].y = tly + (tdisY / NET_X_NUM) * (x + 1);
						workPos[2].y = uly + (udisY / NET_X_NUM) * (x);
						workPos[3].y = uly + (udisY / NET_X_NUM) * (x + 1);
					}
					else{
						workPos[0].y = tly - (tdisY / NET_X_NUM) * (x);
						workPos[1].y = tly - (tdisY / NET_X_NUM) * (x + 1);
						workPos[2].y = uly - (udisY / NET_X_NUM) * (x);
						workPos[3].y = uly - (udisY / NET_X_NUM) * (x + 1);
					}
					break;
				case NET_PARTS_LEFT://LEFT
					//�l�̒���
					if (x == 0){
						//�K�v�����v�Z
						if (y == 0){
							tlx = ulx = m_aPos[1].x;
							trx = urx = m_aPos[2].x;
							tdisX = udisX = trx - tlx;
							tly = uly = m_aPos[1].y;
							trY = ury = m_aPos[2].y;
							trY >= tly ? tdisY = udisY = trY - tly : tdisY = udisY = tly - trY;
							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.x - m_aPos[1].x;
							CtoRdisX = m_aPos[2].x - m_centerPos.x;
							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.x - m_aPos[1].x;
							CtoRdisX = m_aPos[2].x - m_centerPos.x;
						}

						//X�̒���
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						urx = m_aPos[2].x - ((((CtoRdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						ulx = m_aPos[1].x + ((((LtoCdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						udisX = urx - ulx;

						//Y�̒���
						tly = uly;
						trY = ury;
						tdisY = udisY;
						uly = m_aPos[1].y + ((((m_centerPos.y - m_aPos[2].y) / NET_Y_NUM) * (y + 1)));
						ury = m_aPos[2].y + ((((m_centerPos.y - m_aPos[1].y) / NET_Y_NUM) * (y + 1)));
						ury >= uly ? udisY = ury - uly : udisY = uly - ury;
					}

					//���W�̐ݒ�
					workPos[0].x = tlx + ((tdisX / NET_X_NUM) * x);
					workPos[1].x = tlx + ((tdisX / NET_X_NUM) * (x + 1));
					workPos[2].x = ulx + ((udisX / NET_X_NUM) * x);
					workPos[3].x = ulx + ((udisX / NET_X_NUM) * (x + 1));

					if (yAng){	//�݂��̂ق������ɂ���
						workPos[0].y = tly + (tdisY / NET_X_NUM) * (x);
						workPos[1].y = tly + (tdisY / NET_X_NUM) * (x + 1);
						workPos[2].y = uly + (udisY / NET_X_NUM) * (x);
						workPos[3].y = uly + (udisY / NET_X_NUM) * (x + 1);
					}
					else{
						workPos[0].y = tly - (tdisY / NET_X_NUM) * (x);
						workPos[1].y = tly - (tdisY / NET_X_NUM) * (x + 1);
						workPos[2].y = uly - (udisY / NET_X_NUM) * (x);
						workPos[3].y = uly - (udisY / NET_X_NUM) * (x + 1);
					}
					break;
				}

				//���݂̃|�W�V��������
				m_aNet[z][y][x].SetPosFree(workPos[0], workPos[1], workPos[2], workPos[3]);
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
		if (i == 2)
			m_bAllPress = true;
	}

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
		m_bDrawArrow = false;
		m_nFrameCnt = 0;		//�t���[���J�E���g�̏�����
		for (int i = 0; i < 3; i++)
			m_bThrow[i] = false;
		break;
	}

}


//====================================================
//
// �w������x���̍X�V
//
//====================================================
void cNet::ShoutPhaseUpdate(){

	//------ �{�^�����������`�F�b�N ------
	for (int i = 0; i < 3; i++){
		if (!m_bPressButton[i] && !m_bThrow[i]){
			//------- �������u�ԂɖړI�ʒu���� ----------
			if (i == 1)
				m_ThreePurposePos[i].x = SCREEN_WIDTH / 2.0f;
			else if (i == 0)
				m_ThreePurposePos[i].x = (SCREEN_WIDTH / 2.0f) - ((SCREEN_WIDTH * m_fHalfCircleSize) / 2.0f);
			else
				m_ThreePurposePos[i].x = (SCREEN_WIDTH / 2.0f) + ((SCREEN_WIDTH * m_fHalfCircleSize) / 2.0f);
			m_ThreePurposePos[i].y = SCREEN_HEIGHT - (SCREEN_HEIGHT * m_fHalfCircleSize);
			m_bThrow[i] = true;
			
			//****** �f�o�b�N *******
			//m_aPos[i] = m_ThreePurposePos[i];
			//gamePhase = GAME_PHASE::PHASE_MAX;
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
			if (m_aPos[i].y < m_ThreePurposePos[i].y)
				m_aPos[i].y = m_ThreePurposePos[i].y;
			//X����
			if (m_ThreePurposePos[i].x < m_aPos[i].x){
				fSp = (m_aPos[i].x - m_ThreePurposePos[i].x) / SPEED_HALFCIRCLE;
				if (fSp < MIN_SPEED)
					fSp = MIN_SPEED;
				m_aPos[i].x -= fSp;
				if (m_aPos[i].x < m_ThreePurposePos[i].x)
					m_aPos[i].x = m_ThreePurposePos[i].x;
			}
			else{
				fSp = (m_ThreePurposePos[i].x - m_aPos[i].x) / SPEED_HALFCIRCLE;
				if (fSp < MIN_SPEED)
					fSp = MIN_SPEED;
				m_aPos[i].x += fSp;
				if (m_aPos[i].x > m_ThreePurposePos[i].x)
					m_aPos[i].x = m_ThreePurposePos[i].x;
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
	m_halfCircle.SetPosY(SCREEN_HEIGHT -  m_halfCircle.GetSizeY() * m_halfCircle.GetScaleY() * 0.5f);


	//------ �����������Đ��b����������グ ------
	if (m_fHalfCircleSize <= 0.0f){
		m_nFrameCnt++;
		if (m_nFrameCnt >= INTERVAL_THOROW_PULL){
			m_nFrameCnt = 0;	//������
			m_bPurpose = false;
			gamePhase = PHASE_PULL;
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
		return;
	}

	//------ �ړI�ʒu���Z�b�g --------
	if (!m_bPurpose){

		//�����グ�񐔈��ȏ�ŏI��
		if (m_nPullNum >= PULL_NUM){
			//�V�[���ړ��H
			gamePhase = PHASE_MAX;
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

#endif