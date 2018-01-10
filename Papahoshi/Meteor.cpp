//======================================================================
//	Meteor
//	
//	�T�v�Q�F�^�C�g���I�u�W�F�N�g/����
//	����ҁF���� ����
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>		//HRESULT��

#include "debugproc.h"		//printdebug
#include "Meteor.h"
#include "Texture.h"

//-----------------------------
//�}�N����`
//-----------------------------
#define METEOR_LIFETIME (60)
#define METEOR_SIZE (10.0f)
#define METEOR_MOVE (2.5f)

#define RANDAM_METEOR_POS (300)

#define RANDAM_METEOR_SET ((float)CRandam::RandamRenge(RANDAM_METEOR_POS, SCREEN_WIDTH - RANDAM_METEOR_POS))
#define RANDAM_METEOR_TIME (CRandam::RandamRenge(200, 400))

//-----------------------------
//�񋓌^��`
//-----------------------------

//-----------------------------
//�N���X��`
//-----------------------------

//-----------------------------
//�O���[�o��
//-----------------------------


//=======================================================================================
//
//		�R���X�g���N�^
//
//=======================================================================================
cMeteor::cMeteor(){

}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cMeteor::~cMeteor(){

}

//=======================================================================================
//
//		������
//
//=======================================================================================
void cMeteor::Init(){
	
	//�|�C���^�̐ݒ�
	cSpriteParam* pSprite = m_Sprite;

	for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop ++, pSprite++)
	{
		pSprite->SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_SPHERE_LIGHT));
		pSprite->SetVtxColorA(255.0f / Meteorloop + 1);
		pSprite->SetMove(D3DXVECTOR2(-METEOR_MOVE, METEOR_MOVE));
		pSprite->SetSize(D3DXVECTOR2(METEOR_SIZE, METEOR_SIZE));
	}

	m_nLifeTime = METEOR_LIFETIME;
	m_nMakeTime = RANDAM_METEOR_TIME;
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cMeteor::UnInit(){

}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cMeteor::Update(){

	//�|�C���^�̐ݒ�
	cSpriteParam* pSprite = m_Sprite;
	cSpriteParam* pOldSprite = m_Sprite;

	if (m_bUseFlag)
	{//�g�p���̏���

		for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++, pSprite++)
		{
			if (Meteorloop == 0)
			{
				pSprite->SetPos(pSprite->GetPos() + pSprite->GetMove());
			}
			else
			{
				pSprite->SetPos(pOldSprite->GetPos());
			}

			pOldSprite = pSprite;	//�ߋ����W�̕ۑ�
		}

		m_nLifeTime--;			//�������Ԃ̌���
		if (m_nLifeTime <= 0)
		{
			m_bUseFlag = false;
			m_nLifeTime = METEOR_LIFETIME;
		}
	}
	else
	{//���g�p�̏ꍇ�̏���
		m_nMakeTime--;	//�������Ԃ̌���

		if (m_nMakeTime <= 0)
			SetMeteor();
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cMeteor::Draw(){

	//�|�C���^�̐ݒ�
	cSpriteParam* pSprite = m_Sprite;

	if (!m_bUseFlag)	return;	//���g�p�̏ꍇ�͏������Ȃ�

	for (int Meteorloop = 0; Meteorloop < MAX_METEOR; Meteorloop++, pSprite++)
	{
		pSprite->Draw();
	}
}

//=======================================================================================
//
//		�����̐ݒ�
//
//=======================================================================================
void cMeteor::SetMeteor(){

	//�|�C���^�̐ݒ�
	cSpriteParam* pSprite = m_Sprite;

	pSprite->SetPos(D3DXVECTOR2(RANDAM_METEOR_SET, RANDAM_METEOR_SET));	//�o�����W�������_���ɐݒ�

	m_bUseFlag = true;					//�g�p�t���O�����Ă�
	m_nMakeTime = RANDAM_METEOR_TIME;	//�������Ԃ̍Đݒ�
}