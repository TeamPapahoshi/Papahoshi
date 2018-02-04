//======================================================================
//	Star
//	
//	�T�v�Q�F������
//	����ҁF�����@��
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>
#include <math.h>
#include <fstream>
#include "debugproc.h"
#include "Common.h"
#include "Texture.h"
#include "NormalStars.h"
#include "rand.h"
#include "Input.h"
#include <cmath>

//-----------------------------
//�}�N����`
//-----------------------------
#define STAR_SIZE	(20)
#define RESPAWN_FREAM (200)
#define MAX_NORMAL_STAR_NUM	(50)

//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cNormalStar::cNormalStar(){

	// �����̏�����
	CRandam::InitRand();

	// �g�p�����i�[�t�@�C������ǂݍ��ނ��ǂ����ԕύX��������
	m_nMaxNum = MAX_NORMAL_STAR_NUM;

	// ���I�C���X�^���X
	m_pStarData = new cNormalStarData[m_nMaxNum]();	//��������
	m_pRoot = m_pStarData;							// �擪�A�h���X�ۑ�



	// ������
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// ��������
		m_pStarData->m_bDraw = true;
		SetCountAndUse(true);

		// �T�C�Y�̕ύX
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));

		// �e�N�X�`���̐ݒ�
		m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR));

		// ���W�̌���
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);

		//CreateRamdomPos = D3DXVECTOR2(SCREEN_WIDTH/2.0f+50, SCREEN_HEIGHT-100);
		m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// ���

		// �����蔻��
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE/2.0f);

		// �ړ��̖ړI�ʒu����
		m_pStarData->m_PurposPos = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);
		// �ړI�n�܂ł̋����𑪒�
		m_pStarData->m_PurPosDist.x =fabs(m_pStarData->m_PurposPos.x - m_pStarData->m_sprite.GetPos().x);
		m_pStarData->m_PurPosDist.y = fabs(m_pStarData->m_PurposPos.y - m_pStarData->m_sprite.GetPos().y);

	}

}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cNormalStar::~cNormalStar(){


	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	delete[] m_pStarData;
}
//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cNormalStar::Update(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �C�x���g�i�[���[�v�H
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		// �C�x���g���Ăяo����銴��
		if (m_pStarData->m_bCreateEvent){
			Create();
		}

		else if (m_pStarData->m_bDestroyEvent){
			Destroy();
		}

		else if (m_pStarData->m_bRespawnEvent){
			Respawn();
		}
		
		// �����蔻��
		m_pStarData->m_Collision.SetType(cCollider::CIRCLE);
		m_pStarData->m_Collision.SetCircleCollider(m_pStarData->m_sprite.GetPos(), STAR_SIZE / 2.0f);


	}

	// �C�x���g�̋N��
	// �f�o�b�O�L�[
	if (GetKeyboardTrigger(DIK_R)){
		m_pStarData = m_pRoot;	// �擪�ɖ߂�
		for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
			m_pStarData->m_bDestroyEvent = true;
		}
	}
	//if (GetKeyboardTrigger(DIK_K)){
	//	m_pStarData = m_pRoot;	// �擪�ɖ߂�
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (m_pStarData->m_bDraw)	// ��������
	//			continue;
	//		m_pStarData->m_bCreateEvent = true;
	//		break;
	//	}
	//}
	//// �f�o�b�O�L�[
	//if (GetKeyboardTrigger(DIK_D)){
	//	m_pStarData = m_pRoot;	// �擪�ɖ߂�
	//	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){
	//		if (!m_pStarData->m_bUse)	// ��������
	//			continue;
	//		m_pStarData->m_bDestroyEvent = true;
	//		break;
	//	}
	//}

}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cNormalStar::Draw(){

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;

	// �`��
	for (int nCountStarNum = 0; nCountStarNum < m_nMaxNum; nCountStarNum++, m_pStarData++){

		if (!m_pStarData->m_bDraw)
			continue;

		m_pStarData->m_sprite.Draw();

		if (m_pStarData->m_bUse)
			m_pStarData->m_Collision.Draw();
	}

	// �擪�ɖ߂�
	m_pStarData = m_pRoot;


	// �f�o�b�O�v�����g
	PrintDebugProc("���������������u��������������\n");
	PrintDebugProc("���݂̐� %d/%d\n", m_nCurrentNum, m_nMaxNum);
	PrintDebugProc("R�L�[�Ń��Z�b�g\n");
	PrintDebugProc("���X�|�[���C���^�[�o���m�F %d/%d\n", m_pStarData->m_nRespawnFrame, RESPAWN_FREAM);
	PrintDebugProc("������������������������������\n");


}
//=======================================================================================
//
//		����
//
//=======================================================================================
void cNormalStar::Create(){

	// �����C�x���g�̊J�n
	if (!m_pStarData->m_bCreateEnd){



		// �����ȊO�͓��������ɂȂ�͂�������R�s�؂ł����͂�
		//****** �����ɉ��o�Ƃ����������������Ă��� **********
		//m_pStarData->m_bUse = true;->����ł��ł��邯�Ǎ���͐����������Ă�����������
		m_pStarData->m_bDraw = true;



		//****************************************************



		// ���o����������琶���I���t���O�𗧂Ă�->if(EffectEnd()){m_pStar->....}
		//m_pStarData->m_bCreateEnd = true;

		m_pStarData->m_bCreateEnd = true;



	}


	// �����I���t���O���������烊�Z�b�g���ďI��
	if (m_pStarData->m_bCreateEnd){

		//	���Z�b�g
		m_pStarData->m_bCreateEnd = false;
	
		// �t���O�I��
		SetCountAndUse(true);
		m_pStarData->m_bCreateEvent = false;
		return;
	}
}


