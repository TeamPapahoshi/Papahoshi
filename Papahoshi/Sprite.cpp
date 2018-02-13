//======================================================================
//	Sprite
//	
//	�T�v�Q�F�X�v���C�g�̐ݒ�ƕ`��
//	����ҁF�����@��
//	
//======================================================================

//------------------------------
// �C���N���[�h�t�@�C��
//------------------------------
#include <math.h>

#include "Sprite.h"
#include "Direct3D.h"

//---------------------------
// �}�N����`
//---------------------------
//���_�t�H�[�}�b�g
#define FVF_VERTEX_2D_TEXTURE (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//�`�撸�_��
#define NUM_VERTEX_SPRITE	(4)

//�`��|���S����
#define NUM_POLYGON_SPRITE	(2)


//---------------------------------
//�\���̒�`
//---------------------------------
//���_���
typedef struct _tVertex2D{

	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//�e�N�X�`���̃p�[�X�y�N�e�B�u�R�l�N�g
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W

} tVertex2D;


//---------------------------
//�O���[�o���ϐ�
//---------------------------
//���_�o�b�t�@
static LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffSprite = NULL;

//=======================================================================================
//
//		�X�v���C�g�Ǘ�������
//
//	[�߂�l]	S_OK �F ����������		E_FAIL : ���������s
//
//=======================================================================================
cSpriteParam::cSpriteParam(){

	// �����l(�g��Ȃ��ꍇ�͂��̂܂܂�)
	m_pos = D3DXVECTOR2(100.0f, 100.0f);
	m_posFree[0] = D3DXVECTOR2(100.0f, 100.0f);
	m_posFree[1] = D3DXVECTOR2(100.0f, 100.0f);
	m_posFree[2] = D3DXVECTOR2(100.0f, 100.0f);
	m_posFree[3] = D3DXVECTOR2(100.0f, 100.0f);
	m_size		= D3DXVECTOR2(100.0f, 100.0f);
	m_scale		= D3DXVECTOR2(1.0f, 1.0f);
	m_texUVRatio = D3DXVECTOR2(1.0f, 1.0f);
	m_vtxColor	= D3DXCOLOR(255, 255, 255, 255);
	m_rad		= 0.0f;
	m_texUV		= false;
	m_pTex		= NULL;
	

	// �����l(�g��Ȃ��ꍇ�͂��̂܂܂�)
	m_texPatternDivideX=1;		
	m_texPatternDivideY=1;		
	m_intervalChangePattern = 999;			
	m_currentAnimPattern=0;	
	m_bTexAnimationLoop = false;
	m_CountAnimationFrame = 0;

	m_bAddBlend = false;

}

