//======================================================================
//	EffectManeger�w�b�_
//	
//	�T�v�Q�F�G�t�F�N�g�Ǘ��p
//	����ҁF���� ����
//	
//======================================================================

//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include <Windows.h>		//HRESULT��

#include "SceneManeger.h"	//BaseScene

#include "EffectManeger.h"	

#include "debugproc.h"		//printdebug

//�g�p����G�t�F�N�g�̃C���N���[�h��
#include "EffectCircle.h"
#include "EffectSphereLight.h"

//-----------------------------
//�}�N����`
//-----------------------------

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
//		������
//
//=======================================================================================
void cEffectManeger::Init()
{
	//�|�C���^�̏�����
	for (int InitEffectloop = 0; InitEffectloop < MAX_EFFECT; InitEffectloop++)
		m_pEffect[InitEffectloop] = NULL;
}

//=======================================================================================
//
//		�I��
//
//=======================================================================================
void cEffectManeger::Uninit()
{
	for (int UninitEffectloop = 0; UninitEffectloop < MAX_EFFECT; UninitEffectloop++)
	{
		//���I�m�ۂ����G�t�F�N�g�̍폜
		delete m_pEffect[UninitEffectloop];
		m_pEffect[UninitEffectloop] = NULL;
	}
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cEffectManeger::Update()
{
	for (int UpdateEffectloop = 0; UpdateEffectloop < MAX_EFFECT; UpdateEffectloop++)
	{
		//���g�p�̃G�t�F�N�g�̓X���[
		if (m_pEffect[UpdateEffectloop] == NULL) continue;

		//�G�t�F�N�g�̍X�V
		m_pEffect[UpdateEffectloop]->Update();

		//�g�p���t���O������Ă�����
		if (!m_pEffect[UpdateEffectloop]->GetUseFlag())
		{
			//�m�ۂ��Ă����G�t�F�N�g�̍폜
			delete m_pEffect[UpdateEffectloop];
			m_pEffect[UpdateEffectloop] = NULL;
		}
	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cEffectManeger::Draw()
{
	for (int DrawEffectloop = 0; DrawEffectloop < MAX_EFFECT; DrawEffectloop++)
	{
		//���g�p�̃G�t�F�N�g�̓X���[
		if (m_pEffect[DrawEffectloop] == NULL) continue;
			
		m_pEffect[DrawEffectloop]->Draw();
	}
}

//=======================================================================================
//
//		�G�t�F�N�g�ݒ�֐�
//
//=======================================================================================
void cEffectManeger::SetEffectBase(EFFECT_NUM			effect,
								   LPDIRECT3DTEXTURE9	ptex, 
								   D3DXVECTOR2			pos, 
								   D3DXVECTOR2			size, 
								   D3DXVECTOR2			move,
								   D3DXCOLOR			color, 
								   int					life,
								   int					division)
{
	for (int SetEffectloop = 0; SetEffectloop < MAX_EFFECT; SetEffectloop++)
	{
		//���g�p�̃G�t�F�N�g�ɐݒ�
		if (m_pEffect[SetEffectloop] != NULL)	continue;

		switch (effect)
		{
		case EFFECT_CIRCLE:
			//�~�`�G�t�F�N�g�̔z�u
			m_pEffect[SetEffectloop] = new cEffectCircle;
			m_pEffect[SetEffectloop]->SetEffect(ptex, pos, size, move, color, life, division);
			break;
		
		case EFFECT_SPHERE_LIGHT:
			//�ی^�̌��G�t�F�N�g�z�u
			m_pEffect[SetEffectloop] = new cEffectSphereLight;
			m_pEffect[SetEffectloop]->SetEffect(ptex, pos, size, move, color, life, division);
			break;

		default:
			break;
		}

		break;
	}
}