#ifndef RESULTSCENE_H
#define RESULTSCENE_H

#include "SceneBase.h"
#include "InGameScene.h"

class ResultScene : public SceneBase
{
public:
	ResultScene();
	virtual~ResultScene();
	
public:
	virtual void Exec();  // 処理を行う
	virtual void Draw();  // 描画を行う

	virtual bool IsEnd() const;

	int Result;

private:
	void step_Input();
};

#endif // !RESULTSCENE_H



