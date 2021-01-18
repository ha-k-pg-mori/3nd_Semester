#ifndef INGAMESCENE_H
#define INGAMESCENE_H

#include "DxLib.h"
#include "SceneBase.h"
// 定義ヘッター
#include "../Definition.h"

class InGameScene : public SceneBase
{
public:
	InGameScene();
	virtual~InGameScene();

public:
	virtual void Exec();  // 処理を行う
	virtual void Draw();  // 描画を行う

	virtual bool IsEnd() const;

	int Player00;
	int Player01;
	int Player02;
	int Player03;
	int Wall;
	int Ground;
	int Target;
	int UnsetCreate;
	int SetCrate;
	
	int ClickCounter = 0;

	int Animation;

	int Color = GetColor(0, 0, 0);

private:
	void step_StartJingle();
	void step_Input();
	void step_ClearJingle();

// 倉庫番に関係する関数群
private:
	// ゲームクリア判定
	bool IsClear()const;
	// 初期化状態にリセット
	void Reset();
	// 移動処理
	void Move( DirType dir_ );

	

private:
	int m_StageData[STAGE_HEIGHT][STAGE_WIDTH];
	int m_PlayerX; // 配列上のx
	int m_PlayerY; // 配列上のy	
};

#endif // !RESULTSCENE_H
