﻿# pragma once
# include "Common.hpp"
# include "IGameObject.hpp"

class StaticPlatform : public IGameObject
{
public:
	StaticPlatform() = default;
	explicit StaticPlatform(P2Body body, SizeF size);

	void update(double dt) override;
	void draw() const override;
	void onCollision(const IGameObject& other, const Vec2& normal) override;
	P2BodyID bodyID() const override;
	ObjectType getObjectType() const override;



private:
	P2Body m_body;
	SizeF m_size;
	Color m_color = Palette::Black;
};
