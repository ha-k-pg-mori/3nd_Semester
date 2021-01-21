#include "InGameScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

enum
{
	STEP_START_JINGLE,
	STEP_INPUT,
	STEP_CLEAR_JINGLE,
	STEP_END,
};

int MosyonList[]
{
	LoadGraphScreen(0, 0, "data/Player/player_00.png", TRUE),
	LoadGraphScreen(0, 0, "data/Player/player_01.png", TRUE),
	LoadGraphScreen(0, 0, "data/Player/player_02.png", TRUE),
	LoadGraphScreen(0, 0, "data/Player/player_03.png", TRUE),
	LoadGraphScreen(0, 0, "data/Player/player_04.png", TRUE),
	LoadGraphScreen(0, 0, "data/Player/player_05.png", TRUE),
	LoadGraphScreen(0, 0, "data/Player/player_06.png", TRUE),
	LoadGraphScreen(0, 0, "data/Player/player_07.png", TRUE),
	LoadGraphScreen(0, 0, "data/Player/player_08.png", TRUE),
	LoadGraphScreen(0, 0, "data/Player/player_09.png", TRUE),
	LoadGraphScreen(0, 0, "data/Player/player_10.png", TRUE),
	LoadGraphScreen(0, 0, "data/Player/player_11.png", TRUE),
};




const int g_SampleStage[STAGE_HEIGHT][STAGE_WIDTH] =
{
	0,0,0,1,1,1,1,1,0,0,0,
	0,0,0,1,3,3,3,1,0,0,0,
	0,0,0,1,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,1,0,0,0,
	1,1,1,1,1,0,1,1,1,1,1,
	1,0,0,4,0,0,1,0,0,0,1,
	1,0,1,0,0,4,0,4,0,0,1,
	1,0,0,0,1,1,1,0,0,0,1,
	1,1,1,0,1,0,1,0,1,1,1,
	0,0,1,0,1,0,1,0,1,0,0,
	0,0,1,0,0,0,0,0,1,0,0,
	0,0,1,0,0,2,0,0,1,0,0,
	0,0,1,1,1,0,1,1,1,0,0,
};


InGameScene::InGameScene()
	:m_PlayerX(0)
	, m_PlayerY(0)
{
	Reset();

	set_Step(STEP_START_JINGLE);

	Ground = LoadGraph("data/Ground/ground.png");

	Wall = LoadGraph("data/Ground/block.png");

	Player00 = LoadGraph("data/Player/player_00.png");

	Player01 = LoadGraph("data/Player/player_03.png");

	Player02 = LoadGraph("data/Player/player_07.png");

	Player03 = LoadGraph("data/Player/player_10.png");

	Target = LoadGraph("data/Crate/Crate_00.png");

	UnsetCreate = LoadGraph("data/Crate/crate_02.png");

	SetCrate = LoadGraph("data/Crate/crate_01.png");
}

InGameScene::~InGameScene()
{
	
}

void InGameScene::Exec()
{
	switch (m_Step)
	{
	case STEP_START_JINGLE: step_StartJingle(); break;
	case STEP_INPUT:  step_Input();  break;
	case STEP_CLEAR_JINGLE:  step_ClearJingle();  break;
	default: break;
	}
	// @@Debug �J�ڊm�F�p�̉�����
	// m_Step��J�E���g�A�b�v
	/*m_Step++;
	if (m_Step >= 120)
	{
		SceneManager::SetNextScene(SceneID_Result);
	}*/
	

}

void InGameScene::Draw()
{
	

	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			int color = 0;
			
			switch (m_StageData[y][x])
			{
			case Objecttype_Ground:
				// 0 �Ȃ�
				color = DrawGraph(x * CHIP_WIDTH , y * CHIP_HEIGHT , Ground, FALSE);
				break;
			case Objecttype_Wall:
				color = DrawGraph(x * CHIP_WIDTH , y * CHIP_HEIGHT , Wall, FALSE);
				//color = GetColor(255, 255, 255);	 // 1 ��(255, 255, 255)
				break;
			case Objecttype_Target:
				color = DrawGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, Target, FALSE);	 // 3 ��(255,   0,   0)
				break;
			case Objecttype_UnsetCrate:
				color = DrawGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, UnsetCreate, FALSE);	 // 4 ��(255,   0, 255)
				break;
			case Objecttype_SetCrate:
				color =DrawGraph(x * CHIP_WIDTH, y* CHIP_HEIGHT, SetCrate, FALSE);	 // 7 ��(  0, 255,   0)
				break;
			}

			//DrawGraph(x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, Ground, FALSE);

			// DrawBox�ŕ`�悷��Ȃ�n�ʈȊO�Ƃ�������ł�悢
			/*if (m_StageData[y][x] = Objecttype_Ground)
			{
				DrawBox(x * CHIP_WIDTH,
					y * CHIP_HEIGHT,
					x * CHIP_WIDTH + CHIP_WIDTH,
					y * CHIP_HEIGHT + CHIP_HEIGHT,
					color,
					TRUE);
			}*/
		}
	}
    
	

	//DrawGraph(0, 0, Wall, FALSE);

	

	DrawGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, Player01, FALSE);
	
	/*DrawBox(m_PlayerX * CHIP_WIDTH,
		m_PlayerY * CHIP_HEIGHT,
		m_PlayerX * CHIP_WIDTH + CHIP_WIDTH,
		m_PlayerY * CHIP_HEIGHT + CHIP_HEIGHT,
		GetColor(0, 0, 255),
		TRUE);*/
	if (IsClear())
	{
		DrawString(100, 240, "!! Game Clear !!", GetColor(255, 255, 0));
	}

	

	DrawString(20, 20, "InGameScene", GetColor(0, 0, 0));

	DrawFormatString(400,20, Color, "%d", ClickCounter);
	
}

