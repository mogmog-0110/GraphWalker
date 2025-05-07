#include "stdafx.h"
#include "Player.hpp"

Player::Player(P2Body body)
	: m_body(body)
{
}

void Player::update(double dt)
{
	move(dt);
	jump();
}

void Player::draw() const
{
	m_body.draw(m_color);
}

void Player::onCollision(const IGameObject& other, const Vec2& normal)
{
	if (other.getObjectType() == ObjectType::StaticPlatform && normal.y < -0.5 )
	{
		m_isOnGround = true;
	}
}

P2BodyID Player::bodyID() const
{
	return m_body.id();
}

ObjectType Player::getObjectType() const
{
	return ObjectType::Player;
}

void Player::move(double dt)
{
	if (KeyLeft.pressed())
	{
		m_body.applyForce(Vec2{-1, 0} * m_speed * dt);
	}

	if (KeyRight.pressed())
	{
		m_body.applyForce(Vec2{ 1, 0 } * m_speed * dt);
	}	
}

void Player::jump()
{
	if (KeyUp.down() && m_isOnGround)
	{
		m_isOnGround = false;
		m_body.applyLinearImpulse(Vec2{ 0, -1 } * m_jump);
	}
}
