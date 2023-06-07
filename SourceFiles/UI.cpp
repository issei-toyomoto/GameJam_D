﻿#include "DxLib.h"
#include "UI.h"

//int UI::score;
//int UI::time;
//int UI::stage;
//int UI::Timelimit = 60;
//int UI::FPSCnt;
UI::UI() {
    score = 0;
    Timelimit = 61;
    FPSCnt = 0;
}

UI::~UI() {
}

int UI::Update() //キー入力情報更新
{
    if ((FPSCnt++) % 60 == 0) {
        Timelimit = Timelimit - 1;
    }
    if (Timelimit <= 0) {
        return -1;
    }
}

void UI::Draw() const{ // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(60);

    DrawFormatString(10, 15, 0xffffff, "Stage ");
    SetFontSize(40);
    DrawFormatString(600, 10, 0xffffff, "Time\n %2d",Timelimit);
    SetFontSize(50);
    DrawFormatString(800, 25, 0xffffff, "SCORE : %d", score);
};