﻿/********************************
* リザルト
* 作者：島袋
********************************/
#include "main.h"
#include "PadInput.h"

Result::Result(int score) {
    // 初期化処理
    state = 0;

    this->score = score;
};

Result::~Result() {
    // 終了処理
};

AbstractScene* Result::Update() { // ここで値の更新など、処理
    if (InputControl::OnButton(XINPUT_BUTTON_A))return new Title();
    return this; // シーン継続
};

void Result::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);

    DrawFormatString(20, 50, 0xffffff, "Result");
    DrawFormatString(20, 100, 0xffffff, "SCORE : %d", score);
};