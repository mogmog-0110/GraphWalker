#pragma once
#include "Common.hpp"
#include "GameDataManager.hpp"
#include "Game.hpp"

class Title : public App::Scene
{
public:
	Title(const InitData& init);

	void update() override;
	void draw() const override;

private:
	int32 m_selectedStage = 0;

};
