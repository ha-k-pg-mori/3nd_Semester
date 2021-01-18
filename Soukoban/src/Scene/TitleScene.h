#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();

	

public:
	virtual void Exec();  // 処理を行う
	virtual void Draw();  // 描画を行う

	virtual bool IsEnd() const; // シーンが終了したかどうかを返す

private:
	void step_LogoIn();
	void step_Input();

};

#endif // !TITLESCENE_H



