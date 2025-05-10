# pragma once
# include "Common.hpp"
# include "Asset.hpp"
# include "IGameObject.hpp"
# include "ObjectFactory.hpp"
# include "GraphArea.hpp"
# include "FormulaVisualizer.hpp"
# include "GameDataManager.hpp"
# include "StageBuilder.hpp"

class Game : public App::Scene
{
public:
	Game(const InitData& init);

	void update() override;
	void draw() const override;

private:
	GameState m_gameState = GameState::Playing;
	bool m_isClear = false;
	P2World m_world{ 980.0 };
	Array<P2Body> m_bodies;

	HashTable<P2BodyID, String> m_idMap;
	HashTable<String, std::shared_ptr<IGameObject>> m_objects;

	GraphArea m_graph;
	RectF m_graphRect = RectF{ 60, 30, baseSize.x - 280, baseSize.y - 120 };

	FormulaVisualizer m_formula;
	TextEditState m_formulaInput;
	Optional<int32> m_nextFocusIndex;

	Array<String> m_formulaHistory;



	double m_stepTime = (1.0 / 200.0); // 物理演算のシミュレーションステップ
	double m_accumulatedTime = 0.0; //物理演算のシミュレーション蓄積時間

	void generateStaticFromFormula();
	void resetStage();
};
