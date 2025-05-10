#include "stdafx.h"
#include "Player.hpp"

Player::Player(P2Body body, double radius)
	: m_body(body), m_radius(radius)
{
}

void Player::update(double dt)
{
	if (!GameDataManager::get().isPuttingFormula)
	{
		move(dt);
		jump();
	}

	if (m_body.getPos().y > 1200) // 画面外・落下判定
	{
		GameDataManager::get().resetFlag = true;
	}
}

void Player::draw() const
{
	m_body.draw(m_color);
	//texture.resized(m_radius * 2.0).drawAt(m_body.getPos());
}

void Player::onCollision(const IGameObject& other, const Vec2& normal)
{
	if (other.getObjectType() == ObjectType::StaticPlatform && normal.y < -0.5)
	{
		m_isOnGround = true;
	}

	if (other.getObjectType() == ObjectType::StaticLineString && normal.y < -0.5)
	{
		m_isOnGround = true;
	}

	if (other.getObjectType() == ObjectType::Flag)
	{
		GameDataManager::get().stageClearFlags[GameDataManager::get().currentStage - 1] = true;
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
		m_body.applyForce(Vec2{ -1, 0 } *m_speed * dt);
	}

	if (KeyRight.pressed())
	{
		m_body.applyForce(Vec2{ 1, 0 } *m_speed * dt);
	}
}

void Player::jump()
{
	if (KeyUp.down() && m_isOnGround)
	{
		m_isOnGround = false;
		m_body.applyLinearImpulse(Vec2{ 0, -1 } *m_jump);
	}
}
