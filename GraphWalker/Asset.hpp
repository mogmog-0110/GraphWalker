# pragma once
# include "Common.hpp"

namespace Assets
{
	// 初期化
	void init();

	// 定数(inlineを付けてコンパイル時に展開可能にする)
	// 繰り返し使うものはここで定義。

	inline constexpr int32 MainLine = 5;
	inline constexpr int32 SubLine = 2;

	inline constexpr Color ThemeColor = Palette::Skyblue;
	inline constexpr Color SubColor = Palette::Gray;
	inline constexpr Color GraphColor = Palette::White;
}
