#pragma once

#include "AbstractScene.h"

class Result : public AbstractScene {
private:
    int state;
    int score;
public:
    // コンストラクタ
    Result(int score);

    // デストラクタ
    ~Result();

    // 描画以外の更新を実装
    virtual AbstractScene* Update() override;

    // 描画に関することを実装
    virtual void Draw() const override;
};