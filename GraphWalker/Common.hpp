# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.16

// シーンの列挙型
enum class State
{
	Title,
	Game,
};

enum class ObjectType
{
	Player,
	StaticPlatform,
	Flag
};

// 使用する象限の種類
enum class QuadrantMode
{
	All,
	Q1,
	Q1_Q2,
	Q1_Q4
};

// 画面サイズ
const Size baseSize = {1280, 720};

// 共有データ
struct GameData
{
	// ステージ数
	int32 stageCount = 3;

	// ステージのクリアフラグ
	Array<bool> stageClearFlags = Array<bool>(stageCount, false);
};

using App = SceneManager<State, GameData>;
