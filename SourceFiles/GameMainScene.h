#pragma once

#include "AbstractScene.h"

class GameMain : public AbstractScene {
private:
    int state;
    int score = 0;

    int BackImg;    //背景画像

public:
    // コンストラクタ
    GameMain();

    // デストラクタ
    ~GameMain();

	// 描画以外の更新を実装
	virtual AbstractScene* Update() override;

	// 描画に関することを実装
	virtual void Draw() const override;
};