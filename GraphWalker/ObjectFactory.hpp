# pragma once
# include "Common.hpp"
# include "IGameObject.hpp"
# include "Player.hpp"
# include "StaticPlatform.hpp"

class ObjectFactory
{
public:
	static std::unique_ptr<IGameObject> createPlayer(P2World& world, HashTable<P2BodyID, String>& idMap, const String& name, Vec2 pos, double radius);
	static std::unique_ptr<IGameObject> createStaticPlatform(P2World& world, HashTable<P2BodyID, String>& idMap, const String& name, Vec2 pos, SizeF size);
private:

};
