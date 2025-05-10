#include "stdafx.h"
#include "FormulaVisualizer.hpp"

FormulaVisualizer::FormulaVisualizer(double xMin, double xMax, double step)
	: m_xMin(xMin), m_xMax(xMax), m_step(step)
{
	m_parser.setVariable(U"x", nullptr); // xを変数として設定
}

bool FormulaVisualizer::setExpression(const String& expr)
{
	m_parser = MathParser();
	// 最初にダミー評価して正しいか確認（例外を避ける）
	double x = 0.0;
	m_parser.setVariable(U"x", &x);
	m_parser.setExpression(expr);

	m_expression = expr;

	return m_parser.evalOpt().has_value();
}

Array<Vec2> FormulaVisualizer::getPoints() const
{
	return m_screenPoints;
}

void FormulaVisualizer::clearPoints()
{
	m_points.clear();
	m_screenPoints.clear();
	m_expression.clear();
	m_parser.setExpression(U""); // 数式をクリア
	m_parser.setVariable(U"x", nullptr); // xのポインタをクリア
}

void FormulaVisualizer::generatePoints(const GraphArea& graph)
{
	m_points.clear();
	m_screenPoints.clear();

	double x = m_xMin;
	m_parser.setVariable(U"x", &x);

	const double minDistanceSq = 0.0064;
	Optional<Vec2> prev = none;

	while (x <= m_xMax)
	{
		const Optional<double> yOpt = m_parser.evalOpt();
		if (yOpt && std::isfinite(*yOpt)) // NaN や inf を除外
		{
			Vec2 logic = Vec2{ x, *yOpt };
			Vec2 screen = graph.logicToScreen(logic);

			m_screenPoints << screen;

			if (not prev || (logic - *prev).lengthSq() >= minDistanceSq)
			{
				m_points << logic;
				prev = logic;
			}
		}
		x += m_step;
	}
}



void FormulaVisualizer::draw(const ColorF& color) const
{
	if (m_points.size() < 2) return;

	for (size_t i = 1; i < m_screenPoints.size(); ++i)
	{
		Line{ m_screenPoints[i - 1], m_screenPoints[i] }.draw(LineStyle::SquareDot, 1.5, color);
	}
}




