# pragma once
# include "Common.hpp"
# include "IGameObject.hpp"

class StaticLineString : public IGameObject
{
public:
	StaticLineString() = default;
	explicit StaticLineString(P2Body body);

	void update(double dt) override;
	void draw() const override;
	void onCollision(const IGameObject& other, const Vec2& normal) override;
	P2BodyID bodyID() const override;
	ObjectType getObjectType() const override;



private:
	P2Body m_body;
	Color m_color = Palette::Blue;
};
