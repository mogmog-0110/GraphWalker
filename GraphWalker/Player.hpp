﻿# pragma once
# include "Common.hpp"
# include "IGameObject.hpp"
# include "GameDataManager.hpp"

class Player : public IGameObject
{
public:
	Player() = default;
	explicit Player(P2Body body, double radius);
	void update(double dt) override;
	void draw() const override;
	void onCollision(const IGameObject& other, const Vec2& normal) override;
	P2BodyID bodyID() const override;
	ObjectType getObjectType() const override;

private:
	P2Body m_body;
	double m_radius;
	Color m_color = Palette::Green;
	//Texture texture{ U"😶"_emoji };

	// 物理プロパティ
	double m_speed = 600; // 移動スピード
	double m_jump = 5; // ジャンプ力

	bool m_isOnGround = false; // 接地中か

	void move(double dt);
	void jump();
};
