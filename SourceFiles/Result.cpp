/********************************
* リザルト
* 作者：島袋
********************************/
#include "main.h"
#include "PadInput.h"

Result::Result(int score) {
    // 初期化処理
    state = 0;

    this->score = score;

    Stage1Time = 0;
    Stage2Time = 0;
    Stage3Time = 0;

    TotalScore = 0;

    timer = 0;
};

Result::~Result() {
    // 終了処理
};

AbstractScene* Result::Update() { // ここで値の更新など、処理

    if(timer<=200)   timer++;

    //totalscore計算
    TotalScore = score + (Stage1Time * 100) + (Stage1Time * 100) + (Stage1Time * 100);

    if (InputControl::OnButton(XINPUT_BUTTON_A)&&timer>=200)return new Title();
    
    if (InputControl::OnButton(XINPUT_BUTTON_A)) timer += 200;
    
    if (InputControl::OnButton(XINPUT_BUTTON_B) && timer < 40 ) timer = 40;
    if (InputControl::OnButton(XINPUT_BUTTON_B) && timer < 80 && timer > 40) timer = 80;
    if (InputControl::OnButton(XINPUT_BUTTON_B) && timer < 120 && timer > 80) timer = 120;
    if (InputControl::OnButton(XINPUT_BUTTON_B) && timer < 160 && timer > 120) timer = 160;
    if (InputControl::OnButton(XINPUT_BUTTON_B) && timer < 200 && timer > 160) timer = 200;

    return this; // シーン継続
};

void Result::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);

    DrawFormatString(20, 50, 0xffffff, "Result");
    DrawFormatString(20, 100, 0xffffff, "SCORE : %d", score);

    DrawBox(215, 10, 1065, 710, 0xae804f, TRUE);

    SetFontSize(50);
    DrawString(230, 270, "タイムスコア(残りタイム×100)", 0xaa0000);

    DrawString(350, 150, "スコア", 0xff0000);
    
    if (timer > 40) {
        DrawFormatString(650, 150, 0xffffff, "%6d", score);
    }

    if (timer > 80) {
        SetFontSize(40);
        DrawString(350, 330, "ステージ１", 0x0000aa);
        DrawFormatString(350, 370, 0xffffff, "%02d秒 ×  100 = %6d", Stage1Time, Stage1Time * 100);
    }

    if (timer > 120) {
        DrawString(350, 420, "ステージ2", 0x0000aa);
        DrawFormatString(350, 460, 0xffffff, "%02d秒 ×  100 = %6d", Stage2Time, Stage2Time * 100);
    }

    if (timer > 160) {
        DrawString(350, 510, "ステージ3", 0x0000aa);
        DrawFormatString(350, 550, 0xffffff, "%02d秒 ×  100 = %6d", Stage3Time, Stage3Time * 100);
    }

    SetFontSize(70);
    DrawString(400, 40, "ゲームクリア", 0xfff000);

    DrawString(310, 620, "合計スコア ", 0xff0000);

    if (timer > 200) {
        DrawFormatString(650, 620, 0xffffff, "%6d", score);
    }
};