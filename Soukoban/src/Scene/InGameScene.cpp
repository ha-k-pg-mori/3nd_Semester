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

//int MosyonList[]
//{
//
//};




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
	// @@Debug 遷移確認用の仮処理
	// m_Stepをカウントアップ
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
				// 0 なし
				color = DrawGraph(x * CHIP_WIDTH , y * CHIP_HEIGHT , Ground, FALSE);
				break;
			case Objecttype_Wall:
				color = DrawGraph(x * CHIP_WIDTH , y * CHIP_HEIGHT , Wall, FALSE);
				//color = GetColor(255, 255, 255);	 // 1 白(255, 255, 255)
				break;
			case Objecttype_Target:
				color = DrawGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, Target, FALSE);	 // 3 赤(255,   0,   0)
				break;
			case Objecttype_UnsetCrate:
				color = DrawGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, UnsetCreate, FALSE);	 // 4 紫(255,   0, 255)
				break;
			case Objecttype_SetCrate:
				color =DrawGraph(x * CHIP_WIDTH, y* CHIP_HEIGHT, SetCrate, FALSE);	 // 7 緑(  0, 255,   0)
				break;
			}

			//DrawGraph(x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, Ground, FALSE);

			// DrawBoxで描画するなら地面以外という判定でもよい
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
    
	switch (m_PlayerX,m_PlayerY)
	{
	case DirType_Up:
		DrawGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, Player00, FALSE);
		break;
	case DirType_Down:
		DrawGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, Player01, FALSE);
		break;
	case DirType_Left:
		DrawGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, Player02, FALSE);
		break;
	case DirType_Right:
		DrawGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, Player03, FALSE);
		break;
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
	// @@Debug 遷移確認用の仮処理
	return (m_Step == STEP_END);
}

void InGameScene::step_StartJingle()
{
	set_Step(STEP_INPUT);

}

void InGameScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
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


// ゲームクリア判定
// true = クリアしている
// false = 未クリア
bool InGameScene::IsClear() const
{
	// 2重for文でm_StageDataの配列を検索し、
	// 1つでもObjctType_Unasetcreateが見つかったらfalseを返す
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

	// for文を抜けてきたらObjetType_UnsetCreateがなかったことになり、
	// 逆説的にすべてObjectType_SetCreate状態になっている(== ゲームクリア）
	return true;
}

// 初期化状態にリセット
void InGameScene::Reset()
{
	// コンストラクタで初期化している部分をそのままこちらへ移設する
	// ステージデータを初期化する
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
	// コンストラクタでResetを呼び出す
	// step_Inputで、KeyType_Resetが押されたら、Reset()を呼び出す

	// ※外部データを読み込んだり、ステージを増やす場合は処理内容を考える必要がある
}

// 移動処理
void InGameScene::Move(DirType dir_)
{
	// DirTypeが範囲内か
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

	// 移動先が画面外なら、関数を抜ける
	if (next_x < 0 || next_y < 0 || next_x >(STAGE_WIDTH - 1) || next_y >(STAGE_HEIGHT -1))
	{
		return;
	}

	// 通常移動（移動先がプレーヤーの乗れるマップチップの種類だったらm_PlayerX(Y)をそれぞれnext_x(y)で上書き
	if (m_StageData[next_y][next_x] == Objecttype_Ground ||
		m_StageData[next_y][next_x] == Objecttype_Target)
	{
		m_PlayerX = next_x;
		m_PlayerY = next_y;
	}
	// 移動先に箱（クレート）がある場合
	else if(m_StageData[next_y][next_x] == Objecttype_UnsetCrate ||
		    m_StageData[next_y][next_x] == Objecttype_SetCrate)
	{
		// 2つの先が画面外かチェック
		if (next2_x < 0 || next2_y < 0 || next2_x >(STAGE_WIDTH - 1) || next_y >(STAGE_HEIGHT - 1))
		{
			return;
		}
		// 2つ先の移動できない物かチェック
		if (m_StageData[next2_y][next2_x] != Objecttype_Ground &&
			m_StageData[next2_y][next2_x] != Objecttype_Target)
		{
			return;
		}
		// となりの位置を変更する
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