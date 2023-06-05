/********************************
* リザルト
* 作者：島袋
********************************/
#include "Result.h"
#include "TitleScene.h"
#include "PadInput.h"

Result::Result() {
    // 初期化処理
    state = 0;
};

Result::~Result() {
    // 終了処理
};

AbstractScene* Result::Update() { // ここで値の更新など、処理
    if (PAD_INPUT::OnClick(XINPUT_BUTTON_A))return new Title();
    return this; // シーン継続
};

void Result::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);

    DrawFormatString(20, 50, 0xffffff, "Result");
};