#pragma once
#include "Common.hpp"
#include "Asset.hpp"

class GraphArea
{
public:
	GraphArea(const RectF& fullArea, QuadrantMode mode = QuadrantMode::All);

	void setScreenRect(const RectF& rect);
	void updateLogicBounds();

	Vec2 logicToScreen(const Vec2& logic) const;
	Vec2 screenToLogic(const Vec2& screen) const;

	void draw() const;

private:
	RectF m_screenRect;
	QuadrantMode m_mode;
	double m_xMin = -10, m_xMax = 10;
	double m_yMin = -10, m_yMax = 10;

};
