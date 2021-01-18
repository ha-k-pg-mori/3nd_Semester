#ifndef DEFINITION_H
#define DEFINITION_H

// シーンID
enum SceneID
{
	SceneID_Title,      // タイトル
	SceneID_InGame,     // インゲーム
	SceneID_Result,     // リザルト

	SceneID_Max,
	SceneID_Invalid,    // 無効値
};
// -------------------------------------
// 倉庫番用の定義
const int STAGE_WIDTH = 11;
const int STAGE_HEIGHT = 13;

// マップチップの縦描画サイズ
const int CHIP_WIDTH = 32;
const int CHIP_HEIGHT = 32;



// オブジェクト種類
// 　　　　0  地面
//         1　壁
//         2　プレイヤーの初期地点
//         3　クレート配置場所
//         4　未配置のクレート
//         7　配置済みのクレート
// 　　　　　（配置場所'3'+未配置クレート'4' = 7)

enum ObjectType
{
	Objecttype_Ground,       // 0
	Objecttype_Wall,		 // 1
	Objecttype_Player,		 // 2
	Objecttype_Target,		 // 3
	Objecttype_UnsetCrate,	 // 4
	Objecttype_SetCrate,	 // 7
};

// 移動方向
enum DirType
{
	DirType_Up, 
	DirType_Down,
	DirType_Left,
	DirType_Right,
	
	// 画像読み込みで使用する
	DirType_Max,
};

#endif // !DEFINITION_H