bool InGameScene::IsEnd() const
{
	// @@Debug �J�ڊm�F�p�̉�����
	return (m_Step == STEP_END);
}

void InGameScene::step_StartJingle()
{
	set_Step(STEP_INPUT);

}

void InGameScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPush(KeyType_Clear))
	{
		set_Step(STEP_END);
		SceneManager::SetNextScene(SceneID_Result);
	}
	if (pInputMng->IsPush(KeyType_Reset))
	{
		Reset();
		ClickCounter = 0;
	}
	else if (pInputMng->IsPush(KeyType_Up))
	{
		Move(DirType_Up);
		ClickCounter += 1;
	}
	else if (pInputMng->IsPush(KeyType_Down))
	{
		Move(DirType_Down);
		ClickCounter += 1;
	}
	else if (pInputMng->IsPush(KeyType_Left))
	{
		Move(DirType_Left);
		ClickCounter += 1;
	}
	else if (pInputMng->IsPush(KeyType_Right))
	{
		Move(DirType_Right);
		ClickCounter += 1;
	}


	if(IsClear())
	{
		set_Step(STEP_CLEAR_JINGLE);
	}
}

void InGameScene::step_ClearJingle()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPush(KeyType_Enter))
	{
		set_Step(STEP_END);
		SceneManager::SetNextScene(SceneID_Result);
	}
}


// �Q�[���N���A����
// true = �N���A���Ă���
// false = ���N���A
bool InGameScene::IsClear() const
{
	// 2�dfor����m_StageData�̔z���������A
	// 1�ł�ObjctType_Unasetcreate������������false��Ԃ�
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			if (m_StageData[y][x] == Objecttype_UnsetCrate)
			{
				return false;
			}
		}
	}

	// for���𔲂��Ă�����ObjetType_UnsetCreate���Ȃ��������ƂɂȂ�A
	// �t��I�ɂ��ׂ�ObjectType_SetCreate��ԂɂȂ��Ă���(== �Q�[���N���A�j
	return true;
}

// ��������ԂɃ��Z�b�g
void InGameScene::Reset()
{
	// �R���X�g���N�^�ŏ��������Ă��镔������̂܂܂�����ֈڐ݂���
	// �X�e�[�W�f�[�^�����������
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			m_StageData[y][x] = g_SampleStage[y][x];
			if (m_StageData[y][x] == Objecttype_Player)
			{
				m_PlayerX = x;
				m_PlayerY = y;
				m_StageData[y][x] = Objecttype_Ground;
			}
		}
	}
	// �R���X�g���N�^��Reset��Ăяo��
	// step_Input�ŁAKeyType_Reset�������ꂽ��AReset()��Ăяo��

	// ���O���f�[�^��ǂݍ��񂾂�A�X�e�[�W�𑝂₷�ꍇ�͏�����e��l����K�v������
}

// �ړ�����
void InGameScene::Move(DirType dir_)
{
	// DirType���͈͓��
	if (dir_ >= DirType_Up && dir_ >= DirType_Max)
	{
		return;
	}

	int next_x = m_PlayerX;
	int next_y = m_PlayerY;
	int next2_x = m_PlayerX;
	int next2_y = m_PlayerY;

	switch (dir_)
	{
	case DirType_Up:
		next_y -= 1;
		next2_y -=2 ;
		break;
	case DirType_Down:
		next_y += 1;
		next2_y +=2;
		break;
	case DirType_Left:
		next_x -= 1;
		next2_x -= 2;
		break;
	case DirType_Right:
		next_x += 1;
		next2_x +=2 ;
		break;
	}

	// �ړ��悪��ʊO�Ȃ�A�֐��𔲂���
	if (next_x < 0 || next_y < 0 || next_x >(STAGE_WIDTH - 1) || next_y >(STAGE_HEIGHT -1))
	{
		return;
	}

	// �ʏ�ړ��i�ړ��悪�v���[���[�̏���}�b�v�`�b�v�̎�ނ�������m_PlayerX(Y)����ꂼ��next_x(y)�ŏ㏑��
	if (m_StageData[next_y][next_x] == Objecttype_Ground ||
		m_StageData[next_y][next_x] == Objecttype_Target)
	{
		m_PlayerX = next_x;
		m_PlayerY = next_y;
	}
	// �ړ���ɔ��i�N���[�g�j������ꍇ
	else if(m_StageData[next_y][next_x] == Objecttype_UnsetCrate ||
		    m_StageData[next_y][next_x] == Objecttype_SetCrate)
	{
		// 2�̐悪��ʊO���`�F�b�N
		if (next2_x < 0 || next2_y < 0 || next2_x >(STAGE_WIDTH - 1) || next_y >(STAGE_HEIGHT - 1))
		{
			return;
		}
		// 2��̈ړ��ł��Ȃ������`�F�b�N
		if (m_StageData[next2_y][next2_x] != Objecttype_Ground &&
			m_StageData[next2_y][next2_x] != Objecttype_Target)
		{
			return;
		}
		// �ƂȂ�̈ʒu��ύX����
		if (m_StageData[next_y][next_x] == Objecttype_UnsetCrate)
		{
			m_StageData[next_y][next_x] = Objecttype_Ground;
		}
		else
		{
			m_StageData[next_y][next_x] = Objecttype_Target;
		}

		if (m_StageData[next2_y][next2_x] == Objecttype_Ground)
		{
			m_StageData[next2_y][next2_x] = Objecttype_UnsetCrate;
		}
		else if(m_StageData[next2_y][next2_x] == Objecttype_Target)
		{
			m_StageData[next2_y][next2_x] = Objecttype_SetCrate;
		}


		m_PlayerX = next_x;
		m_PlayerY = next_y;
			
	}
}