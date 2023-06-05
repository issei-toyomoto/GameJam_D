/********************************
* シーンマネージャー
* 作者：島袋
********************************/
#pragma once

// デフォルトの抽象シーンクラス
// ユーザーはこれを継承してシーンを実装すると楽

class AbstractScene {
private:
	int num = 0;
	void a() {
		num = 0;
	};
public:
	// デストラクタ
	virtual ~AbstractScene() {};

	// 描画以外の更新を実装
	virtual AbstractScene* Update() = 0;

	// 描画に関することを実装
	virtual void Draw() const = 0;
};