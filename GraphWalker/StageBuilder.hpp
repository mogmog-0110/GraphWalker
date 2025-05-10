# pragma once
# include "Common.hpp"
# include "IGameObject.hpp"
# include "ObjectFactory.hpp"
# include "GraphArea.hpp"

class StageBuilder
{
public:
	static void build(int32 stageNumber,
		P2World& world,
		HashTable<String, std::shared_ptr<IGameObject>>& objects,
		HashTable<P2BodyID, String>& idMap,
		const GraphArea& graph);
};
