# include "Common.hpp"
# include "Asset.hpp"
# include "Title.hpp"
# include "Game.hpp"

void Main()
{
	// ウィンドウの設定
	Window::Resize(baseSize);
	Window::SetTitle(U"GraphWalker ver 0.1");

	// アセットの登録
	Assets::init();

	// シーンマネージャーの初期化
	App manager;
	//manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);

	while (System::Update())
	{
		// シーンマネージャーの更新
		if (not manager.update())
		{
			break; // シーンマネージャーが終了したらループを抜ける
		}	
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
