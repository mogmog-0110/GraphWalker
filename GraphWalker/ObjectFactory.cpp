#include "stdafx.h"
#include "ObjectFactory.hpp"

String ObjectFactory::generateObjectName(ObjectType type)
{
	const String base = U"" + toString(type);
	const int32 count = m_nameCounters[type]++;
	return base + U"_" + Format(count);
}

void ObjectFactory::decreaseObjectNameCounter(ObjectType type)
{
	if (m_nameCounters[type] > 0)
	{
		m_nameCounters[type]--;
	}
	else
	{
		Print << U"[エラー] オブジェクト名カウンタが負の値になった。";
	}
}

void ObjectFactory::resetObjectNameCounter()
{
	for (auto& [type, count] : m_nameCounters)
	{
		count = 0;
	}
}

String ObjectFactory::toString(ObjectType type)
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

std::unique_ptr<IGameObject> ObjectFactory::createPlayer(P2World& world, HashTable<P2BodyID, String>& idMap, const String& name, Vec2 pos, double radius)
{
	P2Body body = world.createCircle(P2Dynamic, pos, radius, P2Material{ 0.5, 0.0, 1.0 });
	idMap[body.id()] = name;
	return std::make_unique<Player>(body, radius);
}

std::unique_ptr<IGameObject> ObjectFactory::createStaticPlatform(P2World& world, HashTable<P2BodyID, String>& idMap, const String& name, Vec2 pos, SizeF size)
{
	P2Body body = world.createRect(P2Static, pos, size);
	idMap[body.id()] = name;
	return std::make_unique<StaticPlatform>(body, size);
}

std::unique_ptr<IGameObject> ObjectFactory::createFlag(P2World& world, HashTable<P2BodyID, String>& idMap, const String& name, Vec2 pos, SizeF size)
{
	P2Body body = world.createRectSensor(P2Static, pos, size);
	idMap[body.id()] = name;
	return std::make_unique<Flag>(body, size);
}

std::unique_ptr<IGameObject> ObjectFactory::createStaticLineString(P2World& world, HashTable<P2BodyID, String>& idMap, const String& name, Vec2 pos, const LineString& shape)
{
	P2Body body = world.createLineString(P2Static, pos, shape);
	idMap[body.id()] = name;
	return std::make_unique<StaticLineString>(body);
}
