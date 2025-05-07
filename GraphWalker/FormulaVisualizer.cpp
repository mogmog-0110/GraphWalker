#include "stdafx.h"
#include "FormulaVisualizer.hpp"

FormulaVisualizer::FormulaVisualizer(double xMin, double xMax, double step)
	: m_xMin(xMin), m_xMax(xMax), m_step(step)
{
	m_parser.setVariable(U"x", nullptr); // xを変数として設定
}

bool FormulaVisualizer::setExpression(const String& expr)
{
	Print << U"[式セット] 入力された式: " << expr; // ← ログ出力

	m_parser = MathParser();
	// 最初にダミー評価して正しいか確認（例外を避ける）
	double x = 0.0;
	m_parser.setVariable(U"x", &x);
	m_parser.setExpression(expr);

	m_expression = expr;

	return m_parser.evalOpt().has_value();
}

void FormulaVisualizer::generatePoints(const GraphArea& graph)
{
	m_points.clear();
	m_screenPoints.clear();

	double x = m_xMin;

	m_parser.setVariable(U"x", &x);

	while (x <= m_xMax)
	{
		const Optional<double> yOpt = m_parser.evalOpt();
		if (yOpt)
		{
			Vec2 logic = Vec2{ x, *yOpt };
			m_points << logic;
			m_screenPoints << graph.logicToScreen(logic);
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