//=======================================================================================
//
//		�X�v���C�g�`��֐�
//
//=======================================================================================
void cSpriteParam::Draw(){

	//----------------------------
	// �����x0�̂Ƃ��Askip
	//----------------------------
	if (m_vtxColor.a <= 0)
		return;

	//----------------------------
	// ���[�J���ϐ��錾
	//----------------------------
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X���
	tVertex2D *pVtx;							// ���_���

	//---------------------------
	// �A���t�@�u�����h��ݒ�
	//---------------------------
	if (m_bAddBlend){
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// ���f�X�e�B�l�[�V�����J���[�̎w��
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z��r�Ȃ�
	}

	//----------------------------
	// ���_�o�b�t�@�̒��_�����X�V
	//----------------------------
	//----- ���_�o�b�t�@�@���b�N ------------
	g_pVtxBuffSprite->Lock(0, 0, (void **)&pVtx, 0);	//�|�C���^�̃|�C���^

	//---- ���W�v�Z�v�Z -----
	// �A�t�B���ϊ�
	D3DXVECTOR2 vtxPos0[4];
	vtxPos0[0] = AffinTranceform(-m_size.x / 2.0f * m_scale.x, -m_size.y / 2.0f * m_scale.y);
	vtxPos0[1] = AffinTranceform( m_size.x / 2.0f * m_scale.x, -m_size.y / 2.0f * m_scale.y);
	vtxPos0[2] = AffinTranceform(-m_size.x / 2.0f * m_scale.x,  m_size.y / 2.0f * m_scale.y);
	vtxPos0[3] = AffinTranceform( m_size.x / 2.0f * m_scale.x,  m_size.y / 2.0f * m_scale.y);

	// ���W�ʒu(��ŃJ�����̍��W����������)
	D3DXVECTOR2 vtxPos1[4];
	vtxPos1[0] = D3DXVECTOR2(m_pos.x + vtxPos0[0].x, m_pos.y + vtxPos0[0].y);
	vtxPos1[1] = D3DXVECTOR2(m_pos.x + vtxPos0[1].x, m_pos.y + vtxPos0[1].y);
	vtxPos1[2] = D3DXVECTOR2(m_pos.x + vtxPos0[2].x, m_pos.y + vtxPos0[2].y);
	vtxPos1[3] = D3DXVECTOR2(m_pos.x + vtxPos0[3].x, m_pos.y + vtxPos0[3].y);

	//----- ���_���W�@�X�V ------------
	pVtx[0].pos = D3DXVECTOR3(vtxPos1[0].x, vtxPos1[0].y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(vtxPos1[1].x, vtxPos1[1].y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(vtxPos1[2].x, vtxPos1[2].y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(vtxPos1[3].x, vtxPos1[3].y, 0.0f);

	//----- �e�N�X�`�����W �X�V ------------
	float fPosXLeft, fPosXRight, fPosYUp, fPosYDown;	
	int		NumAnimPattern = m_texPatternDivideX*m_texPatternDivideY;// �A�j���[�V�����̑��p�^�[����
	float	TexPatternSizeX = 1.0f / m_texPatternDivideX;			 // 1�p�^�[���̃e�N�X�`���T�C�Y����(X����)
	float	TexPatternSizeY = 1.0f / m_texPatternDivideY;			 // 1�p�^�[���̃e�N�X�`���T�C�Y����(Y����)

	fPosXLeft = (float)(m_currentAnimPattern % m_texPatternDivideX) * TexPatternSizeX;
	fPosXRight = fPosXLeft + TexPatternSizeX;
	fPosYUp = (float)(m_currentAnimPattern / (NumAnimPattern / m_texPatternDivideY)) * TexPatternSizeY;
	fPosYDown = fPosYUp + TexPatternSizeY;

	if (m_texUV)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_texUVRatio.x, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, m_texUVRatio.y);
		pVtx[3].tex = D3DXVECTOR2(m_texUVRatio.x, m_texUVRatio.y);
	}
	else
	{
		pVtx[0].tex = D3DXVECTOR2(fPosXLeft, fPosYUp);
		pVtx[1].tex = D3DXVECTOR2(fPosXRight, fPosYUp);
		pVtx[2].tex = D3DXVECTOR2(fPosXLeft, fPosYDown);
		pVtx[3].tex = D3DXVECTOR2(fPosXRight, fPosYDown);
	}

	//----- rhw �X�V ------------
	pVtx[0].rhw = pVtx[1].rhw = pVtx[2].rhw = pVtx[3].rhw = 1.0f;

	//----- ���_�J���[ �X�V ------------
	pVtx[0].col = pVtx[1].col = pVtx[2].col = pVtx[3].col = 
		D3DCOLOR_RGBA((unsigned char)m_vtxColor.r, (unsigned char)m_vtxColor.g,
		(unsigned char)m_vtxColor.b, (unsigned char)m_vtxColor.a);

	//----- ���_�o�b�t�@�@�A�����b�N ------------
	g_pVtxBuffSprite->Unlock();

	//----------------------------
	// �`�揀��
	//----------------------------
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���փo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffSprite, 0, sizeof(tVertex2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D_TEXTURE);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,m_pTex);

	//----------------------------
	// �`��
	//----------------------------
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON_SPRITE);

	//----------------------------
	// �`��ݒ��������
	//----------------------------
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			// Z��r����
}


