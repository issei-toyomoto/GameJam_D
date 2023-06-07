/********************************
* リザルト
* 作者：島袋
********************************/
#include "main.h"
#include "PadInput.h"

Result::Result(int score, int time[3]) {
    // 初期化処理
    state = 0;

    this->score = score;

    Stage1Time = time[0];
    Stage2Time = time[1];
    Stage3Time = time[2];

    TotalScore = 0;

    timer = 0;

    //サウンド読込
    se_result = LoadSoundMem("Resources/Sounds/se_result.wav");
    se_result_total = LoadSoundMem("Resources/Sounds/se_result_total.wav");
    ChangeVolumeSoundMem(160, se_result);
    ChangeVolumeSoundMem(160, se_result_total);

    AnimImg = LoadGraph("images/readyback.png");
};

Result::~Result() {
    // 終了処理

    // サウンド削除
    StopSoundMem(se_result);
    DeleteSoundMem(se_result);
    StopSoundMem(se_result_total);
    DeleteSoundMem(se_result_total);
};

AbstractScene* Result::Update() { // ここで値の更新など、処理

    if(timer<=230)   timer++;

    //totalscore計算
    TotalScore = score + (Stage1Time * 100) + (Stage1Time * 100) + (Stage1Time * 100);

    if (InputControl::OnButton(XINPUT_BUTTON_A)&&timer>=230)return new Title();
    
    if (InputControl::OnButton(XINPUT_BUTTON_A)) {
        timer += 230;
        if (CheckSoundMem(se_result_total) == 0) PlaySoundMem(se_result_total, DX_PLAYTYPE_BACK, TRUE);
    }
    
    if (InputControl::OnButton(XINPUT_BUTTON_B) && timer < 70 && 30 < timer) timer = 70;
    if (InputControl::OnButton(XINPUT_BUTTON_B) && timer < 110 && timer > 100) timer = 110;
    if (InputControl::OnButton(XINPUT_BUTTON_B) && timer < 150 && timer > 110) timer = 150;
    if (InputControl::OnButton(XINPUT_BUTTON_B) && timer < 190 && timer > 150) timer = 190;
    if (InputControl::OnButton(XINPUT_BUTTON_B) && timer < 230 && timer > 190) timer = 230;

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
    }else if (timer == 40) { if (CheckSoundMem(se_result) == 0) PlaySoundMem(se_result, DX_PLAYTYPE_BACK, TRUE);}

    if (timer > 80) {
        SetFontSize(40);
        DrawString(350, 330, "ステージ１", 0x0000aa);
        DrawFormatString(350, 370, 0xffffff, "%02d秒 ×  100 = %6d", Stage1Time, Stage1Time * 100);
    }else if (timer == 80) { if (CheckSoundMem(se_result) == 0) PlaySoundMem(se_result, DX_PLAYTYPE_BACK, TRUE);}

    if (timer > 120) {
        DrawString(350, 420, "ステージ2", 0x0000aa);
        DrawFormatString(350, 460, 0xffffff, "%02d秒 ×  100 = %6d", Stage2Time, Stage2Time * 100);
    }else if (timer == 120) {if (CheckSoundMem(se_result) == 0) PlaySoundMem(se_result, DX_PLAYTYPE_BACK, TRUE);}

    if (timer > 160) {
        DrawString(350, 510, "ステージ3", 0x0000aa);
        DrawFormatString(350, 550, 0xffffff, "%02d秒 ×  100 = %6d", Stage3Time, Stage3Time * 100);
    }else if (timer == 160) {if (CheckSoundMem(se_result) == 0) PlaySoundMem(se_result, DX_PLAYTYPE_BACK, TRUE);}

    SetFontSize(70);
    DrawString(400, 40, "ゲームクリア", 0xfff000);

    DrawString(310, 620, "合計スコア ", 0xff0000);

    if (timer > 200) {
        DrawFormatString(650, 620, 0xffffff, "%6d", TotalScore);
    }
    else if (timer == 200) {if (CheckSoundMem(se_result_total) == 0) PlaySoundMem(se_result_total, DX_PLAYTYPE_BACK, TRUE);}

    if (timer<30)
    {
        //画像フェードイン
        DrawGraph((SCREEN_WIDTH / 30.f) * timer, 0, AnimImg, true);
    }
};