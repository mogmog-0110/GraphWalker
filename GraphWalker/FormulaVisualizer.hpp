# pragma once
# include "Common.hpp"
# include "GraphArea.hpp"

class FormulaVisualizer
{
public:
	// 数式の表示範囲、ステップ幅の初期化
	FormulaVisualizer(double xMin = -10, double xMax = 10, double step = 0.1);
	bool setExpression(const String& expr);
	void generatePoints(const GraphArea& graph);
	void draw(const ColorF& color = Palette::Red) const;

private:
	MathParser m_parser;
	String m_expression;
	Array<Vec2> m_screenPoints;
	Array<Vec2> m_points;

	double m_xMin;
	double m_xMax;
	double m_step;
};
