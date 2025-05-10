#include "stdafx.h"
#include "StaticLineString.hpp"

StaticLineString::StaticLineString(P2Body body)
	: m_body(body)
{
}

void StaticLineString::update(double dt)
{
}

void StaticLineString::draw() const
{
	m_body.draw(m_color);
}

void StaticLineString::onCollision(const IGameObject& other, const Vec2& normal)
{
}

P2BodyID StaticLineString::bodyID() const
{
	return m_body.id();
}

ObjectType StaticLineString::getObjectType() const
{
	return ObjectType::StaticLineString;
}
