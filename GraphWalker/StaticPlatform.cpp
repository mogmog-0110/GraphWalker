#include "stdafx.h"
#include "StaticPlatform.hpp"

StaticPlatform::StaticPlatform(P2Body body, SizeF size)
	: m_body(body), m_size(size)
{
}

void StaticPlatform::update(double dt)
{
}

void StaticPlatform::draw() const
{
	m_body.draw(m_color);
}

void StaticPlatform::onCollision(const IGameObject& other, const Vec2& normal)
{
}

P2BodyID StaticPlatform::bodyID() const
{
	return m_body.id();
}

ObjectType StaticPlatform::getObjectType() const
{
	return ObjectType::StaticPlatform;
}
