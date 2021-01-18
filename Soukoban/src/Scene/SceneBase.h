#ifndef SCENEBASE_H
#define SCENEBASE_H

class SceneBase
{
public:
	SceneBase();
	virtual~SceneBase();

public:
	// 処理内容は派生クラス毎に違うので、
	// 純粋仮想関数として宣言しておく
	virtual void Exec() = 0;  // 処理を行う
	virtual void Draw() = 0;  // 描画を行う

	virtual bool IsEnd() const; // シーンが終了したかどうかを返す

protected:
	void set_Step(int step_);

protected:
	int m_Step;   // 処理内容を管理する変数
};


#endif // !SCENEBASE_H

