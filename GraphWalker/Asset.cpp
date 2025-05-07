#include "stdafx.h"
#include "Asset.hpp"

void Assets::init()
{
	// フォントの登録
	FontAsset::Register(U"SmallFont", 24);
	FontAsset::Register(U"MidiumFont", 48);
	FontAsset::Register(U"BigFont", 64);
	FontAsset::Register(U"TitleFont", 128);
}
