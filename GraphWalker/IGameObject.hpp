# pragma once
# include "Common.hpp"

// 動くオブジェクトの共通親

class IGameObject
{
public:
	virtual ~IGameObject() = default;
	virtual void update(double dt) = 0;
	virtual void draw() const = 0;
	virtual void onCollision(const IGameObject& other, const Vec2& normal) = 0;
	virtual P2BodyID bodyID() const = 0;
	virtual ObjectType getObjectType() const = 0;
};