//=======================================================================================
//
//		�X�v���C�g�`��֐�(�����`����Ȃ��ꍇ)
//
//=======================================================================================
void cSpriteParam::DrawFreePos(){

	//----------------------------
	// �����x0�̂Ƃ��Askip
	//----------------------------
	if (m_vtxColor.a <= 0)
		return;

	//----------------------------
	// ���[�J���ϐ��錾
	//----------------------------
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X���
	tVertex2D *pVtx;							// ���_���

	//---------------------------
	// �A���t�@�u�����h��ݒ�
	//---------------------------
	if (m_bAddBlend){
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// ���f�X�e�B�l�[�V�����J���[�̎w��
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z��r�Ȃ�
	}

	//----------------------------
	// ���_�o�b�t�@�̒��_�����X�V
	//----------------------------
	//----- ���_�o�b�t�@�@���b�N ------------
	g_pVtxBuffSprite->Lock(0, 0, (void **)&pVtx, 0);	//�|�C���^�̃|�C���^

	//----- ���_���W�@�X�V ------------
	pVtx[0].pos = D3DXVECTOR3(m_posFree[0].x, m_posFree[0].y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posFree[1].x, m_posFree[1].y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posFree[2].x, m_posFree[2].y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posFree[3].x, m_posFree[3].y, 0.0f);

	//----- �e�N�X�`�����W �X�V ------------
	float fPosXLeft, fPosXRight, fPosYUp, fPosYDown;
	int		NumAnimPattern = m_texPatternDivideX*m_texPatternDivideY;// �A�j���[�V�����̑��p�^�[����
	float	TexPatternSizeX = 1.0f / m_texPatternDivideX;			 // 1�p�^�[���̃e�N�X�`���T�C�Y����(X����)
	float	TexPatternSizeY = 1.0f / m_texPatternDivideY;			 // 1�p�^�[���̃e�N�X�`���T�C�Y����(Y����)

	fPosXLeft = (float)(m_currentAnimPattern % m_texPatternDivideX) * TexPatternSizeX;
	fPosXRight = fPosXLeft + TexPatternSizeX;
	fPosYUp = (float)(m_currentAnimPattern / (NumAnimPattern / m_texPatternDivideY)) * TexPatternSizeY;
	fPosYDown = fPosYUp + TexPatternSizeY;

	if (m_texUV)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f			, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_texUVRatio.x, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f		    , m_texUVRatio.y);
		pVtx[3].tex = D3DXVECTOR2(m_texUVRatio.x, m_texUVRatio.y);
	}
	else
	{
		pVtx[0].tex = D3DXVECTOR2(fPosXLeft, fPosYUp);
		pVtx[1].tex = D3DXVECTOR2(fPosXRight, fPosYUp);
		pVtx[2].tex = D3DXVECTOR2(fPosXLeft, fPosYDown);
		pVtx[3].tex = D3DXVECTOR2(fPosXRight, fPosYDown);
	}

	//----- rhw �X�V ------------
	pVtx[0].rhw = pVtx[1].rhw = pVtx[2].rhw = pVtx[3].rhw = 1.0f;

	//----- ���_�J���[ �X�V ------------
	pVtx[0].col = pVtx[1].col = pVtx[2].col = pVtx[3].col =
		D3DCOLOR_RGBA((unsigned char)m_vtxColor.r, (unsigned char)m_vtxColor.g,
		(unsigned char)m_vtxColor.b, (unsigned char)m_vtxColor.a);

	//----- ���_�o�b�t�@�@�A�����b�N ------------
	g_pVtxBuffSprite->Unlock();

	//----------------------------
	// �`�揀��
	//----------------------------
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���փo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffSprite, 0, sizeof(tVertex2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D_TEXTURE);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTex);

	//----------------------------
	// �`��
	//----------------------------
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON_SPRITE);

	//----------------------------
	// �`��ݒ��������
	//----------------------------
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			// Z��r����

}

//=======================================================================================
//
//		�A�j���[�V����
//
//=======================================================================================
void cSpriteParam::AnimationLoop(){


	if (!m_bTexAnimationLoop)
		return;

	m_CountAnimationFrame++;

	if (m_currentAnimPattern > m_texPatternDivideX*m_texPatternDivideY-1){
		m_currentAnimPattern = 0;
	}

	if (m_CountAnimationFrame >= m_intervalChangePattern){

		m_CountAnimationFrame = 0;

		m_currentAnimPattern++;
	}


	
}


//=======================================================================================
//
//		�e�N�X�`�����[�h
//
//=======================================================================================
void cSpriteParam::LoadTexture(LPCSTR fileName){

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// Direct3D�f�o�C�X
	D3DXCreateTextureFromFile(pDevice, fileName, &m_pTex);
}


//=======================================================================================
//
//		�e�N�X�`���Z�b�g
//
//=======================================================================================
void cSpriteParam::SetTexture(LPDIRECT3DTEXTURE9* pTex){
	m_pTex = *pTex;
}



//=======================================================================================
//
//		�X�v���C�g�̃o�b�t�@�̍쐬
//
//	[�߂�l]	S_OK �F ����������		E_FAIL : ���������s
//
//=======================================================================================
HRESULT CreateBufferSprite(void){

	//----------------------------
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	//----------------------------
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// Direct3D�f�o�C�X

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(tVertex2D) * NUM_VERTEX_SPRITE,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D_TEXTURE, D3DPOOL_MANAGED, &g_pVtxBuffSprite, NULL)))
		return E_FAIL;

	//----------------------------
	//����������
	//----------------------------
	return S_OK;
}

//=======================================================================================
//
//		�X�v���C�g�̃o�b�t�@�̉��
//
//=======================================================================================
void	ReleaseBufferSprite(void){

	//----------------------------
	//���_�o�b�t�@�̉��
	//----------------------------
	if (g_pVtxBuffSprite != NULL)
	{
		g_pVtxBuffSprite->Release();
		g_pVtxBuffSprite = NULL;
	}
}

//=======================================================================================
//
//		�A�t�B���ϊ�
//
//=======================================================================================
D3DXVECTOR2 cSpriteParam:: AffinTranceform(float x, float y){

	D3DXVECTOR2 affin;
	affin.x = x*cosf(m_rad) - y*sinf(m_rad);
	affin.y = x*sinf(m_rad) + y*cosf(m_rad);

	return affin;
}