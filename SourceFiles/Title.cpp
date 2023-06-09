﻿/********************************
* タイトル
* 担当：島袋
********************************/
#include "main.h"

Title::Title() {
    // 初期化処理
    state = 0;
    ctrl_state = 0;

    // 画像読み込み
    if ((img_title = LoadGraph("Resources/Images/title.png")) == -1) {};

    AnimImg = LoadGraph("images/readyback.png");
    Anim = 0;
    Start = false;

    // フォント読み込み
    font[0][0] = CreateFontToHandle(NULL, 128, -1, DX_FONTTYPE_NORMAL);
    font[0][1] = CreateFontToHandle(NULL, 64, -1, DX_FONTTYPE_NORMAL);
    font[0][2] = CreateFontToHandle(NULL, 32, -1, DX_FONTTYPE_NORMAL);
    font[0][3] = CreateFontToHandle(NULL, 16, -1, DX_FONTTYPE_NORMAL);
    LPCSTR font_path = "Resources/Fonts/syokakiutage.ttf"; // 読み込むフォントファイルのパス
    if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) < 0) {
        // フォント読込エラー処理
        MessageBox(NULL, "フォント読込失敗", "", MB_OK);
    };
    font[1][0] = CreateFontToHandle("しょかきうたげ（無料版）", 128, 9, DX_FONTTYPE_EDGE);
    font[1][1] = CreateFontToHandle("しょかきうたげ（無料版）", 64, 9, DX_FONTTYPE_EDGE);
    font[1][2] = CreateFontToHandle("しょかきうたげ（無料版）", 32, 9, DX_FONTTYPE_EDGE);
    font[1][3] = CreateFontToHandle("しょかきうたげ（無料版）", 16, 9, DX_FONTTYPE_EDGE);

    // サウンド読み込み
    se_cursor = LoadSoundMem("Resources/Sounds/se_cursor.wav");
    ChangeVolumeSoundMem(130, se_cursor);

    StopSoundMem(Resources::Get(SND, BGM, 2));
};

Title::~Title() {
    // 終了処理
    img_title = 0;

    // フォント削除
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            DeleteFontToHandle(font[i][j]);
        };
    };

    // サウンド削除
    StopSoundMem(se_cursor);
    DeleteSoundMem(se_cursor);
};

AbstractScene* Title::Update() {

    /********************************
    * ゲームモードセレクト処理
    ********************************/
    if (!Start)
    {
        // キーボードのボタンが戻ったら操作受付
        if (((InputControl::TipLeftLStick(STICKL_Y) <= 0.1) && (InputControl::TipLeftLStick(STICKL_Y) >= -0.1)) && !CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN) && !CheckHitKey(KEY_INPUT_SPACE)) {
            ctrl_state = 0;
        };
        if (((InputControl::TipLeftLStick(STICKL_Y) >= 0.5) && ctrl_state == 0) || InputControl::OnButton(XINPUT_BUTTON_DPAD_UP) || (CheckHitKey(KEY_INPUT_UP) && ctrl_state == 0)) {
            // カーソル上
            PlaySoundMem(se_cursor, DX_PLAYTYPE_BACK, TRUE);
            if (state <= 0) {
                state = 4;
            }
            else {
                state -= 1;
            };
            ctrl_state = 1;
        }
        else if (((InputControl::TipLeftLStick(STICKL_Y) <= -0.5) && ctrl_state == 0) || InputControl::OnButton(XINPUT_BUTTON_DPAD_DOWN) || (CheckHitKey(KEY_INPUT_DOWN) && ctrl_state == 0)) {
            // カーソル下
            PlaySoundMem(se_cursor, DX_PLAYTYPE_BACK, TRUE);
            if (state >= 4) {
                state = 0;
            }
            else {
                state += 1;
            };
            ctrl_state = 1;
        };

        if (InputControl::OnButton(XINPUT_BUTTON_B) || InputControl::OnButton(XINPUT_BUTTON_A) || CheckHitKey(KEY_INPUT_SPACE)) {
            if (state == 0) {
                // スタート選択
                Start = true;
            }
            else if (state == 1) {
                // ヘルプ選択
                return new Help();
            }
            else if (state == 2) {
                // ランキング選択
                return new DrawRanking();
            }
            else if (state == 3) {
                //クレジット選択
                return new Credit();
            }
            else if (state == 4) {
                // 終わる選択
                return nullptr;
            };
        };
    }
    else
    {
        Anim++;
        if (30 < Anim)
        {
            return new GameMain();
        };
    }

    return this;
};

void Title::Draw() const {
    // 背景表示
    DrawGraph(0, 0, img_title, TRUE);

    // タイトル表示
    DrawStringToHandle(280, 130, GAME_NAME, 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_128], 0xffffff);
    DrawStringToHandle(300, 260, "草花スラッシュ ～勇者たけしのちょう戦～", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);

    // バージョン表示（仮）
    DrawStringToHandle(20, 690, "v6.06", 0x000000, font[FONT_TYPE_DEFAULT][FONT_SIZE_16], 0xffffff);

    // ゲームモードセレクトの項目
    DrawStringToHandle(630, 350, "スタート", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    DrawStringToHandle(630, 400, "ヘルプ", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    DrawStringToHandle(630, 450, "ランキング", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    DrawStringToHandle(630, 500, "クレジット", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    DrawStringToHandle(630, 550, "終わる", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);

    DrawStringToHandle(380, 670, "左スティックで選たく、Bボタンで決定", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);

    // ゲームモードセレクトのカーソル処理
    if (state == 0) {
        DrawStringToHandle(570, 350, "→", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    }
    else if (state == 1) {
        DrawStringToHandle(570, 400, "→", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    }
    else if (state == 2) {
        DrawStringToHandle(570, 450, "→", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    }
    else if (state == 3) {
        DrawStringToHandle(570, 500, "→", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    }
    else if (state == 4) {
        DrawStringToHandle(570, 550, "→", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    };

    // BGM 再生
    if (CheckSoundMem(Resources::Get(SND, BGM, TITLE)) == 0) {
        PlaySoundMem(Resources::Get(SND, BGM, TITLE), DX_PLAYTYPE_LOOP, TRUE);
    };

    if (Start) 
    {
        //画像フェードイン
        DrawGraph(SCREEN_WIDTH - (SCREEN_WIDTH / 30.f) * Anim, 0, AnimImg, true);
    }
};