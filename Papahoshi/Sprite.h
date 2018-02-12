//======================================================================
//	Sprite
//	
//	�T�v�Q�F�X�v���C�g
//	����ҁF�����@��
//	
//======================================================================

#ifndef ___SPRITE_H___
#define ___SPRITE_H___

//---------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------
#include "Common.h"		
#include <Windows.h>	//HRESULT��
#include "d3dx9.h"		//D3DXVECTOR2��

//---------------------------------
// �v���g�^�C�v�錾
//---------------------------------
HRESULT CreateBufferSprite(void);	// �X�v���C�g�̒��_�o�b�t�@�̐ݒ�
void	ReleaseBufferSprite(void);	// �X�v���C�g�̒��_�o�b�t�@�̉��


//---------------------------------
// �N���X��`
//---------------------------------
//�X�v���C�g�p�����[�^�N���X
class cSpriteParam {

private:

	// (�g���������l���Z�b�g����)

	// �X�v���C�g
	LPDIRECT3DTEXTURE9 m_pTex;	// �e�N�X�`���̃|�C���^

	D3DXVECTOR2 m_pos;			// ���W�ʒu
	D3DXVECTOR2 m_posFree[4];	// ���W�ʒu(�����`�ɂ��Ȃ����͂������g��)
	D3DXVECTOR2 m_size;			// �傫��
	D3DXVECTOR2 m_scale;		// �g�嗦
	D3DXVECTOR2 m_move;			// �ړ���(�ǉ�)
	float		m_rad;			// �p�x
	D3DXCOLOR	m_vtxColor;		// ���_�J���[
	bool		m_texUV;		// �e�N�X�`��UV�g�p�t���O

	// �e�N�X�`��UV
	bool	m_bTexAnimationLoop;		// �e�N�X�`���A�j���[�V�������g�p(Loop�̂�)
	int		m_texPatternDivideX;		// �e�N�X�`�����ł̕�����(X����)
	int		m_texPatternDivideY;		// �e�N�X�`�����ł̕�����(Y����)
	int		m_intervalChangePattern;	// �A�j���[�V�����̐؂�ւ��^�C�~���O(�t���[����)
	int		m_CountAnimationFrame;		// �A�j���[�V�����J�E���g�p
	int		m_currentAnimPattern;		// �A�j���[�V�����p�^�[���ԍ�
	D3DXVECTOR2   m_texUVRatio;			// �e�N�X�`��UV�̊���

	//�A���t�@�u�����h�X�C�b�`
	bool	m_bAddBlend;		//���Z����

public:

	cSpriteParam();									// �R���X�g���N�^
	void Draw();									// �`��
	void DrawFreePos();								// �����`����Ȃ��`��
	void LoadTexture(LPCSTR fileName);				// �e�N�X�`���̃��[�h
	void SetTexture(LPDIRECT3DTEXTURE9* pTex);		// �e�N�X�`���̃Z�b�g
	void AnimationLoop();							// �A�j���[�V�������[�v�̂�

	D3DXVECTOR2 AffinTranceform(float x, float y);	// �A�t�B���ϊ�

	//----�ݒ�p-----
	void SetTexPatternDevide(int x, int y){
		m_texPatternDivideX = x;
		m_texPatternDivideY = y;
	}
	void SetIntervalChangePattern(int data){
		m_intervalChangePattern = data;
	}
	void SetCurrentAnimPattern(int data){
		m_currentAnimPattern = data;
	}
	void SetAnimationFlag(bool data){
		m_bTexAnimationLoop = true;
	}


