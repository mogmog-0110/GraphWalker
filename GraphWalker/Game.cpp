# include "stdafx.h"
# include "Game.hpp"

// コンストラクタ
Game::Game(const InitData& init)
	: IScene{ init }, m_graph(RectF{100, 50, 1200, 800}, QuadrantMode::All), m_formula(-10, 10, 0.1)
{
	// 画面中央にグラフを配置
	m_graph.setScreenRect(m_graphRect);

	// グラフ上にプレイヤーを配置
	String name = generateObjectName(ObjectType::Player);
	m_objects[name] = ObjectFactory::createPlayer(m_world, m_idMap, name, m_graph.logicToScreen(Vec2{ -10, 2 }), 15);

	// StaticPlatformをテスト配置
	name = generateObjectName(ObjectType::StaticPlatform);
	m_objects[name] = ObjectFactory::createStaticPlatform(m_world, m_idMap, name, m_graph.logicToScreen(Vec2{ -10, 0 }), SizeF(50, 70));
	name = generateObjectName(ObjectType::StaticPlatform);
	m_objects[name] = ObjectFactory::createStaticPlatform(m_world, m_idMap, name, m_graph.logicToScreen(Vec2{ 10, 0 }), SizeF(50, 70));

	m_formulaInput.text = U"";

};

// 更新処理
void Game::update()
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

	SimpleGUI::TextBox(m_formulaInput, Vec2{ 60, 655 }, 900);
	if (SimpleGUI::Button(U"確定", Vec2{ 980, 655 }) || KeyEnter.down())
	{
		try
		{
			if (m_formula.setExpression(m_formulaInput.text))
			{
				m_formula.generatePoints(m_graph);
			}
			else
			{
				Print << U"[エラー] 数式が無効です";
			}
		}
		catch (const std::exception& e)
		{
			Print << U"[例外] 数式の処理中にエラー: " << Unicode::FromUTF8(e.what());
		}
	}
}

// 描画処理
void Game::draw() const
{
	m_graph.draw();
	m_formula.draw();

	for (const auto& [name, obj] : m_objects)
	{
		obj->draw();
	}
}

String Game::generateObjectName(ObjectType type)
{
	const String base = U"" + toString(type);
	const int32 count = m_nameCounters[type]++;
	return base + U"_" + Format(count);
}

String Game::toString(ObjectType type) const
{
	switch (type)
	{
	case ObjectType::Player:
		return U"Player";
	case ObjectType::StaticPlatform:
		return U"StaticPlatform";
	case ObjectType::Flag:
		return U"Flag";
	default:
		return U"None";
	}
}
