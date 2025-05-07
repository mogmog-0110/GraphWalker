# pragma once
# include "Common.hpp"
# include "Asset.hpp"
# include "IGameObject.hpp"
# include "ObjectFactory.hpp"
# include "GraphArea.hpp"
# include "FormulaVisualizer.hpp"

class Game : public App::Scene
{
public:
	Game(const InitData& init);

	void update() override;
	void draw() const override;

private:
	P2World m_world{ 980.0 };
	Array<P2Body> m_bodies;

	HashTable<P2BodyID, String> m_idMap;
	HashTable<String, std::unique_ptr<IGameObject>> m_objects;
	HashTable<ObjectType, int32> m_nameCounters;

	GraphArea m_graph;
	RectF m_graphRect = RectF{ 60, 30, baseSize.x - 280, baseSize.y - 120 };

	FormulaVisualizer m_formula;
	TextEditState m_formulaInput;

	double m_stepTime = (1.0 / 200.0); // 物理演算のシミュレーションステップ
	double m_accumulatedTime = 0.0; //物理演算のシミュレーション蓄積時間

	String generateObjectName(ObjectType type);
	String toString(ObjectType type) const;



};
