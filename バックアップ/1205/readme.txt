

�Q�[���Ƃ��Ă̏�����GameMain.cpp�ōs���܂��B�@�\��ǉ�����Ƃ���GameMaiin�ɒǉ����Ă��������B�B

�V�[���̒ǉ�
SceneManeger.h��enum��ǉ����� cpp�œ��I�C���X�^���X���܂��B���Ԃ�\�[�X����΂킩��܂��B
GameMain�ɂ͉����ǉ�����K�v�͂���܂���

�`��
cSpriteParam��`�悳�������N���X��private�ɂ������܂� player���݂���킩��Ǝv���܂��B

�����蔻��(�Ƃ肠�����~�Ɖ~)
cColider�������蔻��������������N���X��private�ɂ������܂��B
cCollidert::SetType()�ł����蔻�肪�l�p���~����ݒ肵�āAcCollider::SetCircleCollider()��������Collider::SetQuadCollider()�ō��W���Z�b�g����
cCollider::Draw()������Δ��̔������̃e�N�X�`���ł����蔻�肪�`�悳��܂��Bplayer���݂���킩��Ǝv���܂�

���ƒ��ӂ��邱�Ƃ�������SceneTitle������΂킩��Ǝv���܂����A�����蔻��̃`�F�b�N�̓V�[���ł��Ă���̂�
����������̏�����Update�Ƃ͕ʂ̊֐�(SceneTitle��player.OnColid�̂���)������čs���Ă��������B
���R��player��Enemy���C���X�^���X���Ă���ꏊ���V�[��������ł��B���ƃI�u�W�F�N�g�w���ōl�������A�v���C���[��
�G�l�~�[�̗v�f����������̂͂����������ȂƂ�����������ł��B
���ɂ������@�������狳���Ă��������B

�A�j���[�V����
�������͂܂��������Ă��Ȃ��ł����AcSpriteparam�Ńe�N�X�`��UV�̐ݒ�͂ł���̂ŁA�蓮�łł��܂��Bplayer���݂���킩��Ǝv���܂�

�e�N�X�`���̓ǂݍ��݂̓I�u�W�F�N�g���Ƃɓǂݍ��݂܂��B