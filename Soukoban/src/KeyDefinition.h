#ifndef KEY_DEFINITION_H
#define KEY_DEFINITION_H

#include "DxLib.h"

// �L�[�̎��
enum KeyType
{
	KeyType_Up,    // ��ړ�
	KeyType_Down,  // ���ړ�
	KeyType_Left,  // ���ړ�
	KeyType_Right, // �E�ړ�
	KeyType_Enter, // ����
	KeyType_Reset, // ���Z�b�g
	KeyType_Clear,

	KeyType_Max    // �L�[�̎�ނ̐�
};

// �L�[�̎�ނɑΉ�����A���ۂ̓��͔z��
const int KEY_ASSIGN[KeyType_Max] =
{
	KEY_INPUT_UP,     // KeyType_Up
	KEY_INPUT_DOWN,   // KeyType_Down
	KEY_INPUT_LEFT,   // KeyType_Left
	KEY_INPUT_RIGHT,  // KeyType_Right
	KEY_INPUT_RETURN, // KeyType_Enter
	KEY_INPUT_R,      // KeyType_Reset
	KEY_INPUT_C,
};

#endif // !KEY_DEFINITION_H

