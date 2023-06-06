#include "common.h"
#include "main.h"
#include "Result.h"
#include "PadInput.h"

#define DEBUG

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

   #ifdef DEBUG
    int margin = (SCREEN_HEIGHT - 100) % BLOCK_SIZE / 2;
    for (int i = 100 + margin; i < 720; i += BLOCK_SIZE)
    {
        DrawLine(margin, i, 1280 - margin, i, 0xffffff);
        if ((i - 100) / BLOCK_SIZE % 5 == 0)DrawLine(margin, i, 1280 - margin, i, 0xff0000);
    }

    margin = SCREEN_WIDTH % BLOCK_SIZE / 2;
    for (int i = margin; i < 1280; i += BLOCK_SIZE)
    {
        DrawLine(i, 100 + margin, i, 720 - margin, 0xffffff);
        if (i / BLOCK_SIZE % 5 == 0)DrawLine(i, 100 + margin, i, 720 - margin, 0xff0000);
    }
#endif

    DrawFormatString(20, 120, 0xffffff, "Game Main");
    DrawFormatString(1130, 10, 0xffffff, "SCORE : %d", score);
};