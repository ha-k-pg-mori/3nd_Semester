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
	virtual void Exec();  // ˆ—‚ğs‚¤
	virtual void Draw();  // •`‰æ‚ğs‚¤

	virtual bool IsEnd() const;

	int Result;

private:
	void step_Input();
};

#endif // !RESULTSCENE_H



