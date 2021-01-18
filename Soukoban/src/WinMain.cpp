#include"DxLib.h"
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"
#include "Manager/InputManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DXライブラリ初期化処理
	SetOutApplicationLogValidFlag(FALSE);  // ログ出力
	ChangeWindowMode(TRUE);                // ウィンドウモード
	SetGraphMode(640, 480, 32);            // 画面モード変更
	SetBackgroundColor(125,125, 125);     // 背景色                 
	SetMainWindowText("My倉庫番");     // メニューバーのタイトル

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1){return -1;}

	// 描画先を裏の画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームを始める前の初期化処理
	GameManager::CreateInstance();
	InputManager::CreateInstance();
	SceneManager::CreateInstance();
	


	// ゲームループ
	while (true)
	{
		// Windowsのメッセージ処理に失敗したか、閉じこめられたら終了
		if (ProcessMessage() != 0) { break; }

		// DxLibのお約束：画面クリア
		ClearDrawScreen();
		clsDx();

		InputManager* pInputMng = InputManager::GetInstance();
		SceneManager* pSceneMng = SceneManager::GetInstance();

		// 処理
		pInputMng->Update();
		pSceneMng->Exec();

		// 表示
		pSceneMng->Draw();

		// DxLibのお約束：画面更新
		ScreenFlip();
	}

	

	InputManager::DestroyInstance();
	InputManager::DestroyInstance();
	GameManager::DestroyInstance();

	

	// キー入力待ち
	WaitKey();				

	// ＤＸライブラリ使用の終了処理
	DxLib_End();				

	// ソフトの終了 
	return 0;				
}