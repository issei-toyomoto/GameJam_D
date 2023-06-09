#pragma once

#include "AbstractScene.h"

#define FONT_TYPE_DEFAULT 0
#define FONT_TYPE_LOAD_1 1

#define FONT_SIZE_128 0
#define FONT_SIZE_64 1
#define FONT_SIZE_32 2
#define FONT_SIZE_16 3

class Help : public AbstractScene {
private:
    int state = 0;
    int ctrl_state;
    int img_title, img_ctrl, img_help[7];
    int font[2][4];
    int bgm, se_cursor, se_select;

    int AnimImg;    //画面移行演出に使う画像
    int Anim;       //画面移行演出管理
    bool Start;     //ゲームメインに移行するならtrue
public:
    // コンストラクタ
    Help();

    // デストラクタ
    ~Help();

	// 描画以外の更新を実装
	virtual AbstractScene* Update() override;

	// 描画に関することを実装
	virtual void Draw() const override;
};