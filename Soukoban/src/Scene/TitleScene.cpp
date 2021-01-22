#include"TitleScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"


enum 
{
	STEP_LOGO_IN,
	STEP_INPUT,
	STEP_END,
};

TitleScene::TitleScene()
{
	set_Step(STEP_LOGO_IN);
}

TitleScene::~TitleScene()
{
	
}

void TitleScene::Exec()
{
	switch (m_Step)
	{
	case STEP_LOGO_IN: step_LogoIn(); break;
	case STEP_INPUT:  step_Input();  break;
	default: break;
	}

	// @@Debug �J�ڊm�F�p�̉�����
	// m_Step��J�E���g�A�b�v
	/*InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPush(KeyType_Enter))
	{
		m_Step = 120;
		SceneManager::SetNextScene(SceneID_InGame);
	}*/
}

void TitleScene::Draw()
{
	DrawString(20, 20, "TitleScene", GetColor(0, 0, 0));

	DrawString(240,240, "Please press Enter", GetColor(0, 0, 0));
}


bool TitleScene::IsEnd() const
{
	// @@Debug �J�ڊm�F�p�̉�����
	return (m_Step == STEP_END);
}

void TitleScene::step_LogoIn()
{
	set_Step(STEP_INPUT);
}

void TitleScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPush(KeyType_Enter))
	{
		set_Step(STEP_END);
		SceneManager::SetNextScene(SceneID_InGame);
	}
}