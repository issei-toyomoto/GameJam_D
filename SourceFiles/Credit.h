#pragma once
#include "AbstractScene.h"

class Credit : public AbstractScene
{
private:
    int g_KeyFlg; //同じ入力キーか
    int g_OldKey; //前回の入力
    int g_NowKey; //今回の入力キー
    int img_title;
public:
    // コンストラクタ
    Credit();

    // デストラクタ
    ~Credit();

    // 描画以外の更新を実装
    virtual AbstractScene* Update() override;

    // 描画に関することを実装
    virtual void Draw() const override;

};

