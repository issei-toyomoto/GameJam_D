/********************************
* タイトル
* 作者：島袋
********************************/
#include "main.h"

Title::Title() {
    // 初期化処理
    state = 0;
};

Title::~Title() {
    // 終了処理
};

AbstractScene* Title::Update() { // ここで値の更新など、処理

    return this; // シーン継続
};

void Title::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);

    DrawFormatString(20, 50, 0xffffff, GAME_NAME);

    DrawFormatString(20, 95, 0xffffff, "ゲームスタート：Spaceキー");
    DrawFormatString(20, 110, 0xffffff, "ゲーム終了：Escキー");
};