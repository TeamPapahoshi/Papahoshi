//======================================================================
//	RyuseiLine
//	
//	�T�v�Q�F�����̋O��
//	����ҁF�����@��
//	
//======================================================================
//-----------------------------
//�C���N���[�h�t�@�C��
//-----------------------------
#include "RyuseiLine.h"
#include "Common.h"
#include "debugproc.h"
#include "Texture.h"
//-----------------------------
//�}�N����`
//-----------------------------
#define LIFE_TIME	(60)
#define SIZE		(40)
#define MAX_RYUSEI_LINE (30)
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
cRyuseiLine::cRyuseiLine(){

	// ���I�m��
	m_pRyuseiLine = new tRyuseiLine[MAX_RYUSEI_LINE];
	m_pRoot = m_pRyuseiLine;	// �擪���i�[


	for (int nCunt = 0; nCunt < MAX_RYUSEI_LINE; nCunt++, m_pRyuseiLine++){
		// �����l
		m_pRyuseiLine->t_bUse = false;
		m_pRyuseiLine->t_LifeTime = LIFE_TIME;
		m_pRyuseiLine->t_sprite.SetSize(D3DXVECTOR2(SIZE, SIZE));
		m_pRyuseiLine->t_sprite.SetAddBlend(true);
		m_pRyuseiLine->t_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR_LIGHT));
		m_pRyuseiLine->t_sprite.SetVtxColor(D3DXCOLOR(255, 255, 0, 155));
	}

}

//=======================================================================================
//
//		�f�X�g���N�^
//
//=======================================================================================
cRyuseiLine::~cRyuseiLine(){
}

//=======================================================================================
//
//		�X�V
//
//=======================================================================================
void cRyuseiLine::Update(D3DXVECTOR2 pos,D3DXCOLOR col){

	


	//**********************IN*********************************************
	// �擪�ɖ߂�
	m_pRyuseiLine = m_pRoot;
	m_pRyuseiLine->t_fFrame++;

	if (m_pRyuseiLine->t_fFrame > 2){

		m_pRyuseiLine->t_fFrame = 0;
		// ����
		for (int nCunt = 0; nCunt < MAX_RYUSEI_LINE; nCunt++, m_pRyuseiLine++){

			if (m_pRyuseiLine->t_bUse)
				continue;



			// �����l
			m_pRyuseiLine->t_bUse = true;
			m_pRyuseiLine->t_LifeTime = LIFE_TIME;
			m_pRyuseiLine->t_sprite.SetSize(D3DXVECTOR2(SIZE, SIZE));
			m_pRyuseiLine->t_sprite.SetPos(pos);

			break;
		}
	}

	// �擪�ɖ߂�
	m_pRyuseiLine = m_pRoot;

	// �X�V
	for (int nCunt = 0; nCunt < MAX_RYUSEI_LINE; nCunt++, m_pRyuseiLine++){

		if (!m_pRyuseiLine->t_bUse)
			continue;


		// LifeTime�����炷
		m_pRyuseiLine->t_LifeTime--;

		// LifeTime�ƃT�C�Y�����킹��
		m_pRyuseiLine->t_sprite.SetSize(D3DXVECTOR2(SIZE*m_pRyuseiLine->t_LifeTime / LIFE_TIME, SIZE*m_pRyuseiLine->t_LifeTime / LIFE_TIME));

		// LifeTime�ƃ������킹��
		m_pRyuseiLine->t_sprite.SetVtxColorA(155 * m_pRyuseiLine->t_LifeTime / LIFE_TIME);

		if (m_pRyuseiLine->t_LifeTime <= 0){
			m_pRyuseiLine->t_bUse = false;
		}

	}
}

//=======================================================================================
//
//		�`��
//
//=======================================================================================
void cRyuseiLine::Draw(){

	// �擪�ɖ߂�
	m_pRyuseiLine = m_pRoot;

	for (int nCunt = 0; nCunt < MAX_RYUSEI_LINE; nCunt++, m_pRyuseiLine++){

		if (m_pRyuseiLine->t_bUse)
			m_pRyuseiLine->t_sprite.Draw();
	}

}