# include "stdafx.h"
# include "Game.hpp"

// 静的メンバ変数の定義
HashTable<ObjectType, int32> ObjectFactory::m_nameCounters;

// コンストラクタ
Game::Game(const InitData& init)
	: IScene{ init }, m_graph(RectF{ 100, 50, 1200, 800 }, QuadrantMode::All), m_formula(-20, 20, 0.1)
{
	// 画面中央にグラフを配置
	m_graph.setScreenRect(m_graphRect);

	// シザー矩形の範囲を登録する
	Graphics2D::SetScissorRect(m_graphRect.asRect());

	// ステージ生成
	StageBuilder::build(
		GameDataManager::get().currentStage,
		m_world,
		m_objects,
		m_idMap,
		m_graph);

	// クリアフラグを初期化
	GameDataManager::get().stageClearFlags[GameDataManager::get().currentStage - 1] = false;
};

// 更新処理
void Game::update()
{
	switch (m_gameState)
	{
	case GameState::Playing:
	{
		for (m_accumulatedTime += Scene::DeltaTime(); m_stepTime <= m_accumulatedTime; m_accumulatedTime -= m_stepTime)
		{
			// 2D 物理演算のワールドを更新する
			m_world.update(m_stepTime);

			// GameObjectを更新する
			for (auto& [name, obj] : m_objects)
			{
				obj->update(m_stepTime);
			}

			// 衝突チェック
			for (auto&& [pair, collision] : m_world.getCollisions())
			{
				const auto itA = m_idMap.find(pair.a);
				const auto itB = m_idMap.find(pair.b);

				if (itA != m_idMap.end() && itB != m_idMap.end())
				{
					auto& objA = *m_objects[itA->second];
					auto& objB = *m_objects[itB->second];


					objA.onCollision(objB, collision.normal());
					objB.onCollision(objA, collision.normal());
				}
			}
		}

		if (m_nextFocusIndex)
		{
			m_formulaInput.active = true;
			m_nextFocusIndex.reset();
		}

		if (!m_formulaInput.active && KeyTab.down())
		{
			m_nextFocusIndex = 0;
		}

		const bool wasActive = m_formulaInput.active;
		GameDataManager::get().isPuttingFormula = m_formulaInput.active;
		SimpleGUI::TextBox(m_formulaInput, Vec2{ 235, 655 }, 700);

		if (wasActive && !m_formulaInput.active && m_formulaInput.tabKey)
		{
			m_nextFocusIndex = 0;
		}

		bool isValid = false;

		try
		{
			if (not m_formulaInput.text.isEmpty() && m_formula.setExpression(m_formulaInput.text))
			{
				m_formula.generatePoints(m_graph);
				isValid = true;
			}
			else
			{
				//Print << U"[エラー] 数式が空、または無効です";
			}
		}
		catch (const std::exception& e)
		{
			//Print << U"[例外] 数式の処理中にエラー: " << Unicode::FromUTF8(e.what());
		}

		if ((SimpleGUI::Button(U"確定", Vec2{ 980, 655 }) || KeyEnter.down()) && isValid)
		{
			generateStaticFromFormula();
			m_formulaInput.text.clear();
		}

		if (GameDataManager::get().stageClearFlags[GameDataManager::get().currentStage - 1])
		{
			m_gameState = GameState::Clear;
		}

		// Rキーで手動リセット
		if (KeyR.down() && !GameDataManager::get().isPuttingFormula)
		{
			GameDataManager::GameDataManager::get().resetFlag = true;;
		}

		if (GameDataManager::get().resetFlag)
		{
			resetStage();
			GameDataManager::get().resetFlag = false;
		}

		break;
	}
	case GameState::Clear:
	{
		GameDataManager::get().stageClearFlags[GameDataManager::get().currentStage - 1] = true;
		if (KeyEnter.down())
		{
			changeScene(State::Title, 0.5s);
		}
	}
	}

}

