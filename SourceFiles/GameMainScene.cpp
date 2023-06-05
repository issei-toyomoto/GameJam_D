
/********************************
* ゲームメイン
* 作者：島袋
********************************/
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
    if (PAD_INPUT::OnClick(XINPUT_BUTTON_A))return new Result(score);

    return this; // シーン継続
};

void GameMain::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);
    DrawGraph(0, 0, BackImg, true);

    DrawFormatString(20, 50, 0xffffff, "Game Main");
    DrawFormatString(20, 100, 0xffffff, "SCORE : %d", score);
};