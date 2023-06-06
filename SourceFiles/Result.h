#pragma once

#include "AbstractScene.h"

class Result : public AbstractScene {
private:
    int state;
    int score;

    int FlowerImg;
    int GrassImg;

    int Stage1Time;
    int Stage2Time;
    int Stage3Time;

    int TotalScore;

    int timer;
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