//=======================================================================================
//
//		�폜(�ꉞ�����)
//
//=======================================================================================
void cNormalStar::Destroy(){

	// �����C�x���g�̊J�n
	if (!m_pStarData->m_bDestroyEnd){

		SetCountAndUse(false);

		// �����ȊO�͓��������ɂȂ�͂�������R�s�؂ł����͂�
		//****** �����ɉ��o�Ƃ������������Ă��� **********




		//****************************************************


		// ���o�����������I���t���O�𗧂Ă�->if(EffectEnd()){m_pStar->....}
		m_pStarData->m_bDestroyEnd = true;

	

	}

	// �����I���t���O���������烊�Z�b�g���ďI��
	if (m_pStarData->m_bDestroyEnd){

		// �I�������瑦���X�|�[������
		m_pStarData->m_bRespawnEvent = true;

		//	���Z�b�g
		m_pStarData->m_bDestroyEnd = false;
		m_pStarData->m_bDraw = false;
		m_pStarData->m_bDestroyEvent = false;

		return;
	}
}

////=======================================================================================
////
////		���X�|�[��
////
////=======================================================================================
void cNormalStar::Respawn(){

	
	if (!m_pStarData->m_bRespawnEnd){

		// �t���[�����Z�J�n
		m_pStarData->m_nRespawnFrame++;

		if (m_pStarData->m_nRespawnFrame > RESPAWN_FREAM){

			// ���W�̌���
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
			CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
			m_pStarData->m_sprite.SetPos(CreateRamdomPos);		// ���


			m_pStarData->m_PurposPos = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT);
			m_pStarData->m_PurPosDist.x = fabs(m_pStarData->m_PurposPos.x - m_pStarData->m_sprite.GetPos().x);
			m_pStarData->m_PurPosDist.y = fabs(m_pStarData->m_PurposPos.y - m_pStarData->m_sprite.GetPos().y);

			m_pStarData->m_bRespawnEnd = true;
		}
	}

	// �����I���t���O���������烊�Z�b�g���ďI��
	if (m_pStarData->m_bRespawnEnd){

	
		// �����C�x���g�J�n
		m_pStarData->m_bCreateEvent = true;



		//	���Z�b�g
		m_pStarData->m_nRespawnFrame = 0;


		m_pStarData->m_bRespawnEnd = false;
		m_pStarData->m_bRespawnEvent = false;
		return;
	}
}





//=======================================================================================
//
//		�ԂƂ̏���
//
//=======================================================================================
//--- �Ԃ̃f�[�^�擾 ---
void cNormalStar::SetNetData(cNet* data){
	m_pNetData = data;
}

