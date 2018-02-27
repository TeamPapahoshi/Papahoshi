//===========================================
//
// Papahoshi  SceneTraning.cpp
//
// Mei Goto.
//
//===========================================

//-----------------------------
// �C���N���[�h��
//-----------------------------
#include "SceneTraning.h"
#include "Input.h"
#include "Transition.h"

//=======================================================================================
//
//		������
//
//=======================================================================================
cSceneTraning::cSceneTraning(){

	// ��
	m_pNet = new cNet();

	// �u���b�N�z�[��
	m_pBlackHole = new cBlackHole();
	m_pBlackHole->SetNetData(m_pNet);

	// 覐�
	m_pSpaceRock = new cSpaceRock();
	m_pSpaceRock->SetNetData(m_pNet);

	// �T���v��
	m_pSampleStar = new cSampleStar();

	// ����
	m_pRyusei = new cRyusei();
	m_pRyusei->SetNetData(m_pNet);

	// �Q�[�W
	m_pGage = new cGage();
	m_pGage->Init();

	// ���u��
	m_pNomalStar = new cNormalStar();
	m_pNomalStar->SetBlackHoleData(m_pBlackHole);
	m_pNomalStar->SetNetData(m_pNet);
	m_pNomalStar->SetGageData(m_pGage);

	// ���Q��
	m_pConsellation = new cConstellation();


	// UI
	m_pGameUI = new cGameUI();

	// �^�C�}�[
	m_pTimer = new cTimer();

	// �w�i
	m_pBG = new cBG();
	m_pBG->SetBG(cBG::GAME_SKY);

	//�v���C�T�|�[�g
	m_pPlaySupport = new cPlaySupport();

	//---- BGM�̍Đ� ----
	PlaySound(SOUND_LABEL::SOUND_LABEL_BGM_GAME);
	SetVolume(GAME_BGM_VOLUME, SOUND_LABEL::SOUND_LABEL_BGM_GAME);
	SetVolume(FEVER_BGM_VOLUME, SOUND_LABEL::SOUND_LABEL_BGM_GAME_FEVER);

	for (int i = 0; i < 180; i++){
		m_nLeverDirection[i] = 5;
	}
	m_bSceneChange = false;

}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
cSceneTraning::~cSceneTraning(){

	// �f���[�g
	delete m_pBG;
	delete m_pNomalStar;
	delete m_pSpaceRock;
	delete m_pRyusei;
	delete m_pGage;
	delete m_pBlackHole;
	delete m_pSampleStar;
	delete m_pNet;
	delete m_pGameUI;
	delete m_pTimer;
	delete m_pConsellation;
	delete m_pPlaySupport;

	//----- BGM�̒�~ -----
	StopSound(SOUND_LABEL::SOUND_LABEL_BGM_GAME);
	StopSound(SOUND_LABEL::SOUND_LABEL_BGM_GAME_FEVER);
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cSceneTraning::Update(){

	m_pNet->Update();			// ����
	m_pBG->Update();			// �w�i
	m_pGage->Update();			// �Q�[�W
	m_pGameUI->Update();		// UI
	m_pTimer->Update();			// �^�C�}�[

	//--- �� -----��ł܂Ƃ߂�
	m_pNomalStar->Update();
	m_pBlackHole->Update();
	m_pSpaceRock->Update();
	m_pSampleStar->Update();
	m_pRyusei->Update();
	m_pConsellation->Update();

	m_pPlaySupport->Update(m_pNet->GetGamePhase(), m_pNet->GetAllPress(), m_pNet->GetRevor());


	//----- �c�莞�ԂŐ������鐯���w�� --------
	if (m_pTimer->GetTime() == 50){
		m_pBlackHole->SetCreateStart();

	}


	CheckCollision();			//�����蔻��


	//�A�i�E���X�̍X�V
	if (m_pAnnounce){
		m_pAnnounce->Update();
		if (m_pAnnounce->CallFin()){
			delete m_pAnnounce;
			m_pAnnounce = NULL;
		}
	}

	//---- FEVER�X�^�[�g ------
	if (m_pGage->GetFeverStart()){

		m_bFever = true;
		m_pGage->SetFeverStart(false);
		m_pRyusei->SetFeverStar();

		//--- �A�i�E���X�Ăяo�� -----
		if (m_bFever)
			m_pAnnounce = new cAnnounce(cAnnounce::eAnnounceType::Fever);

		//--- BGM�ύX ---
		StopSound(SOUND_LABEL::SOUND_LABEL_BGM_GAME);
		PlaySound(SOUND_LABEL::SOUND_LABEL_BGM_GAME_FEVER);

		//---- UI�ύX ----
		m_pGameUI->SetTheerMotion(cTheerGirl::eGirlMotion::FEVER);
		m_pGameUI->SetUiType(cGameUI::eUItype::FEVER);
	}

	//---- Fever�I�� ------
	if (m_pGage->GetFeverFin()){

		m_bFever = false;
		m_pGage->SetFeverFin(false);
		m_pRyusei->SetFeverEnd();

		//--- BGM�ύX ---
		StopSound(SOUND_LABEL::SOUND_LABEL_BGM_GAME_FEVER);
		PlaySound(SOUND_LABEL::SOUND_LABEL_BGM_GAME);

		//---- UI�ύX ----
		m_pGameUI->SetTheerMotion(cTheerGirl::eGirlMotion::NOMAL);
		m_pGameUI->SetUiType(cGameUI::eUItype::NOMAL);
	}

	//---- �g�����I�� ----
	if (CheckCommand() && !m_bSceneChange){
		m_bSceneChange = true;
		cSceneManeger::ChangeSceneSetTransition(cSceneManeger::TITLE, cTransition::TRANSITION_TYPE::TRANSITION_DICE_SCALE_CHANGE);
	}

}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cSceneTraning::Draw(){

	m_pBG->Draw();				// �w�i
	m_pBlackHole->Draw();
	m_pSampleStar->Draw();
	m_pSpaceRock->Draw();
	m_pNomalStar->Draw();
	m_pRyusei->Draw();
	//m_pConsellation->Draw();
	m_pNet->Draw();

	m_pGameUI->Draw();
	m_pGage->Draw();
	m_pTimer->Draw();
	m_pPlaySupport->Draw();

	if (m_pAnnounce)
		m_pAnnounce->Draw();
}

//============================================
//
// �����蔻����擾
//
//============================================
void cSceneTraning::CheckCollision(){


	// ��ł��ꂢ�ɂ܂Ƃ߂�
	//************************************************************************************************************************************

	//---�Ԃƃ��u���̔���type2---
	for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			continue;

		for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			if (m_pNet->GetPullFlug()){
				if (CheckCollisionCircleToLine(m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetLeft(), m_pNet->GetNetCenter()) ||
					CheckCollisionCircleToLine(m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetCenter(), m_pNet->GetNetRight())){

					m_pNomalStar->OnCollidToNet(nCountStar);
				}
			}
		}
	}


	//---�ԂƗ����̔���type2---
	for (int nCountStar = 0; nCountStar < m_pRyusei->GetMaxNum(); nCountStar++){

		if (!m_pRyusei->GetStarData()[nCountStar].m_bUse)
			continue;

		for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			if (m_pNet->GetPullFlug()){
				if (CheckCollisionCircleToLine(m_pRyusei->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					m_pRyusei->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetLeft(), m_pNet->GetNetCenter()) ||
					CheckCollisionCircleToLine(m_pRyusei->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					m_pRyusei->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetCenter(), m_pNet->GetNetRight())){

					m_pRyusei->OnCollidToNet(nCountStar);
				}
			}


			// �Ԃ͈͓̔��ɂ���Ƃ��̏���
			if (cCollider::CheckCollisionCircleToTriangle(m_pRyusei->GetStarData()[nCountStar].m_Collision, m_pNet->GetCollider()[nCountNet])){

				m_pRyusei->OnCollidToNetArea(nCountStar);
			}

			if (!cCollider::CheckCollisionCircleToTriangle(m_pRyusei->GetStarData()[nCountStar].m_Collision, m_pNet->GetCollider()[0])
				&& !cCollider::CheckCollisionCircleToTriangle(m_pRyusei->GetStarData()[nCountStar].m_Collision, m_pNet->GetCollider()[1])){

				m_pRyusei->SetStream(true, nCountStar);
			}


		}

	}

	//---�Ԃ�覐΂̔���type2---
	for (int nCountStar = 0; nCountStar < m_pSpaceRock->GetMaxNum(); nCountStar++){

		if (!m_pSpaceRock->GetStarData()[nCountStar].m_bUse)
			continue;

		for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			if (m_pNet->GetPullFlug()){
				if (CheckCollisionCircleToLine(m_pSpaceRock->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					m_pSpaceRock->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetLeft(), m_pNet->GetNetCenter()) ||
					CheckCollisionCircleToLine(m_pSpaceRock->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					m_pSpaceRock->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetCenter(), m_pNet->GetNetRight())){

					m_pSpaceRock->OnCollidToNet(nCountStar);
				}
			}
		}
	}

	//---�Ԃƃu���b�N�z�[���̂̔���type2---
	for (int nCountStar = 0; nCountStar < m_pBlackHole->GetMaxNum(); nCountStar++){

		if (!m_pBlackHole->GetStarData()[nCountStar].m_bUse)
			continue;

		for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			if (m_pNet->GetPullFlug()){
				if (CheckCollisionCircleToLine(m_pBlackHole->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					m_pBlackHole->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetLeft(), m_pNet->GetNetCenter()) ||
					CheckCollisionCircleToLine(m_pBlackHole->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos,
					m_pBlackHole->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetCenter(), m_pNet->GetNetRight())){

					m_pBlackHole->OnCollidToNet(nCountStar);
				}
			}
		}
	}

	//************************************************************************************************************************************

	//���u���ƃu���b�N�z�[��
	for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			continue;

		for (int nCountBlackHole = 0; nCountBlackHole < m_pBlackHole->GetMaxNum(); nCountBlackHole++){

			if (!m_pBlackHole->GetStarData()[nCountBlackHole].m_bUse)
				continue;

			// �z�����ݔ͈�
			if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, m_pBlackHole->GetStarData()[nCountBlackHole].m_VacumeRange)){
				m_pNomalStar->OnCollidToBlackHoleVacumeRange(nCountStar, nCountBlackHole);
			}
			// �폜�͈�
			if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, m_pBlackHole->GetStarData()[nCountBlackHole].m_DeleteRange)){
				m_pNomalStar->OnCollidToBlackHoleDeleteRange(nCountStar, nCountBlackHole);

			}
		}
	}

	//���u���Ɨ���
	for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			continue;

		for (int nCountSpaceRock = 0; nCountSpaceRock < m_pSpaceRock->GetMaxNum(); nCountSpaceRock++){

			if (!m_pSpaceRock->GetStarData()[nCountSpaceRock].m_bUse)
				continue;

			if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, m_pSpaceRock->GetStarData()[nCountSpaceRock].m_Collision)){
				m_pNomalStar->OnCollidToSpaceRock(nCountStar);
				m_pSpaceRock->OnCollidToNormalStar(nCountSpaceRock);
			}

		}
	}
}

