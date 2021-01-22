#include"DxLib.h"
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"
#include "Manager/InputManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DX���C�u��������������
	SetOutApplicationLogValidFlag(FALSE);  // ���O�o��
	ChangeWindowMode(TRUE);                // �E�B���h�E���[�h
	SetGraphMode(640, 480, 32);            // ��ʃ��[�h�ύX
	SetBackgroundColor(125,125, 125);     // �w�i�F                 
	SetMainWindowText("倉庫番");     // ���j���[�o�[�̃^�C�g��

	// �c�w���C�u��������������
	if (DxLib_Init() == -1){return -1;}

	// �`���𗠂̉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[����n�߂�O�̏���������
	GameManager::CreateInstance();
	InputManager::CreateInstance();
	SceneManager::CreateInstance();
	
	

	// �Q�[�����[�v
	while (true)
	{
		// Windows�̃��b�Z�[�W�����Ɏ��s�������A�����߂�ꂽ��I��
		if (ProcessMessage() != 0) { break; }

		// DxLib�̂��񑩁F��ʃN���A
		ClearDrawScreen();
		clsDx();

		InputManager* pInputMng = InputManager::GetInstance();
		SceneManager* pSceneMng = SceneManager::GetInstance();

		// ����
		pInputMng->Update();
		pSceneMng->Exec();

		// �\��
		pSceneMng->Draw();

		// DxLib�̂��񑩁F��ʍX�V
		ScreenFlip();
	}

	

	InputManager::DestroyInstance();
	InputManager::DestroyInstance();
	GameManager::DestroyInstance();

	

	// �L�[���͑҂�
	WaitKey();				

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();				

	// �\�t�g�̏I�� 
	return 0;				
}