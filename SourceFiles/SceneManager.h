/********************************
* シーンマネージャー
* 作者：島袋
********************************/
#pragma once

#include "AbstractScene.h"

// シーンマネージャークラス
// 各シーンの切り替えを管理。

class SceneManager : public AbstractScene {
private:
	AbstractScene* mScene; // 現在のシーン
public:
	// コンストラクタ
	SceneManager(AbstractScene* scene) : mScene(scene) {}

	// デストラクタ
	~SceneManager() {
		delete mScene;
	};

	// 描画以外の更新を実装
	AbstractScene* Update() override;

	// 描画に関することを実装
	void Draw() const override;
};