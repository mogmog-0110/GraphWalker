#include "stdafx.h"
#include "GraphArea.hpp"

GraphArea::GraphArea(const RectF& screenRect, QuadrantMode mode)
	: m_screenRect{ screenRect }, m_mode{ mode }
{
	updateLogicBounds();
}

void GraphArea::setScreenRect(const RectF& rect)
{
	m_screenRect = rect;
	updateLogicBounds();
}

void GraphArea::updateLogicBounds()
{
	m_xMin = 0, m_xMax = 10;
	m_yMin = 0, m_yMax = 10;

	switch (m_mode)
	{
	case QuadrantMode::All:
		m_xMin = -10, m_xMax = 10;
		m_yMin = -10, m_yMax = 10;
		break;
	case QuadrantMode::Q1:
		m_xMin = 0, m_xMax = 10;
		m_yMin = 0, m_yMax = 10;
		break;
	case QuadrantMode::Q1_Q2:
		m_xMin = -10, m_xMax = 10;
		m_yMin = 0, m_yMax = 10;
		break;
	case QuadrantMode::Q1_Q4:
		m_xMin = 0, m_xMax = 10;
		m_yMin = -10, m_yMax = 10;
		break;
	}

	const double logicAspect = (m_xMax - m_xMin) / (m_yMax - m_yMin);
	const double screenAspect = m_screenRect.w / m_screenRect.h;

	if (logicAspect > screenAspect)
	{
		// 横長すぎ → y を拡げる
		const double centerY = (m_yMin + m_yMax) * 0.5;
		const double halfY = (m_xMax - m_xMin) / screenAspect * 0.5;
		m_yMin = centerY - halfY;
		m_yMax = centerY + halfY;
	}
	else
	{
		// 縦長すぎ → x を拡げる
		const double centerX = (m_xMin + m_xMax) * 0.5;
		const double halfX = (m_yMax - m_yMin) * screenAspect * 0.5;
		m_xMin = centerX - halfX;
		m_xMax = centerX + halfX;
	}
}

Vec2 GraphArea::logicToScreen(const Vec2& logic) const
{
	double xRatio = (logic.x - m_xMin) / (m_xMax - m_xMin);
	double yRatio = 1.0 - (logic.y - m_yMin) / (m_yMax - m_yMin);
	return {
		m_screenRect.x + xRatio * m_screenRect.w,
		m_screenRect.y + yRatio * m_screenRect.h
	};
}

Vec2 GraphArea::screenToLogic(const Vec2& screen) const
{
	double xRatio = (screen.x - m_screenRect.x) / m_screenRect.w;
	double yRatio = (screen.y - m_screenRect.y) / m_screenRect.h;
	return {
		m_xMin + xRatio * (m_xMax - m_xMin),
		m_yMin + (1.0 - yRatio) * (m_yMax - m_yMin)
	};
}

void GraphArea::draw() const
{
	m_screenRect.draw(Assets::GraphColor);

	// マス直線
	for (int x = static_cast<int>(m_xMin); x <= static_cast<int>(m_xMax); ++x)
	{
		Line{ logicToScreen({ (double)x, m_yMin }), logicToScreen({ (double)x, m_yMax }) }
		.draw((x % 10 == 0) ? Assets::MainLine : Assets::SubLine, Palette::Lightgray);
	}
	for (int y = static_cast<int>(m_yMin); y <= static_cast<int>(m_yMax); ++y)
	{
		Line{ logicToScreen({ m_xMin, (double)y }), logicToScreen({ m_xMax, (double)y }) }
		.draw((y % 10 == 0) ? Assets::MainLine : Assets::SubLine, Palette::Lightgray);
	}

	// 軸
	Line{ logicToScreen({ m_xMin, 0.0 }), logicToScreen({ m_xMax, 0.0 }) }
	.drawArrow(Assets::MainLine, SizeF{ 10, 10 }, Assets::SubColor);
	Line{ logicToScreen({ 0.0, m_yMin }), logicToScreen({ 0.0, m_yMax }) }
	.drawArrow(Assets::MainLine, SizeF{ 10, 10 }, Assets::SubColor);

	// 原点
	if (m_xMin <= 0.0 && 0.0 <= m_xMax && m_yMin <= 0.0 && 0.0 <= m_yMax)
	{
		Circle{ logicToScreen({ 0, 0 }), 4 }.draw(Palette::Red);
	}

	// 表示文字
	FontAsset(U"SmallFont")(U"x").drawAt(logicToScreen({ m_xMax, 0.0 }) + Vec2{ -10, -15 }, Palette::Black);
	FontAsset(U"SmallFont")(U"y").drawAt(logicToScreen({ 0.0, m_yMax }) + Vec2{ 15, 10 }, Palette::Black);
}

