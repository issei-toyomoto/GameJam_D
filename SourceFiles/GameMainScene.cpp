/********************************
* ゲームメイン
********************************/
#include "main.h"

GameMain::GameMain() {
    // 初期化処理
    state = 0;
};

GameMain::~GameMain() {
    // 終了処理
};

AbstractScene* GameMain::Update() { // ここで値の更新など、処理

    return this; // シーン継続
};

void GameMain::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);

    DrawFormatString(20, 50, 0xffffff, "Game Main");
};