#include "stdafx.h"
#include "ObjectFactory.hpp"

std::unique_ptr<IGameObject> ObjectFactory::createPlayer(P2World& world, HashTable<P2BodyID, String>& idMap, const String& name, Vec2 pos, double radius)
{
	P2Body body = world.createCircle(P2Dynamic, pos, radius, P2Material{0.5, 0.0, 1.0});
	idMap[body.id()] = name;
	return std::make_unique<Player>(body);
}

std::unique_ptr<IGameObject> ObjectFactory::createStaticPlatform(P2World& world, HashTable<P2BodyID, String>& idMap, const String& name, Vec2 pos, SizeF size)
{
	P2Body body = world.createRect(P2Static, pos, size);
	idMap[body.id()] = name;
	return std::make_unique<StaticPlatform>(body);
}
