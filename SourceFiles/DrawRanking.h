#pragma once

#include "AbstractScene.h"
#include"DrawRanking.h"

class DrawRanking : public AbstractScene {
private:
    int font[2][4];
    int Img;	//背景画像格納用
    int BackImg;

public:
     
    DrawRanking();

    ~DrawRanking();

    // 描画以外の更新を実装
    virtual AbstractScene* Update() override;

    // 描画に関することを実装
    virtual void Draw() const override;
};