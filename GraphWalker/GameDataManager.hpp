# pragma once
# include "Common.hpp"

struct GameData
{
	int32 stageCount = 3;
	int32 currentStage = 2;
	Array<bool> stageClearFlags = Array<bool>(stageCount, false);

	bool resetFlag = false; // ステージリセットフラグ
	bool isPuttingFormula = false; // 数式入力中フラグ
};

class GameDataManager
{
public:
	// グローバルアクセス関数
	static GameData& get()
	{
		static GameData instance;
		return instance;
	}

	// コピー・ムーブ禁止
	GameDataManager() = delete;
	GameDataManager(const GameDataManager&) = delete;
	GameDataManager& operator=(const GameDataManager&) = delete;
};