	void SetPosFree(D3DXVECTOR2 data1, D3DXVECTOR2 data2, D3DXVECTOR2 data3, D3DXVECTOR2 data4){
		m_posFree[0] = data1;
		m_posFree[1] = data2;
		m_posFree[2] = data3;
		m_posFree[3] = data4;
	}
	void SetPos(D3DXVECTOR2 data){		// pos
		m_pos = data;
	}
	void SetPosX(float data){
		m_pos.x = data;
	}
	void SetPosY(float data){
		m_pos.y = data;
	}
	void SetSize(D3DXVECTOR2 data){		// size
		m_size = data;
	}
	void SetSizeX(float data){
		m_size.x = data;
	}
	void SetSizeY(float data){
		m_size.y = data;
	}
	void SetScale(D3DXVECTOR2 data){	// scale
		m_scale = data;
	}

	//�ǉ�
	void SetMove(D3DXVECTOR2 data){
		m_move = data;
	}

	void SetMoveX(float data){
		m_move.x = data;
	}

	void SetMoveY(float data){
		m_move.y = data;
	}
	//�ǉ������܂�

	void SetScaleX(float data){
		m_scale.x = data;
	}
	void SetScaleY(float data){
		m_scale.y = data;
	}
	void SetRad(float data){
		m_rad = data;
	}
	void SetVtxColor(D3DXCOLOR data){
		m_vtxColor = data;
	}
	void SetVtxColorR(float data){
		m_vtxColor.r = data;
	}
	void SetVtxColorG(float data){
		m_vtxColor.g = data;
	}
	void SetVtxColorB(float data){
		m_vtxColor.b = data;
	}
	void SetVtxColorA(float data){
		m_vtxColor.a = data;
	}

	void SetTexUVFlag(void)
	{
		m_texUV = true;
	}
	void SetTexUVRatio(D3DXVECTOR2 data)
	{
		m_texUVRatio = data;
	}
	void SetTexUVRatioX(float data)
	{
		m_texUVRatio.x = data;
	}
	void SetTexUVRatioY(float data)
	{
		m_texUVRatio.y = data;
	}
	void SetAddBlend(bool data){
		m_bAddBlend = data;
	}


	//----�擾�p----
	int GetCurrentAnimPattern(){
		return m_currentAnimPattern;
	}
	D3DXVECTOR2 GerPosFree0(){
		return m_posFree[0];
	}
	D3DXVECTOR2 GerPosFree1(){
		return m_posFree[1];
	}
	D3DXVECTOR2 GerPosFree2(){
		return m_posFree[2];
	}
	D3DXVECTOR2 GerPosFree3(){
		return m_posFree[3];
	}
	D3DXVECTOR2 GetPos(){		// pos
		return m_pos;
	}
	float GetPosX(){
		return m_pos.x;
	}
	float GetPosY(){
		return m_pos.y;
	}
	D3DXVECTOR2 GetSize(){		// size
		return m_size;
	}
	float GetSizeX(){
		return m_size.x;
	}
	float GetSizeY(){
		return m_size.y;
	}
	D3DXVECTOR2 GetScale(){		// scale
		return m_scale;
	}
	float GetScaleX(){
		return m_scale.x;
	}
	float GetScaleY(){
		return m_scale.y;
	}

	//�ǉ�
	D3DXVECTOR2 GetMove(){		// scale
		return m_move;
	}
	float GetMoveX(){
		return m_move.x;
	}
	float GetMoveY(){
		return m_move.y;
	}
	//�ǉ������܂�

	float GetRad(){	// rad
		return m_rad;
	}
	D3DXCOLOR GetVtxColor(){	// vexcolor
		return m_vtxColor;
	}
	float GetVtxColorR(){
		return m_vtxColor.r;
	}
	float GetVtxColorG(){
		return m_vtxColor.g;
	}
	float GetVtxColorB(){
		return m_vtxColor.b;
	}
	float GetVtxColorA(){
		return m_vtxColor.a;
	}

	D3DXVECTOR2 GetTexUVRatio()
	{
		return m_texUVRatio;
	}
	float GetTexUVRatioX()
	{
		return m_texUVRatio.x;
	}
	float GetTexUVRatioY()
	{
		return m_texUVRatio.y;
	}
	
};
#endif	//!___SPRITE_H___