// 描画処理
void Game::draw() const
{
	{
		RasterizerState rs = RasterizerState::Default2D;
		rs.scissorEnable = true;

		// シザー矩形を有効化する
		const ScopedRenderStates2D rasterizer{ rs };

		m_graph.draw();
		m_formula.draw();

		for (const auto& [name, obj] : m_objects)
		{
			obj->draw();
		}
	}

	// 文字の表示
	FontAsset(U"SmallFont")(U"F(x) = ").draw(Vec2{ 120, 655 }, Palette::Black);


	// クリアテキストの表示
	if (GameDataManager::get().stageClearFlags[GameDataManager::get().currentStage - 1])
	{
		FontAsset(U"TitleFont")(U"CLEAR").drawAt(m_graph.logicToScreen(Vec2{ 0, 0 }), Palette::Red);
	}

	const Font& font = FontAsset(U"TextFont");


	// ステージ名の表示
	FontAsset(U"TextFont")(U"Stage" + ToString(GameDataManager::get().currentStage)).draw(Vec2{ 1080, 30 }, Palette::Black);

	// 操作説明の表示
	Vec2 basePos{ 1080, 80 };
	font(U"[操作説明]").draw(basePos, Palette::Black);
	font(U"Tabキー : 入力欄へ移動").draw(basePos + Vec2{ 0, 30 }, Palette::Black);
	font(U"Enterキー : 数式を確定").draw(basePos + Vec2{ 0, 60 }, Palette::Black);
	font(U"Escキー : ゲーム終了").draw(basePos + Vec2{ 0, 90 }, Palette::Black);
	font(U"Rキー : ステージリセット").draw(basePos + Vec2{ 0, 120 }, Palette::Black);
	font(U"←キー →キー: 左右移動").draw(basePos + Vec2{ 0, 150 }, Palette::Black);
	font(U"↑ : ジャンプ").draw(basePos + Vec2{ 0, 180 }, Palette::Black);

	// 数式履歴の表示
	Vec2 pos{ 1080, 310 };
	font(U"[数式履歴]").draw(pos, Palette::Black);

	for (size_t i = 0; i < m_formulaHistory.size(); ++i)
	{
		font(Format(i + 1, U". ", m_formulaHistory[i])).draw(pos + Vec2{ 0, 30 + 24 * i }, Palette::Black);
	}

}

void Game::generateStaticFromFormula()
{
	//// すでに生成された グラフオブジェクトを削除
	//Array<String> toErase;
	//for (const auto& [name, obj] : m_objects)
	//{
	//	// オブジェクト種別が LineString に該当するものを削除対象に
	//	if (obj->getObjectType() == ObjectType::StaticLineString)
	//	{
	//		toErase << name;
	//	}
	//}
	//for (const auto& name : toErase)
	//{
	//	m_idMap.erase(m_objects[name]->bodyID());
	//	m_objects.erase(name);
	//	ObjectFactory::decreaseObjectNameCounter(ObjectType::StaticLineString);
	//}

	// 点列から LineString を構築
	LineString graphLine;
	Vec2 startPos = { 0, 0 };
	for (const auto& pos : m_formula.getPoints())
	{
		graphLine << pos;
	}

	// 登録
	const String name = ObjectFactory::generateObjectName(ObjectType::StaticLineString);
	m_objects[name] = ObjectFactory::createStaticLineString(m_world, m_idMap, name, startPos, graphLine);

	// 数式を履歴に追加（重複除外・最大10件）
	if (not m_formulaInput.text.isEmpty())
	{
		if (m_formulaHistory.isEmpty() || m_formulaHistory.back() != m_formulaInput.text)
		{
			m_formulaHistory << m_formulaInput.text;
			if (m_formulaHistory.size() > 10)
			{
				m_formulaHistory.pop_front();
			}
		}
	}

}

void Game::resetStage()
{
	// 全データ初期化
	//m_world.clear();
	m_objects.clear();
	m_idMap.clear();
	ObjectFactory::resetObjectNameCounter();

	// 数式入力と描画状態のクリア
	m_formulaInput.text.clear();
	m_formula.clearPoints();
	m_formulaHistory.clear();

	// ステージ構築
	StageBuilder::build(
		GameDataManager::get().currentStage,
		m_world,
		m_objects,
		m_idMap,
		m_graph);

	// 状態を戻す
	m_gameState = GameState::Playing;
}