//================================================
// 
// �`�F�b�N�R�}���h
//
//================================================
bool cSceneTraning::CheckCommand(){

	//---- �ߋ����̑ޔ� ----
	for (int i = 178; i >= 0; i--){
		m_nLeverDirection[i + 1] = m_nLeverDirection[i];
	}

	//---------------------------
	// ���o�[����
	//---------------------------
	if (GetInputArrowPress(DIK_W, 0, PAD_ARROW_UP) && GetInputArrowPress(DIK_A, 0, PAD_ARROW_LEFT))
		m_nLeverDirection[0] = 7;
	else if (GetInputArrowPress(DIK_W, 0, PAD_ARROW_UP) && GetInputArrowPress(DIK_D, 0, PAD_ARROW_RIGHT))
		m_nLeverDirection[0] = 9;
	else if (GetInputArrowPress(DIK_S, 0, PAD_ARROW_DOWN) && GetInputArrowPress(DIK_D, 0, PAD_ARROW_RIGHT))
		m_nLeverDirection[0] = 3;
	else if (GetInputArrowPress(DIK_S, 0, PAD_ARROW_DOWN) && GetInputArrowPress(DIK_A, 0, PAD_ARROW_LEFT))
		m_nLeverDirection[0] = 1;
	else if (GetInputArrowPress(DIK_W, 0, PAD_ARROW_UP))
		m_nLeverDirection[0] = 8;
	else if (GetInputArrowPress(DIK_A, 0, PAD_ARROW_LEFT))
		m_nLeverDirection[0] = 4;
	else if (GetInputArrowPress(DIK_D, 0, PAD_ARROW_RIGHT))
		m_nLeverDirection[0] = 6;
	else if (GetInputArrowPress(DIK_S, 0, PAD_ARROW_DOWN))
		m_nLeverDirection[0] = 2;
	else
		m_nLeverDirection[0] = 5;

	// 24862486�ŃN���A�B
	int work = 0;
	for (int i = 0; i < 180; i++){
		switch (work)
		{
		case 0:
		case 4:
		case 8:
			if (m_nLeverDirection[i] == 6)
				work++;
			break;
		case 1:
		case 5:
		case 9:
			if (m_nLeverDirection[i] == 8)
				work++;
			break;
		case 2:
		case 6:
		case 10:
			if (m_nLeverDirection[i] == 4)
				work++;
			break;
		case 3:
		case 7:
		case 11:
			if (m_nLeverDirection[i] == 2)
				work++;
			break;
		}

		if (work >= 12)
			return true;
	}

	return false;

}