#include "stdafx.h"
#include "StageBuilder.hpp"

void StageBuilder::build(int32 stage,
	P2World& world,
	HashTable<String, std::shared_ptr<IGameObject>>& objects,
	HashTable<P2BodyID, String>& idMap,
	const GraphArea& graph)
{
	ObjectFactory::resetObjectNameCounter();

	if (stage == 1)
	{
		String name = ObjectFactory::generateObjectName(ObjectType::Player);
		objects[name] = ObjectFactory::createPlayer(world, idMap, name, graph.logicToScreen({ -10, 2 }), 15);

		name = ObjectFactory::generateObjectName(ObjectType::StaticPlatform);
		objects[name] = ObjectFactory::createStaticPlatform(world, idMap, name, graph.logicToScreen({ -10, 0 }), SizeF(50, 65));
		name = ObjectFactory::generateObjectName(ObjectType::StaticPlatform);
		objects[name] = ObjectFactory::createStaticPlatform(world, idMap, name, graph.logicToScreen({ 10, 0 }), SizeF(50, 65));

		name = ObjectFactory::generateObjectName(ObjectType::Flag);
		objects[name] = ObjectFactory::createFlag(world, idMap, name, graph.logicToScreen({ 10, 1.9 }), SizeF(30, 50));
	}
	else if (stage == 2)
	{
		String name = ObjectFactory::generateObjectName(ObjectType::Player);
		objects[name] = ObjectFactory::createPlayer(world, idMap, name, graph.logicToScreen({ -13, 7 }), 15);
		name = ObjectFactory::generateObjectName(ObjectType::StaticPlatform);
		objects[name] = ObjectFactory::createStaticPlatform(world, idMap, name, graph.logicToScreen({ -13, 5 }), SizeF(50, 65));
		name = ObjectFactory::generateObjectName(ObjectType::StaticPlatform);
		objects[name] = ObjectFactory::createStaticPlatform(world, idMap, name, graph.logicToScreen({ 13, -5 }), SizeF(50, 65));
		name = ObjectFactory::generateObjectName(ObjectType::Flag);
		objects[name] = ObjectFactory::createFlag(world, idMap, name, graph.logicToScreen({ 13, -3.1 }), SizeF(30, 50));
	}
	else if (stage == 3)
	{
		String name = ObjectFactory::generateObjectName(ObjectType::Player);
		objects[name] = ObjectFactory::createPlayer(world, idMap, name, graph.logicToScreen({ -13, -4 }), 15);
		name = ObjectFactory::generateObjectName(ObjectType::StaticPlatform);
		objects[name] = ObjectFactory::createStaticPlatform(world, idMap, name, graph.logicToScreen({ -13, -5 }), SizeF(50, 65));
		name = ObjectFactory::generateObjectName(ObjectType::StaticPlatform);
		objects[name] = ObjectFactory::createStaticPlatform(world, idMap, name, graph.logicToScreen({ 13, 5 }), SizeF(50, 65));
		name = ObjectFactory::generateObjectName(ObjectType::Flag);
		objects[name] = ObjectFactory::createFlag(world, idMap, name, graph.logicToScreen({ 13, 6.9 }), SizeF(30, 50));
	}

	// 追加ステージは else if (stage == 2) のように増やす
}

