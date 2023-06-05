/********************************
* タイトル
* 作者：島袋
********************************/
#include "main.h"
#include "PadInput.h"
#include "GameMainScene.h"

Title::Title() {
    // 初期化処理
    state = 0;
};

Title::~Title() {
    // 終了処理
};

AbstractScene* Title::Update() { // ここで値の更新など、処理

    if (PAD_INPUT::OnClick(XINPUT_BUTTON_A))return new GameMain();
    if (PAD_INPUT::OnClick(XINPUT_BUTTON_B))return nullptr;

    return this; // シーン継続
};

void Title::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);

    DrawFormatString(20, 50, 0xffffff, GAME_NAME);

    DrawFormatString(20, 95, 0xffffff, "ゲームスタート：Aボタン");
    DrawFormatString(20, 110, 0xffffff, "ゲーム終了：Bボタン");
};