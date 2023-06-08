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

    bool SaveFlower;    //全ての花を摘んだならtrue
 
    int timer;

    int se_result;
    int se_result_total;

    int AnimImg;    //画面移行演出に使う画像
    int FlowerImg;  //花冠の画像
   
public:
    // コンストラクタ
    Result(int score, int time[3], bool SaveFlower);

    // デストラクタ
    ~Result();

    // 描画以外の更新を実装
    virtual AbstractScene* Update() override;

    // 描画に関することを実装
    virtual void Draw() const override;
};