#include "stdafx.h"
#include "Flag.hpp"

Flag::Flag(P2Body body, SizeF size)
	: m_body(body), m_size(size)
{
}

void Flag::update(double dt)
{
}

void Flag::draw() const
{
	//m_body.draw(m_color);
	texture.resized(m_size).drawAt(m_body.getPos());
}

void Flag::onCollision(const IGameObject& other, const Vec2& normal)
{
}

P2BodyID Flag::bodyID() const
{
	return m_body.id();
}

ObjectType Flag::getObjectType() const
{
	return ObjectType::Flag;
}