//--- �ԂƓ����������̏��� ---
void cNormalStar::OnCollidToNet(int num){

	// �擪���牽�Ԗڂ�
	m_pStarData = m_pRoot;
	m_pStarData += num;


	//// �Ԃ������Ă���Ƃ��݈̂ړ�����
	//if (m_pNetData->GetPullFlug()){

	//	// �ړ�����������
	//	float DistGoalX = m_pStarData->m_PurPosDist.x / 3.0f;	// �O��ɕ����Ĉړ�����
	//	float DistGoalY = m_pStarData->m_PurPosDist.y / 3.0f;


	//	// ��������ړ��ʂ��Z�o(�t���[�����Ŋ���)
	//	m_pStarData->m_Move.x = DistGoalX / 50.0f;
	//	m_pStarData->m_Move.y = DistGoalY / 45.0f;



	//	// �ړ��ʂ𔽉f
	//	if (m_pStarData->m_sprite.GetPosX() > m_pStarData->m_PurposPos.x){
	//		m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() - m_pStarData->m_Move.x);
	//	}
	//	else if ((m_pStarData->m_sprite.GetPosX() < m_pStarData->m_PurposPos.x)){
	//		m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() + m_pStarData->m_Move.x);
	//	}
	//	else{

	//	}
	//	if ((m_pStarData->m_sprite.GetPosY() < m_pStarData->m_PurposPos.y)){
	//		m_pStarData->m_sprite.SetPosY(m_pStarData->m_sprite.GetPosY() + m_pStarData->m_Move.y);
	//	}
	//	else if ((m_pStarData->m_sprite.GetPosY() > m_pStarData->m_PurposPos.y)){
	//		m_pStarData->m_sprite.SetPosY(m_pStarData->m_sprite.GetPosY() + m_pStarData->m_Move.y);
	//	}
	//	else{

	//	}

	//}

		// �ړ�����������
		float DistGoalX = m_pStarData->m_PurPosDist.x / 3.0f;	// �O��ɕ����Ĉړ�����
		float DistGoalY = m_pStarData->m_PurPosDist.y / 3.0f;


		// ��������ړ��ʂ��Z�o(�t���[�����Ŋ���)
		m_pStarData->m_Move.x = m_pStarData->m_PurPosDist.x/50.0f;
		m_pStarData->m_Move.y = m_pStarData->m_PurPosDist.y/50.0f;



		// �ړ��ʂ𔽉f
		if (m_pStarData->m_sprite.GetPosX() >= m_pStarData->m_PurposPos.x){
			m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() - m_pStarData->m_Move.x);
		}
		else if ((m_pStarData->m_sprite.GetPosX() < m_pStarData->m_PurposPos.x)){
			m_pStarData->m_sprite.SetPosX(m_pStarData->m_sprite.GetPosX() + m_pStarData->m_Move.x);
		}
		if ((m_pStarData->m_sprite.GetPosY() <= m_pStarData->m_PurposPos.y)){
			m_pStarData->m_sprite.SetPosY(m_pStarData->m_sprite.GetPosY() + m_pStarData->m_Move.y);
		}
		else if ((m_pStarData->m_sprite.GetPosY() > m_pStarData->m_PurposPos.y)){
			m_pStarData->m_sprite.SetPosY(m_pStarData->m_sprite.GetPosY() + m_pStarData->m_Move.y);
		}
}




//=======================================================================================
//
//		�u���b�N�z�[���Ƃ̏���
//
//=======================================================================================
//---- �u���b�N�z�[���̏����擾 -----
void cNormalStar::SetBlackHoleData(cBlackHole* data){
	m_pBlackHoleData = data;

}

//---- �u���b�N�z�[���z�����ݔ͈͂ɓ����������̏��� -----
void cNormalStar::OnCollidToBlackHole(int Normal, int Black){

	// �U������
	//if (m_pStarData[Normal].t_bVibration){

	//	m_pStarData[Normal].t_nVibrationFrame++;
	//	m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() + 0.15f);

	//	if (m_pStarData[Normal].t_nVibrationFrame > 5){
	//		m_pStarData[Normal].t_bVibration = false;
	//		m_pStarData[Normal].t_nVibrationFrame = 0;
	//	}	
	//}

	//else if (!m_pStarData[Normal].t_bVibration){
	//	m_pStarData[Normal].t_nVibrationFrame++;
	//	m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() - 0.15f);
	//	if (m_pStarData[Normal].t_nVibrationFrame > 5){
	//		m_pStarData[Normal].t_bVibration = true;
	//		m_pStarData[Normal].t_nVibrationFrame = 0;
	//	}
	//}


	//// �u���b�N�z�[���̒��S���擾
	//D3DXVECTOR2 Center = m_pBlackHoleData->GetStarData()[Black].t_Sprite.GetPos();

	//// �u���b�N�z�[���Ɛ��Ƃ̋��������߂�
	//D3DXVECTOR2 Distance;
	//Distance.x = sqrt((m_pStarData[Normal].t_Sprite.GetPosX() - Center.x)*(m_pStarData[Normal].t_Sprite.GetPosX() - Center.x));
	//Distance.y = sqrt((m_pStarData[Normal].t_Sprite.GetPosY() - Center.y)*(m_pStarData[Normal].t_Sprite.GetPosY() - Center.y));

	//// ��������ړ��ʂ��Z�o
	//m_pStarData[Normal].t_Move.x = Distance.x / 800.0f;
	//m_pStarData[Normal].t_Move.y = Distance.y / 800.0f;

	//// �ړ��ʂ𔽉f
	//if (m_pStarData[Normal].t_Sprite.GetPosX() > Center.x){
	//	m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() - m_pStarData[Normal].t_Move.x);
	//}
	//if (m_pStarData[Normal].t_Sprite.GetPosX() < Center.x){
	//	m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() + m_pStarData[Normal].t_Move.x);
	//}

	//if (m_pStarData[Normal].t_Sprite.GetPosY() > Center.y){
	//	m_pStarData[Normal].t_Sprite.SetPosY(m_pStarData[Normal].t_Sprite.GetPosY() - m_pStarData[Normal].t_Move.y);
	//}
	//if (m_pStarData[Normal].t_Sprite.GetPosY() < Center.y){
	//	m_pStarData[Normal].t_Sprite.SetPosY(m_pStarData[Normal].t_Sprite.GetPosY() + m_pStarData[Normal].t_Move.y);
	//}

}

//---- �u���b�N�z�[���̍폜�͈͂ɓ����������̏��� -----
void cNormalStar::OnCollidToDelete(int Normal){

	
}