# pragma once
# include "Common.hpp"
# include "IGameObject.hpp"
# include "Player.hpp"
# include "StaticPlatform.hpp"
# include "StaticLineString.hpp"
# include "Flag.hpp" 

class ObjectFactory
{
public:
	static String generateObjectName(ObjectType);
	static void decreaseObjectNameCounter(ObjectType type);
	static void resetObjectNameCounter();

	static std::unique_ptr<IGameObject> createPlayer(P2World& world, HashTable<P2BodyID, String>& idMap, const String& name, Vec2 pos, double radius);
	static std::unique_ptr<IGameObject> createStaticPlatform(P2World& world, HashTable<P2BodyID, String>& idMap, const String& name, Vec2 pos, SizeF size);
	static std::unique_ptr<IGameObject> createFlag(P2World& world, HashTable<P2BodyID, String>& idMap, const String& name, Vec2 pos, SizeF size);
	static std::unique_ptr<IGameObject> createStaticLineString(P2World& world, HashTable<P2BodyID, String>& idMap, const String& name, Vec2 pos, const LineString& shape);


private:
	static HashTable<ObjectType, int32> m_nameCounters;
	static String toString(ObjectType);

};
