#ifndef TNPUT_MANAGER_H
#define TNPUT_MANAGER_H

#include "../KeyDefinition.h"

// 入力管理クラス
class InputManager
{
private:
	// キー状態構造
	struct KeyState
	{
		bool old;  // 前回チェック時のフラグ情報

		bool push; // 押された瞬間
		bool on;   // 押下されている
		bool pull; // 離された瞬間

		KeyState()
			:old(false)
			, push(false)
			, on(false)
			, pull(false)
		{};
	};

public:
	// キー入力更新
	void Update();

	bool IsPush(KeyType key) const;

	bool IsOn(KeyType key) const;

	bool IsPull(KeyType key) const;

private:
	KeyState m_State[KeyType_Max];

public:
	// staticeなmpInstanceへのアクセス用語数群
	// 実体を作る関数
	static void CreateInstance();
	// 実体を破棄する関数
	static void DestroyInstance();
	// 実体があるかを確認する関数
	static bool IsNull();

	static InputManager* GetInstance();

private:
	InputManager();
	~InputManager();

private:
	// staticにすることで、クラスで1つだけであることを保証する
	static InputManager* m_pInstance;
};

#endif // !TNPUT_MANAGER_H