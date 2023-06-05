#include "main.h"
#include "Result.h"
#include "PadInput.h"

GameMain::GameMain() {
    // 初期化処理
    state = 0;

    BackImg = LoadGraph("images/back.png");
};

GameMain::~GameMain() {
    // 終了処理
};

AbstractScene* GameMain::Update() { // ここで値の更新など、処理
    if (InputControl::PressBotton(XINPUT_BUTTON_START))return new Result(score);

    return this;    //シーン継続
};

void GameMain::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);
    DrawGraph(0, 0, BackImg, true);
    DrawBox(0, 0, 1280, 100, GetColor(0, 0, 0), TRUE);
    DrawFormatString(20, 120, 0xffffff, "Game Main");
    DrawFormatString(1130, 10, 0xffffff, "SCORE : %d", score);
};