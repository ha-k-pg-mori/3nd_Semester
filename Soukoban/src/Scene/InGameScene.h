#ifndef INGAMESCENE_H
#define INGAMESCENE_H

#include "DxLib.h"
#include "SceneBase.h"
// ��`�w�b�^�[
#include "../Definition.h"

class InGameScene : public SceneBase
{
public:
	InGameScene();
	virtual~InGameScene();

public:
	virtual void Exec();  // ������s��
	virtual void Draw();  // �`���s��

	virtual bool IsEnd() const;

	int Player00;
	int Player01;
	int Player02;
	int Player03;
	int Player04;
	int Player05;
	int Player06;
	int Player07;
	int Player08;
	int Player09;
	int Player10;
	int Player11;
	
	int Wall;
	int Ground;
	int Target;
	int UnsetCreate;
	int SetCrate;
	
	int ClickCounter = 0;

	int Direction;
	int Animation;

	int Color = GetColor(0, 0, 0);

private:
	void step_StartJingle();
	void step_Input();
	void step_ClearJingle();

// �q�ɔԂɊ֌W����֐��Q
private:
	// �Q�[���N���A����
	bool IsClear()const;
	// ��������ԂɃ��Z�b�g
	void Reset();
	// �ړ�����
	void Move( DirType dir_ );

	

private:
	int m_StageData[STAGE_HEIGHT][STAGE_WIDTH];
	int m_PlayerX; // �z����x
	int m_PlayerY; // �z����y	
};

#endif // !RESULTSCENE_H
