#pragma once

#include "AbstractScene.h"

class Result : public AbstractScene {
private:
    int state;
    int score;

    int Stage1Time;
    int Stage2Time;
    int Stage3Time;

    int TotalScore;
 
    int timer;

    int se_result;
    int se_result_total;

   
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