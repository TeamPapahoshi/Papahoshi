//=============================================================================
//  Net.cpp
//
//  ����F�㓡 ����
//  �T�v�F�Ԃ̏���
//=============================================================================
/*
�E���݂̂͂肩���̒����@12/15
�@center�Ƃ̋����Ő}��B
�E�܂�������΂��Ďw�𗣂����璸�_�L����@12/18
*/


//-------------------------------------
// �C���N���[�h��
//-------------------------------------
#include "Net.h"
#include "Texture.h"

//-------------------------------------
// �萔�E�}�N����`
//-------------------------------------
#define UKI_SIZE (20.0f)

//=====================================================
//
//  �Ԃ̃R���X�g���N�^
//
//=====================================================
cNet::cNet(){

	//�l���_�̏�����
	m_aPos[0].x = 100.0f;
	m_aPos[0].y = 100.0f;
	m_aPos[1].x = 400.0f;
	m_aPos[1].y = 100.0f;
	m_aPos[2].x = 100.0f;
	m_aPos[2].y = 400.0f;
	m_aPos[3].x = 400.0f;
	m_aPos[3].y = 400.0f;

	//���S�_�̏�����
	m_centerPos = D3DXVECTOR2(250.0f, 250.0f);

	//�X�v���C�g�̏�����
	for (int z = 0; z < NET_PARTS_MAX; z++){
		for (int y = 0; y < NET_Y_NUM; y++){
			for (int x = 0; x < NET_X_NUM; x++){
				m_aNet[z][y][x].SetTexture(cTextureManager::GetTextureTitle(TEX_NET));	// �e�N�X�`���̃Z�b�g
			}
		}
	}
	for (int i = 0; i < 4; i++){
		m_aFourUki[i].SetTexture(cTextureManager::GetTextureTitle(TEX_UKI));
		m_aFourUki[i].SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));
	}
	m_center.SetTexture(cTextureManager::GetTextureTitle(TEX_UKI));
	m_center.SetSize(D3DXVECTOR2(UKI_SIZE, UKI_SIZE));

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

}


//====================================================
//
// �e���_�ɍ��킹�Ă��݂�\��
//
//====================================================
void cNet::SetNet(){

	D3DXVECTOR2 workPos[4];
	float tlx, ulx, trx, urx, tdisX, udisX, ry, ly, ydis;
	tlx = ulx = m_aPos[0].x;
	trx = urx = m_aPos[1].x;
	tdisX = udisX = trx - tlx;
	ly = m_aPos[0].y;
	ry = m_aPos[1].y;
	ydis = ry - ly;

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
				case 0://TOP
					//X�̒���
					if (x == 0){
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						urx = m_aPos[1].x - ((((m_aPos[1].x - m_aPos[0].x) / NET_Y_NUM) * (y + 1)) / 2.0f);
						ulx = m_aPos[0].x + ((((m_aPos[1].x - m_aPos[0].x) / NET_Y_NUM) * (y + 1)) / 2.0f);
						udisX = urx - ulx;

						//Y�̒���
						ly = m_aPos[0].y + ((((m_aPos[1].y - m_aPos[0].x) / NET_X_NUM) * (x + 1)) / 2.0f);
						ry = m_aPos[1].y + ((((m_aPos[1].y - m_aPos[0].x) / NET_X_NUM) * (x + 1)) / 2.0f);
					}

					//���W�̐ݒ�
					workPos[0].x = tlx + ((tdisX / NET_X_NUM) * x);
					workPos[1].x = tlx + ((tdisX / NET_X_NUM) * (x + 1));
					workPos[2].x = ulx + ((udisX / NET_X_NUM) * x);
					workPos[3].x = ulx + ((udisX / NET_X_NUM) * (x + 1));

					workPos[0].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * y;
					workPos[1].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * y;
					workPos[2].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * (y + 1);
					workPos[3].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * (y + 1);
					break;
				case 1://UNDER
					//X�̒���
					if (x == 0){
						tlx = ulx;
						trx = urx;
						tdisX = udisX;
						urx = m_aPos[2].x - ((((m_aPos[3].x - m_aPos[2].x) / NET_Y_NUM) * (y + 1)) / 2.0f);
						ulx = m_aPos[3].x + ((((m_aPos[3].x - m_aPos[2].x) / NET_Y_NUM) * (y + 1)) / 2.0f);
						udisX = urx - ulx;

						//Y�̒���
						ly = m_aPos[2].y + ((((m_aPos[3].y - m_aPos[2].x) / NET_X_NUM) * (x + 1)) / 2.0f);
						ry = m_aPos[3].y + ((((m_aPos[3].y - m_aPos[2].x) / NET_X_NUM) * (x + 1)) / 2.0f);
					}

					//���W�̐ݒ�
					workPos[0].x = tlx + ((tdisX / NET_X_NUM) * x);
					workPos[1].x = tlx + ((tdisX / NET_X_NUM) * (x + 1));
					workPos[2].x = ulx + ((udisX / NET_X_NUM) * x);
					workPos[3].x = ulx + ((udisX / NET_X_NUM) * (x + 1));

					workPos[0].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * y;
					workPos[1].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * y;
					workPos[2].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * (y + 1);
					workPos[3].y = m_aPos[0].y + (m_centerPos.y - m_aPos[0].y) / NET_Y_NUM * (y + 1);
					break;
				case 2://RIGHT
					break;
				case 3://LEFT
					break;
				}

				//���݂̃|�W�V��������
				m_aNet[z][y][x].SetPosFree(workPos[0], workPos[1], workPos[2], workPos[3]);
			}
		}
	}

}