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
#include "Net.h"
#include "Texture.h"
#include "SceneGame.h"
#include "Input.h"

//-------------------------------------
// �萔�E�}�N����`
//-------------------------------------
//�g�p�{�^��
#define BOTTON_NET_UPLEFT		(AC_CON_BUTTON_A)
#define BOTTON_NET_UPRIGHT		(AC_CON_BUTTON_B)
#define BOTTON_NET_DOWNLEFT		(AC_CON_BUTTON_E)
#define BOTTON_NET_DOWNRIGHT	(AC_CON_BUTTON_F)
//�e�N�X�`���T�C�Y
#define UKI_SIZE (20.0f)	//�����̃T�C�Y
#define ARROW_SIZE_X (300.0f)	//���̃T�C�Y
#define ARROW_SIZE_Y (120.0f)
//�X�s�[�h
#define MAX_SPEED	(10.0f)
#define DECRE_SPEED (0.1f)	//�P�t���[�����Ƃɏ������炷��
#define DECRE_THROW_SPEED	(0.1f)	//�܂���

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
	for (int i = 0; i < 4; i++)
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
	for (int i = 0; i < 4; i++){
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
	for (int i = 0; i < 4; i++){
		m_aFourUki[i].Draw();
	}

	//���S�_
	m_center.Draw();

	//���(�\����Ԃ̎�)
	if (m_bDrawArrow)
		m_arrow.Draw();

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
	for (int i = 0; i < 4; i++){
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
				case NET_PARTS_TOP://TOP
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
				case NET_PARTS_UNDER://UNDER
					//�l�̒���
					if (x == 0){
						//�K�v�����v�Z
						if (y == 0){
							tlx = ulx = m_aPos[2].x;
							trx = urx = m_aPos[3].x;
							tdisX = udisX = trx - tlx;
							tly = uly = m_aPos[2].y;
							trY = ury = m_aPos[3].y;
							trY >= tly ? tdisY = udisY = trY - tly : tdisY = udisY = tly - trY;
							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.x - m_aPos[2].x;
							CtoRdisX = m_aPos[3].x - m_centerPos.x;

							trY >= tly ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_aPos[2].x - m_centerPos.x;
							CtoRdisX = m_centerPos.x - m_aPos[3].x;
						}

						//X�̒���
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						urx = m_aPos[3].x + ((((CtoRdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						ulx = m_aPos[2].x - ((((LtoCdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						udisX = urx - ulx;

						//Y�̒���
						tly = uly;
						trY = ury;
						tdisY = udisY;
						uly = m_aPos[2].y + ((((m_centerPos.y - m_aPos[2].y) / NET_Y_NUM) * (y + 1)));
						ury = m_aPos[3].y + ((((m_centerPos.y - m_aPos[3].y) / NET_Y_NUM) * (y + 1)));
						ury >= uly ? udisY = ury - uly : udisY = uly - ury;
					}

					//���W�̐ݒ�
					workPos[2].x = tlx + ((tdisX / NET_X_NUM) * x);
					workPos[3].x = tlx + ((tdisX / NET_X_NUM) * (x + 1));
					workPos[0].x = ulx + ((udisX / NET_X_NUM) * x);
					workPos[1].x = ulx + ((udisX / NET_X_NUM) * (x + 1));

					if (yAng){	//�݂��̂ق������ɂ���
						workPos[2].y = tly + (tdisY / NET_X_NUM) * (x);
						workPos[3].y = tly + (tdisY / NET_X_NUM) * (x + 1);
						workPos[0].y = uly + (udisY / NET_X_NUM) * (x);
						workPos[1].y = uly + (udisY / NET_X_NUM) * (x + 1);
					}
					else{
						workPos[2].y = tly - (tdisY / NET_X_NUM) * (x);
						workPos[3].y = tly - (tdisY / NET_X_NUM) * (x + 1);
						workPos[0].y = uly - (udisY / NET_X_NUM) * (x);
						workPos[1].y = uly - (udisY / NET_X_NUM) * (x + 1);
					}
					break;
				case NET_PARTS_RIGHT://RIGHT
					//�l�̒���
					if (x == 0){
						//�K�v�����v�Z
						if (y == 0){
							tlx = ulx = m_aPos[1].x;
							trx = urx = m_aPos[3].x;
							trx >= tlx ? tdisX = udisX = trx - tlx : tdisX = udisX = tlx - trx;
							tly = uly = m_aPos[1].y;
							trY = ury = m_aPos[3].y;
							tdisY = udisY = trY - tly;
							trx >= tlx ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.y - m_aPos[1].y;
							CtoRdisX = m_aPos[3].y - m_centerPos.y;
						}

						//Y�̒���
						tly = uly;
						trY = ury;
						tdisY = udisY;
						ury = m_aPos[3].y - ((((CtoRdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						uly = m_aPos[1].y + ((((LtoCdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						udisY = ury - uly;

						//X�̒���
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						ulx = m_aPos[1].x + ((((m_centerPos.x - m_aPos[1].x) / NET_Y_NUM) * (y + 1)));
						urx = m_aPos[3].x + ((((m_centerPos.x - m_aPos[3].x) / NET_Y_NUM) * (y + 1)));
						urx >= ulx ? udisX = urx - ulx : udisX = ulx - urx;
					}

					//���W�̐ݒ�
					workPos[1].y = tly + (tdisY / 6) * (x);
					workPos[3].y = tly + (tdisY / 6) * (x + 1);
					workPos[0].y = uly + (udisY / 6) * (x);
					workPos[2].y = uly + (udisY / 6) * (x + 1);

					if (yAng){	//�݂��̂ق������ɂ���
						workPos[1].x = tlx + (tdisX / 6) * (x);
						workPos[3].x = tlx + (tdisX / 6) * (x + 1);
						workPos[0].x = ulx + (udisX / 6) * (x);
						workPos[2].x = ulx + (udisX / 6) * (x + 1);
					}
					else{
						workPos[1].x = tlx - (tdisX / 6) * (x);
						workPos[3].x = tlx - (tdisX / 6) * (x + 1);
						workPos[0].x = ulx - (udisX / 6) * (x);
						workPos[2].x = ulx - (udisX / 6) * (x + 1);
					}
					break;
				case NET_PARTS_LEFT://LEFT
					//�l�̒���
					if (x == 0){
						//�K�v�����v�Z
						if (y == 0){
							tlx = ulx = m_aPos[0].x;
							trx = urx = m_aPos[2].x;
							trx >= tlx ? tdisX = udisX = trx - tlx : tdisX = udisX = tlx - trx;
							tly = uly = m_aPos[0].y;
							trY = ury = m_aPos[2].y;
							tdisY = udisY = trY - tly;
							trx >= tlx ? yAng = 1.0f : yAng = 0.0f;
							LtoCdisX = m_centerPos.y - m_aPos[0].y;
							CtoRdisX = m_aPos[2].y - m_centerPos.y;
						}

						//Y�̒���
						tly = uly;
						trY = ury;
						tdisY = udisY;
						ury = m_aPos[2].y - ((((CtoRdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						uly = m_aPos[0].y + ((((LtoCdisX) / (NET_Y_NUM / 2.0f)) * (y + 1)) / 2.0f);
						udisY = ury - uly;

						//X�̒���
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						ulx = m_aPos[0].x + ((((m_centerPos.x - m_aPos[0].x) / NET_Y_NUM) * (y + 1)));
						urx = m_aPos[2].x + ((((m_centerPos.x - m_aPos[2].x) / NET_Y_NUM) * (y + 1)));
						urx >= ulx ? udisX = urx - ulx : udisX = ulx - urx;
					}

					//���W�̐ݒ�
					workPos[0].y = tly + (tdisY / 6) * (x);
					workPos[2].y = tly + (tdisY / 6) * (x + 1);
					workPos[1].y = uly + (udisY / 6) * (x);
					workPos[3].y = uly + (udisY / 6) * (x + 1);

					if (yAng){	//�݂��̂ق������ɂ���
						workPos[0].x = tlx + (tdisX / 6) * (x);
						workPos[2].x = tlx + (tdisX / 6) * (x + 1);
						workPos[1].x = ulx + (udisX / 6) * (x);
						workPos[3].x = ulx + (udisX / 6) * (x + 1);
					}
					else{
						workPos[0].x = tlx - (tdisX / 6) * (x);
						workPos[2].x = tlx - (tdisX / 6) * (x + 1);
						workPos[1].x = ulx - (udisX / 6) * (x);
						workPos[3].x = ulx - (udisX / 6) * (x + 1);
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
	if (GetInputButtonPress(DIK_N, 0, BOTTON_NET_DOWNLEFT))
		m_bPressButton[2] = true;
	if (GetInputButtonPress(DIK_U, 0, BOTTON_NET_UPLEFT))
		m_bPressButton[0] = true;
	if (GetInputButtonPress(DIK_8, 0, BOTTON_NET_UPRIGHT))
		m_bPressButton[1] = true;
	if (GetInputButtonPress(DIK_9, 0, BOTTON_NET_DOWNRIGHT))
		m_bPressButton[3] = true;

	//---- �S�{�^���v�b�V����Ԃ��ǂ��� ----
	for (int i = 0; i < 4; i++){
		if (!m_bPressButton[i])
			break;
		if (i == 3)
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

		//----- �\����ԏI�� -----
		gamePhase = PHASE_SHOUT;
		m_bDrawArrow = false;

		break;
	}

}


//====================================================
//
// �w������x���̍X�V
//
//====================================================
void cNet::ShoutPhaseUpdate(){

	//------ ���S�_���΂� ------
	m_centerPos.y -= m_fThrowSpeed;
	//�ȂȂ߂ɂƂ΂��Ȃ�X��

	//------ �{�^�����������`�F�b�N ------
	for (int i = 0; i < 4; i++){
		if (!m_bPressButton[i] && !m_bThrow[i]){
			m_bThrow[i] = true;
		}
	}

	//------ �{�^�������Ă��Ȃ����_��Ǐ] -----
	for (int i = 0; i < 4; i++){
		if (!m_bThrow[i])
			m_aPos[i].y -= m_fThrowSpeed;
	}

	//------ ���� ----------
	m_fThrowSpeed -= DECRE_THROW_SPEED;
	if (m_fThrowSpeed < 0)
		m_fThrowSpeed = 0.0f;

	//----- �{�^�������[�X�Œ��_�Ƃ΂����I -----


	//----- ���R�Ɍ�����悤�ɒ��_�Ԃ̍ő又���Ƃ� -----

}


//====================================================
//
// �w�����x���̍X�V
//
//====================================================
void cNet::PullPhaseUpdate(){



}


