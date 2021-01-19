#ifndef DEFINITION_H
#define DEFINITION_H

// �V�[��ID
enum SceneID
{
	SceneID_Title,      // �^�C�g��
	SceneID_InGame,     // �C���Q�[��
	SceneID_Result,     // ���U���g

	SceneID_Max,
	SceneID_Invalid,    // �����l
};
// -------------------------------------
// �q�ɔԗp�̒�`
const int STAGE_WIDTH = 11;
const int STAGE_HEIGHT = 13;

// �}�b�v�`�b�v�̏c�`��T�C�Y
const int CHIP_WIDTH = 32;
const int CHIP_HEIGHT = 32;



// �I�u�W�F�N�g���
// �@�@�@�@0  �n��
//         1�@��
//         2�@�v���C���[�̏����n�_
//         3�@�N���[�g�z�u�ꏊ
//         4�@���z�u�̃N���[�g
//         7�@�z�u�ς݂̃N���[�g
// �@�@�@�@�@�i�z�u�ꏊ'3'+���z�u�N���[�g'4' = 7)

enum ObjectType
{
	Objecttype_Ground,       // 0
	Objecttype_Wall,		 // 1
	Objecttype_Player,		 // 2
	Objecttype_Target,		 // 3
	Objecttype_UnsetCrate,	 // 4
	Objecttype_SetCrate,	 // 7
};

// �ړ�����
enum DirType
{
	DirType_Up, 
	DirType_Down,
	DirType_Left,
	DirType_Right,
	
	// �摜�ǂݍ��݂Ŏg�p����
	DirType_Max,
};

#endif // !DEFINITION_H

