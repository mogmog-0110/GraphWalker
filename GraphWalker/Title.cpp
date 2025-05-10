#include "stdafx.h"
#include "Title.hpp"

// コンストラクタ
Title::Title(const InitData& init)
	: IScene{ init }
{
}

// 更新処理
void Title::update()
{
	const int32 stageCount = GameDataManager::get().stageCount;
	const Vec2 basePos = Vec2{ Scene::Center().x - 100, Scene::Center().y };
	const int32 buttonWidth = 200;
	const int32 buttonHeight = 40;
	const int32 padding = 10;

	// 上下キーで選択ステージを切り替え
	if (KeyUp.down()) {
		m_selectedStage = (m_selectedStage - 1 + stageCount) % stageCount;
	}
	if (KeyDown.down()) {
		m_selectedStage = (m_selectedStage + 1) % stageCount;
	}

	for (int32 i = 0; i < stageCount; ++i)
	{
		Vec2 pos = basePos + Vec2{ 0, i * (buttonHeight + padding) };
		String label = U"ステージ {}"_fmt(i + 1);

		// ハイライト色
		const ColorF bgColor = (i == m_selectedStage) ? ColorF{ 0.6, 0.9, 1.0 } : ColorF{ 1.0 };

		// 手動クリック or Enterキーで選択中ステージを起動
		if (SimpleGUI::Button(label, pos, buttonWidth)
			|| (i == m_selectedStage && KeyEnter.down()))
		{
			GameDataManager::get().currentStage = i + 1;
			changeScene(State::Game, 0.5s);
		}
	}

	// 「やめる」ボタン
	Vec2 exitPos = basePos + Vec2{ 0, stageCount * (buttonHeight + padding) + 20 };
	if (SimpleGUI::Button(U"やめる", exitPos, buttonWidth))
	{
		System::Exit();
	}
}


// 描画処理
void Title::draw() const
{
	FontAsset(U"TitleFont")(U"Graph Walker").drawAt(Scene::Center().x, Scene::Center().y - 200, Palette::Black);
}


