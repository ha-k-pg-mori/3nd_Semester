#include "ResultScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"



enum
{
	STEP_LOGO_IN,
	STEP_INPUT,
	STEP_END,
};

ResultScene::ResultScene()
{
	set_Step(STEP_LOGO_IN);
	Result = LoadGraph("data/Clear.png");
}

ResultScene::~ResultScene()
{
	switch (m_Step)
	{
	//case STEP_LOGO_IN: step_LogoIn(); break;
	case STEP_INPUT:  step_Input();  break;
	default: break;
	}
	Result;

}

void ResultScene::Exec()
{
	// @@Debug �J�ڊm�F�p�̉�����
	// m_Step��J�E���g�A�b�v
	/*m_Step++;
	if (m_Step >= 120)
	{
		SceneManager::SetNextScene(SceneID_Title);
	}*/
	switch (m_Step)
	{
		//case STEP_LOGO_IN: step_LogoIn(); break;
	case STEP_INPUT:  step_Input();  break;
	default: break;
	}
}

void ResultScene::Draw()
{
	
	//DrawGraph(20, 20, Result, FALSE);

	LoadGraphScreen(120,120, "data/Clear.png", TRUE);

	DrawString(20, 20, "ResultScene", GetColor(0, 0, 0));

	//DrawFormatString(400, 20, Color, "%d", ClickCounter);
}

bool ResultScene::IsEnd() const
{
	// @@Debug �J�ڊm�F�p�̉�����
	return (m_Step == STEP_END);
}

void ResultScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPush(KeyType_Enter))
	{
		set_Step(STEP_END);
		SceneManager::SetNextScene(SceneID_Title);
	}
}